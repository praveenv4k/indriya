// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sensor.proto

#ifndef PROTOBUF_sensor_2eproto__INCLUDED
#define PROTOBUF_sensor_2eproto__INCLUDED

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
#include "pose.pb.h"
#include "camerasensor.pb.h"
#include "raysensor.pb.h"
#include "contactsensor.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_sensor_2eproto();
void protobuf_AssignDesc_sensor_2eproto();
void protobuf_ShutdownFile_sensor_2eproto();

class Sensor;

// ===================================================================

class Sensor : public ::google::protobuf::Message {
 public:
  Sensor();
  virtual ~Sensor();

  Sensor(const Sensor& from);

  inline Sensor& operator=(const Sensor& from) {
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
  static const Sensor& default_instance();

  void Swap(Sensor* other);

  // implements Message ----------------------------------------------

  inline Sensor* New() const { return New(NULL); }

  Sensor* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Sensor& from);
  void MergeFrom(const Sensor& from);
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
  void InternalSwap(Sensor* other);
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

  // optional uint32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // required string parent = 3;
  bool has_parent() const;
  void clear_parent();
  static const int kParentFieldNumber = 3;
  const ::std::string& parent() const;
  void set_parent(const ::std::string& value);
  void set_parent(const char* value);
  void set_parent(const char* value, size_t size);
  ::std::string* mutable_parent();
  ::std::string* release_parent();
  void set_allocated_parent(::std::string* parent);

  // required uint32 parent_id = 4;
  bool has_parent_id() const;
  void clear_parent_id();
  static const int kParentIdFieldNumber = 4;
  ::google::protobuf::uint32 parent_id() const;
  void set_parent_id(::google::protobuf::uint32 value);

  // required string type = 5;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 5;
  const ::std::string& type() const;
  void set_type(const ::std::string& value);
  void set_type(const char* value);
  void set_type(const char* value, size_t size);
  ::std::string* mutable_type();
  ::std::string* release_type();
  void set_allocated_type(::std::string* type);

  // optional bool always_on = 6;
  bool has_always_on() const;
  void clear_always_on();
  static const int kAlwaysOnFieldNumber = 6;
  bool always_on() const;
  void set_always_on(bool value);

  // optional double update_rate = 7;
  bool has_update_rate() const;
  void clear_update_rate();
  static const int kUpdateRateFieldNumber = 7;
  double update_rate() const;
  void set_update_rate(double value);

  // optional .experimot.msgs.Pose pose = 8;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 8;
  const ::experimot::msgs::Pose& pose() const;
  ::experimot::msgs::Pose* mutable_pose();
  ::experimot::msgs::Pose* release_pose();
  void set_allocated_pose(::experimot::msgs::Pose* pose);

  // optional .experimot.msgs.CameraSensor camera = 9;
  bool has_camera() const;
  void clear_camera();
  static const int kCameraFieldNumber = 9;
  const ::experimot::msgs::CameraSensor& camera() const;
  ::experimot::msgs::CameraSensor* mutable_camera();
  ::experimot::msgs::CameraSensor* release_camera();
  void set_allocated_camera(::experimot::msgs::CameraSensor* camera);

  // optional .experimot.msgs.RaySensor ray = 10;
  bool has_ray() const;
  void clear_ray();
  static const int kRayFieldNumber = 10;
  const ::experimot::msgs::RaySensor& ray() const;
  ::experimot::msgs::RaySensor* mutable_ray();
  ::experimot::msgs::RaySensor* release_ray();
  void set_allocated_ray(::experimot::msgs::RaySensor* ray);

  // optional .experimot.msgs.ContactSensor contact = 11;
  bool has_contact() const;
  void clear_contact();
  static const int kContactFieldNumber = 11;
  const ::experimot::msgs::ContactSensor& contact() const;
  ::experimot::msgs::ContactSensor* mutable_contact();
  ::experimot::msgs::ContactSensor* release_contact();
  void set_allocated_contact(::experimot::msgs::ContactSensor* contact);

  // optional bool visualize = 12;
  bool has_visualize() const;
  void clear_visualize();
  static const int kVisualizeFieldNumber = 12;
  bool visualize() const;
  void set_visualize(bool value);

  // optional string topic = 13;
  bool has_topic() const;
  void clear_topic();
  static const int kTopicFieldNumber = 13;
  const ::std::string& topic() const;
  void set_topic(const ::std::string& value);
  void set_topic(const char* value);
  void set_topic(const char* value, size_t size);
  ::std::string* mutable_topic();
  ::std::string* release_topic();
  void set_allocated_topic(::std::string* topic);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Sensor)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_parent();
  inline void clear_has_parent();
  inline void set_has_parent_id();
  inline void clear_has_parent_id();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_always_on();
  inline void clear_has_always_on();
  inline void set_has_update_rate();
  inline void clear_has_update_rate();
  inline void set_has_pose();
  inline void clear_has_pose();
  inline void set_has_camera();
  inline void clear_has_camera();
  inline void set_has_ray();
  inline void clear_has_ray();
  inline void set_has_contact();
  inline void clear_has_contact();
  inline void set_has_visualize();
  inline void clear_has_visualize();
  inline void set_has_topic();
  inline void clear_has_topic();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr parent_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 parent_id_;
  ::google::protobuf::internal::ArenaStringPtr type_;
  double update_rate_;
  ::experimot::msgs::Pose* pose_;
  ::experimot::msgs::CameraSensor* camera_;
  ::experimot::msgs::RaySensor* ray_;
  ::experimot::msgs::ContactSensor* contact_;
  ::google::protobuf::internal::ArenaStringPtr topic_;
  bool always_on_;
  bool visualize_;
  friend void  protobuf_AddDesc_sensor_2eproto();
  friend void protobuf_AssignDesc_sensor_2eproto();
  friend void protobuf_ShutdownFile_sensor_2eproto();

  void InitAsDefaultInstance();
  static Sensor* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Sensor

// required string name = 1;
inline bool Sensor::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Sensor::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Sensor::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Sensor::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Sensor::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.name)
}
inline void Sensor::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Sensor.name)
}
inline void Sensor::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Sensor.name)
}
inline ::std::string* Sensor::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Sensor::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.name)
}

// optional uint32 id = 2;
inline bool Sensor::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Sensor::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Sensor::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Sensor::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Sensor::id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.id)
  return id_;
}
inline void Sensor::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.id)
}

// required string parent = 3;
inline bool Sensor::has_parent() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Sensor::set_has_parent() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Sensor::clear_has_parent() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Sensor::clear_parent() {
  parent_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_parent();
}
inline const ::std::string& Sensor::parent() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.parent)
  return parent_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_parent(const ::std::string& value) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.parent)
}
inline void Sensor::set_parent(const char* value) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Sensor.parent)
}
inline void Sensor::set_parent(const char* value, size_t size) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Sensor.parent)
}
inline ::std::string* Sensor::mutable_parent() {
  set_has_parent();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.parent)
  return parent_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Sensor::release_parent() {
  clear_has_parent();
  return parent_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_allocated_parent(::std::string* parent) {
  if (parent != NULL) {
    set_has_parent();
  } else {
    clear_has_parent();
  }
  parent_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), parent);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.parent)
}

// required uint32 parent_id = 4;
inline bool Sensor::has_parent_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Sensor::set_has_parent_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Sensor::clear_has_parent_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Sensor::clear_parent_id() {
  parent_id_ = 0u;
  clear_has_parent_id();
}
inline ::google::protobuf::uint32 Sensor::parent_id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.parent_id)
  return parent_id_;
}
inline void Sensor::set_parent_id(::google::protobuf::uint32 value) {
  set_has_parent_id();
  parent_id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.parent_id)
}

// required string type = 5;
inline bool Sensor::has_type() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Sensor::set_has_type() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Sensor::clear_has_type() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Sensor::clear_type() {
  type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_type();
}
inline const ::std::string& Sensor::type() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.type)
  return type_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_type(const ::std::string& value) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.type)
}
inline void Sensor::set_type(const char* value) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Sensor.type)
}
inline void Sensor::set_type(const char* value, size_t size) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Sensor.type)
}
inline ::std::string* Sensor::mutable_type() {
  set_has_type();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.type)
  return type_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Sensor::release_type() {
  clear_has_type();
  return type_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_allocated_type(::std::string* type) {
  if (type != NULL) {
    set_has_type();
  } else {
    clear_has_type();
  }
  type_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), type);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.type)
}

// optional bool always_on = 6;
inline bool Sensor::has_always_on() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Sensor::set_has_always_on() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Sensor::clear_has_always_on() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Sensor::clear_always_on() {
  always_on_ = false;
  clear_has_always_on();
}
inline bool Sensor::always_on() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.always_on)
  return always_on_;
}
inline void Sensor::set_always_on(bool value) {
  set_has_always_on();
  always_on_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.always_on)
}

// optional double update_rate = 7;
inline bool Sensor::has_update_rate() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Sensor::set_has_update_rate() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Sensor::clear_has_update_rate() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Sensor::clear_update_rate() {
  update_rate_ = 0;
  clear_has_update_rate();
}
inline double Sensor::update_rate() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.update_rate)
  return update_rate_;
}
inline void Sensor::set_update_rate(double value) {
  set_has_update_rate();
  update_rate_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.update_rate)
}

// optional .experimot.msgs.Pose pose = 8;
inline bool Sensor::has_pose() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Sensor::set_has_pose() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Sensor::clear_has_pose() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Sensor::clear_pose() {
  if (pose_ != NULL) pose_->::experimot::msgs::Pose::Clear();
  clear_has_pose();
}
inline const ::experimot::msgs::Pose& Sensor::pose() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.pose)
  return pose_ != NULL ? *pose_ : *default_instance_->pose_;
}
inline ::experimot::msgs::Pose* Sensor::mutable_pose() {
  set_has_pose();
  if (pose_ == NULL) {
    pose_ = new ::experimot::msgs::Pose;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.pose)
  return pose_;
}
inline ::experimot::msgs::Pose* Sensor::release_pose() {
  clear_has_pose();
  ::experimot::msgs::Pose* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void Sensor::set_allocated_pose(::experimot::msgs::Pose* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    set_has_pose();
  } else {
    clear_has_pose();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.pose)
}

// optional .experimot.msgs.CameraSensor camera = 9;
inline bool Sensor::has_camera() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Sensor::set_has_camera() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Sensor::clear_has_camera() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Sensor::clear_camera() {
  if (camera_ != NULL) camera_->::experimot::msgs::CameraSensor::Clear();
  clear_has_camera();
}
inline const ::experimot::msgs::CameraSensor& Sensor::camera() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.camera)
  return camera_ != NULL ? *camera_ : *default_instance_->camera_;
}
inline ::experimot::msgs::CameraSensor* Sensor::mutable_camera() {
  set_has_camera();
  if (camera_ == NULL) {
    camera_ = new ::experimot::msgs::CameraSensor;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.camera)
  return camera_;
}
inline ::experimot::msgs::CameraSensor* Sensor::release_camera() {
  clear_has_camera();
  ::experimot::msgs::CameraSensor* temp = camera_;
  camera_ = NULL;
  return temp;
}
inline void Sensor::set_allocated_camera(::experimot::msgs::CameraSensor* camera) {
  delete camera_;
  camera_ = camera;
  if (camera) {
    set_has_camera();
  } else {
    clear_has_camera();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.camera)
}

// optional .experimot.msgs.RaySensor ray = 10;
inline bool Sensor::has_ray() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Sensor::set_has_ray() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Sensor::clear_has_ray() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Sensor::clear_ray() {
  if (ray_ != NULL) ray_->::experimot::msgs::RaySensor::Clear();
  clear_has_ray();
}
inline const ::experimot::msgs::RaySensor& Sensor::ray() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.ray)
  return ray_ != NULL ? *ray_ : *default_instance_->ray_;
}
inline ::experimot::msgs::RaySensor* Sensor::mutable_ray() {
  set_has_ray();
  if (ray_ == NULL) {
    ray_ = new ::experimot::msgs::RaySensor;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.ray)
  return ray_;
}
inline ::experimot::msgs::RaySensor* Sensor::release_ray() {
  clear_has_ray();
  ::experimot::msgs::RaySensor* temp = ray_;
  ray_ = NULL;
  return temp;
}
inline void Sensor::set_allocated_ray(::experimot::msgs::RaySensor* ray) {
  delete ray_;
  ray_ = ray;
  if (ray) {
    set_has_ray();
  } else {
    clear_has_ray();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.ray)
}

// optional .experimot.msgs.ContactSensor contact = 11;
inline bool Sensor::has_contact() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Sensor::set_has_contact() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Sensor::clear_has_contact() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Sensor::clear_contact() {
  if (contact_ != NULL) contact_->::experimot::msgs::ContactSensor::Clear();
  clear_has_contact();
}
inline const ::experimot::msgs::ContactSensor& Sensor::contact() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.contact)
  return contact_ != NULL ? *contact_ : *default_instance_->contact_;
}
inline ::experimot::msgs::ContactSensor* Sensor::mutable_contact() {
  set_has_contact();
  if (contact_ == NULL) {
    contact_ = new ::experimot::msgs::ContactSensor;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.contact)
  return contact_;
}
inline ::experimot::msgs::ContactSensor* Sensor::release_contact() {
  clear_has_contact();
  ::experimot::msgs::ContactSensor* temp = contact_;
  contact_ = NULL;
  return temp;
}
inline void Sensor::set_allocated_contact(::experimot::msgs::ContactSensor* contact) {
  delete contact_;
  contact_ = contact;
  if (contact) {
    set_has_contact();
  } else {
    clear_has_contact();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.contact)
}

// optional bool visualize = 12;
inline bool Sensor::has_visualize() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Sensor::set_has_visualize() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Sensor::clear_has_visualize() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Sensor::clear_visualize() {
  visualize_ = false;
  clear_has_visualize();
}
inline bool Sensor::visualize() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.visualize)
  return visualize_;
}
inline void Sensor::set_visualize(bool value) {
  set_has_visualize();
  visualize_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.visualize)
}

// optional string topic = 13;
inline bool Sensor::has_topic() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void Sensor::set_has_topic() {
  _has_bits_[0] |= 0x00001000u;
}
inline void Sensor::clear_has_topic() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void Sensor::clear_topic() {
  topic_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_topic();
}
inline const ::std::string& Sensor::topic() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Sensor.topic)
  return topic_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_topic(const ::std::string& value) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Sensor.topic)
}
inline void Sensor::set_topic(const char* value) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Sensor.topic)
}
inline void Sensor::set_topic(const char* value, size_t size) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Sensor.topic)
}
inline ::std::string* Sensor::mutable_topic() {
  set_has_topic();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Sensor.topic)
  return topic_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Sensor::release_topic() {
  clear_has_topic();
  return topic_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sensor::set_allocated_topic(::std::string* topic) {
  if (topic != NULL) {
    set_has_topic();
  } else {
    clear_has_topic();
  }
  topic_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), topic);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Sensor.topic)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Sensor> SensorPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Sensor const> ConstSensorPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_sensor_2eproto__INCLUDED
