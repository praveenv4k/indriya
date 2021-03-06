// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: model_configuration.proto

#ifndef PROTOBUF_model_5fconfiguration_2eproto__INCLUDED
#define PROTOBUF_model_5fconfiguration_2eproto__INCLUDED

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
#include "time.pb.h"
#include "pose.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace Indriya {
namespace Core {
namespace Msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_model_5fconfiguration_2eproto();
void protobuf_AssignDesc_model_5fconfiguration_2eproto();
void protobuf_ShutdownFile_model_5fconfiguration_2eproto();

class ModelConfiguration;

// ===================================================================

class ModelConfiguration : public ::google::protobuf::Message {
 public:
  ModelConfiguration();
  virtual ~ModelConfiguration();

  ModelConfiguration(const ModelConfiguration& from);

  inline ModelConfiguration& operator=(const ModelConfiguration& from) {
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
  static const ModelConfiguration& default_instance();

  void Swap(ModelConfiguration* other);

  // implements Message ----------------------------------------------

  inline ModelConfiguration* New() const { return New(NULL); }

  ModelConfiguration* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ModelConfiguration& from);
  void MergeFrom(const ModelConfiguration& from);
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
  void InternalSwap(ModelConfiguration* other);
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

  // required .Indriya.Core.Msgs.Time time = 1;
  bool has_time() const;
  void clear_time();
  static const int kTimeFieldNumber = 1;
  const ::Indriya::Core::Msgs::Time& time() const;
  ::Indriya::Core::Msgs::Time* mutable_time();
  ::Indriya::Core::Msgs::Time* release_time();
  void set_allocated_time(::Indriya::Core::Msgs::Time* time);

  // repeated string joint_names = 2;
  int joint_names_size() const;
  void clear_joint_names();
  static const int kJointNamesFieldNumber = 2;
  const ::std::string& joint_names(int index) const;
  ::std::string* mutable_joint_names(int index);
  void set_joint_names(int index, const ::std::string& value);
  void set_joint_names(int index, const char* value);
  void set_joint_names(int index, const char* value, size_t size);
  ::std::string* add_joint_names();
  void add_joint_names(const ::std::string& value);
  void add_joint_names(const char* value);
  void add_joint_names(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& joint_names() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_joint_names();

  // repeated double joint_positions = 3;
  int joint_positions_size() const;
  void clear_joint_positions();
  static const int kJointPositionsFieldNumber = 3;
  double joint_positions(int index) const;
  void set_joint_positions(int index, double value);
  void add_joint_positions(double value);
  const ::google::protobuf::RepeatedField< double >&
      joint_positions() const;
  ::google::protobuf::RepeatedField< double >*
      mutable_joint_positions();

  // optional .Indriya.Core.Msgs.Pose pose = 4;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 4;
  const ::Indriya::Core::Msgs::Pose& pose() const;
  ::Indriya::Core::Msgs::Pose* mutable_pose();
  ::Indriya::Core::Msgs::Pose* release_pose();
  void set_allocated_pose(::Indriya::Core::Msgs::Pose* pose);

  // optional string link_name = 5;
  bool has_link_name() const;
  void clear_link_name();
  static const int kLinkNameFieldNumber = 5;
  const ::std::string& link_name() const;
  void set_link_name(const ::std::string& value);
  void set_link_name(const char* value);
  void set_link_name(const char* value, size_t size);
  ::std::string* mutable_link_name();
  ::std::string* release_link_name();
  void set_allocated_link_name(::std::string* link_name);

  // @@protoc_insertion_point(class_scope:Indriya.Core.Msgs.ModelConfiguration)
 private:
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_pose();
  inline void clear_has_pose();
  inline void set_has_link_name();
  inline void clear_has_link_name();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::Indriya::Core::Msgs::Time* time_;
  ::google::protobuf::RepeatedPtrField< ::std::string> joint_names_;
  ::google::protobuf::RepeatedField< double > joint_positions_;
  ::Indriya::Core::Msgs::Pose* pose_;
  ::google::protobuf::internal::ArenaStringPtr link_name_;
  friend void  protobuf_AddDesc_model_5fconfiguration_2eproto();
  friend void protobuf_AssignDesc_model_5fconfiguration_2eproto();
  friend void protobuf_ShutdownFile_model_5fconfiguration_2eproto();

  void InitAsDefaultInstance();
  static ModelConfiguration* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ModelConfiguration

// required .Indriya.Core.Msgs.Time time = 1;
inline bool ModelConfiguration::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ModelConfiguration::set_has_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ModelConfiguration::clear_has_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ModelConfiguration::clear_time() {
  if (time_ != NULL) time_->::Indriya::Core::Msgs::Time::Clear();
  clear_has_time();
}
inline const ::Indriya::Core::Msgs::Time& ModelConfiguration::time() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.ModelConfiguration.time)
  return time_ != NULL ? *time_ : *default_instance_->time_;
}
inline ::Indriya::Core::Msgs::Time* ModelConfiguration::mutable_time() {
  set_has_time();
  if (time_ == NULL) {
    time_ = new ::Indriya::Core::Msgs::Time;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.ModelConfiguration.time)
  return time_;
}
inline ::Indriya::Core::Msgs::Time* ModelConfiguration::release_time() {
  clear_has_time();
  ::Indriya::Core::Msgs::Time* temp = time_;
  time_ = NULL;
  return temp;
}
inline void ModelConfiguration::set_allocated_time(::Indriya::Core::Msgs::Time* time) {
  delete time_;
  time_ = time;
  if (time) {
    set_has_time();
  } else {
    clear_has_time();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.ModelConfiguration.time)
}

// repeated string joint_names = 2;
inline int ModelConfiguration::joint_names_size() const {
  return joint_names_.size();
}
inline void ModelConfiguration::clear_joint_names() {
  joint_names_.Clear();
}
inline const ::std::string& ModelConfiguration::joint_names(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.ModelConfiguration.joint_names)
  return joint_names_.Get(index);
}
inline ::std::string* ModelConfiguration::mutable_joint_names(int index) {
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.ModelConfiguration.joint_names)
  return joint_names_.Mutable(index);
}
inline void ModelConfiguration::set_joint_names(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.ModelConfiguration.joint_names)
  joint_names_.Mutable(index)->assign(value);
}
inline void ModelConfiguration::set_joint_names(int index, const char* value) {
  joint_names_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:Indriya.Core.Msgs.ModelConfiguration.joint_names)
}
inline void ModelConfiguration::set_joint_names(int index, const char* value, size_t size) {
  joint_names_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Indriya.Core.Msgs.ModelConfiguration.joint_names)
}
inline ::std::string* ModelConfiguration::add_joint_names() {
  return joint_names_.Add();
}
inline void ModelConfiguration::add_joint_names(const ::std::string& value) {
  joint_names_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.ModelConfiguration.joint_names)
}
inline void ModelConfiguration::add_joint_names(const char* value) {
  joint_names_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:Indriya.Core.Msgs.ModelConfiguration.joint_names)
}
inline void ModelConfiguration::add_joint_names(const char* value, size_t size) {
  joint_names_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:Indriya.Core.Msgs.ModelConfiguration.joint_names)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
ModelConfiguration::joint_names() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.ModelConfiguration.joint_names)
  return joint_names_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
ModelConfiguration::mutable_joint_names() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.ModelConfiguration.joint_names)
  return &joint_names_;
}

// repeated double joint_positions = 3;
inline int ModelConfiguration::joint_positions_size() const {
  return joint_positions_.size();
}
inline void ModelConfiguration::clear_joint_positions() {
  joint_positions_.Clear();
}
inline double ModelConfiguration::joint_positions(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.ModelConfiguration.joint_positions)
  return joint_positions_.Get(index);
}
inline void ModelConfiguration::set_joint_positions(int index, double value) {
  joint_positions_.Set(index, value);
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.ModelConfiguration.joint_positions)
}
inline void ModelConfiguration::add_joint_positions(double value) {
  joint_positions_.Add(value);
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.ModelConfiguration.joint_positions)
}
inline const ::google::protobuf::RepeatedField< double >&
ModelConfiguration::joint_positions() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.ModelConfiguration.joint_positions)
  return joint_positions_;
}
inline ::google::protobuf::RepeatedField< double >*
ModelConfiguration::mutable_joint_positions() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.ModelConfiguration.joint_positions)
  return &joint_positions_;
}

// optional .Indriya.Core.Msgs.Pose pose = 4;
inline bool ModelConfiguration::has_pose() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ModelConfiguration::set_has_pose() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ModelConfiguration::clear_has_pose() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ModelConfiguration::clear_pose() {
  if (pose_ != NULL) pose_->::Indriya::Core::Msgs::Pose::Clear();
  clear_has_pose();
}
inline const ::Indriya::Core::Msgs::Pose& ModelConfiguration::pose() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.ModelConfiguration.pose)
  return pose_ != NULL ? *pose_ : *default_instance_->pose_;
}
inline ::Indriya::Core::Msgs::Pose* ModelConfiguration::mutable_pose() {
  set_has_pose();
  if (pose_ == NULL) {
    pose_ = new ::Indriya::Core::Msgs::Pose;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.ModelConfiguration.pose)
  return pose_;
}
inline ::Indriya::Core::Msgs::Pose* ModelConfiguration::release_pose() {
  clear_has_pose();
  ::Indriya::Core::Msgs::Pose* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void ModelConfiguration::set_allocated_pose(::Indriya::Core::Msgs::Pose* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    set_has_pose();
  } else {
    clear_has_pose();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.ModelConfiguration.pose)
}

// optional string link_name = 5;
inline bool ModelConfiguration::has_link_name() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ModelConfiguration::set_has_link_name() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ModelConfiguration::clear_has_link_name() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ModelConfiguration::clear_link_name() {
  link_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_link_name();
}
inline const ::std::string& ModelConfiguration::link_name() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.ModelConfiguration.link_name)
  return link_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ModelConfiguration::set_link_name(const ::std::string& value) {
  set_has_link_name();
  link_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.ModelConfiguration.link_name)
}
inline void ModelConfiguration::set_link_name(const char* value) {
  set_has_link_name();
  link_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Indriya.Core.Msgs.ModelConfiguration.link_name)
}
inline void ModelConfiguration::set_link_name(const char* value, size_t size) {
  set_has_link_name();
  link_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Indriya.Core.Msgs.ModelConfiguration.link_name)
}
inline ::std::string* ModelConfiguration::mutable_link_name() {
  set_has_link_name();
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.ModelConfiguration.link_name)
  return link_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ModelConfiguration::release_link_name() {
  clear_has_link_name();
  return link_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ModelConfiguration::set_allocated_link_name(::std::string* link_name) {
  if (link_name != NULL) {
    set_has_link_name();
  } else {
    clear_has_link_name();
  }
  link_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), link_name);
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.ModelConfiguration.link_name)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<Indriya::Core::Msgs::ModelConfiguration> ModelConfigurationPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace Msgs
}  // namespace Core
}  // namespace Indriya

typedef const boost::shared_ptr<Indriya::Core::Msgs::ModelConfiguration const> ConstModelConfigurationPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_model_5fconfiguration_2eproto__INCLUDED
