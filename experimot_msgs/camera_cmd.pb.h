// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: camera_cmd.proto

#ifndef PROTOBUF_camera_5fcmd_2eproto__INCLUDED
#define PROTOBUF_camera_5fcmd_2eproto__INCLUDED

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
void protobuf_AddDesc_camera_5fcmd_2eproto();
void protobuf_AssignDesc_camera_5fcmd_2eproto();
void protobuf_ShutdownFile_camera_5fcmd_2eproto();

class CameraCmd;

// ===================================================================

class CameraCmd : public ::google::protobuf::Message {
 public:
  CameraCmd();
  virtual ~CameraCmd();

  CameraCmd(const CameraCmd& from);

  inline CameraCmd& operator=(const CameraCmd& from) {
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
  static const CameraCmd& default_instance();

  void Swap(CameraCmd* other);

  // implements Message ----------------------------------------------

  inline CameraCmd* New() const { return New(NULL); }

  CameraCmd* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CameraCmd& from);
  void MergeFrom(const CameraCmd& from);
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
  void InternalSwap(CameraCmd* other);
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

  // optional string follow_model = 1;
  bool has_follow_model() const;
  void clear_follow_model();
  static const int kFollowModelFieldNumber = 1;
  const ::std::string& follow_model() const;
  void set_follow_model(const ::std::string& value);
  void set_follow_model(const char* value);
  void set_follow_model(const char* value, size_t size);
  ::std::string* mutable_follow_model();
  ::std::string* release_follow_model();
  void set_allocated_follow_model(::std::string* follow_model);

  // @@protoc_insertion_point(class_scope:experimot.msgs.CameraCmd)
 private:
  inline void set_has_follow_model();
  inline void clear_has_follow_model();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr follow_model_;
  friend void  protobuf_AddDesc_camera_5fcmd_2eproto();
  friend void protobuf_AssignDesc_camera_5fcmd_2eproto();
  friend void protobuf_ShutdownFile_camera_5fcmd_2eproto();

  void InitAsDefaultInstance();
  static CameraCmd* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CameraCmd

// optional string follow_model = 1;
inline bool CameraCmd::has_follow_model() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CameraCmd::set_has_follow_model() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CameraCmd::clear_has_follow_model() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CameraCmd::clear_follow_model() {
  follow_model_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_follow_model();
}
inline const ::std::string& CameraCmd::follow_model() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.CameraCmd.follow_model)
  return follow_model_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CameraCmd::set_follow_model(const ::std::string& value) {
  set_has_follow_model();
  follow_model_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.CameraCmd.follow_model)
}
inline void CameraCmd::set_follow_model(const char* value) {
  set_has_follow_model();
  follow_model_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.CameraCmd.follow_model)
}
inline void CameraCmd::set_follow_model(const char* value, size_t size) {
  set_has_follow_model();
  follow_model_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.CameraCmd.follow_model)
}
inline ::std::string* CameraCmd::mutable_follow_model() {
  set_has_follow_model();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.CameraCmd.follow_model)
  return follow_model_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CameraCmd::release_follow_model() {
  clear_has_follow_model();
  return follow_model_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CameraCmd::set_allocated_follow_model(::std::string* follow_model) {
  if (follow_model != NULL) {
    set_has_follow_model();
  } else {
    clear_has_follow_model();
  }
  follow_model_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), follow_model);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.CameraCmd.follow_model)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::CameraCmd> CameraCmdPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::CameraCmd const> ConstCameraCmdPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_camera_5fcmd_2eproto__INCLUDED
