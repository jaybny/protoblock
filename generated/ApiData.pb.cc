// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ApiData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ApiData.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace fantasybit {

namespace {

const ::google::protobuf::Descriptor* FantasyNameHash_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FantasyNameHash_reflection_ = NULL;
const ::google::protobuf::Descriptor* Distribution_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Distribution_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ApiData_2eproto() {
  protobuf_AddDesc_ApiData_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ApiData.proto");
  GOOGLE_CHECK(file != NULL);
  FantasyNameHash_descriptor_ = file->message_type(0);
  static const int FantasyNameHash_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FantasyNameHash, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FantasyNameHash, hash_),
  };
  FantasyNameHash_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FantasyNameHash_descriptor_,
      FantasyNameHash::default_instance_,
      FantasyNameHash_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FantasyNameHash, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FantasyNameHash, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FantasyNameHash));
  Distribution_descriptor_ = file->message_type(1);
  static const int Distribution_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, gameid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, teamid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, season_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, week_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, fantasy_nameid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, playerid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, proj_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, award_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, result_),
  };
  Distribution_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Distribution_descriptor_,
      Distribution::default_instance_,
      Distribution_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Distribution, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Distribution));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ApiData_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FantasyNameHash_descriptor_, &FantasyNameHash::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Distribution_descriptor_, &Distribution::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ApiData_2eproto() {
  delete FantasyNameHash::default_instance_;
  delete FantasyNameHash_reflection_;
  delete Distribution::default_instance_;
  delete Distribution_reflection_;
}

void protobuf_AddDesc_ApiData_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rApiData.proto\022\nfantasybit\"-\n\017FantasyNa"
    "meHash\022\014\n\004name\030\n \001(\t\022\014\n\004hash\030\036 \001(\004\"\243\001\n\014D"
    "istribution\022\016\n\006gameid\030\002 \001(\t\022\016\n\006teamid\030\004 "
    "\001(\t\022\016\n\006season\030\005 \001(\005\022\014\n\004week\030\006 \001(\005\022\026\n\016fan"
    "tasy_nameid\030\001 \001(\005\022\020\n\010playerid\030\003 \001(\t\022\014\n\004p"
    "roj\030\007 \001(\005\022\r\n\005award\030\010 \001(\002\022\016\n\006result\030\t \001(\002", 240);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ApiData.proto", &protobuf_RegisterTypes);
  FantasyNameHash::default_instance_ = new FantasyNameHash();
  Distribution::default_instance_ = new Distribution();
  FantasyNameHash::default_instance_->InitAsDefaultInstance();
  Distribution::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ApiData_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ApiData_2eproto {
  StaticDescriptorInitializer_ApiData_2eproto() {
    protobuf_AddDesc_ApiData_2eproto();
  }
} static_descriptor_initializer_ApiData_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int FantasyNameHash::kNameFieldNumber;
const int FantasyNameHash::kHashFieldNumber;
#endif  // !_MSC_VER

FantasyNameHash::FantasyNameHash()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FantasyNameHash::InitAsDefaultInstance() {
}

FantasyNameHash::FantasyNameHash(const FantasyNameHash& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FantasyNameHash::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  hash_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FantasyNameHash::~FantasyNameHash() {
  SharedDtor();
}

void FantasyNameHash::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void FantasyNameHash::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FantasyNameHash::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FantasyNameHash_descriptor_;
}

const FantasyNameHash& FantasyNameHash::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ApiData_2eproto();
  return *default_instance_;
}

FantasyNameHash* FantasyNameHash::default_instance_ = NULL;

FantasyNameHash* FantasyNameHash::New() const {
  return new FantasyNameHash;
}

void FantasyNameHash::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    hash_ = GOOGLE_ULONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FantasyNameHash::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string name = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(240)) goto parse_hash;
        break;
      }

      // optional uint64 hash = 30;
      case 30: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_hash:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &hash_)));
          set_has_hash();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FantasyNameHash::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string name = 10;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      10, this->name(), output);
  }

  // optional uint64 hash = 30;
  if (has_hash()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(30, this->hash(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FantasyNameHash::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string name = 10;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        10, this->name(), target);
  }

  // optional uint64 hash = 30;
  if (has_hash()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(30, this->hash(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FantasyNameHash::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 10;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional uint64 hash = 30;
    if (has_hash()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->hash());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FantasyNameHash::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FantasyNameHash* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FantasyNameHash*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FantasyNameHash::MergeFrom(const FantasyNameHash& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_hash()) {
      set_hash(from.hash());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FantasyNameHash::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FantasyNameHash::CopyFrom(const FantasyNameHash& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FantasyNameHash::IsInitialized() const {

  return true;
}

void FantasyNameHash::Swap(FantasyNameHash* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(hash_, other->hash_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FantasyNameHash::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FantasyNameHash_descriptor_;
  metadata.reflection = FantasyNameHash_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Distribution::kGameidFieldNumber;
const int Distribution::kTeamidFieldNumber;
const int Distribution::kSeasonFieldNumber;
const int Distribution::kWeekFieldNumber;
const int Distribution::kFantasyNameidFieldNumber;
const int Distribution::kPlayeridFieldNumber;
const int Distribution::kProjFieldNumber;
const int Distribution::kAwardFieldNumber;
const int Distribution::kResultFieldNumber;
#endif  // !_MSC_VER

Distribution::Distribution()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Distribution::InitAsDefaultInstance() {
}

Distribution::Distribution(const Distribution& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Distribution::SharedCtor() {
  _cached_size_ = 0;
  gameid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  teamid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  season_ = 0;
  week_ = 0;
  fantasy_nameid_ = 0;
  playerid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  proj_ = 0;
  award_ = 0;
  result_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Distribution::~Distribution() {
  SharedDtor();
}

void Distribution::SharedDtor() {
  if (gameid_ != &::google::protobuf::internal::kEmptyString) {
    delete gameid_;
  }
  if (teamid_ != &::google::protobuf::internal::kEmptyString) {
    delete teamid_;
  }
  if (playerid_ != &::google::protobuf::internal::kEmptyString) {
    delete playerid_;
  }
  if (this != default_instance_) {
  }
}

void Distribution::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Distribution::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Distribution_descriptor_;
}

const Distribution& Distribution::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ApiData_2eproto();
  return *default_instance_;
}

Distribution* Distribution::default_instance_ = NULL;

Distribution* Distribution::New() const {
  return new Distribution;
}

void Distribution::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_gameid()) {
      if (gameid_ != &::google::protobuf::internal::kEmptyString) {
        gameid_->clear();
      }
    }
    if (has_teamid()) {
      if (teamid_ != &::google::protobuf::internal::kEmptyString) {
        teamid_->clear();
      }
    }
    season_ = 0;
    week_ = 0;
    fantasy_nameid_ = 0;
    if (has_playerid()) {
      if (playerid_ != &::google::protobuf::internal::kEmptyString) {
        playerid_->clear();
      }
    }
    proj_ = 0;
    award_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    result_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Distribution::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 fantasy_nameid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &fantasy_nameid_)));
          set_has_fantasy_nameid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_gameid;
        break;
      }

      // optional string gameid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_gameid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_gameid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->gameid().data(), this->gameid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_playerid;
        break;
      }

      // optional string playerid = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_playerid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_playerid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->playerid().data(), this->playerid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_teamid;
        break;
      }

      // optional string teamid = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_teamid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_teamid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->teamid().data(), this->teamid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_season;
        break;
      }

      // optional int32 season = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_season:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &season_)));
          set_has_season();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_week;
        break;
      }

      // optional int32 week = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_week:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &week_)));
          set_has_week();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_proj;
        break;
      }

      // optional int32 proj = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_proj:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &proj_)));
          set_has_proj();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(69)) goto parse_award;
        break;
      }

      // optional float award = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_award:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &award_)));
          set_has_award();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(77)) goto parse_result;
        break;
      }

      // optional float result = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_result:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &result_)));
          set_has_result();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Distribution::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 fantasy_nameid = 1;
  if (has_fantasy_nameid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->fantasy_nameid(), output);
  }

  // optional string gameid = 2;
  if (has_gameid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->gameid().data(), this->gameid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->gameid(), output);
  }

  // optional string playerid = 3;
  if (has_playerid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->playerid().data(), this->playerid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->playerid(), output);
  }

  // optional string teamid = 4;
  if (has_teamid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->teamid().data(), this->teamid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->teamid(), output);
  }

  // optional int32 season = 5;
  if (has_season()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->season(), output);
  }

  // optional int32 week = 6;
  if (has_week()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->week(), output);
  }

  // optional int32 proj = 7;
  if (has_proj()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->proj(), output);
  }

  // optional float award = 8;
  if (has_award()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(8, this->award(), output);
  }

  // optional float result = 9;
  if (has_result()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(9, this->result(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Distribution::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 fantasy_nameid = 1;
  if (has_fantasy_nameid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->fantasy_nameid(), target);
  }

  // optional string gameid = 2;
  if (has_gameid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->gameid().data(), this->gameid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->gameid(), target);
  }

  // optional string playerid = 3;
  if (has_playerid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->playerid().data(), this->playerid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->playerid(), target);
  }

  // optional string teamid = 4;
  if (has_teamid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->teamid().data(), this->teamid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->teamid(), target);
  }

  // optional int32 season = 5;
  if (has_season()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->season(), target);
  }

  // optional int32 week = 6;
  if (has_week()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->week(), target);
  }

  // optional int32 proj = 7;
  if (has_proj()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->proj(), target);
  }

  // optional float award = 8;
  if (has_award()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(8, this->award(), target);
  }

  // optional float result = 9;
  if (has_result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(9, this->result(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Distribution::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string gameid = 2;
    if (has_gameid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->gameid());
    }

    // optional string teamid = 4;
    if (has_teamid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->teamid());
    }

    // optional int32 season = 5;
    if (has_season()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->season());
    }

    // optional int32 week = 6;
    if (has_week()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->week());
    }

    // optional int32 fantasy_nameid = 1;
    if (has_fantasy_nameid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->fantasy_nameid());
    }

    // optional string playerid = 3;
    if (has_playerid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->playerid());
    }

    // optional int32 proj = 7;
    if (has_proj()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->proj());
    }

    // optional float award = 8;
    if (has_award()) {
      total_size += 1 + 4;
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional float result = 9;
    if (has_result()) {
      total_size += 1 + 4;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Distribution::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Distribution* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Distribution*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Distribution::MergeFrom(const Distribution& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_gameid()) {
      set_gameid(from.gameid());
    }
    if (from.has_teamid()) {
      set_teamid(from.teamid());
    }
    if (from.has_season()) {
      set_season(from.season());
    }
    if (from.has_week()) {
      set_week(from.week());
    }
    if (from.has_fantasy_nameid()) {
      set_fantasy_nameid(from.fantasy_nameid());
    }
    if (from.has_playerid()) {
      set_playerid(from.playerid());
    }
    if (from.has_proj()) {
      set_proj(from.proj());
    }
    if (from.has_award()) {
      set_award(from.award());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_result()) {
      set_result(from.result());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Distribution::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Distribution::CopyFrom(const Distribution& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Distribution::IsInitialized() const {

  return true;
}

void Distribution::Swap(Distribution* other) {
  if (other != this) {
    std::swap(gameid_, other->gameid_);
    std::swap(teamid_, other->teamid_);
    std::swap(season_, other->season_);
    std::swap(week_, other->week_);
    std::swap(fantasy_nameid_, other->fantasy_nameid_);
    std::swap(playerid_, other->playerid_);
    std::swap(proj_, other->proj_);
    std::swap(award_, other->award_);
    std::swap(result_, other->result_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Distribution::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Distribution_descriptor_;
  metadata.reflection = Distribution_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace fantasybit

// @@protoc_insertion_point(global_scope)
