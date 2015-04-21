// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gesture.proto

#ifndef PROTOBUF_gesture_2eproto__INCLUDED
#define PROTOBUF_gesture_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_gesture_2eproto();
void protobuf_AssignDesc_gesture_2eproto();
void protobuf_ShutdownFile_gesture_2eproto();

class GestureDescription;
class GestureRecognitionModule;
class GestureRecognitionModules;
class GestureTrigger;

enum GestureDescription_GestureType {
  GestureDescription_GestureType_None = 0,
  GestureDescription_GestureType_Discrete = 1,
  GestureDescription_GestureType_Continuous = 2
};
bool GestureDescription_GestureType_IsValid(int value);
const GestureDescription_GestureType GestureDescription_GestureType_GestureType_MIN = GestureDescription_GestureType_None;
const GestureDescription_GestureType GestureDescription_GestureType_GestureType_MAX = GestureDescription_GestureType_Continuous;
const int GestureDescription_GestureType_GestureType_ARRAYSIZE = GestureDescription_GestureType_GestureType_MAX + 1;

const ::google::protobuf::EnumDescriptor* GestureDescription_GestureType_descriptor();
inline const ::std::string& GestureDescription_GestureType_Name(GestureDescription_GestureType value) {
  return ::google::protobuf::internal::NameOfEnum(
    GestureDescription_GestureType_descriptor(), value);
}
inline bool GestureDescription_GestureType_Parse(
    const ::std::string& name, GestureDescription_GestureType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GestureDescription_GestureType>(
    GestureDescription_GestureType_descriptor(), name, value);
}
// ===================================================================

class GestureDescription : public ::google::protobuf::Message {
 public:
  GestureDescription();
  virtual ~GestureDescription();

  GestureDescription(const GestureDescription& from);

  inline GestureDescription& operator=(const GestureDescription& from) {
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
  static const GestureDescription& default_instance();

  void Swap(GestureDescription* other);

  // implements Message ----------------------------------------------

  inline GestureDescription* New() const { return New(NULL); }

  GestureDescription* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GestureDescription& from);
  void MergeFrom(const GestureDescription& from);
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
  void InternalSwap(GestureDescription* other);
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

  typedef GestureDescription_GestureType GestureType;
  static const GestureType None = GestureDescription_GestureType_None;
  static const GestureType Discrete = GestureDescription_GestureType_Discrete;
  static const GestureType Continuous = GestureDescription_GestureType_Continuous;
  static inline bool GestureType_IsValid(int value) {
    return GestureDescription_GestureType_IsValid(value);
  }
  static const GestureType GestureType_MIN =
    GestureDescription_GestureType_GestureType_MIN;
  static const GestureType GestureType_MAX =
    GestureDescription_GestureType_GestureType_MAX;
  static const int GestureType_ARRAYSIZE =
    GestureDescription_GestureType_GestureType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  GestureType_descriptor() {
    return GestureDescription_GestureType_descriptor();
  }
  static inline const ::std::string& GestureType_Name(GestureType value) {
    return GestureDescription_GestureType_Name(value);
  }
  static inline bool GestureType_Parse(const ::std::string& name,
      GestureType* value) {
    return GestureDescription_GestureType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required .experimot.msgs.GestureDescription.GestureType type = 2;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::experimot::msgs::GestureDescription_GestureType type() const;
  void set_type(::experimot::msgs::GestureDescription_GestureType value);

  // optional bool active = 3;
  bool has_active() const;
  void clear_active();
  static const int kActiveFieldNumber = 3;
  bool active() const;
  void set_active(bool value);

  // optional int32 progress = 4;
  bool has_progress() const;
  void clear_progress();
  static const int kProgressFieldNumber = 4;
  ::google::protobuf::int32 progress() const;
  void set_progress(::google::protobuf::int32 value);

  // optional int32 confidence = 5;
  bool has_confidence() const;
  void clear_confidence();
  static const int kConfidenceFieldNumber = 5;
  ::google::protobuf::int32 confidence() const;
  void set_confidence(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:experimot.msgs.GestureDescription)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_active();
  inline void clear_has_active();
  inline void set_has_progress();
  inline void clear_has_progress();
  inline void set_has_confidence();
  inline void clear_has_confidence();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  int type_;
  bool active_;
  ::google::protobuf::int32 progress_;
  ::google::protobuf::int32 confidence_;
  friend void  protobuf_AddDesc_gesture_2eproto();
  friend void protobuf_AssignDesc_gesture_2eproto();
  friend void protobuf_ShutdownFile_gesture_2eproto();

  void InitAsDefaultInstance();
  static GestureDescription* default_instance_;
};
// -------------------------------------------------------------------

class GestureRecognitionModule : public ::google::protobuf::Message {
 public:
  GestureRecognitionModule();
  virtual ~GestureRecognitionModule();

  GestureRecognitionModule(const GestureRecognitionModule& from);

  inline GestureRecognitionModule& operator=(const GestureRecognitionModule& from) {
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
  static const GestureRecognitionModule& default_instance();

  void Swap(GestureRecognitionModule* other);

  // implements Message ----------------------------------------------

  inline GestureRecognitionModule* New() const { return New(NULL); }

  GestureRecognitionModule* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GestureRecognitionModule& from);
  void MergeFrom(const GestureRecognitionModule& from);
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
  void InternalSwap(GestureRecognitionModule* other);
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

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // repeated .experimot.msgs.GestureDescription motions = 2;
  int motions_size() const;
  void clear_motions();
  static const int kMotionsFieldNumber = 2;
  const ::experimot::msgs::GestureDescription& motions(int index) const;
  ::experimot::msgs::GestureDescription* mutable_motions(int index);
  ::experimot::msgs::GestureDescription* add_motions();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureDescription >&
      motions() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureDescription >*
      mutable_motions();

  // @@protoc_insertion_point(class_scope:experimot.msgs.GestureRecognitionModule)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureDescription > motions_;
  friend void  protobuf_AddDesc_gesture_2eproto();
  friend void protobuf_AssignDesc_gesture_2eproto();
  friend void protobuf_ShutdownFile_gesture_2eproto();

  void InitAsDefaultInstance();
  static GestureRecognitionModule* default_instance_;
};
// -------------------------------------------------------------------

class GestureRecognitionModules : public ::google::protobuf::Message {
 public:
  GestureRecognitionModules();
  virtual ~GestureRecognitionModules();

  GestureRecognitionModules(const GestureRecognitionModules& from);

  inline GestureRecognitionModules& operator=(const GestureRecognitionModules& from) {
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
  static const GestureRecognitionModules& default_instance();

  void Swap(GestureRecognitionModules* other);

  // implements Message ----------------------------------------------

  inline GestureRecognitionModules* New() const { return New(NULL); }

  GestureRecognitionModules* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GestureRecognitionModules& from);
  void MergeFrom(const GestureRecognitionModules& from);
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
  void InternalSwap(GestureRecognitionModules* other);
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

  // repeated .experimot.msgs.GestureRecognitionModule modules = 1;
  int modules_size() const;
  void clear_modules();
  static const int kModulesFieldNumber = 1;
  const ::experimot::msgs::GestureRecognitionModule& modules(int index) const;
  ::experimot::msgs::GestureRecognitionModule* mutable_modules(int index);
  ::experimot::msgs::GestureRecognitionModule* add_modules();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureRecognitionModule >&
      modules() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureRecognitionModule >*
      mutable_modules();

  // @@protoc_insertion_point(class_scope:experimot.msgs.GestureRecognitionModules)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureRecognitionModule > modules_;
  friend void  protobuf_AddDesc_gesture_2eproto();
  friend void protobuf_AssignDesc_gesture_2eproto();
  friend void protobuf_ShutdownFile_gesture_2eproto();

  void InitAsDefaultInstance();
  static GestureRecognitionModules* default_instance_;
};
// -------------------------------------------------------------------

class GestureTrigger : public ::google::protobuf::Message {
 public:
  GestureTrigger();
  virtual ~GestureTrigger();

  GestureTrigger(const GestureTrigger& from);

  inline GestureTrigger& operator=(const GestureTrigger& from) {
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
  static const GestureTrigger& default_instance();

  void Swap(GestureTrigger* other);

  // implements Message ----------------------------------------------

  inline GestureTrigger* New() const { return New(NULL); }

  GestureTrigger* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GestureTrigger& from);
  void MergeFrom(const GestureTrigger& from);
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
  void InternalSwap(GestureTrigger* other);
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

  // required int32 id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // required .experimot.msgs.GestureDescription motion = 2;
  bool has_motion() const;
  void clear_motion();
  static const int kMotionFieldNumber = 2;
  const ::experimot::msgs::GestureDescription& motion() const;
  ::experimot::msgs::GestureDescription* mutable_motion();
  ::experimot::msgs::GestureDescription* release_motion();
  void set_allocated_motion(::experimot::msgs::GestureDescription* motion);

  // @@protoc_insertion_point(class_scope:experimot.msgs.GestureTrigger)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_motion();
  inline void clear_has_motion();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::experimot::msgs::GestureDescription* motion_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_gesture_2eproto();
  friend void protobuf_AssignDesc_gesture_2eproto();
  friend void protobuf_ShutdownFile_gesture_2eproto();

  void InitAsDefaultInstance();
  static GestureTrigger* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// GestureDescription

// required string name = 1;
inline bool GestureDescription::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GestureDescription::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GestureDescription::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GestureDescription::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& GestureDescription::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureDescription.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GestureDescription::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureDescription.name)
}
inline void GestureDescription::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.GestureDescription.name)
}
inline void GestureDescription::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.GestureDescription.name)
}
inline ::std::string* GestureDescription::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.GestureDescription.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GestureDescription::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GestureDescription::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.GestureDescription.name)
}

// required .experimot.msgs.GestureDescription.GestureType type = 2;
inline bool GestureDescription::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GestureDescription::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GestureDescription::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GestureDescription::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::experimot::msgs::GestureDescription_GestureType GestureDescription::type() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureDescription.type)
  return static_cast< ::experimot::msgs::GestureDescription_GestureType >(type_);
}
inline void GestureDescription::set_type(::experimot::msgs::GestureDescription_GestureType value) {
  assert(::experimot::msgs::GestureDescription_GestureType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureDescription.type)
}

// optional bool active = 3;
inline bool GestureDescription::has_active() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GestureDescription::set_has_active() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GestureDescription::clear_has_active() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GestureDescription::clear_active() {
  active_ = false;
  clear_has_active();
}
inline bool GestureDescription::active() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureDescription.active)
  return active_;
}
inline void GestureDescription::set_active(bool value) {
  set_has_active();
  active_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureDescription.active)
}

// optional int32 progress = 4;
inline bool GestureDescription::has_progress() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void GestureDescription::set_has_progress() {
  _has_bits_[0] |= 0x00000008u;
}
inline void GestureDescription::clear_has_progress() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void GestureDescription::clear_progress() {
  progress_ = 0;
  clear_has_progress();
}
inline ::google::protobuf::int32 GestureDescription::progress() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureDescription.progress)
  return progress_;
}
inline void GestureDescription::set_progress(::google::protobuf::int32 value) {
  set_has_progress();
  progress_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureDescription.progress)
}

// optional int32 confidence = 5;
inline bool GestureDescription::has_confidence() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void GestureDescription::set_has_confidence() {
  _has_bits_[0] |= 0x00000010u;
}
inline void GestureDescription::clear_has_confidence() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void GestureDescription::clear_confidence() {
  confidence_ = 0;
  clear_has_confidence();
}
inline ::google::protobuf::int32 GestureDescription::confidence() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureDescription.confidence)
  return confidence_;
}
inline void GestureDescription::set_confidence(::google::protobuf::int32 value) {
  set_has_confidence();
  confidence_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureDescription.confidence)
}

// -------------------------------------------------------------------

// GestureRecognitionModule

// required string name = 1;
inline bool GestureRecognitionModule::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GestureRecognitionModule::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GestureRecognitionModule::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GestureRecognitionModule::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& GestureRecognitionModule::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureRecognitionModule.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GestureRecognitionModule::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureRecognitionModule.name)
}
inline void GestureRecognitionModule::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.GestureRecognitionModule.name)
}
inline void GestureRecognitionModule::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.GestureRecognitionModule.name)
}
inline ::std::string* GestureRecognitionModule::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.GestureRecognitionModule.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GestureRecognitionModule::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GestureRecognitionModule::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.GestureRecognitionModule.name)
}

// repeated .experimot.msgs.GestureDescription motions = 2;
inline int GestureRecognitionModule::motions_size() const {
  return motions_.size();
}
inline void GestureRecognitionModule::clear_motions() {
  motions_.Clear();
}
inline const ::experimot::msgs::GestureDescription& GestureRecognitionModule::motions(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureRecognitionModule.motions)
  return motions_.Get(index);
}
inline ::experimot::msgs::GestureDescription* GestureRecognitionModule::mutable_motions(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.GestureRecognitionModule.motions)
  return motions_.Mutable(index);
}
inline ::experimot::msgs::GestureDescription* GestureRecognitionModule::add_motions() {
  // @@protoc_insertion_point(field_add:experimot.msgs.GestureRecognitionModule.motions)
  return motions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureDescription >&
GestureRecognitionModule::motions() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.GestureRecognitionModule.motions)
  return motions_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureDescription >*
GestureRecognitionModule::mutable_motions() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.GestureRecognitionModule.motions)
  return &motions_;
}

// -------------------------------------------------------------------

// GestureRecognitionModules

// repeated .experimot.msgs.GestureRecognitionModule modules = 1;
inline int GestureRecognitionModules::modules_size() const {
  return modules_.size();
}
inline void GestureRecognitionModules::clear_modules() {
  modules_.Clear();
}
inline const ::experimot::msgs::GestureRecognitionModule& GestureRecognitionModules::modules(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureRecognitionModules.modules)
  return modules_.Get(index);
}
inline ::experimot::msgs::GestureRecognitionModule* GestureRecognitionModules::mutable_modules(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.GestureRecognitionModules.modules)
  return modules_.Mutable(index);
}
inline ::experimot::msgs::GestureRecognitionModule* GestureRecognitionModules::add_modules() {
  // @@protoc_insertion_point(field_add:experimot.msgs.GestureRecognitionModules.modules)
  return modules_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureRecognitionModule >&
GestureRecognitionModules::modules() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.GestureRecognitionModules.modules)
  return modules_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::GestureRecognitionModule >*
GestureRecognitionModules::mutable_modules() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.GestureRecognitionModules.modules)
  return &modules_;
}

// -------------------------------------------------------------------

// GestureTrigger

// required int32 id = 1;
inline bool GestureTrigger::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GestureTrigger::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GestureTrigger::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GestureTrigger::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 GestureTrigger::id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureTrigger.id)
  return id_;
}
inline void GestureTrigger::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.GestureTrigger.id)
}

// required .experimot.msgs.GestureDescription motion = 2;
inline bool GestureTrigger::has_motion() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GestureTrigger::set_has_motion() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GestureTrigger::clear_has_motion() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GestureTrigger::clear_motion() {
  if (motion_ != NULL) motion_->::experimot::msgs::GestureDescription::Clear();
  clear_has_motion();
}
inline const ::experimot::msgs::GestureDescription& GestureTrigger::motion() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.GestureTrigger.motion)
  return motion_ != NULL ? *motion_ : *default_instance_->motion_;
}
inline ::experimot::msgs::GestureDescription* GestureTrigger::mutable_motion() {
  set_has_motion();
  if (motion_ == NULL) {
    motion_ = new ::experimot::msgs::GestureDescription;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.GestureTrigger.motion)
  return motion_;
}
inline ::experimot::msgs::GestureDescription* GestureTrigger::release_motion() {
  clear_has_motion();
  ::experimot::msgs::GestureDescription* temp = motion_;
  motion_ = NULL;
  return temp;
}
inline void GestureTrigger::set_allocated_motion(::experimot::msgs::GestureDescription* motion) {
  delete motion_;
  motion_ = motion;
  if (motion) {
    set_has_motion();
  } else {
    clear_has_motion();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.GestureTrigger.motion)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::GestureDescription> GestureDescriptionPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::experimot::msgs::GestureDescription_GestureType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::experimot::msgs::GestureDescription_GestureType>() {
  return ::experimot::msgs::GestureDescription_GestureType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

typedef const boost::shared_ptr<experimot::msgs::GestureDescription const> ConstGestureDescriptionPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_gesture_2eproto__INCLUDED
