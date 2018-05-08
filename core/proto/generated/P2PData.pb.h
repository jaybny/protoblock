// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: P2PData.proto

#ifndef PROTOBUF_P2PData_2eproto__INCLUDED
#define PROTOBUF_P2PData_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_P2PData_2eproto();
void protobuf_AssignDesc_P2PData_2eproto();
void protobuf_ShutdownFile_P2PData_2eproto();

class Peer;

// ===================================================================

class Peer : public ::google::protobuf::Message {
 public:
  Peer();
  virtual ~Peer();

  Peer(const Peer& from);

  inline Peer& operator=(const Peer& from) {
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
  static const Peer& default_instance();

  void Swap(Peer* other);

  // implements Message ----------------------------------------------

  Peer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Peer& from);
  void MergeFrom(const Peer& from);
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

  // optional string address = 10;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 10;
  inline const ::std::string& address() const;
  inline void set_address(const ::std::string& value);
  inline void set_address(const char* value);
  inline void set_address(const char* value, size_t size);
  inline ::std::string* mutable_address();
  inline ::std::string* release_address();
  inline void set_allocated_address(::std::string* address);

  // optional uint64 lastSync = 20;
  inline bool has_lastsync() const;
  inline void clear_lastsync();
  static const int kLastSyncFieldNumber = 20;
  inline ::google::protobuf::uint64 lastsync() const;
  inline void set_lastsync(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.Peer)
 private:
  inline void set_has_address();
  inline void clear_has_address();
  inline void set_has_lastsync();
  inline void clear_has_lastsync();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* address_;
  ::google::protobuf::uint64 lastsync_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_P2PData_2eproto();
  friend void protobuf_AssignDesc_P2PData_2eproto();
  friend void protobuf_ShutdownFile_P2PData_2eproto();

  void InitAsDefaultInstance();
  static Peer* default_instance_;
};
// ===================================================================


// ===================================================================

// Peer

// optional string address = 10;
inline bool Peer::has_address() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Peer::set_has_address() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Peer::clear_has_address() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Peer::clear_address() {
  if (address_ != &::google::protobuf::internal::kEmptyString) {
    address_->clear();
  }
  clear_has_address();
}
inline const ::std::string& Peer::address() const {
  return *address_;
}
inline void Peer::set_address(const ::std::string& value) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(value);
}
inline void Peer::set_address(const char* value) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(value);
}
inline void Peer::set_address(const char* value, size_t size) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Peer::mutable_address() {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  return address_;
}
inline ::std::string* Peer::release_address() {
  clear_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = address_;
    address_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Peer::set_allocated_address(::std::string* address) {
  if (address_ != &::google::protobuf::internal::kEmptyString) {
    delete address_;
  }
  if (address) {
    set_has_address();
    address_ = address;
  } else {
    clear_has_address();
    address_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional uint64 lastSync = 20;
inline bool Peer::has_lastsync() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Peer::set_has_lastsync() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Peer::clear_has_lastsync() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Peer::clear_lastsync() {
  lastsync_ = GOOGLE_ULONGLONG(0);
  clear_has_lastsync();
}
inline ::google::protobuf::uint64 Peer::lastsync() const {
  return lastsync_;
}
inline void Peer::set_lastsync(::google::protobuf::uint64 value) {
  set_has_lastsync();
  lastsync_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_P2PData_2eproto__INCLUDED
