//
//  FanatsyAgent.cpp
//  fantasybit
//
//  Created by Jay Berg on 4/6/14.
//
//

#include "FantasyAgent.h"
#include "Processor.h"
#include <iostream>
#include "PeerNode.h"
#include "Commissioner.h"
#include <utility>
#include "DataPersist.h"
#include <fc/optional.hpp>
#include "FantasyName.h"



using namespace std;


namespace fantasybit {

FantasyAgent::FantasyAgent() : client{nullptr} {
    Reader<Secret2> read{ GET_ROOT_DIR() +  secretfilename};
    if ( !read.good() )
        return;

    Secret2 secret{};
    while (read.ReadNext(secret)) {
        m_secrets.push_back(secret);
        qInfo() << secret.fantasy_name() << " have key";
        if ( AmFantasyAgent(secret.public_key())) {
            m_oracle = str2priv(secret.private_key());
            qInfo() << " is oracle key";
        }
    }
}

std::multimap<std::string,std::string> FantasyAgent::getMyNames() {
    std::multimap<std::string,std::string> ret;
    for ( auto s2 : m_secrets ) {
        ret.emplace(s2.fantasy_name(),s2.public_key());
    }

    return ret;
}

std::map<string,MyFantasyName> FantasyAgent::getMyNamesStatus() {
    std::map<string,MyFantasyName> ret{};
    for ( auto s2 : m_secrets ) {
        MyFantasyName fn{};
        fn.set_name(s2.fantasy_name());
        auto fname = Commissioner::getName(Commissioner::str2pk(s2.public_key()));
        if ( fname == nullptr ) {
            if ( Commissioner::isAliasAvailable(s2.fantasy_name()))
                fn.set_status(MyNameStatus::requested);
            else
                fn.set_status(MyNameStatus::notavil);
        }
        else if ( fname->alias() == s2.fantasy_name() )
            fn.set_status(MyNameStatus::confirmed);
        else if ( FantasyName::name_hash(s2.fantasy_name()) == fname->hash() ) {
            fn.set_status(MyNameStatus::confirmed);
            fn.set_name(fname->alias());
        }
        else
            fn.set_status(MyNameStatus::none);

        auto s = ret.find(fn.name());
        if ( s != end(ret) ) {
            if ( s->second.status() >= fn.status() )
                continue;
        }

        ret[fn.name()] = fn;
    }

    return ret;
}

void FantasyAgent::onSignedTransaction(SignedTransaction &sn)
{
    pendingTrans.emplace_back(sn);
    qDebug() << sn.DebugString();
}

bool FantasyAgent::HaveClient() {
    return client != nullptr;
}

bool FantasyAgent::amDataAgent() {
    //Todo: fix
    if (m_oracle && m_priv)
        return (*m_oracle).get_secret() == (*m_priv).get_secret();
    else
        return false;
}

bool FantasyAgent::AmFantasyAgent(fc::ecc::public_key_data pubkey) {
    return Commissioner::GENESIS_PUB_KEY == pubkey;
}

bool FantasyAgent::AmFantasyAgent(std::string pubkey) {
    return Commissioner::GENESIS_PUB_KEY == Commissioner::str2pk(pubkey);
}

SignedTransaction FantasyAgent::makeSigned(Transaction &trans)
{
    SignedTransaction st{};
    st.mutable_trans()->CopyFrom(trans);
    auto p = getIdSig(trans.SerializeAsString());
    st.set_id(p.first);
    st.set_sig(p.second);
    st.set_fantasy_name(client->alias());
    return st;
}


std::string FantasyAgent::getSecret() const {
    return m_priv ? (*m_priv).get_secret().str() : "";
}

fc::ecc::public_key_data FantasyAgent::pubKey() {
    return (*m_priv).get_public_key();
}

std::string FantasyAgent::pubKeyStr() {
    return m_priv ?
                Commissioner::pk2str((*m_priv).get_public_key().serialize())
              : "";
}


std::pair<std::string, std::string> FantasyAgent::getIdSig(std::string &in) {
    return m_priv ? getIdSig(in, *m_priv)
                   :  std::make_pair("","");
}


std::pair<std::string, std::string>
FantasyAgent::getIdSig(std::string &in, fc::ecc::private_key &pk) {
    fc::sha256 sha = fc::sha256::hash( in );
    return make_pair(sha.str(), Commissioner::sig2str(pk.sign(sha)));
}

fc::ecc::private_key FantasyAgent::str2priv(const std::string &in) {
    return fc::ecc::private_key::regenerate(fc::sha256{ in });
}



FantasyAgent::status FantasyAgent::signPlayer(std::string name) {
    status ret = NOTAVAILABLE;
   
    if ( Commissioner::isAliasAvailable(name) ) {
		for (auto fn : m_secrets) {
			if (fn.fantasy_name() == name) {
				m_priv = fc::ecc::private_key::generate();
				client = std::make_unique<FantasyName>(name, (*m_priv).get_public_key().serialize());
				ret = AVAIL;
                //LOG(lg, info) << "name available, already have it in secret file " << name;
                qInfo() <<"name available, already have it in secret file " << name;
			}
		}

		if (ret != AVAIL) {
			m_priv = fc::ecc::private_key::generate();
			client = std::make_unique<FantasyName>(name, (*m_priv).get_public_key().serialize());

			Writer<Secret> writer{ GET_ROOT_DIR() + secretfilename, ios::app };
			Secret2 secret{};
			secret.set_private_key(getSecret());
			secret.set_public_key(pubKeyStr());
			secret.set_fantasy_name(name);
			writer(secret);
            //LOG(lg, info) << "name available saving secret to file " << name;
            qInfo() << "name available saving secret to file " << name;
		}

    }
    //lets see if I already have the keys for this name
    else for ( auto fn : m_secrets) {
        if ( FantasyName::name_hash(fn.fantasy_name()) == FantasyName::name_hash(name)) {
            if ( auto p = Commissioner::getName(name) ) {
                if ( p->pubkey() == Commissioner::str2pk(fn.public_key()) ) {
                    ret = OWNED;
                    m_priv = str2priv(fn.private_key());
                    client = std::make_unique<FantasyName>(*p);
                    if ( AmFantasyAgent(p->pubkey()))
                        m_oracle = m_priv;
                    //LOG(lg, info) << "I already own it " << name;
                    qInfo()<< "I already own it " << name;
                }
                else {
                    qInfo() << "I have wrong pub" << name;
                    //LOG(lg, warning) << "I have wrong pub" << name;
                }

            }
            else {
                //LOG(lg, warning) << "Cant find name?" << name;
                qInfo() << "Cant find name?" << name;
            }
        }
    }

    if ( ret == NOTAVAILABLE )
        qInfo() << "name not avaiable" << name;

    return ret;
}


//static SignedBlock makeGenesisBlock() {
/*
bool FantasyAgent::makeGenesis()
{
	LOG(lg, trace) << "genesis ";

	Block sb = Commissioner::makeGenesisBlock();

	BlockProcessor bp{};
	bp.init();
	bp.process(sb);
	return true;
}
*/

bool FantasyAgent::beDataAgent() {
#ifdef NO_ORACLE_CHECK_TESTING	
    qInfo() << " no oracle test";

    if ( !m_priv )
        m_priv = fc::ecc::private_key::generate();

    if ( !HaveClient() )
        client = std::make_unique<FantasyName>
                ("NO_ORACLE_CHECK_TESTING",m_priv.get_public_key().serialize());

	m_oracle = m_priv;
    Commissioner::GENESIS_PUB_KEY = m_oracle.get_public_key();
	return true;
#endif	

    bool ret = false;

    if (AmFantasyAgent(pubKey())) {
        qInfo() << " is oracle key";
		m_oracle = m_priv;
        ret = true;
    }
    else for ( auto fn : m_secrets) {
        if ( AmFantasyAgent(fn.public_key())) {
            qInfo() << " found agent key";
            m_priv = str2priv(fn.private_key());
            m_oracle = m_priv;
            client = std::make_unique<FantasyName>
                    (Commissioner::FantasyAgentName(),(*m_priv).get_public_key());
            ret = true;
            break;
        }
    }

    if (!ret) {
        Secret2 oracle{};
        Reader<Secret2> read{ GET_ROOT_DIR() + "oracle.txt" };
        if (!read.good())
            qWarning() << " no oracle.txt";
        else if (read.ReadNext(oracle)) {
            if (AmFantasyAgent(oracle.public_key())) {
                qInfo() << " have oracle.txt";
                m_priv = str2priv(oracle.private_key());
                m_oracle = m_priv;
                client = std::make_unique<FantasyName>
                        (Commissioner::FantasyAgentName(),(*m_priv).get_public_key());
                ret = true;
            }
            else
                qWarning() << "oracle is NOT Commissioner::GENESIS_PUB_KEY";
		}
        else
            qCritical() << " bad read oracle.txt";
	}

    return ret;
}


Block FantasyAgent::makeNewBlockAsDataAgent(const SignedTransaction &dt) {
	Block b{};
	
	if (!amDataAgent()) {
        qWarning() << "am not DataAgent - try tp beDataAgent";

		if (!beDataAgent()) {
            qCritical() << "cant makeNewBlockAsDataAgent am not agent";
			return b;
		}
	}
    qInfo() << "I am DataAgent";

    auto prev = Node::getlastLocalBlock().signedhead().head();

	BlockHeader bh{};
	bh.set_version(Commissioner::BLOCK_VERSION);
	bh.set_num(prev.num() + 1);
	bh.set_prev_id(fc::sha256::hash(prev.SerializeAsString()).str());
	bh.set_timestamp( std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	//todo: t
	bh.set_generator_pk(pubKeyStr());
	bh.set_generating_sig(fc::sha256::hash(prev.generating_sig() + bh.generator_pk()).str());
	bh.set_basetarget(0); //todo
	bh.set_blocktype(BlockHeader_Type_DATA);
	bh.set_transaction_id(""); //todo: merkle root of tx 

	SignedBlockHeader sbh{};
	sbh.mutable_head()->CopyFrom(bh);

    auto p = getIdSig(sbh.head().SerializeAsString(),*m_oracle);
	sbh.set_sig(p.second);
	//todo: store block hash from p.first 

	b.mutable_signedhead()->CopyFrom(sbh);

	SignedTransaction st{};
	SignedTransaction* st2 = b.add_signed_transactions();
	st2->CopyFrom(dt);


	leveldb::ReadOptions options;
	options.snapshot = Node::txpool->GetSnapshot();
	leveldb::Iterator *iter = Node::txpool->NewIterator(options);

	for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
		
		st.ParseFromString(iter->value().ToString());

		SignedTransaction* st2 = b.add_signed_transactions();
		st2->CopyFrom(st);
	}

	/*
	if (pendingTrans.size() == 0)
		return b;

	for (auto &pt : pendingTrans)
	{
		SignedTransaction* st2 = b.add_signed_transactions();
		st2->CopyFrom(pt);
	}

	pendingTrans.clear();
	*/
	delete iter;
	Node::txpool->ReleaseSnapshot(options.snapshot);


	//sb.set_id(p.first);	
	//BlockProcessor bp{};
	//bp.init();
	//bp.process(sb);


	return b;

}
/*
Block FantasyAgent::makeNewBlockAsOracle() {
	Block b{};

	if (pendingTrans.size() == 0)
		return b;

	if (!beOracle())
	{
		fbutils::LogFalse(std::string("cant makeNewBlockAsOracle am not him"));
		return b;
	}

	BlockHeader bh{};
	bh.set_prev_id
		("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	bh.set_num(2);
	bh.set_version(Commissioner::BLOCK_VERSION);

	SignedBlockHeader sbh{};
	sbh.mutable_head()->CopyFrom(bh);

	for (auto &pt : pendingTrans)
	{
		SignedTransaction* st2 = b.add_signed_transactions();
		st2->CopyFrom(pt);
	}

	b.mutable_signedhead()->CopyFrom(sbh);

	auto p = getIdSig(sbh.head().SerializeAsString(), m_oracle);
	//sb.set_id(p.first);
	sbh.set_sig(p.second);


	//BlockProcessor bp{};
	//bp.init();
	//bp.process(sb);
	pendingTrans.clear();

	return b;

}


/*
NameTrans nametrans{};
nametrans.set_hash(10576213825162658308);
nametrans.set_public_key(std::string("mT1M2MeDjA1RsWkwT7cjE6bbjprcNi84cWyWNvWU1iBa"));
nametrans.set_nonce(57428892);
nametrans.set_utc_sec(1408989677);
nametrans.set_prev_id("00000000000000000000000000000000000000000000000000000000");
nametrans.set_sig("iKkkiYrzqzRo4Cgz1TeZty4JY4KUrDWyPgeF5tKpeRoRD14zWubsFneY8fW7UodCpP3JXXrFvWh6UkSWD7NcktHDK9gb4i9D3m");
nametrans.set_sigid("19cacff77cae784ada296272e43b6dd6f22975d1");

Transaction trans{};
trans.set_version(1);
trans.set_type(TransType::NAME);
//[fantasybit.NameTrans.name_trans]
trans.MutableExtension(NameTrans::name_trans)->CopyFrom(nametrans);

SignedTransaction st{};
st.mutable_trans()->CopyFrom(trans);
st.set_id("6ca607c105f8f9adfa652a89c285e58a1848f35caef132267e0385f79c453eb4");
st.set_sig("iKkki4FAQFoNR4foHVv1KNqfnJ1Fm1xuTToW3LgRjfAem2PSuPU3cH7ZPiJNm3xyTLt2bJx5kdRMfn1aEhfCGiTsHbE3PHBeis");
st.set_fantasy_name("FantasyAgent");

BlockHeader bh{};
bh.set_prev_id("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
bh.set_num(1);

Block b{};
b.mutable_head()->CopyFrom(bh);
SignedTransaction* st2 = b.add_signed_transactions();
st2->CopyFrom(st);

SignedBlock sb{};
sb.mutable_block()->CopyFrom(b);
sb.set_id("c9348ceb2551871534121114cd707c40653303250602aad6c6e0c67c522e5e9c");
sb.set_sig("iKkkiYr6vYFtkRtxCeWQvu7iZ9oFdLwrpRe1P3XYUwZz3BvBuwiufWTFj1JSRJ3d1zjvp9W2whNVTWtT5Jxtn1ByyiW3qQYMyy");

//std::cout << sb.DebugString();
//Commissioner::GenesisBlock = sb;
/*
auto nt = Commissioner::createGenesisName();
NameTrans nt2{};
nt2.set_hash(nt.name_hash);
nt2.set_public_key(Commissioner::pk2str(nt.pubkey));
nt2.set_nonce(nt.nonce);
nt2.set_utc_sec(nt.utc_sec.sec_since_epoch());
nt2.set_prev_id(nt.prev.str());
nt2.set_sig(Commissioner::sig2str(nt.sig));
nt2.set_sigid(nt.sigid());

Transaction trans{};
trans.set_version(1);
trans.set_type(TransType::NAME);
//trans.SetExtension(NameTrans::name_trans, );
trans.MutableExtension(NameTrans::name_trans)->CopyFrom(nt2);
//trans.SetExtension(NameTrans::name_trans, nt2);

SignedTransaction st{};
st.mutable_trans()->CopyFrom(trans);
auto p = getIdSig(trans.SerializeAsString());
st.set_id(p.first);
st.set_sig(p.second);
st.set_fantasy_name("FantasyAgent");

BlockHeader bh{};
bh.set_prev_id
("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
bh.set_num(1);

Block b{};
b.mutable_head()->CopyFrom(bh);
SignedTransaction* st2 = b.add_signed_transactions();
st2->CopyFrom(st);

SignedBlock sb{};
sb.mutable_block()->CopyFrom(b);
auto pp = getIdSig(sb.block().SerializeAsString());
sb.set_id(pp.first);
sb.set_sig(pp.second);
//std::cout << "1 id " << pp.first << " sig " << pp.second << "\n";
*/
/*auto a = sb.block().signed_transactions().Get(0);
auto p1 = getIdSig(a.trans().SerializeAsString());
a.set_id(p1.first);
a.set_sig(p1.second);

std::cout << "\n" << a.DebugString() << "\n";

auto p = getIdSig(sb.block().SerializeAsString());
sb.set_id(p.first);
sb.set_sig(p.second);
std::cout << "\n" << sb.DebugString() << "\n";
*/

}
