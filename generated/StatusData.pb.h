// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: StatusData.proto

#ifndef PROTOBUF_StatusData_2eproto__INCLUDED
#define PROTOBUF_StatusData_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace fantasybit {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_StatusData_2eproto();
void protobuf_AssignDesc_StatusData_2eproto();
void protobuf_ShutdownFile_StatusData_2eproto();

class PlayerStatus;
class GameStatus;
class TeamDepth;
class GlobalState;

enum PlayerStatus_Status {
  PlayerStatus_Status_ACTIVE = 0,
  PlayerStatus_Status_INACTIVE = 1,
  PlayerStatus_Status_OTHER = 3,
  PlayerStatus_Status_FA = 4
};
bool PlayerStatus_Status_IsValid(int value);
const PlayerStatus_Status PlayerStatus_Status_Status_MIN = PlayerStatus_Status_ACTIVE;
const PlayerStatus_Status PlayerStatus_Status_Status_MAX = PlayerStatus_Status_FA;
const int PlayerStatus_Status_Status_ARRAYSIZE = PlayerStatus_Status_Status_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerStatus_Status_descriptor();
inline const ::std::string& PlayerStatus_Status_Name(PlayerStatus_Status value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerStatus_Status_descriptor(), value);
}
inline bool PlayerStatus_Status_Parse(
    const ::std::string& name, PlayerStatus_Status* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerStatus_Status>(
    PlayerStatus_Status_descriptor(), name, value);
}
enum GameStatus_Status {
  GameStatus_Status_SCHEDULED = 0,
  GameStatus_Status_PREGAME = 2,
  GameStatus_Status_INGAME = 3,
  GameStatus_Status_POSTGAME = 5,
  GameStatus_Status_CLOSED = 4
};
bool GameStatus_Status_IsValid(int value);
const GameStatus_Status GameStatus_Status_Status_MIN = GameStatus_Status_SCHEDULED;
const GameStatus_Status GameStatus_Status_Status_MAX = GameStatus_Status_POSTGAME;
const int GameStatus_Status_Status_ARRAYSIZE = GameStatus_Status_Status_MAX + 1;

const ::google::protobuf::EnumDescriptor* GameStatus_Status_descriptor();
inline const ::std::string& GameStatus_Status_Name(GameStatus_Status value) {
  return ::google::protobuf::internal::NameOfEnum(
    GameStatus_Status_descriptor(), value);
}
inline bool GameStatus_Status_Parse(
    const ::std::string& name, GameStatus_Status* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GameStatus_Status>(
    GameStatus_Status_descriptor(), name, value);
}
enum GlobalState_State {
  GlobalState_State_OFFSEASON = 10,
  GlobalState_State_INSEASON = 30
};
bool GlobalState_State_IsValid(int value);
const GlobalState_State GlobalState_State_State_MIN = GlobalState_State_OFFSEASON;
const GlobalState_State GlobalState_State_State_MAX = GlobalState_State_INSEASON;
const int GlobalState_State_State_ARRAYSIZE = GlobalState_State_State_MAX + 1;

const ::google::protobuf::EnumDescriptor* GlobalState_State_descriptor();
inline const ::std::string& GlobalState_State_Name(GlobalState_State value) {
  return ::google::protobuf::internal::NameOfEnum(
    GlobalState_State_descriptor(), value);
}
inline bool GlobalState_State_Parse(
    const ::std::string& name, GlobalState_State* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GlobalState_State>(
    GlobalState_State_descriptor(), name, value);
}
enum PlayerGameStatus {
  OUT = 0,
  IN = 1,
  NA = 2
};
bool PlayerGameStatus_IsValid(int value);
const PlayerGameStatus PlayerGameStatus_MIN = OUT;
const PlayerGameStatus PlayerGameStatus_MAX = NA;
const int PlayerGameStatus_ARRAYSIZE = PlayerGameStatus_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerGameStatus_descriptor();
inline const ::std::string& PlayerGameStatus_Name(PlayerGameStatus value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerGameStatus_descriptor(), value);
}
inline bool PlayerGameStatus_Parse(
    const ::std::string& name, PlayerGameStatus* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerGameStatus>(
    PlayerGameStatus_descriptor(), name, value);
}
// ===================================================================

class PlayerStatus : public ::google::protobuf::Message {
 public:
  PlayerStatus();
  virtual ~PlayerStatus();

  PlayerStatus(const PlayerStatus& from);

  inline PlayerStatus& operator=(const PlayerStatus& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PlayerStatus& default_instance();

  void Swap(PlayerStatus* other);

  // implements Message ----------------------------------------------

  PlayerStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayerStatus& from);
  void MergeFrom(const PlayerStatus& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef PlayerStatus_Status Status;
  static const Status ACTIVE = PlayerStatus_Status_ACTIVE;
  static const Status INACTIVE = PlayerStatus_Status_INACTIVE;
  static const Status OTHER = PlayerStatus_Status_OTHER;
  static const Status FA = PlayerStatus_Status_FA;
  static inline bool Status_IsValid(int value) {
    return PlayerStatus_Status_IsValid(value);
  }
  static const Status Status_MIN =
    PlayerStatus_Status_Status_MIN;
  static const Status Status_MAX =
    PlayerStatus_Status_Status_MAX;
  static const int Status_ARRAYSIZE =
    PlayerStatus_Status_Status_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Status_descriptor() {
    return PlayerStatus_Status_descriptor();
  }
  static inline const ::std::string& Status_Name(Status value) {
    return PlayerStatus_Status_Name(value);
  }
  static inline bool Status_Parse(const ::std::string& name,
      Status* value) {
    return PlayerStatus_Status_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional string teamid = 20;
  inline bool has_teamid() const;
  inline void clear_teamid();
  static const int kTeamidFieldNumber = 20;
  inline const ::std::string& teamid() const;
  inline void set_teamid(const ::std::string& value);
  inline void set_teamid(const char* value);
  inline void set_teamid(const char* value, size_t size);
  inline ::std::string* mutable_teamid();
  inline ::std::string* release_teamid();
  inline void set_allocated_teamid(::std::string* teamid);

  // optional .fantasybit.PlayerStatus.Status status = 30;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 30;
  inline ::fantasybit::PlayerStatus_Status status() const;
  inline void set_status(::fantasybit::PlayerStatus_Status value);

  // @@protoc_insertion_point(class_scope:fantasybit.PlayerStatus)
 private:
  inline void set_has_teamid();
  inline void clear_has_teamid();
  inline void set_has_status();
  inline void clear_has_status();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* teamid_;
  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_StatusData_2eproto();
  friend void protobuf_AssignDesc_StatusData_2eproto();
  friend void protobuf_ShutdownFile_StatusData_2eproto();

  void InitAsDefaultInstance();
  static PlayerStatus* default_instance_;
};
// -------------------------------------------------------------------

class   GameStatus : public ::google::protobuf::Message {
 public:
  GameStatus();
  virtual ~GameStatus();

  GameStatus(const GameStatus& from);

  inline GameStatus& operator=(const GameStatus& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GameStatus& default_instance();

  void Swap(GameStatus* other);

  // implements Message ----------------------------------------------

  GameStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GameStatus& from);
  void MergeFrom(const GameStatus& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef GameStatus_Status Status;
  static const Status SCHEDULED = GameStatus_Status_SCHEDULED;
  static const Status PREGAME = GameStatus_Status_PREGAME;
  static const Status INGAME = GameStatus_Status_INGAME;
  static const Status POSTGAME = GameStatus_Status_POSTGAME;
  static const Status CLOSED = GameStatus_Status_CLOSED;
  static inline bool Status_IsValid(int value) {
    return GameStatus_Status_IsValid(value);
  }
  static const Status Status_MIN =
    GameStatus_Status_Status_MIN;
  static const Status Status_MAX =
    GameStatus_Status_Status_MAX;
  static const int Status_ARRAYSIZE =
    GameStatus_Status_Status_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Status_descriptor() {
    return GameStatus_Status_descriptor();
  }
  static inline const ::std::string& Status_Name(Status value) {
    return GameStatus_Status_Name(value);
  }
  static inline bool Status_Parse(const ::std::string& name,
      Status* value) {
    return GameStatus_Status_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .fantasybit.GameStatus.Status status = 10;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 10;
  inline ::fantasybit::GameStatus_Status status() const;
  inline void set_status(::fantasybit::GameStatus_Status value);

  // optional uint32 datetime = 20;
  inline bool has_datetime() const;
  inline void clear_datetime();
  static const int kDatetimeFieldNumber = 20;
  inline ::google::protobuf::uint32 datetime() const;
  inline void set_datetime(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:fantasybit.GameStatus)
 private:
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_datetime();
  inline void clear_has_datetime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  int status_;
  ::google::protobuf::uint32 datetime_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_StatusData_2eproto();
  friend void protobuf_AssignDesc_StatusData_2eproto();
  friend void protobuf_ShutdownFile_StatusData_2eproto();

  void InitAsDefaultInstance();
  static GameStatus* default_instance_;
};
// -------------------------------------------------------------------

class TeamDepth : public ::google::protobuf::Message {
 public:
  TeamDepth();
  virtual ~TeamDepth();

  TeamDepth(const TeamDepth& from);

  inline TeamDepth& operator=(const TeamDepth& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TeamDepth& default_instance();

  void Swap(TeamDepth* other);

  // implements Message ----------------------------------------------

  TeamDepth* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TeamDepth& from);
  void MergeFrom(const TeamDepth& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string qb = 10;
  inline int qb_size() const;
  inline void clear_qb();
  static const int kQbFieldNumber = 10;
  inline const ::std::string& qb(int index) const;
  inline ::std::string* mutable_qb(int index);
  inline void set_qb(int index, const ::std::string& value);
  inline void set_qb(int index, const char* value);
  inline void set_qb(int index, const char* value, size_t size);
  inline ::std::string* add_qb();
  inline void add_qb(const ::std::string& value);
  inline void add_qb(const char* value);
  inline void add_qb(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& qb() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_qb();

  // repeated string rb = 20;
  inline int rb_size() const;
  inline void clear_rb();
  static const int kRbFieldNumber = 20;
  inline const ::std::string& rb(int index) const;
  inline ::std::string* mutable_rb(int index);
  inline void set_rb(int index, const ::std::string& value);
  inline void set_rb(int index, const char* value);
  inline void set_rb(int index, const char* value, size_t size);
  inline ::std::string* add_rb();
  inline void add_rb(const ::std::string& value);
  inline void add_rb(const char* value);
  inline void add_rb(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& rb() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_rb();

  // repeated string wr = 30;
  inline int wr_size() const;
  inline void clear_wr();
  static const int kWrFieldNumber = 30;
  inline const ::std::string& wr(int index) const;
  inline ::std::string* mutable_wr(int index);
  inline void set_wr(int index, const ::std::string& value);
  inline void set_wr(int index, const char* value);
  inline void set_wr(int index, const char* value, size_t size);
  inline ::std::string* add_wr();
  inline void add_wr(const ::std::string& value);
  inline void add_wr(const char* value);
  inline void add_wr(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& wr() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_wr();

  // repeated string te = 40;
  inline int te_size() const;
  inline void clear_te();
  static const int kTeFieldNumber = 40;
  inline const ::std::string& te(int index) const;
  inline ::std::string* mutable_te(int index);
  inline void set_te(int index, const ::std::string& value);
  inline void set_te(int index, const char* value);
  inline void set_te(int index, const char* value, size_t size);
  inline ::std::string* add_te();
  inline void add_te(const ::std::string& value);
  inline void add_te(const char* value);
  inline void add_te(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& te() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_te();

  // repeated string k = 50;
  inline int k_size() const;
  inline void clear_k();
  static const int kKFieldNumber = 50;
  inline const ::std::string& k(int index) const;
  inline ::std::string* mutable_k(int index);
  inline void set_k(int index, const ::std::string& value);
  inline void set_k(int index, const char* value);
  inline void set_k(int index, const char* value, size_t size);
  inline ::std::string* add_k();
  inline void add_k(const ::std::string& value);
  inline void add_k(const char* value);
  inline void add_k(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& k() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_k();

  // @@protoc_insertion_point(class_scope:fantasybit.TeamDepth)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::std::string> qb_;
  ::google::protobuf::RepeatedPtrField< ::std::string> rb_;
  ::google::protobuf::RepeatedPtrField< ::std::string> wr_;
  ::google::protobuf::RepeatedPtrField< ::std::string> te_;
  ::google::protobuf::RepeatedPtrField< ::std::string> k_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_StatusData_2eproto();
  friend void protobuf_AssignDesc_StatusData_2eproto();
  friend void protobuf_ShutdownFile_StatusData_2eproto();

  void InitAsDefaultInstance();
  static TeamDepth* default_instance_;
};
// -------------------------------------------------------------------

class GlobalState : public ::google::protobuf::Message {
 public:
  GlobalState();
  virtual ~GlobalState();

  GlobalState(const GlobalState& from);

  inline GlobalState& operator=(const GlobalState& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GlobalState& default_instance();

  void Swap(GlobalState* other);

  // implements Message ----------------------------------------------

  GlobalState* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GlobalState& from);
  void MergeFrom(const GlobalState& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef GlobalState_State State;
  static const State OFFSEASON = GlobalState_State_OFFSEASON;
  static const State INSEASON = GlobalState_State_INSEASON;
  static inline bool State_IsValid(int value) {
    return GlobalState_State_IsValid(value);
  }
  static const State State_MIN =
    GlobalState_State_State_MIN;
  static const State State_MAX =
    GlobalState_State_State_MAX;
  static const int State_ARRAYSIZE =
    GlobalState_State_State_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  State_descriptor() {
    return GlobalState_State_descriptor();
  }
  static inline const ::std::string& State_Name(State value) {
    return GlobalState_State_Name(value);
  }
  static inline bool State_Parse(const ::std::string& name,
      State* value) {
    return GlobalState_State_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .fantasybit.GlobalState.State state = 1;
  inline bool has_state() const;
  inline void clear_state();
  static const int kStateFieldNumber = 1;
  inline ::fantasybit::GlobalState_State state() const;
  inline void set_state(::fantasybit::GlobalState_State value);

  // optional uint32 season = 10;
  inline bool has_season() const;
  inline void clear_season();
  static const int kSeasonFieldNumber = 10;
  inline ::google::protobuf::uint32 season() const;
  inline void set_season(::google::protobuf::uint32 value);

  // optional uint32 week = 20;
  inline bool has_week() const;
  inline void clear_week();
  static const int kWeekFieldNumber = 20;
  inline ::google::protobuf::uint32 week() const;
  inline void set_week(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:fantasybit.GlobalState)
 private:
  inline void set_has_state();
  inline void clear_has_state();
  inline void set_has_season();
  inline void clear_has_season();
  inline void set_has_week();
  inline void clear_has_week();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  int state_;
  ::google::protobuf::uint32 season_;
  ::google::protobuf::uint32 week_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_StatusData_2eproto();
  friend void protobuf_AssignDesc_StatusData_2eproto();
  friend void protobuf_ShutdownFile_StatusData_2eproto();

  void InitAsDefaultInstance();
  static GlobalState* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayerStatus

// optional string teamid = 20;
inline bool PlayerStatus::has_teamid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerStatus::set_has_teamid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerStatus::clear_has_teamid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerStatus::clear_teamid() {
  if (teamid_ != &::google::protobuf::internal::kEmptyString) {
    teamid_->clear();
  }
  clear_has_teamid();
}
inline const ::std::string& PlayerStatus::teamid() const {
  return *teamid_;
}
inline void PlayerStatus::set_teamid(const ::std::string& value) {
  set_has_teamid();
  if (teamid_ == &::google::protobuf::internal::kEmptyString) {
    teamid_ = new ::std::string;
  }
  teamid_->assign(value);
}
inline void PlayerStatus::set_teamid(const char* value) {
  set_has_teamid();
  if (teamid_ == &::google::protobuf::internal::kEmptyString) {
    teamid_ = new ::std::string;
  }
  teamid_->assign(value);
}
inline void PlayerStatus::set_teamid(const char* value, size_t size) {
  set_has_teamid();
  if (teamid_ == &::google::protobuf::internal::kEmptyString) {
    teamid_ = new ::std::string;
  }
  teamid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PlayerStatus::mutable_teamid() {
  set_has_teamid();
  if (teamid_ == &::google::protobuf::internal::kEmptyString) {
    teamid_ = new ::std::string;
  }
  return teamid_;
}
inline ::std::string* PlayerStatus::release_teamid() {
  clear_has_teamid();
  if (teamid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = teamid_;
    teamid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void PlayerStatus::set_allocated_teamid(::std::string* teamid) {
  if (teamid_ != &::google::protobuf::internal::kEmptyString) {
    delete teamid_;
  }
  if (teamid) {
    set_has_teamid();
    teamid_ = teamid;
  } else {
    clear_has_teamid();
    teamid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .fantasybit.PlayerStatus.Status status = 30;
inline bool PlayerStatus::has_status() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PlayerStatus::set_has_status() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PlayerStatus::clear_has_status() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PlayerStatus::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::fantasybit::PlayerStatus_Status PlayerStatus::status() const {
  return static_cast< ::fantasybit::PlayerStatus_Status >(status_);
}
inline void PlayerStatus::set_status(::fantasybit::PlayerStatus_Status value) {
  assert(::fantasybit::PlayerStatus_Status_IsValid(value));
  set_has_status();
  status_ = value;
}

// -------------------------------------------------------------------

// GameStatus

// optional .fantasybit.GameStatus.Status status = 10;
inline bool GameStatus::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GameStatus::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GameStatus::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GameStatus::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::fantasybit::GameStatus_Status GameStatus::status() const {
  return static_cast< ::fantasybit::GameStatus_Status >(status_);
}
inline void GameStatus::set_status(::fantasybit::GameStatus_Status value) {
  assert(::fantasybit::GameStatus_Status_IsValid(value));
  set_has_status();
  status_ = value;
}

// optional uint32 datetime = 20;
inline bool GameStatus::has_datetime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GameStatus::set_has_datetime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GameStatus::clear_has_datetime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GameStatus::clear_datetime() {
  datetime_ = 0u;
  clear_has_datetime();
}
inline ::google::protobuf::uint32 GameStatus::datetime() const {
  return datetime_;
}
inline void GameStatus::set_datetime(::google::protobuf::uint32 value) {
  set_has_datetime();
  datetime_ = value;
}

// -------------------------------------------------------------------

// TeamDepth

// repeated string qb = 10;
inline int TeamDepth::qb_size() const {
  return qb_.size();
}
inline void TeamDepth::clear_qb() {
  qb_.Clear();
}
inline const ::std::string& TeamDepth::qb(int index) const {
  return qb_.Get(index);
}
inline ::std::string* TeamDepth::mutable_qb(int index) {
  return qb_.Mutable(index);
}
inline void TeamDepth::set_qb(int index, const ::std::string& value) {
  qb_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_qb(int index, const char* value) {
  qb_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_qb(int index, const char* value, size_t size) {
  qb_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TeamDepth::add_qb() {
  return qb_.Add();
}
inline void TeamDepth::add_qb(const ::std::string& value) {
  qb_.Add()->assign(value);
}
inline void TeamDepth::add_qb(const char* value) {
  qb_.Add()->assign(value);
}
inline void TeamDepth::add_qb(const char* value, size_t size) {
  qb_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TeamDepth::qb() const {
  return qb_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TeamDepth::mutable_qb() {
  return &qb_;
}

// repeated string rb = 20;
inline int TeamDepth::rb_size() const {
  return rb_.size();
}
inline void TeamDepth::clear_rb() {
  rb_.Clear();
}
inline const ::std::string& TeamDepth::rb(int index) const {
  return rb_.Get(index);
}
inline ::std::string* TeamDepth::mutable_rb(int index) {
  return rb_.Mutable(index);
}
inline void TeamDepth::set_rb(int index, const ::std::string& value) {
  rb_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_rb(int index, const char* value) {
  rb_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_rb(int index, const char* value, size_t size) {
  rb_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TeamDepth::add_rb() {
  return rb_.Add();
}
inline void TeamDepth::add_rb(const ::std::string& value) {
  rb_.Add()->assign(value);
}
inline void TeamDepth::add_rb(const char* value) {
  rb_.Add()->assign(value);
}
inline void TeamDepth::add_rb(const char* value, size_t size) {
  rb_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TeamDepth::rb() const {
  return rb_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TeamDepth::mutable_rb() {
  return &rb_;
}

// repeated string wr = 30;
inline int TeamDepth::wr_size() const {
  return wr_.size();
}
inline void TeamDepth::clear_wr() {
  wr_.Clear();
}
inline const ::std::string& TeamDepth::wr(int index) const {
  return wr_.Get(index);
}
inline ::std::string* TeamDepth::mutable_wr(int index) {
  return wr_.Mutable(index);
}
inline void TeamDepth::set_wr(int index, const ::std::string& value) {
  wr_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_wr(int index, const char* value) {
  wr_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_wr(int index, const char* value, size_t size) {
  wr_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TeamDepth::add_wr() {
  return wr_.Add();
}
inline void TeamDepth::add_wr(const ::std::string& value) {
  wr_.Add()->assign(value);
}
inline void TeamDepth::add_wr(const char* value) {
  wr_.Add()->assign(value);
}
inline void TeamDepth::add_wr(const char* value, size_t size) {
  wr_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TeamDepth::wr() const {
  return wr_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TeamDepth::mutable_wr() {
  return &wr_;
}

// repeated string te = 40;
inline int TeamDepth::te_size() const {
  return te_.size();
}
inline void TeamDepth::clear_te() {
  te_.Clear();
}
inline const ::std::string& TeamDepth::te(int index) const {
  return te_.Get(index);
}
inline ::std::string* TeamDepth::mutable_te(int index) {
  return te_.Mutable(index);
}
inline void TeamDepth::set_te(int index, const ::std::string& value) {
  te_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_te(int index, const char* value) {
  te_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_te(int index, const char* value, size_t size) {
  te_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TeamDepth::add_te() {
  return te_.Add();
}
inline void TeamDepth::add_te(const ::std::string& value) {
  te_.Add()->assign(value);
}
inline void TeamDepth::add_te(const char* value) {
  te_.Add()->assign(value);
}
inline void TeamDepth::add_te(const char* value, size_t size) {
  te_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TeamDepth::te() const {
  return te_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TeamDepth::mutable_te() {
  return &te_;
}

// repeated string k = 50;
inline int TeamDepth::k_size() const {
  return k_.size();
}
inline void TeamDepth::clear_k() {
  k_.Clear();
}
inline const ::std::string& TeamDepth::k(int index) const {
  return k_.Get(index);
}
inline ::std::string* TeamDepth::mutable_k(int index) {
  return k_.Mutable(index);
}
inline void TeamDepth::set_k(int index, const ::std::string& value) {
  k_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_k(int index, const char* value) {
  k_.Mutable(index)->assign(value);
}
inline void TeamDepth::set_k(int index, const char* value, size_t size) {
  k_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TeamDepth::add_k() {
  return k_.Add();
}
inline void TeamDepth::add_k(const ::std::string& value) {
  k_.Add()->assign(value);
}
inline void TeamDepth::add_k(const char* value) {
  k_.Add()->assign(value);
}
inline void TeamDepth::add_k(const char* value, size_t size) {
  k_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
TeamDepth::k() const {
  return k_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
TeamDepth::mutable_k() {
  return &k_;
}

// -------------------------------------------------------------------

// GlobalState

// optional .fantasybit.GlobalState.State state = 1;
inline bool GlobalState::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GlobalState::set_has_state() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GlobalState::clear_has_state() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GlobalState::clear_state() {
  state_ = 10;
  clear_has_state();
}
inline ::fantasybit::GlobalState_State GlobalState::state() const {
  return static_cast< ::fantasybit::GlobalState_State >(state_);
}
inline void GlobalState::set_state(::fantasybit::GlobalState_State value) {
  assert(::fantasybit::GlobalState_State_IsValid(value));
  set_has_state();
  state_ = value;
}

// optional uint32 season = 10;
inline bool GlobalState::has_season() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GlobalState::set_has_season() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GlobalState::clear_has_season() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GlobalState::clear_season() {
  season_ = 0u;
  clear_has_season();
}
inline ::google::protobuf::uint32 GlobalState::season() const {
  return season_;
}
inline void GlobalState::set_season(::google::protobuf::uint32 value) {
  set_has_season();
  season_ = value;
}

// optional uint32 week = 20;
inline bool GlobalState::has_week() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GlobalState::set_has_week() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GlobalState::clear_has_week() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GlobalState::clear_week() {
  week_ = 0u;
  clear_has_week();
}
inline ::google::protobuf::uint32 GlobalState::week() const {
  return week_;
}
inline void GlobalState::set_week(::google::protobuf::uint32 value) {
  set_has_week();
  week_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace fantasybit

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::fantasybit::PlayerStatus_Status>() {
  return ::fantasybit::PlayerStatus_Status_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::fantasybit::GameStatus_Status>() {
  return ::fantasybit::GameStatus_Status_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::fantasybit::GlobalState_State>() {
  return ::fantasybit::GlobalState_State_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::fantasybit::PlayerGameStatus>() {
  return ::fantasybit::PlayerGameStatus_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_StatusData_2eproto__INCLUDED
