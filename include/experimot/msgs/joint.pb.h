// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: joint.proto

#ifndef PROTOBUF_joint_2eproto__INCLUDED
#define PROTOBUF_joint_2eproto__INCLUDED

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
#include "axis.pb.h"
#include "pose.pb.h"
#include "sensor.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_joint_2eproto();
void protobuf_AssignDesc_joint_2eproto();
void protobuf_ShutdownFile_joint_2eproto();

class Joint;

enum Joint_Type {
  Joint_Type_REVOLUTE = 1,
  Joint_Type_REVOLUTE2 = 2,
  Joint_Type_PRISMATIC = 3,
  Joint_Type_UNIVERSAL = 4,
  Joint_Type_BALL = 5,
  Joint_Type_SCREW = 6,
  Joint_Type_GEARBOX = 7
};
bool Joint_Type_IsValid(int value);
const Joint_Type Joint_Type_Type_MIN = Joint_Type_REVOLUTE;
const Joint_Type Joint_Type_Type_MAX = Joint_Type_GEARBOX;
const int Joint_Type_Type_ARRAYSIZE = Joint_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Joint_Type_descriptor();
inline const ::std::string& Joint_Type_Name(Joint_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Joint_Type_descriptor(), value);
}
inline bool Joint_Type_Parse(
    const ::std::string& name, Joint_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Joint_Type>(
    Joint_Type_descriptor(), name, value);
}
// ===================================================================

class Joint : public ::google::protobuf::Message {
 public:
  Joint();
  virtual ~Joint();

  Joint(const Joint& from);

  inline Joint& operator=(const Joint& from) {
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
  static const Joint& default_instance();

  void Swap(Joint* other);

  // implements Message ----------------------------------------------

  inline Joint* New() const { return New(NULL); }

  Joint* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Joint& from);
  void MergeFrom(const Joint& from);
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
  void InternalSwap(Joint* other);
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

  typedef Joint_Type Type;
  static const Type REVOLUTE = Joint_Type_REVOLUTE;
  static const Type REVOLUTE2 = Joint_Type_REVOLUTE2;
  static const Type PRISMATIC = Joint_Type_PRISMATIC;
  static const Type UNIVERSAL = Joint_Type_UNIVERSAL;
  static const Type BALL = Joint_Type_BALL;
  static const Type SCREW = Joint_Type_SCREW;
  static const Type GEARBOX = Joint_Type_GEARBOX;
  static inline bool Type_IsValid(int value) {
    return Joint_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Joint_Type_Type_MIN;
  static const Type Type_MAX =
    Joint_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Joint_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Joint_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Joint_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Joint_Type_Parse(name, value);
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

  // optional uint32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // repeated double angle = 3;
  int angle_size() const;
  void clear_angle();
  static const int kAngleFieldNumber = 3;
  double angle(int index) const;
  void set_angle(int index, double value);
  void add_angle(double value);
  const ::google::protobuf::RepeatedField< double >&
      angle() const;
  ::google::protobuf::RepeatedField< double >*
      mutable_angle();

  // optional .experimot.msgs.Joint.Type type = 4;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 4;
  ::experimot::msgs::Joint_Type type() const;
  void set_type(::experimot::msgs::Joint_Type value);

  // optional string parent = 5;
  bool has_parent() const;
  void clear_parent();
  static const int kParentFieldNumber = 5;
  const ::std::string& parent() const;
  void set_parent(const ::std::string& value);
  void set_parent(const char* value);
  void set_parent(const char* value, size_t size);
  ::std::string* mutable_parent();
  ::std::string* release_parent();
  void set_allocated_parent(::std::string* parent);

  // optional uint32 parent_id = 6;
  bool has_parent_id() const;
  void clear_parent_id();
  static const int kParentIdFieldNumber = 6;
  ::google::protobuf::uint32 parent_id() const;
  void set_parent_id(::google::protobuf::uint32 value);

  // optional string child = 7;
  bool has_child() const;
  void clear_child();
  static const int kChildFieldNumber = 7;
  const ::std::string& child() const;
  void set_child(const ::std::string& value);
  void set_child(const char* value);
  void set_child(const char* value, size_t size);
  ::std::string* mutable_child();
  ::std::string* release_child();
  void set_allocated_child(::std::string* child);

  // optional uint32 child_id = 8;
  bool has_child_id() const;
  void clear_child_id();
  static const int kChildIdFieldNumber = 8;
  ::google::protobuf::uint32 child_id() const;
  void set_child_id(::google::protobuf::uint32 value);

  // optional .experimot.msgs.Pose pose = 9;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 9;
  const ::experimot::msgs::Pose& pose() const;
  ::experimot::msgs::Pose* mutable_pose();
  ::experimot::msgs::Pose* release_pose();
  void set_allocated_pose(::experimot::msgs::Pose* pose);

  // optional .experimot.msgs.Axis axis1 = 10;
  bool has_axis1() const;
  void clear_axis1();
  static const int kAxis1FieldNumber = 10;
  const ::experimot::msgs::Axis& axis1() const;
  ::experimot::msgs::Axis* mutable_axis1();
  ::experimot::msgs::Axis* release_axis1();
  void set_allocated_axis1(::experimot::msgs::Axis* axis1);

  // optional .experimot.msgs.Axis axis2 = 11;
  bool has_axis2() const;
  void clear_axis2();
  static const int kAxis2FieldNumber = 11;
  const ::experimot::msgs::Axis& axis2() const;
  ::experimot::msgs::Axis* mutable_axis2();
  ::experimot::msgs::Axis* release_axis2();
  void set_allocated_axis2(::experimot::msgs::Axis* axis2);

  // optional double cfm = 12;
  bool has_cfm() const;
  void clear_cfm();
  static const int kCfmFieldNumber = 12;
  double cfm() const;
  void set_cfm(double value);

  // optional double bounce = 13;
  bool has_bounce() const;
  void clear_bounce();
  static const int kBounceFieldNumber = 13;
  double bounce() const;
  void set_bounce(double value);

  // optional double velocity = 14;
  bool has_velocity() const;
  void clear_velocity();
  static const int kVelocityFieldNumber = 14;
  double velocity() const;
  void set_velocity(double value);

  // optional double fudge_factor = 15;
  bool has_fudge_factor() const;
  void clear_fudge_factor();
  static const int kFudgeFactorFieldNumber = 15;
  double fudge_factor() const;
  void set_fudge_factor(double value);

  // optional double limit_cfm = 16;
  bool has_limit_cfm() const;
  void clear_limit_cfm();
  static const int kLimitCfmFieldNumber = 16;
  double limit_cfm() const;
  void set_limit_cfm(double value);

  // optional double limit_erp = 17;
  bool has_limit_erp() const;
  void clear_limit_erp();
  static const int kLimitErpFieldNumber = 17;
  double limit_erp() const;
  void set_limit_erp(double value);

  // optional double suspension_cfm = 18;
  bool has_suspension_cfm() const;
  void clear_suspension_cfm();
  static const int kSuspensionCfmFieldNumber = 18;
  double suspension_cfm() const;
  void set_suspension_cfm(double value);

  // optional double suspension_erp = 19;
  bool has_suspension_erp() const;
  void clear_suspension_erp();
  static const int kSuspensionErpFieldNumber = 19;
  double suspension_erp() const;
  void set_suspension_erp(double value);

  // repeated .experimot.msgs.Sensor sensor = 20;
  int sensor_size() const;
  void clear_sensor();
  static const int kSensorFieldNumber = 20;
  const ::experimot::msgs::Sensor& sensor(int index) const;
  ::experimot::msgs::Sensor* mutable_sensor(int index);
  ::experimot::msgs::Sensor* add_sensor();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Sensor >&
      sensor() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Sensor >*
      mutable_sensor();

  // @@protoc_insertion_point(class_scope:experimot.msgs.Joint)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_parent();
  inline void clear_has_parent();
  inline void set_has_parent_id();
  inline void clear_has_parent_id();
  inline void set_has_child();
  inline void clear_has_child();
  inline void set_has_child_id();
  inline void clear_has_child_id();
  inline void set_has_pose();
  inline void clear_has_pose();
  inline void set_has_axis1();
  inline void clear_has_axis1();
  inline void set_has_axis2();
  inline void clear_has_axis2();
  inline void set_has_cfm();
  inline void clear_has_cfm();
  inline void set_has_bounce();
  inline void clear_has_bounce();
  inline void set_has_velocity();
  inline void clear_has_velocity();
  inline void set_has_fudge_factor();
  inline void clear_has_fudge_factor();
  inline void set_has_limit_cfm();
  inline void clear_has_limit_cfm();
  inline void set_has_limit_erp();
  inline void clear_has_limit_erp();
  inline void set_has_suspension_cfm();
  inline void clear_has_suspension_cfm();
  inline void set_has_suspension_erp();
  inline void clear_has_suspension_erp();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::RepeatedField< double > angle_;
  ::google::protobuf::uint32 id_;
  int type_;
  ::google::protobuf::internal::ArenaStringPtr parent_;
  ::google::protobuf::internal::ArenaStringPtr child_;
  ::google::protobuf::uint32 parent_id_;
  ::google::protobuf::uint32 child_id_;
  ::experimot::msgs::Pose* pose_;
  ::experimot::msgs::Axis* axis1_;
  ::experimot::msgs::Axis* axis2_;
  double cfm_;
  double bounce_;
  double velocity_;
  double fudge_factor_;
  double limit_cfm_;
  double limit_erp_;
  double suspension_cfm_;
  double suspension_erp_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Sensor > sensor_;
  friend void  protobuf_AddDesc_joint_2eproto();
  friend void protobuf_AssignDesc_joint_2eproto();
  friend void protobuf_ShutdownFile_joint_2eproto();

  void InitAsDefaultInstance();
  static Joint* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Joint

// required string name = 1;
inline bool Joint::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Joint::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Joint::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Joint::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Joint::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.name)
}
inline void Joint::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Joint.name)
}
inline void Joint::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Joint.name)
}
inline ::std::string* Joint::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Joint::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.name)
}

// optional uint32 id = 2;
inline bool Joint::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Joint::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Joint::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Joint::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Joint::id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.id)
  return id_;
}
inline void Joint::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.id)
}

// repeated double angle = 3;
inline int Joint::angle_size() const {
  return angle_.size();
}
inline void Joint::clear_angle() {
  angle_.Clear();
}
inline double Joint::angle(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.angle)
  return angle_.Get(index);
}
inline void Joint::set_angle(int index, double value) {
  angle_.Set(index, value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.angle)
}
inline void Joint::add_angle(double value) {
  angle_.Add(value);
  // @@protoc_insertion_point(field_add:experimot.msgs.Joint.angle)
}
inline const ::google::protobuf::RepeatedField< double >&
Joint::angle() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.Joint.angle)
  return angle_;
}
inline ::google::protobuf::RepeatedField< double >*
Joint::mutable_angle() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.Joint.angle)
  return &angle_;
}

// optional .experimot.msgs.Joint.Type type = 4;
inline bool Joint::has_type() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Joint::set_has_type() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Joint::clear_has_type() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Joint::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::experimot::msgs::Joint_Type Joint::type() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.type)
  return static_cast< ::experimot::msgs::Joint_Type >(type_);
}
inline void Joint::set_type(::experimot::msgs::Joint_Type value) {
  assert(::experimot::msgs::Joint_Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.type)
}

// optional string parent = 5;
inline bool Joint::has_parent() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Joint::set_has_parent() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Joint::clear_has_parent() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Joint::clear_parent() {
  parent_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_parent();
}
inline const ::std::string& Joint::parent() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.parent)
  return parent_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_parent(const ::std::string& value) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.parent)
}
inline void Joint::set_parent(const char* value) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Joint.parent)
}
inline void Joint::set_parent(const char* value, size_t size) {
  set_has_parent();
  parent_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Joint.parent)
}
inline ::std::string* Joint::mutable_parent() {
  set_has_parent();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.parent)
  return parent_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Joint::release_parent() {
  clear_has_parent();
  return parent_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_allocated_parent(::std::string* parent) {
  if (parent != NULL) {
    set_has_parent();
  } else {
    clear_has_parent();
  }
  parent_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), parent);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.parent)
}

// optional uint32 parent_id = 6;
inline bool Joint::has_parent_id() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Joint::set_has_parent_id() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Joint::clear_has_parent_id() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Joint::clear_parent_id() {
  parent_id_ = 0u;
  clear_has_parent_id();
}
inline ::google::protobuf::uint32 Joint::parent_id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.parent_id)
  return parent_id_;
}
inline void Joint::set_parent_id(::google::protobuf::uint32 value) {
  set_has_parent_id();
  parent_id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.parent_id)
}

// optional string child = 7;
inline bool Joint::has_child() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Joint::set_has_child() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Joint::clear_has_child() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Joint::clear_child() {
  child_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_child();
}
inline const ::std::string& Joint::child() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.child)
  return child_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_child(const ::std::string& value) {
  set_has_child();
  child_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.child)
}
inline void Joint::set_child(const char* value) {
  set_has_child();
  child_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Joint.child)
}
inline void Joint::set_child(const char* value, size_t size) {
  set_has_child();
  child_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Joint.child)
}
inline ::std::string* Joint::mutable_child() {
  set_has_child();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.child)
  return child_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Joint::release_child() {
  clear_has_child();
  return child_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Joint::set_allocated_child(::std::string* child) {
  if (child != NULL) {
    set_has_child();
  } else {
    clear_has_child();
  }
  child_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), child);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.child)
}

// optional uint32 child_id = 8;
inline bool Joint::has_child_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Joint::set_has_child_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Joint::clear_has_child_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Joint::clear_child_id() {
  child_id_ = 0u;
  clear_has_child_id();
}
inline ::google::protobuf::uint32 Joint::child_id() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.child_id)
  return child_id_;
}
inline void Joint::set_child_id(::google::protobuf::uint32 value) {
  set_has_child_id();
  child_id_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.child_id)
}

// optional .experimot.msgs.Pose pose = 9;
inline bool Joint::has_pose() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Joint::set_has_pose() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Joint::clear_has_pose() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Joint::clear_pose() {
  if (pose_ != NULL) pose_->::experimot::msgs::Pose::Clear();
  clear_has_pose();
}
inline const ::experimot::msgs::Pose& Joint::pose() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.pose)
  return pose_ != NULL ? *pose_ : *default_instance_->pose_;
}
inline ::experimot::msgs::Pose* Joint::mutable_pose() {
  set_has_pose();
  if (pose_ == NULL) {
    pose_ = new ::experimot::msgs::Pose;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.pose)
  return pose_;
}
inline ::experimot::msgs::Pose* Joint::release_pose() {
  clear_has_pose();
  ::experimot::msgs::Pose* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void Joint::set_allocated_pose(::experimot::msgs::Pose* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    set_has_pose();
  } else {
    clear_has_pose();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.pose)
}

// optional .experimot.msgs.Axis axis1 = 10;
inline bool Joint::has_axis1() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Joint::set_has_axis1() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Joint::clear_has_axis1() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Joint::clear_axis1() {
  if (axis1_ != NULL) axis1_->::experimot::msgs::Axis::Clear();
  clear_has_axis1();
}
inline const ::experimot::msgs::Axis& Joint::axis1() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.axis1)
  return axis1_ != NULL ? *axis1_ : *default_instance_->axis1_;
}
inline ::experimot::msgs::Axis* Joint::mutable_axis1() {
  set_has_axis1();
  if (axis1_ == NULL) {
    axis1_ = new ::experimot::msgs::Axis;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.axis1)
  return axis1_;
}
inline ::experimot::msgs::Axis* Joint::release_axis1() {
  clear_has_axis1();
  ::experimot::msgs::Axis* temp = axis1_;
  axis1_ = NULL;
  return temp;
}
inline void Joint::set_allocated_axis1(::experimot::msgs::Axis* axis1) {
  delete axis1_;
  axis1_ = axis1;
  if (axis1) {
    set_has_axis1();
  } else {
    clear_has_axis1();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.axis1)
}

// optional .experimot.msgs.Axis axis2 = 11;
inline bool Joint::has_axis2() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Joint::set_has_axis2() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Joint::clear_has_axis2() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Joint::clear_axis2() {
  if (axis2_ != NULL) axis2_->::experimot::msgs::Axis::Clear();
  clear_has_axis2();
}
inline const ::experimot::msgs::Axis& Joint::axis2() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.axis2)
  return axis2_ != NULL ? *axis2_ : *default_instance_->axis2_;
}
inline ::experimot::msgs::Axis* Joint::mutable_axis2() {
  set_has_axis2();
  if (axis2_ == NULL) {
    axis2_ = new ::experimot::msgs::Axis;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.axis2)
  return axis2_;
}
inline ::experimot::msgs::Axis* Joint::release_axis2() {
  clear_has_axis2();
  ::experimot::msgs::Axis* temp = axis2_;
  axis2_ = NULL;
  return temp;
}
inline void Joint::set_allocated_axis2(::experimot::msgs::Axis* axis2) {
  delete axis2_;
  axis2_ = axis2;
  if (axis2) {
    set_has_axis2();
  } else {
    clear_has_axis2();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Joint.axis2)
}

// optional double cfm = 12;
inline bool Joint::has_cfm() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Joint::set_has_cfm() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Joint::clear_has_cfm() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Joint::clear_cfm() {
  cfm_ = 0;
  clear_has_cfm();
}
inline double Joint::cfm() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.cfm)
  return cfm_;
}
inline void Joint::set_cfm(double value) {
  set_has_cfm();
  cfm_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.cfm)
}

// optional double bounce = 13;
inline bool Joint::has_bounce() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void Joint::set_has_bounce() {
  _has_bits_[0] |= 0x00001000u;
}
inline void Joint::clear_has_bounce() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void Joint::clear_bounce() {
  bounce_ = 0;
  clear_has_bounce();
}
inline double Joint::bounce() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.bounce)
  return bounce_;
}
inline void Joint::set_bounce(double value) {
  set_has_bounce();
  bounce_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.bounce)
}

// optional double velocity = 14;
inline bool Joint::has_velocity() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void Joint::set_has_velocity() {
  _has_bits_[0] |= 0x00002000u;
}
inline void Joint::clear_has_velocity() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void Joint::clear_velocity() {
  velocity_ = 0;
  clear_has_velocity();
}
inline double Joint::velocity() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.velocity)
  return velocity_;
}
inline void Joint::set_velocity(double value) {
  set_has_velocity();
  velocity_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.velocity)
}

// optional double fudge_factor = 15;
inline bool Joint::has_fudge_factor() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void Joint::set_has_fudge_factor() {
  _has_bits_[0] |= 0x00004000u;
}
inline void Joint::clear_has_fudge_factor() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void Joint::clear_fudge_factor() {
  fudge_factor_ = 0;
  clear_has_fudge_factor();
}
inline double Joint::fudge_factor() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.fudge_factor)
  return fudge_factor_;
}
inline void Joint::set_fudge_factor(double value) {
  set_has_fudge_factor();
  fudge_factor_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.fudge_factor)
}

// optional double limit_cfm = 16;
inline bool Joint::has_limit_cfm() const {
  return (_has_bits_[0] & 0x00008000u) != 0;
}
inline void Joint::set_has_limit_cfm() {
  _has_bits_[0] |= 0x00008000u;
}
inline void Joint::clear_has_limit_cfm() {
  _has_bits_[0] &= ~0x00008000u;
}
inline void Joint::clear_limit_cfm() {
  limit_cfm_ = 0;
  clear_has_limit_cfm();
}
inline double Joint::limit_cfm() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.limit_cfm)
  return limit_cfm_;
}
inline void Joint::set_limit_cfm(double value) {
  set_has_limit_cfm();
  limit_cfm_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.limit_cfm)
}

// optional double limit_erp = 17;
inline bool Joint::has_limit_erp() const {
  return (_has_bits_[0] & 0x00010000u) != 0;
}
inline void Joint::set_has_limit_erp() {
  _has_bits_[0] |= 0x00010000u;
}
inline void Joint::clear_has_limit_erp() {
  _has_bits_[0] &= ~0x00010000u;
}
inline void Joint::clear_limit_erp() {
  limit_erp_ = 0;
  clear_has_limit_erp();
}
inline double Joint::limit_erp() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.limit_erp)
  return limit_erp_;
}
inline void Joint::set_limit_erp(double value) {
  set_has_limit_erp();
  limit_erp_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.limit_erp)
}

// optional double suspension_cfm = 18;
inline bool Joint::has_suspension_cfm() const {
  return (_has_bits_[0] & 0x00020000u) != 0;
}
inline void Joint::set_has_suspension_cfm() {
  _has_bits_[0] |= 0x00020000u;
}
inline void Joint::clear_has_suspension_cfm() {
  _has_bits_[0] &= ~0x00020000u;
}
inline void Joint::clear_suspension_cfm() {
  suspension_cfm_ = 0;
  clear_has_suspension_cfm();
}
inline double Joint::suspension_cfm() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.suspension_cfm)
  return suspension_cfm_;
}
inline void Joint::set_suspension_cfm(double value) {
  set_has_suspension_cfm();
  suspension_cfm_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.suspension_cfm)
}

// optional double suspension_erp = 19;
inline bool Joint::has_suspension_erp() const {
  return (_has_bits_[0] & 0x00040000u) != 0;
}
inline void Joint::set_has_suspension_erp() {
  _has_bits_[0] |= 0x00040000u;
}
inline void Joint::clear_has_suspension_erp() {
  _has_bits_[0] &= ~0x00040000u;
}
inline void Joint::clear_suspension_erp() {
  suspension_erp_ = 0;
  clear_has_suspension_erp();
}
inline double Joint::suspension_erp() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.suspension_erp)
  return suspension_erp_;
}
inline void Joint::set_suspension_erp(double value) {
  set_has_suspension_erp();
  suspension_erp_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Joint.suspension_erp)
}

// repeated .experimot.msgs.Sensor sensor = 20;
inline int Joint::sensor_size() const {
  return sensor_.size();
}
inline void Joint::clear_sensor() {
  sensor_.Clear();
}
inline const ::experimot::msgs::Sensor& Joint::sensor(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Joint.sensor)
  return sensor_.Get(index);
}
inline ::experimot::msgs::Sensor* Joint::mutable_sensor(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Joint.sensor)
  return sensor_.Mutable(index);
}
inline ::experimot::msgs::Sensor* Joint::add_sensor() {
  // @@protoc_insertion_point(field_add:experimot.msgs.Joint.sensor)
  return sensor_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Sensor >&
Joint::sensor() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.Joint.sensor)
  return sensor_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Sensor >*
Joint::mutable_sensor() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.Joint.sensor)
  return &sensor_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Joint> JointPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::experimot::msgs::Joint_Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::experimot::msgs::Joint_Type>() {
  return ::experimot::msgs::Joint_Type_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

typedef const boost::shared_ptr<experimot::msgs::Joint const> ConstJointPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_joint_2eproto__INCLUDED