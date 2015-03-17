// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: surface.proto

#ifndef PROTOBUF_surface_2eproto__INCLUDED
#define PROTOBUF_surface_2eproto__INCLUDED

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
#include "friction.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_surface_2eproto();
void protobuf_AssignDesc_surface_2eproto();
void protobuf_ShutdownFile_surface_2eproto();

class Surface;

// ===================================================================

class Surface : public ::google::protobuf::Message {
 public:
  Surface();
  virtual ~Surface();

  Surface(const Surface& from);

  inline Surface& operator=(const Surface& from) {
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
  static const Surface& default_instance();

  void Swap(Surface* other);

  // implements Message ----------------------------------------------

  inline Surface* New() const { return New(NULL); }

  Surface* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Surface& from);
  void MergeFrom(const Surface& from);
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
  void InternalSwap(Surface* other);
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

  // optional .experimot.msgs.Friction friction = 1;
  bool has_friction() const;
  void clear_friction();
  static const int kFrictionFieldNumber = 1;
  const ::experimot::msgs::Friction& friction() const;
  ::experimot::msgs::Friction* mutable_friction();
  ::experimot::msgs::Friction* release_friction();
  void set_allocated_friction(::experimot::msgs::Friction* friction);

  // optional double restitution_coefficient = 2;
  bool has_restitution_coefficient() const;
  void clear_restitution_coefficient();
  static const int kRestitutionCoefficientFieldNumber = 2;
  double restitution_coefficient() const;
  void set_restitution_coefficient(double value);

  // optional double bounce_threshold = 3;
  bool has_bounce_threshold() const;
  void clear_bounce_threshold();
  static const int kBounceThresholdFieldNumber = 3;
  double bounce_threshold() const;
  void set_bounce_threshold(double value);

  // optional double soft_cfm = 4;
  bool has_soft_cfm() const;
  void clear_soft_cfm();
  static const int kSoftCfmFieldNumber = 4;
  double soft_cfm() const;
  void set_soft_cfm(double value);

  // optional double soft_erp = 5;
  bool has_soft_erp() const;
  void clear_soft_erp();
  static const int kSoftErpFieldNumber = 5;
  double soft_erp() const;
  void set_soft_erp(double value);

  // optional double kp = 6;
  bool has_kp() const;
  void clear_kp();
  static const int kKpFieldNumber = 6;
  double kp() const;
  void set_kp(double value);

  // optional double kd = 7;
  bool has_kd() const;
  void clear_kd();
  static const int kKdFieldNumber = 7;
  double kd() const;
  void set_kd(double value);

  // optional double max_vel = 8;
  bool has_max_vel() const;
  void clear_max_vel();
  static const int kMaxVelFieldNumber = 8;
  double max_vel() const;
  void set_max_vel(double value);

  // optional double min_depth = 9;
  bool has_min_depth() const;
  void clear_min_depth();
  static const int kMinDepthFieldNumber = 9;
  double min_depth() const;
  void set_min_depth(double value);

  // optional bool collide_without_contact = 10;
  bool has_collide_without_contact() const;
  void clear_collide_without_contact();
  static const int kCollideWithoutContactFieldNumber = 10;
  bool collide_without_contact() const;
  void set_collide_without_contact(bool value);

  // optional uint32 collide_without_contact_bitmask = 11;
  bool has_collide_without_contact_bitmask() const;
  void clear_collide_without_contact_bitmask();
  static const int kCollideWithoutContactBitmaskFieldNumber = 11;
  ::google::protobuf::uint32 collide_without_contact_bitmask() const;
  void set_collide_without_contact_bitmask(::google::protobuf::uint32 value);

  // optional uint32 collide_bitmask = 12;
  bool has_collide_bitmask() const;
  void clear_collide_bitmask();
  static const int kCollideBitmaskFieldNumber = 12;
  ::google::protobuf::uint32 collide_bitmask() const;
  void set_collide_bitmask(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Surface)
 private:
  inline void set_has_friction();
  inline void clear_has_friction();
  inline void set_has_restitution_coefficient();
  inline void clear_has_restitution_coefficient();
  inline void set_has_bounce_threshold();
  inline void clear_has_bounce_threshold();
  inline void set_has_soft_cfm();
  inline void clear_has_soft_cfm();
  inline void set_has_soft_erp();
  inline void clear_has_soft_erp();
  inline void set_has_kp();
  inline void clear_has_kp();
  inline void set_has_kd();
  inline void clear_has_kd();
  inline void set_has_max_vel();
  inline void clear_has_max_vel();
  inline void set_has_min_depth();
  inline void clear_has_min_depth();
  inline void set_has_collide_without_contact();
  inline void clear_has_collide_without_contact();
  inline void set_has_collide_without_contact_bitmask();
  inline void clear_has_collide_without_contact_bitmask();
  inline void set_has_collide_bitmask();
  inline void clear_has_collide_bitmask();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::experimot::msgs::Friction* friction_;
  double restitution_coefficient_;
  double bounce_threshold_;
  double soft_cfm_;
  double soft_erp_;
  double kp_;
  double kd_;
  double max_vel_;
  double min_depth_;
  bool collide_without_contact_;
  ::google::protobuf::uint32 collide_without_contact_bitmask_;
  ::google::protobuf::uint32 collide_bitmask_;
  friend void  protobuf_AddDesc_surface_2eproto();
  friend void protobuf_AssignDesc_surface_2eproto();
  friend void protobuf_ShutdownFile_surface_2eproto();

  void InitAsDefaultInstance();
  static Surface* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Surface

// optional .experimot.msgs.Friction friction = 1;
inline bool Surface::has_friction() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Surface::set_has_friction() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Surface::clear_has_friction() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Surface::clear_friction() {
  if (friction_ != NULL) friction_->::experimot::msgs::Friction::Clear();
  clear_has_friction();
}
inline const ::experimot::msgs::Friction& Surface::friction() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.friction)
  return friction_ != NULL ? *friction_ : *default_instance_->friction_;
}
inline ::experimot::msgs::Friction* Surface::mutable_friction() {
  set_has_friction();
  if (friction_ == NULL) {
    friction_ = new ::experimot::msgs::Friction;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Surface.friction)
  return friction_;
}
inline ::experimot::msgs::Friction* Surface::release_friction() {
  clear_has_friction();
  ::experimot::msgs::Friction* temp = friction_;
  friction_ = NULL;
  return temp;
}
inline void Surface::set_allocated_friction(::experimot::msgs::Friction* friction) {
  delete friction_;
  friction_ = friction;
  if (friction) {
    set_has_friction();
  } else {
    clear_has_friction();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Surface.friction)
}

// optional double restitution_coefficient = 2;
inline bool Surface::has_restitution_coefficient() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Surface::set_has_restitution_coefficient() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Surface::clear_has_restitution_coefficient() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Surface::clear_restitution_coefficient() {
  restitution_coefficient_ = 0;
  clear_has_restitution_coefficient();
}
inline double Surface::restitution_coefficient() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.restitution_coefficient)
  return restitution_coefficient_;
}
inline void Surface::set_restitution_coefficient(double value) {
  set_has_restitution_coefficient();
  restitution_coefficient_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.restitution_coefficient)
}

// optional double bounce_threshold = 3;
inline bool Surface::has_bounce_threshold() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Surface::set_has_bounce_threshold() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Surface::clear_has_bounce_threshold() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Surface::clear_bounce_threshold() {
  bounce_threshold_ = 0;
  clear_has_bounce_threshold();
}
inline double Surface::bounce_threshold() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.bounce_threshold)
  return bounce_threshold_;
}
inline void Surface::set_bounce_threshold(double value) {
  set_has_bounce_threshold();
  bounce_threshold_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.bounce_threshold)
}

// optional double soft_cfm = 4;
inline bool Surface::has_soft_cfm() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Surface::set_has_soft_cfm() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Surface::clear_has_soft_cfm() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Surface::clear_soft_cfm() {
  soft_cfm_ = 0;
  clear_has_soft_cfm();
}
inline double Surface::soft_cfm() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.soft_cfm)
  return soft_cfm_;
}
inline void Surface::set_soft_cfm(double value) {
  set_has_soft_cfm();
  soft_cfm_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.soft_cfm)
}

// optional double soft_erp = 5;
inline bool Surface::has_soft_erp() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Surface::set_has_soft_erp() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Surface::clear_has_soft_erp() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Surface::clear_soft_erp() {
  soft_erp_ = 0;
  clear_has_soft_erp();
}
inline double Surface::soft_erp() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.soft_erp)
  return soft_erp_;
}
inline void Surface::set_soft_erp(double value) {
  set_has_soft_erp();
  soft_erp_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.soft_erp)
}

// optional double kp = 6;
inline bool Surface::has_kp() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Surface::set_has_kp() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Surface::clear_has_kp() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Surface::clear_kp() {
  kp_ = 0;
  clear_has_kp();
}
inline double Surface::kp() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.kp)
  return kp_;
}
inline void Surface::set_kp(double value) {
  set_has_kp();
  kp_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.kp)
}

// optional double kd = 7;
inline bool Surface::has_kd() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Surface::set_has_kd() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Surface::clear_has_kd() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Surface::clear_kd() {
  kd_ = 0;
  clear_has_kd();
}
inline double Surface::kd() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.kd)
  return kd_;
}
inline void Surface::set_kd(double value) {
  set_has_kd();
  kd_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.kd)
}

// optional double max_vel = 8;
inline bool Surface::has_max_vel() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Surface::set_has_max_vel() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Surface::clear_has_max_vel() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Surface::clear_max_vel() {
  max_vel_ = 0;
  clear_has_max_vel();
}
inline double Surface::max_vel() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.max_vel)
  return max_vel_;
}
inline void Surface::set_max_vel(double value) {
  set_has_max_vel();
  max_vel_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.max_vel)
}

// optional double min_depth = 9;
inline bool Surface::has_min_depth() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Surface::set_has_min_depth() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Surface::clear_has_min_depth() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Surface::clear_min_depth() {
  min_depth_ = 0;
  clear_has_min_depth();
}
inline double Surface::min_depth() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.min_depth)
  return min_depth_;
}
inline void Surface::set_min_depth(double value) {
  set_has_min_depth();
  min_depth_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.min_depth)
}

// optional bool collide_without_contact = 10;
inline bool Surface::has_collide_without_contact() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Surface::set_has_collide_without_contact() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Surface::clear_has_collide_without_contact() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Surface::clear_collide_without_contact() {
  collide_without_contact_ = false;
  clear_has_collide_without_contact();
}
inline bool Surface::collide_without_contact() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.collide_without_contact)
  return collide_without_contact_;
}
inline void Surface::set_collide_without_contact(bool value) {
  set_has_collide_without_contact();
  collide_without_contact_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.collide_without_contact)
}

// optional uint32 collide_without_contact_bitmask = 11;
inline bool Surface::has_collide_without_contact_bitmask() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Surface::set_has_collide_without_contact_bitmask() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Surface::clear_has_collide_without_contact_bitmask() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Surface::clear_collide_without_contact_bitmask() {
  collide_without_contact_bitmask_ = 0u;
  clear_has_collide_without_contact_bitmask();
}
inline ::google::protobuf::uint32 Surface::collide_without_contact_bitmask() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.collide_without_contact_bitmask)
  return collide_without_contact_bitmask_;
}
inline void Surface::set_collide_without_contact_bitmask(::google::protobuf::uint32 value) {
  set_has_collide_without_contact_bitmask();
  collide_without_contact_bitmask_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.collide_without_contact_bitmask)
}

// optional uint32 collide_bitmask = 12;
inline bool Surface::has_collide_bitmask() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Surface::set_has_collide_bitmask() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Surface::clear_has_collide_bitmask() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Surface::clear_collide_bitmask() {
  collide_bitmask_ = 0u;
  clear_has_collide_bitmask();
}
inline ::google::protobuf::uint32 Surface::collide_bitmask() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Surface.collide_bitmask)
  return collide_bitmask_;
}
inline void Surface::set_collide_bitmask(::google::protobuf::uint32 value) {
  set_has_collide_bitmask();
  collide_bitmask_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Surface.collide_bitmask)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Surface> SurfacePtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Surface const> ConstSurfacePtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_surface_2eproto__INCLUDED
