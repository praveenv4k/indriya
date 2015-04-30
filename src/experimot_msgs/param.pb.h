// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: param.proto

#ifndef PROTOBUF_param_2eproto__INCLUDED
#define PROTOBUF_param_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_param_2eproto();
void protobuf_AssignDesc_param_2eproto();
void protobuf_ShutdownFile_param_2eproto();

class Param;

// ===================================================================

class Param : public ::google::protobuf::Message {
 public:
  Param();
  virtual ~Param();

  Param(const Param& from);

  inline Param& operator=(const Param& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Param& default_instance();

  void Swap(Param* other);

  // implements Message ----------------------------------------------

  inline Param* New() const { return New(NULL); }

  Param* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Param& from);
  void MergeFrom(const Param& from);
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
  void InternalSwap(Param* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string key = 1;
  bool has_key() const;
  void clear_key();
  static const int kKeyFieldNumber = 1;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  void set_key(const char* value);
  void set_key(const char* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // required string value = 2;
  bool has_value() const;
  void clear_value();
  static const int kValueFieldNumber = 2;
  const ::std::string& value() const;
  void set_value(const ::std::string& value);
  void set_value(const char* value);
  void set_value(const char* value, size_t size);
  ::std::string* mutable_value();
  ::std::string* release_value();
  void set_allocated_value(::std::string* value);

  // required string dataType = 3;
  bool has_datatype() const;
  void clear_datatype();
  static const int kDataTypeFieldNumber = 3;
  const ::std::string& datatype() const;
  void set_datatype(const ::std::string& value);
  void set_datatype(const char* value);
  void set_datatype(const char* value, size_t size);
  ::std::string* mutable_datatype();
  ::std::string* release_datatype();
  void set_allocated_datatype(::std::string* datatype);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Param)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_value();
  inline void clear_has_value();
  inline void set_has_datatype();
  inline void clear_has_datatype();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  ::google::protobuf::internal::ArenaStringPtr value_;
  ::google::protobuf::internal::ArenaStringPtr datatype_;
  friend void  protobuf_AddDesc_param_2eproto();
  friend void protobuf_AssignDesc_param_2eproto();
  friend void protobuf_ShutdownFile_param_2eproto();

  void InitAsDefaultInstance();
  static Param* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Param

// required string key = 1;
inline bool Param::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Param::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Param::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Param::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_key();
}
inline const ::std::string& Param::key() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Param.key)
  return key_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_key(const ::std::string& value) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Param.key)
}
inline void Param::set_key(const char* value) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Param.key)
}
inline void Param::set_key(const char* value, size_t size) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Param.key)
}
inline ::std::string* Param::mutable_key() {
  set_has_key();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Param.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Param::release_key() {
  clear_has_key();
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    set_has_key();
  } else {
    clear_has_key();
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Param.key)
}

// required string value = 2;
inline bool Param::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Param::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Param::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Param::clear_value() {
  value_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_value();
}
inline const ::std::string& Param::value() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Param.value)
  return value_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_value(const ::std::string& value) {
  set_has_value();
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Param.value)
}
inline void Param::set_value(const char* value) {
  set_has_value();
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Param.value)
}
inline void Param::set_value(const char* value, size_t size) {
  set_has_value();
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Param.value)
}
inline ::std::string* Param::mutable_value() {
  set_has_value();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Param.value)
  return value_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Param::release_value() {
  clear_has_value();
  return value_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_allocated_value(::std::string* value) {
  if (value != NULL) {
    set_has_value();
  } else {
    clear_has_value();
  }
  value_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Param.value)
}

// required string dataType = 3;
inline bool Param::has_datatype() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Param::set_has_datatype() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Param::clear_has_datatype() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Param::clear_datatype() {
  datatype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_datatype();
}
inline const ::std::string& Param::datatype() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Param.dataType)
  return datatype_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_datatype(const ::std::string& value) {
  set_has_datatype();
  datatype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Param.dataType)
}
inline void Param::set_datatype(const char* value) {
  set_has_datatype();
  datatype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Param.dataType)
}
inline void Param::set_datatype(const char* value, size_t size) {
  set_has_datatype();
  datatype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Param.dataType)
}
inline ::std::string* Param::mutable_datatype() {
  set_has_datatype();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Param.dataType)
  return datatype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Param::release_datatype() {
  clear_has_datatype();
  return datatype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Param::set_allocated_datatype(::std::string* datatype) {
  if (datatype != NULL) {
    set_has_datatype();
  } else {
    clear_has_datatype();
  }
  datatype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), datatype);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Param.dataType)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Param> ParamPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Param const> ConstParamPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_param_2eproto__INCLUDED
