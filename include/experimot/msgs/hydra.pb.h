// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hydra.proto

#ifndef PROTOBUF_hydra_2eproto__INCLUDED
#define PROTOBUF_hydra_2eproto__INCLUDED

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
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_hydra_2eproto();
void protobuf_AssignDesc_hydra_2eproto();
void protobuf_ShutdownFile_hydra_2eproto();

class Hydra;
class Hydra_Paddle;

// ===================================================================

class Hydra_Paddle : public ::google::protobuf::Message {
 public:
  Hydra_Paddle();
  virtual ~Hydra_Paddle();

  Hydra_Paddle(const Hydra_Paddle& from);

  inline Hydra_Paddle& operator=(const Hydra_Paddle& from) {
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
  static const Hydra_Paddle& default_instance();

  void Swap(Hydra_Paddle* other);

  // implements Message ----------------------------------------------

  inline Hydra_Paddle* New() const { return New(NULL); }

  Hydra_Paddle* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hydra_Paddle& from);
  void MergeFrom(const Hydra_Paddle& from);
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
  void InternalSwap(Hydra_Paddle* other);
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

  // required .experimot.msgs.Pose pose = 1;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 1;
  const ::experimot::msgs::Pose& pose() const;
  ::experimot::msgs::Pose* mutable_pose();
  ::experimot::msgs::Pose* release_pose();
  void set_allocated_pose(::experimot::msgs::Pose* pose);

  // required bool button_bumper = 2;
  bool has_button_bumper() const;
  void clear_button_bumper();
  static const int kButtonBumperFieldNumber = 2;
  bool button_bumper() const;
  void set_button_bumper(bool value);

  // required bool button_1 = 3;
  bool has_button_1() const;
  void clear_button_1();
  static const int kButton1FieldNumber = 3;
  bool button_1() const;
  void set_button_1(bool value);

  // required bool button_2 = 4;
  bool has_button_2() const;
  void clear_button_2();
  static const int kButton2FieldNumber = 4;
  bool button_2() const;
  void set_button_2(bool value);

  // required bool button_3 = 5;
  bool has_button_3() const;
  void clear_button_3();
  static const int kButton3FieldNumber = 5;
  bool button_3() const;
  void set_button_3(bool value);

  // required bool button_4 = 6;
  bool has_button_4() const;
  void clear_button_4();
  static const int kButton4FieldNumber = 6;
  bool button_4() const;
  void set_button_4(bool value);

  // required bool button_joy = 7;
  bool has_button_joy() const;
  void clear_button_joy();
  static const int kButtonJoyFieldNumber = 7;
  bool button_joy() const;
  void set_button_joy(bool value);

  // required bool button_center = 8;
  bool has_button_center() const;
  void clear_button_center();
  static const int kButtonCenterFieldNumber = 8;
  bool button_center() const;
  void set_button_center(bool value);

  // required double joy_x = 9;
  bool has_joy_x() const;
  void clear_joy_x();
  static const int kJoyXFieldNumber = 9;
  double joy_x() const;
  void set_joy_x(double value);

  // required double joy_y = 10;
  bool has_joy_y() const;
  void clear_joy_y();
  static const int kJoyYFieldNumber = 10;
  double joy_y() const;
  void set_joy_y(double value);

  // required double trigger = 11;
  bool has_trigger() const;
  void clear_trigger();
  static const int kTriggerFieldNumber = 11;
  double trigger() const;
  void set_trigger(double value);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Hydra.Paddle)
 private:
  inline void set_has_pose();
  inline void clear_has_pose();
  inline void set_has_button_bumper();
  inline void clear_has_button_bumper();
  inline void set_has_button_1();
  inline void clear_has_button_1();
  inline void set_has_button_2();
  inline void clear_has_button_2();
  inline void set_has_button_3();
  inline void clear_has_button_3();
  inline void set_has_button_4();
  inline void clear_has_button_4();
  inline void set_has_button_joy();
  inline void clear_has_button_joy();
  inline void set_has_button_center();
  inline void clear_has_button_center();
  inline void set_has_joy_x();
  inline void clear_has_joy_x();
  inline void set_has_joy_y();
  inline void clear_has_joy_y();
  inline void set_has_trigger();
  inline void clear_has_trigger();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::experimot::msgs::Pose* pose_;
  bool button_bumper_;
  bool button_1_;
  bool button_2_;
  bool button_3_;
  bool button_4_;
  bool button_joy_;
  bool button_center_;
  double joy_x_;
  double joy_y_;
  double trigger_;
  friend void  protobuf_AddDesc_hydra_2eproto();
  friend void protobuf_AssignDesc_hydra_2eproto();
  friend void protobuf_ShutdownFile_hydra_2eproto();

  void InitAsDefaultInstance();
  static Hydra_Paddle* default_instance_;
};
// -------------------------------------------------------------------

class Hydra : public ::google::protobuf::Message {
 public:
  Hydra();
  virtual ~Hydra();

  Hydra(const Hydra& from);

  inline Hydra& operator=(const Hydra& from) {
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
  static const Hydra& default_instance();

  void Swap(Hydra* other);

  // implements Message ----------------------------------------------

  inline Hydra* New() const { return New(NULL); }

  Hydra* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hydra& from);
  void MergeFrom(const Hydra& from);
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
  void InternalSwap(Hydra* other);
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

  typedef Hydra_Paddle Paddle;

  // accessors -------------------------------------------------------

  // required .experimot.msgs.Hydra.Paddle right = 1;
  bool has_right() const;
  void clear_right();
  static const int kRightFieldNumber = 1;
  const ::experimot::msgs::Hydra_Paddle& right() const;
  ::experimot::msgs::Hydra_Paddle* mutable_right();
  ::experimot::msgs::Hydra_Paddle* release_right();
  void set_allocated_right(::experimot::msgs::Hydra_Paddle* right);

  // required .experimot.msgs.Hydra.Paddle left = 2;
  bool has_left() const;
  void clear_left();
  static const int kLeftFieldNumber = 2;
  const ::experimot::msgs::Hydra_Paddle& left() const;
  ::experimot::msgs::Hydra_Paddle* mutable_left();
  ::experimot::msgs::Hydra_Paddle* release_left();
  void set_allocated_left(::experimot::msgs::Hydra_Paddle* left);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Hydra)
 private:
  inline void set_has_right();
  inline void clear_has_right();
  inline void set_has_left();
  inline void clear_has_left();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::experimot::msgs::Hydra_Paddle* right_;
  ::experimot::msgs::Hydra_Paddle* left_;
  friend void  protobuf_AddDesc_hydra_2eproto();
  friend void protobuf_AssignDesc_hydra_2eproto();
  friend void protobuf_ShutdownFile_hydra_2eproto();

  void InitAsDefaultInstance();
  static Hydra* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Hydra_Paddle

// required .experimot.msgs.Pose pose = 1;
inline bool Hydra_Paddle::has_pose() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hydra_Paddle::set_has_pose() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hydra_Paddle::clear_has_pose() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hydra_Paddle::clear_pose() {
  if (pose_ != NULL) pose_->::experimot::msgs::Pose::Clear();
  clear_has_pose();
}
inline const ::experimot::msgs::Pose& Hydra_Paddle::pose() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.pose)
  return pose_ != NULL ? *pose_ : *default_instance_->pose_;
}
inline ::experimot::msgs::Pose* Hydra_Paddle::mutable_pose() {
  set_has_pose();
  if (pose_ == NULL) {
    pose_ = new ::experimot::msgs::Pose;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Hydra.Paddle.pose)
  return pose_;
}
inline ::experimot::msgs::Pose* Hydra_Paddle::release_pose() {
  clear_has_pose();
  ::experimot::msgs::Pose* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void Hydra_Paddle::set_allocated_pose(::experimot::msgs::Pose* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    set_has_pose();
  } else {
    clear_has_pose();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Hydra.Paddle.pose)
}

// required bool button_bumper = 2;
inline bool Hydra_Paddle::has_button_bumper() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hydra_Paddle::set_has_button_bumper() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hydra_Paddle::clear_has_button_bumper() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hydra_Paddle::clear_button_bumper() {
  button_bumper_ = false;
  clear_has_button_bumper();
}
inline bool Hydra_Paddle::button_bumper() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_bumper)
  return button_bumper_;
}
inline void Hydra_Paddle::set_button_bumper(bool value) {
  set_has_button_bumper();
  button_bumper_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_bumper)
}

// required bool button_1 = 3;
inline bool Hydra_Paddle::has_button_1() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Hydra_Paddle::set_has_button_1() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Hydra_Paddle::clear_has_button_1() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Hydra_Paddle::clear_button_1() {
  button_1_ = false;
  clear_has_button_1();
}
inline bool Hydra_Paddle::button_1() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_1)
  return button_1_;
}
inline void Hydra_Paddle::set_button_1(bool value) {
  set_has_button_1();
  button_1_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_1)
}

// required bool button_2 = 4;
inline bool Hydra_Paddle::has_button_2() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Hydra_Paddle::set_has_button_2() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Hydra_Paddle::clear_has_button_2() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Hydra_Paddle::clear_button_2() {
  button_2_ = false;
  clear_has_button_2();
}
inline bool Hydra_Paddle::button_2() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_2)
  return button_2_;
}
inline void Hydra_Paddle::set_button_2(bool value) {
  set_has_button_2();
  button_2_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_2)
}

// required bool button_3 = 5;
inline bool Hydra_Paddle::has_button_3() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Hydra_Paddle::set_has_button_3() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Hydra_Paddle::clear_has_button_3() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Hydra_Paddle::clear_button_3() {
  button_3_ = false;
  clear_has_button_3();
}
inline bool Hydra_Paddle::button_3() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_3)
  return button_3_;
}
inline void Hydra_Paddle::set_button_3(bool value) {
  set_has_button_3();
  button_3_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_3)
}

// required bool button_4 = 6;
inline bool Hydra_Paddle::has_button_4() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Hydra_Paddle::set_has_button_4() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Hydra_Paddle::clear_has_button_4() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Hydra_Paddle::clear_button_4() {
  button_4_ = false;
  clear_has_button_4();
}
inline bool Hydra_Paddle::button_4() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_4)
  return button_4_;
}
inline void Hydra_Paddle::set_button_4(bool value) {
  set_has_button_4();
  button_4_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_4)
}

// required bool button_joy = 7;
inline bool Hydra_Paddle::has_button_joy() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Hydra_Paddle::set_has_button_joy() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Hydra_Paddle::clear_has_button_joy() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Hydra_Paddle::clear_button_joy() {
  button_joy_ = false;
  clear_has_button_joy();
}
inline bool Hydra_Paddle::button_joy() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_joy)
  return button_joy_;
}
inline void Hydra_Paddle::set_button_joy(bool value) {
  set_has_button_joy();
  button_joy_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_joy)
}

// required bool button_center = 8;
inline bool Hydra_Paddle::has_button_center() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Hydra_Paddle::set_has_button_center() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Hydra_Paddle::clear_has_button_center() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Hydra_Paddle::clear_button_center() {
  button_center_ = false;
  clear_has_button_center();
}
inline bool Hydra_Paddle::button_center() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.button_center)
  return button_center_;
}
inline void Hydra_Paddle::set_button_center(bool value) {
  set_has_button_center();
  button_center_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.button_center)
}

// required double joy_x = 9;
inline bool Hydra_Paddle::has_joy_x() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Hydra_Paddle::set_has_joy_x() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Hydra_Paddle::clear_has_joy_x() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Hydra_Paddle::clear_joy_x() {
  joy_x_ = 0;
  clear_has_joy_x();
}
inline double Hydra_Paddle::joy_x() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.joy_x)
  return joy_x_;
}
inline void Hydra_Paddle::set_joy_x(double value) {
  set_has_joy_x();
  joy_x_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.joy_x)
}

// required double joy_y = 10;
inline bool Hydra_Paddle::has_joy_y() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Hydra_Paddle::set_has_joy_y() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Hydra_Paddle::clear_has_joy_y() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Hydra_Paddle::clear_joy_y() {
  joy_y_ = 0;
  clear_has_joy_y();
}
inline double Hydra_Paddle::joy_y() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.joy_y)
  return joy_y_;
}
inline void Hydra_Paddle::set_joy_y(double value) {
  set_has_joy_y();
  joy_y_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.joy_y)
}

// required double trigger = 11;
inline bool Hydra_Paddle::has_trigger() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Hydra_Paddle::set_has_trigger() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Hydra_Paddle::clear_has_trigger() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Hydra_Paddle::clear_trigger() {
  trigger_ = 0;
  clear_has_trigger();
}
inline double Hydra_Paddle::trigger() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.Paddle.trigger)
  return trigger_;
}
inline void Hydra_Paddle::set_trigger(double value) {
  set_has_trigger();
  trigger_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Hydra.Paddle.trigger)
}

// -------------------------------------------------------------------

// Hydra

// required .experimot.msgs.Hydra.Paddle right = 1;
inline bool Hydra::has_right() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hydra::set_has_right() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hydra::clear_has_right() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hydra::clear_right() {
  if (right_ != NULL) right_->::experimot::msgs::Hydra_Paddle::Clear();
  clear_has_right();
}
inline const ::experimot::msgs::Hydra_Paddle& Hydra::right() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.right)
  return right_ != NULL ? *right_ : *default_instance_->right_;
}
inline ::experimot::msgs::Hydra_Paddle* Hydra::mutable_right() {
  set_has_right();
  if (right_ == NULL) {
    right_ = new ::experimot::msgs::Hydra_Paddle;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Hydra.right)
  return right_;
}
inline ::experimot::msgs::Hydra_Paddle* Hydra::release_right() {
  clear_has_right();
  ::experimot::msgs::Hydra_Paddle* temp = right_;
  right_ = NULL;
  return temp;
}
inline void Hydra::set_allocated_right(::experimot::msgs::Hydra_Paddle* right) {
  delete right_;
  right_ = right;
  if (right) {
    set_has_right();
  } else {
    clear_has_right();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Hydra.right)
}

// required .experimot.msgs.Hydra.Paddle left = 2;
inline bool Hydra::has_left() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hydra::set_has_left() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hydra::clear_has_left() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hydra::clear_left() {
  if (left_ != NULL) left_->::experimot::msgs::Hydra_Paddle::Clear();
  clear_has_left();
}
inline const ::experimot::msgs::Hydra_Paddle& Hydra::left() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Hydra.left)
  return left_ != NULL ? *left_ : *default_instance_->left_;
}
inline ::experimot::msgs::Hydra_Paddle* Hydra::mutable_left() {
  set_has_left();
  if (left_ == NULL) {
    left_ = new ::experimot::msgs::Hydra_Paddle;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Hydra.left)
  return left_;
}
inline ::experimot::msgs::Hydra_Paddle* Hydra::release_left() {
  clear_has_left();
  ::experimot::msgs::Hydra_Paddle* temp = left_;
  left_ = NULL;
  return temp;
}
inline void Hydra::set_allocated_left(::experimot::msgs::Hydra_Paddle* left) {
  delete left_;
  left_ = left;
  if (left) {
    set_has_left();
  } else {
    clear_has_left();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Hydra.left)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Hydra> HydraPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Hydra const> ConstHydraPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hydra_2eproto__INCLUDED
