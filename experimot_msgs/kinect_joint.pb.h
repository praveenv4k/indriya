// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kinect_joint.proto

#ifndef PROTOBUF_kinect_5fjoint_2eproto__INCLUDED
#define PROTOBUF_kinect_5fjoint_2eproto__INCLUDED

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
#include "vector3d.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_kinect_5fjoint_2eproto();
void protobuf_AssignDesc_kinect_5fjoint_2eproto();
void protobuf_ShutdownFile_kinect_5fjoint_2eproto();

class KinectJoint;

enum KinectJoint_TrackingState {
  KinectJoint_TrackingState_NotTracked = 0,
  KinectJoint_TrackingState_Inferred = 1,
  KinectJoint_TrackingState_Tracked = 2
};
bool KinectJoint_TrackingState_IsValid(int value);
const KinectJoint_TrackingState KinectJoint_TrackingState_TrackingState_MIN = KinectJoint_TrackingState_NotTracked;
const KinectJoint_TrackingState KinectJoint_TrackingState_TrackingState_MAX = KinectJoint_TrackingState_Tracked;
const int KinectJoint_TrackingState_TrackingState_ARRAYSIZE = KinectJoint_TrackingState_TrackingState_MAX + 1;

const ::google::protobuf::EnumDescriptor* KinectJoint_TrackingState_descriptor();
inline const ::std::string& KinectJoint_TrackingState_Name(KinectJoint_TrackingState value) {
  return ::google::protobuf::internal::NameOfEnum(
    KinectJoint_TrackingState_descriptor(), value);
}
inline bool KinectJoint_TrackingState_Parse(
    const ::std::string& name, KinectJoint_TrackingState* value) {
  return ::google::protobuf::internal::ParseNamedEnum<KinectJoint_TrackingState>(
    KinectJoint_TrackingState_descriptor(), name, value);
}
// ===================================================================

class KinectJoint : public ::google::protobuf::Message {
 public:
  KinectJoint();
  virtual ~KinectJoint();

  KinectJoint(const KinectJoint& from);

  inline KinectJoint& operator=(const KinectJoint& from) {
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
  static const KinectJoint& default_instance();

  void Swap(KinectJoint* other);

  // implements Message ----------------------------------------------

  inline KinectJoint* New() const { return New(NULL); }

  KinectJoint* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KinectJoint& from);
  void MergeFrom(const KinectJoint& from);
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
  void InternalSwap(KinectJoint* other);
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

  typedef KinectJoint_TrackingState TrackingState;
  static const TrackingState NotTracked = KinectJoint_TrackingState_NotTracked;
  static const TrackingState Inferred = KinectJoint_TrackingState_Inferred;
  static const TrackingState Tracked = KinectJoint_TrackingState_Tracked;
  static inline bool TrackingState_IsValid(int value) {
    return KinectJoint_TrackingState_IsValid(value);
  }
  static const TrackingState TrackingState_MIN =
    KinectJoint_TrackingState_TrackingState_MIN;
  static const TrackingState TrackingState_MAX =
    KinectJoint_TrackingState_TrackingState_MAX;
  static const int TrackingState_ARRAYSIZE =
    KinectJoint_TrackingState_TrackingState_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  TrackingState_descriptor() {
    return KinectJoint_TrackingState_descriptor();
  }
  static inline const ::std::string& TrackingState_Name(TrackingState value) {
    return KinectJoint_TrackingState_Name(value);
  }
  static inline bool TrackingState_Parse(const ::std::string& name,
      TrackingState* value) {
    return KinectJoint_TrackingState_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .experimot.msgs.KinectJoint.TrackingState State = 1;
  bool has_state() const;
  void clear_state();
  static const int kStateFieldNumber = 1;
  ::experimot::msgs::KinectJoint_TrackingState state() const;
  void set_state(::experimot::msgs::KinectJoint_TrackingState value);

  // required .experimot.msgs.Vector3d Position = 2;
  bool has_position() const;
  void clear_position();
  static const int kPositionFieldNumber = 2;
  const ::experimot::msgs::Vector3d& position() const;
  ::experimot::msgs::Vector3d* mutable_position();
  ::experimot::msgs::Vector3d* release_position();
  void set_allocated_position(::experimot::msgs::Vector3d* position);

  // @@protoc_insertion_point(class_scope:experimot.msgs.KinectJoint)
 private:
  inline void set_has_state();
  inline void clear_has_state();
  inline void set_has_position();
  inline void clear_has_position();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::experimot::msgs::Vector3d* position_;
  int state_;
  friend void  protobuf_AddDesc_kinect_5fjoint_2eproto();
  friend void protobuf_AssignDesc_kinect_5fjoint_2eproto();
  friend void protobuf_ShutdownFile_kinect_5fjoint_2eproto();

  void InitAsDefaultInstance();
  static KinectJoint* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// KinectJoint

// required .experimot.msgs.KinectJoint.TrackingState State = 1;
inline bool KinectJoint::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KinectJoint::set_has_state() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KinectJoint::clear_has_state() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KinectJoint::clear_state() {
  state_ = 0;
  clear_has_state();
}
inline ::experimot::msgs::KinectJoint_TrackingState KinectJoint::state() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.KinectJoint.State)
  return static_cast< ::experimot::msgs::KinectJoint_TrackingState >(state_);
}
inline void KinectJoint::set_state(::experimot::msgs::KinectJoint_TrackingState value) {
  assert(::experimot::msgs::KinectJoint_TrackingState_IsValid(value));
  set_has_state();
  state_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.KinectJoint.State)
}

// required .experimot.msgs.Vector3d Position = 2;
inline bool KinectJoint::has_position() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KinectJoint::set_has_position() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KinectJoint::clear_has_position() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KinectJoint::clear_position() {
  if (position_ != NULL) position_->::experimot::msgs::Vector3d::Clear();
  clear_has_position();
}
inline const ::experimot::msgs::Vector3d& KinectJoint::position() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.KinectJoint.Position)
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::experimot::msgs::Vector3d* KinectJoint::mutable_position() {
  set_has_position();
  if (position_ == NULL) {
    position_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.KinectJoint.Position)
  return position_;
}
inline ::experimot::msgs::Vector3d* KinectJoint::release_position() {
  clear_has_position();
  ::experimot::msgs::Vector3d* temp = position_;
  position_ = NULL;
  return temp;
}
inline void KinectJoint::set_allocated_position(::experimot::msgs::Vector3d* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.KinectJoint.Position)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::KinectJoint> KinectJointPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::experimot::msgs::KinectJoint_TrackingState> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::experimot::msgs::KinectJoint_TrackingState>() {
  return ::experimot::msgs::KinectJoint_TrackingState_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

typedef const boost::shared_ptr<experimot::msgs::KinectJoint const> ConstKinectJointPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_kinect_5fjoint_2eproto__INCLUDED