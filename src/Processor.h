//
//  Source.h
//  fantasybit
//
//  Created by Jay Berg on 8/24/14.
//
//

#ifndef __fantasybit__Processor__
#define __fantasybit__Processor__

#include "Commissioner.h"
#include "ProtoData.pb.h"
#include <fc/crypto/sha256.hpp>
#include <fc/crypto/elliptic.hpp>
#include <algorithm>
#include <iostream>
#include "fbutils.h";
#include "Source.h"
#include <leveldb/db.h>

namespace fantasybit
{

	//using namespace leveldb;

//using comish = fantasybit::Commissioner;
using ldbP = std::unique_ptr < leveldb::DB > ;
class BlockRecorder 
{
	leveldb::DB *blockstatus;
	leveldb::DB *namehashpup;
	leveldb::DB *pubfantasyname;
	leveldb::DB *pubbalance;
	leveldb::DB *gamesids;
	leveldb::DB *projections;
	leveldb::WriteOptions write_sync{};

	std::map<Uid, leveldb::DB*> game_projections_db{};
public:
	BlockRecorder() {}

	void init()
	{
		write_sync.sync = true;
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::Status status;
		status = leveldb::DB::Open(options, filedir("blockstatus"), &blockstatus);
		status = leveldb::DB::Open(options, filedir("namehashpup"), &namehashpup);
		status = leveldb::DB::Open(options, filedir("pubfantasyname"), &pubfantasyname);
		status = leveldb::DB::Open(options, filedir("pubbalance"), &pubbalance);
		status = leveldb::DB::Open(options, filedir("gameids"), &gamesids);
		//status = leveldb::DB::Open(options, filedir("projections"), &pubbalance);
		//status = leveldb::DB::Open(options, filedir("last-projections"), &pubbalance);
		leveldb::Iterator* it = gamesids->NewIterator(leveldb::ReadOptions());
		for (it->SeekToFirst(); it->Valid(); it->Next())
		{
			leveldb::DB* db;
			Uid id = it->key().ToString();
			if (leveldb::DB::Open(options, filedir("gameids/")+id, &db).ok())
			{
				game_projections_db[id] = db;
			}
		}
	}

	void startBlock(int num) 
	{
		int lock = -1;
		leveldb::Slice value((char*)&num, sizeof(int));
		blockstatus->Put(write_sync, "processing", value);
	}

	void endBlock()
	{
		int none = -1;
		leveldb::Slice value((char*)&none, sizeof(int));
		blockstatus->Put(write_sync, "processing", value);
	}

	bool inSync()
	{
		std::string value;
		blockstatus->Get(leveldb::ReadOptions(), "processing", &value);
		int num = *(reinterpret_cast<const int *>(value.c_str()));
		return num < 0;
	}

	void recordName(const hash_t &hash,const std::string &pubkey,const std::string &name)
	{
		leveldb::Slice hkey((char*)&hash, sizeof(hash_t));
		namehashpup->Put(leveldb::WriteOptions(), hkey, pubkey);
		pubfantasyname->Put(leveldb::WriteOptions(), pubkey, name);

		std::string temp;
		if (pubbalance->Get(leveldb::ReadOptions(), pubkey, &temp).IsNotFound())
		{
			uint64_t bal = 0;
			leveldb::Slice bval((char*)&bal, sizeof(uint64_t));
			pubbalance->Put(leveldb::WriteOptions(), pubkey, bval);
		}
	}

	void addProjection(Uid &game, Uid &player, std::string &fname, int16_t points)
	{
		std::string temp;
		//if (pubbalance->Get(leveldb::ReadOptions(), pubkey, &temp).IsNotFound())
		leveldb::Slice pval((char*)&points, sizeof(int16_t));

		auto iter = game_projections_db.find(game);
		if (iter != end(game_projections_db))
		{
			iter->second->Put(leveldb::WriteOptions(), player.append(":").append(fname), pval);
		}
	}

	void removeGameId(Uid &game)
	{
		auto iter = game_projections_db.find(game);
		if (iter != end(game_projections_db))
		{
			delete iter->second;
			leveldb::DestroyDB(filedir(iter->first),leveldb::Options());
			gamesids->Delete(leveldb::WriteOptions(), game);
		}
	}

	void addGameId(Uid &game)
	{
		gamesids->Put(leveldb::WriteOptions(), game, game);
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::DB* db;
		if (leveldb::DB::Open(options, filedir(game), &db).ok())
			game_projections_db[game] = db;
	}

	void addBalance(std::string &pubkey,uint64_t add)
	{
		uint64_t newval = 0;
		std::string temp;

		if (pubbalance->Get(leveldb::ReadOptions(), pubkey, &temp).ok())
		{
			newval = *(reinterpret_cast<uint64_t *>(&temp));
		}

		add += newval;
		leveldb::Slice bval((char*)&add, sizeof(uint64_t));
		pubbalance->Put(leveldb::WriteOptions(), pubkey, bval);

	}

	std::string filedir(const std::string &in)
	{
		return ROOT_DIR + "index/" + in;
	}
};

class BlockProcessor
{
	BlockRecorder mRecorder{};
	bool verify_name(const SignedTransaction &, const NameTrans &, const fc::ecc::signature&, const fc::sha256 &);
public:
	BlockProcessor() {
		//mRecorder.init();
	}
		
	void init() 
	{
		mRecorder.init();
		if (!mRecorder.inSync());
	}


	bool process(SignedBlock &sblock)
	{
		if (sblock.version() != Commissioner::BLOCK_VERSION ) 
			return fbutils::LogFalse(std::string("Processor::process wrong block version ").append(sblock.DebugString()));

		fc::sha256 digest = fc::sha256::hash(sblock.block().SerializeAsString() );
		if (digest.str() != sblock.id())
			return 
			fbutils::LogFalse(std::string("Processor::process block hash error digest \n").append(sblock.DebugString()).append(digest.str()));
		assert(digest.str() == sblock.id());

		fc::ecc::signature sig = Commissioner::str2sig(sblock.sig());
		//assert(Commissioner::verifyOracle(sig, digest));
		if (!Commissioner::verifyOracle(sig, digest))
#ifdef NO_ORACLE_CHECK_TESTING
			if (!Commissioner::GENESIS_NUM == sblock.block().head().num())
#endif
			return fbutils::LogFalse(std::string("Processor::process only oracle can sign blocks!! ").append(sblock.DebugString()));

		mRecorder.startBlock(sblock.block().head().num());
		for (const auto &st : sblock.block().signed_transactions())
		{
			Transaction t{ st.trans() };

			fc::sha256 digest = fc::sha256::hash(t.SerializeAsString());
			if (digest.str() != st.id()) {
				fbutils::LogFalse(std::string("Processor::process signed transaction hash error digest ").append(st.DebugString()));
				continue;
			}

			if (t.version() != Commissioner::TRANS_VERSION) {
				fbutils::LogFalse(std::string("Processor::process wrong transaction version ").append(st.DebugString()));
				continue;
			}

			fc::ecc::signature sig = Commissioner::str2sig(st.sig());

			if (t.type() == TransType::NAME)
			{
				auto nt = t.GetExtension(NameTrans::name_trans);
				if (verify_name(st, nt, sig, digest))
				{
					mRecorder.recordName(FantasyName::name_hash(nt.fantasy_name()), nt.public_key(), nt.fantasy_name());
					auto pfn = Commissioner::makeName(nt.fantasy_name(), nt.public_key());
					Commissioner::Aliases.emplace(pfn->hash(), pfn->pubkey);
					Commissioner::FantasyNames.emplace(pfn->pubkey, pfn);
				}

				continue;
			}

			if (!Commissioner::verifyByName(sig, digest, st.fantasy_name()))
			{
				fbutils::LogFalse(std::string("Processor::process cant verify trans sig").append(st.DebugString()));
				continue;
			}

			switch (t.type())
			{
				case TransType::PROJECTION:
				{
					auto pt = t.GetExtension(ProjectionTrans::proj_trans);
					auto iter = Source::EventProjectionResult.find(pt.game_id());
					if (iter != end(Source::EventProjectionResult))
					{
						auto pp = pt.fpp_projection();
						iter->second.addProjection(st.fantasy_name(), pp.fantasy_player_id(), pp.points());
					}
					break;
				}
				case TransType::RESULT:
				{
					auto rt = t.GetExtension(ResultTrans::result_trans);
					//auto iter = Source::EventProjectionResult.find(rt.game_id());
					//if (iter == end(Source::EventProjectionResult)) {
					//}

					auto iter = Source::EventProjectionResult.emplace(make_pair(rt.game_id(), rt.game_id()));
					iter.first->second.setDataAgent(st.fantasy_name());
					//auto &source = Source::EventProjectionResult[rt.game_id()];
					for (const auto &fpp : rt.fpp_results())
					{
						iter.first->second.addResult(fpp.fantasy_player_id(), fpp.points());
						//auto pp = pt.fpp_projection();
						//iter->second.addProjection(st.fantasy_name(), pp.fantasy_player_id(), pp.points());
					}
					break;
				}
				default:
					break;
			}
		}

		std::cout << " BLOCK(" << sblock.block().head().num() << ") processed! \n";
		mRecorder.endBlock();
		//sblock.block().head().num());
		return true;
			//std::cout << t.DebugString() << "\n";//process(t)
		//mRecorder.comitBlock(block);	
	}

};

}


#endif
