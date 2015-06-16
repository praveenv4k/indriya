// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: voice.proto

#ifndef PROTOBUF_voice_2eproto__INCLUDED
#define PROTOBUF_voice_2eproto__INCLUDED

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
#include "param.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_voice_2eproto();
void protobuf_AssignDesc_voice_2eproto();
void protobuf_ShutdownFile_voice_2eproto();

class VoiceCommandDescription;
class VoiceRecognitionModule;
class VoiceRecognitionModules;

// ===================================================================

class VoiceCommandDescription : public ::google::protobuf::Message {
 public:
  VoiceCommandDescription();
  virtual ~VoiceCommandDescription();

  VoiceCommandDescription(const VoiceCommandDescription& from);

  inline VoiceCommandDescription& operator=(const VoiceCommandDescription& from) {
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
  static const VoiceCommandDescription& default_instance();

  void Swap(VoiceCommandDescription* other);

  // implements Message ----------------------------------------------

  inline VoiceCommandDescription* New() const { return New(NULL); }

  VoiceCommandDescription* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VoiceCommandDescription& from);
  void MergeFrom(const VoiceCommandDescription& from);
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
  void InternalSwap(VoiceCommandDescription* other);
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

  // required string command = 1;
  bool has_command() const;
  void clear_command();
  static const int kCommandFieldNumber = 1;
  const ::std::string& command() const;
  void set_command(const ::std::string& value);
  void set_command(const char* value);
  void set_command(const char* value, size_t size);
  ::std::string* mutable_command();
  ::std::string* release_command();
  void set_allocated_command(::std::string* command);

  // optional bool active = 2;
  bool has_active() const;
  void clear_active();
  static const int kActiveFieldNumber = 2;
  bool active() const;
  void set_active(bool value);

  // optional int32 confidence = 3;
  bool has_confidence() const;
  void clear_confidence();
  static const int kConfidenceFieldNumber = 3;
  ::google::protobuf::int32 confidence() const;
  void set_confidence(::google::protobuf::int32 value);

  // optional string language = 4;
  bool has_language() const;
  void clear_language();
  static const int kLanguageFieldNumber = 4;
  const ::std::string& language() const;
  void set_language(const ::std::string& value);
  void set_language(const char* value);
  void set_language(const char* value, size_t size);
  ::std::string* mutable_language();
  ::std::string* release_language();
  void set_allocated_language(::std::string* language);

  // @@protoc_insertion_point(class_scope:experimot.msgs.VoiceCommandDescription)
 private:
  inline void set_has_command();
  inline void clear_has_command();
  inline void set_has_active();
  inline void clear_has_active();
  inline void set_has_confidence();
  inline void clear_has_confidence();
  inline void set_has_language();
  inline void clear_has_language();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr command_;
  bool active_;
  ::google::protobuf::int32 confidence_;
  ::google::protobuf::internal::ArenaStringPtr language_;
  friend void  protobuf_AddDesc_voice_2eproto();
  friend void protobuf_AssignDesc_voice_2eproto();
  friend void protobuf_ShutdownFile_voice_2eproto();

  void InitAsDefaultInstance();
  static VoiceCommandDescription* default_instance_;
};
// -------------------------------------------------------------------

class VoiceRecognitionModule : public ::google::protobuf::Message {
 public:
  VoiceRecognitionModule();
  virtual ~VoiceRecognitionModule();

  VoiceRecognitionModule(const VoiceRecognitionModule& from);

  inline VoiceRecognitionModule& operator=(const VoiceRecognitionModule& from) {
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
  static const VoiceRecognitionModule& default_instance();

  void Swap(VoiceRecognitionModule* other);

  // implements Message ----------------------------------------------

  inline VoiceRecognitionModule* New() const { return New(NULL); }

  VoiceRecognitionModule* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VoiceRecognitionModule& from);
  void MergeFrom(const VoiceRecognitionModule& from);
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
  void InternalSwap(VoiceRecognitionModule* other);
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

  // repeated .experimot.msgs.Param params = 2;
  int params_size() const;
  void clear_params();
  static const int kParamsFieldNumber = 2;
  const ::experimot::msgs::Param& params(int index) const;
  ::experimot::msgs::Param* mutable_params(int index);
  ::experimot::msgs::Param* add_params();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Param >&
      params() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Param >*
      mutable_params();

  // repeated .experimot.msgs.VoiceCommandDescription commands = 3;
  int commands_size() const;
  void clear_commands();
  static const int kCommandsFieldNumber = 3;
  const ::experimot::msgs::VoiceCommandDescription& commands(int index) const;
  ::experimot::msgs::VoiceCommandDescription* mutable_commands(int index);
  ::experimot::msgs::VoiceCommandDescription* add_commands();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceCommandDescription >&
      commands() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceCommandDescription >*
      mutable_commands();

  // @@protoc_insertion_point(class_scope:experimot.msgs.VoiceRecognitionModule)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Param > params_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceCommandDescription > commands_;
  friend void  protobuf_AddDesc_voice_2eproto();
  friend void protobuf_AssignDesc_voice_2eproto();
  friend void protobuf_ShutdownFile_voice_2eproto();

  void InitAsDefaultInstance();
  static VoiceRecognitionModule* default_instance_;
};
// -------------------------------------------------------------------

class VoiceRecognitionModules : public ::google::protobuf::Message {
 public:
  VoiceRecognitionModules();
  virtual ~VoiceRecognitionModules();

  VoiceRecognitionModules(const VoiceRecognitionModules& from);

  inline VoiceRecognitionModules& operator=(const VoiceRecognitionModules& from) {
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
  static const VoiceRecognitionModules& default_instance();

  void Swap(VoiceRecognitionModules* other);

  // implements Message ----------------------------------------------

  inline VoiceRecognitionModules* New() const { return New(NULL); }

  VoiceRecognitionModules* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VoiceRecognitionModules& from);
  void MergeFrom(const VoiceRecognitionModules& from);
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
  void InternalSwap(VoiceRecognitionModules* other);
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

  // repeated .experimot.msgs.VoiceRecognitionModule modules = 1;
  int modules_size() const;
  void clear_modules();
  static const int kModulesFieldNumber = 1;
  const ::experimot::msgs::VoiceRecognitionModule& modules(int index) const;
  ::experimot::msgs::VoiceRecognitionModule* mutable_modules(int index);
  ::experimot::msgs::VoiceRecognitionModule* add_modules();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceRecognitionModule >&
      modules() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceRecognitionModule >*
      mutable_modules();

  // @@protoc_insertion_point(class_scope:experimot.msgs.VoiceRecognitionModules)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceRecognitionModule > modules_;
  friend void  protobuf_AddDesc_voice_2eproto();
  friend void protobuf_AssignDesc_voice_2eproto();
  friend void protobuf_ShutdownFile_voice_2eproto();

  void InitAsDefaultInstance();
  static VoiceRecognitionModules* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// VoiceCommandDescription

// required string command = 1;
inline bool VoiceCommandDescription::has_command() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void VoiceCommandDescription::set_has_command() {
  _has_bits_[0] |= 0x00000001u;
}
inline void VoiceCommandDescription::clear_has_command() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void VoiceCommandDescription::clear_command() {
  command_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_command();
}
inline const ::std::string& VoiceCommandDescription::command() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceCommandDescription.command)
  return command_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceCommandDescription::set_command(const ::std::string& value) {
  set_has_command();
  command_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.VoiceCommandDescription.command)
}
inline void VoiceCommandDescription::set_command(const char* value) {
  set_has_command();
  command_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.VoiceCommandDescription.command)
}
inline void VoiceCommandDescription::set_command(const char* value, size_t size) {
  set_has_command();
  command_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.VoiceCommandDescription.command)
}
inline ::std::string* VoiceCommandDescription::mutable_command() {
  set_has_command();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceCommandDescription.command)
  return command_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* VoiceCommandDescription::release_command() {
  clear_has_command();
  return command_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceCommandDescription::set_allocated_command(::std::string* command) {
  if (command != NULL) {
    set_has_command();
  } else {
    clear_has_command();
  }
  command_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), command);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.VoiceCommandDescription.command)
}

// optional bool active = 2;
inline bool VoiceCommandDescription::has_active() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void VoiceCommandDescription::set_has_active() {
  _has_bits_[0] |= 0x00000002u;
}
inline void VoiceCommandDescription::clear_has_active() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void VoiceCommandDescription::clear_active() {
  active_ = false;
  clear_has_active();
}
inline bool VoiceCommandDescription::active() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceCommandDescription.active)
  return active_;
}
inline void VoiceCommandDescription::set_active(bool value) {
  set_has_active();
  active_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.VoiceCommandDescription.active)
}

// optional int32 confidence = 3;
inline bool VoiceCommandDescription::has_confidence() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void VoiceCommandDescription::set_has_confidence() {
  _has_bits_[0] |= 0x00000004u;
}
inline void VoiceCommandDescription::clear_has_confidence() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void VoiceCommandDescription::clear_confidence() {
  confidence_ = 0;
  clear_has_confidence();
}
inline ::google::protobuf::int32 VoiceCommandDescription::confidence() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceCommandDescription.confidence)
  return confidence_;
}
inline void VoiceCommandDescription::set_confidence(::google::protobuf::int32 value) {
  set_has_confidence();
  confidence_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.VoiceCommandDescription.confidence)
}

// optional string language = 4;
inline bool VoiceCommandDescription::has_language() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void VoiceCommandDescription::set_has_language() {
  _has_bits_[0] |= 0x00000008u;
}
inline void VoiceCommandDescription::clear_has_language() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void VoiceCommandDescription::clear_language() {
  language_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_language();
}
inline const ::std::string& VoiceCommandDescription::language() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceCommandDescription.language)
  return language_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceCommandDescription::set_language(const ::std::string& value) {
  set_has_language();
  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.VoiceCommandDescription.language)
}
inline void VoiceCommandDescription::set_language(const char* value) {
  set_has_language();
  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.VoiceCommandDescription.language)
}
inline void VoiceCommandDescription::set_language(const char* value, size_t size) {
  set_has_language();
  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.VoiceCommandDescription.language)
}
inline ::std::string* VoiceCommandDescription::mutable_language() {
  set_has_language();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceCommandDescription.language)
  return language_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* VoiceCommandDescription::release_language() {
  clear_has_language();
  return language_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceCommandDescription::set_allocated_language(::std::string* language) {
  if (language != NULL) {
    set_has_language();
  } else {
    clear_has_language();
  }
  language_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), language);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.VoiceCommandDescription.language)
}

// -------------------------------------------------------------------

// VoiceRecognitionModule

// required string name = 1;
inline bool VoiceRecognitionModule::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void VoiceRecognitionModule::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void VoiceRecognitionModule::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void VoiceRecognitionModule::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& VoiceRecognitionModule::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceRecognitionModule.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceRecognitionModule::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.VoiceRecognitionModule.name)
}
inline void VoiceRecognitionModule::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.VoiceRecognitionModule.name)
}
inline void VoiceRecognitionModule::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.VoiceRecognitionModule.name)
}
inline ::std::string* VoiceRecognitionModule::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceRecognitionModule.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* VoiceRecognitionModule::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VoiceRecognitionModule::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.VoiceRecognitionModule.name)
}

// repeated .experimot.msgs.Param params = 2;
inline int VoiceRecognitionModule::params_size() const {
  return params_.size();
}
inline void VoiceRecognitionModule::clear_params() {
  params_.Clear();
}
inline const ::experimot::msgs::Param& VoiceRecognitionModule::params(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceRecognitionModule.params)
  return params_.Get(index);
}
inline ::experimot::msgs::Param* VoiceRecognitionModule::mutable_params(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceRecognitionModule.params)
  return params_.Mutable(index);
}
inline ::experimot::msgs::Param* VoiceRecognitionModule::add_params() {
  // @@protoc_insertion_point(field_add:experimot.msgs.VoiceRecognitionModule.params)
  return params_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Param >&
VoiceRecognitionModule::params() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.VoiceRecognitionModule.params)
  return params_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Param >*
VoiceRecognitionModule::mutable_params() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.VoiceRecognitionModule.params)
  return &params_;
}

// repeated .experimot.msgs.VoiceCommandDescription commands = 3;
inline int VoiceRecognitionModule::commands_size() const {
  return commands_.size();
}
inline void VoiceRecognitionModule::clear_commands() {
  commands_.Clear();
}
inline const ::experimot::msgs::VoiceCommandDescription& VoiceRecognitionModule::commands(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceRecognitionModule.commands)
  return commands_.Get(index);
}
inline ::experimot::msgs::VoiceCommandDescription* VoiceRecognitionModule::mutable_commands(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceRecognitionModule.commands)
  return commands_.Mutable(index);
}
inline ::experimot::msgs::VoiceCommandDescription* VoiceRecognitionModule::add_commands() {
  // @@protoc_insertion_point(field_add:experimot.msgs.VoiceRecognitionModule.commands)
  return commands_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceCommandDescription >&
VoiceRecognitionModule::commands() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.VoiceRecognitionModule.commands)
  return commands_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceCommandDescription >*
VoiceRecognitionModule::mutable_commands() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.VoiceRecognitionModule.commands)
  return &commands_;
}

// -------------------------------------------------------------------

// VoiceRecognitionModules

// repeated .experimot.msgs.VoiceRecognitionModule modules = 1;
inline int VoiceRecognitionModules::modules_size() const {
  return modules_.size();
}
inline void VoiceRecognitionModules::clear_modules() {
  modules_.Clear();
}
inline const ::experimot::msgs::VoiceRecognitionModule& VoiceRecognitionModules::modules(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.VoiceRecognitionModules.modules)
  return modules_.Get(index);
}
inline ::experimot::msgs::VoiceRecognitionModule* VoiceRecognitionModules::mutable_modules(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.VoiceRecognitionModules.modules)
  return modules_.Mutable(index);
}
inline ::experimot::msgs::VoiceRecognitionModule* VoiceRecognitionModules::add_modules() {
  // @@protoc_insertion_point(field_add:experimot.msgs.VoiceRecognitionModules.modules)
  return modules_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceRecognitionModule >&
VoiceRecognitionModules::modules() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.VoiceRecognitionModules.modules)
  return modules_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::VoiceRecognitionModule >*
VoiceRecognitionModules::mutable_modules() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.VoiceRecognitionModules.modules)
  return &modules_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::VoiceCommandDescription> VoiceCommandDescriptionPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::VoiceCommandDescription const> ConstVoiceCommandDescriptionPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_voice_2eproto__INCLUDED
