// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: friction.proto

#ifndef PROTOBUF_friction_2eproto__INCLUDED
#define PROTOBUF_friction_2eproto__INCLUDED

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
#include "vector3d.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_friction_2eproto();
void protobuf_AssignDesc_friction_2eproto();
void protobuf_ShutdownFile_friction_2eproto();

class Friction;

// ===================================================================

class Friction : public ::google::protobuf::Message {
 public:
  Friction();
  virtual ~Friction();

  Friction(const Friction& from);

  inline Friction& operator=(const Friction& from) {
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
  static const Friction& default_instance();

  void Swap(Friction* other);

  // implements Message ----------------------------------------------

  inline Friction* New() const { return New(NULL); }

  Friction* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Friction& from);
  void MergeFrom(const Friction& from);
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
  void InternalSwap(Friction* other);
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

  // optional double mu = 1;
  bool has_mu() const;
  void clear_mu();
  static const int kMuFieldNumber = 1;
  double mu() const;
  void set_mu(double value);

  // optional double mu2 = 2;
  bool has_mu2() const;
  void clear_mu2();
  static const int kMu2FieldNumber = 2;
  double mu2() const;
  void set_mu2(double value);

  // optional .experimot.msgs.Vector3d fdir1 = 3;
  bool has_fdir1() const;
  void clear_fdir1();
  static const int kFdir1FieldNumber = 3;
  const ::experimot::msgs::Vector3d& fdir1() const;
  ::experimot::msgs::Vector3d* mutable_fdir1();
  ::experimot::msgs::Vector3d* release_fdir1();
  void set_allocated_fdir1(::experimot::msgs::Vector3d* fdir1);

  // optional double slip1 = 4;
  bool has_slip1() const;
  void clear_slip1();
  static const int kSlip1FieldNumber = 4;
  double slip1() const;
  void set_slip1(double value);

  // optional double slip2 = 5;
  bool has_slip2() const;
  void clear_slip2();
  static const int kSlip2FieldNumber = 5;
  double slip2() const;
  void set_slip2(double value);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Friction)
 private:
  inline void set_has_mu();
  inline void clear_has_mu();
  inline void set_has_mu2();
  inline void clear_has_mu2();
  inline void set_has_fdir1();
  inline void clear_has_fdir1();
  inline void set_has_slip1();
  inline void clear_has_slip1();
  inline void set_has_slip2();
  inline void clear_has_slip2();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  double mu_;
  double mu2_;
  ::experimot::msgs::Vector3d* fdir1_;
  double slip1_;
  double slip2_;
  friend void  protobuf_AddDesc_friction_2eproto();
  friend void protobuf_AssignDesc_friction_2eproto();
  friend void protobuf_ShutdownFile_friction_2eproto();

  void InitAsDefaultInstance();
  static Friction* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Friction

// optional double mu = 1;
inline bool Friction::has_mu() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Friction::set_has_mu() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Friction::clear_has_mu() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Friction::clear_mu() {
  mu_ = 0;
  clear_has_mu();
}
inline double Friction::mu() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Friction.mu)
  return mu_;
}
inline void Friction::set_mu(double value) {
  set_has_mu();
  mu_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Friction.mu)
}

// optional double mu2 = 2;
inline bool Friction::has_mu2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Friction::set_has_mu2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Friction::clear_has_mu2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Friction::clear_mu2() {
  mu2_ = 0;
  clear_has_mu2();
}
inline double Friction::mu2() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Friction.mu2)
  return mu2_;
}
inline void Friction::set_mu2(double value) {
  set_has_mu2();
  mu2_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Friction.mu2)
}

// optional .experimot.msgs.Vector3d fdir1 = 3;
inline bool Friction::has_fdir1() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Friction::set_has_fdir1() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Friction::clear_has_fdir1() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Friction::clear_fdir1() {
  if (fdir1_ != NULL) fdir1_->::experimot::msgs::Vector3d::Clear();
  clear_has_fdir1();
}
inline const ::experimot::msgs::Vector3d& Friction::fdir1() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Friction.fdir1)
  return fdir1_ != NULL ? *fdir1_ : *default_instance_->fdir1_;
}
inline ::experimot::msgs::Vector3d* Friction::mutable_fdir1() {
  set_has_fdir1();
  if (fdir1_ == NULL) {
    fdir1_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Friction.fdir1)
  return fdir1_;
}
inline ::experimot::msgs::Vector3d* Friction::release_fdir1() {
  clear_has_fdir1();
  ::experimot::msgs::Vector3d* temp = fdir1_;
  fdir1_ = NULL;
  return temp;
}
inline void Friction::set_allocated_fdir1(::experimot::msgs::Vector3d* fdir1) {
  delete fdir1_;
  fdir1_ = fdir1;
  if (fdir1) {
    set_has_fdir1();
  } else {
    clear_has_fdir1();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Friction.fdir1)
}

// optional double slip1 = 4;
inline bool Friction::has_slip1() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Friction::set_has_slip1() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Friction::clear_has_slip1() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Friction::clear_slip1() {
  slip1_ = 0;
  clear_has_slip1();
}
inline double Friction::slip1() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Friction.slip1)
  return slip1_;
}
inline void Friction::set_slip1(double value) {
  set_has_slip1();
  slip1_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Friction.slip1)
}

// optional double slip2 = 5;
inline bool Friction::has_slip2() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Friction::set_has_slip2() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Friction::clear_has_slip2() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Friction::clear_slip2() {
  slip2_ = 0;
  clear_has_slip2();
}
inline double Friction::slip2() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Friction.slip2)
  return slip2_;
}
inline void Friction::set_slip2(double value) {
  set_has_slip2();
  slip2_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Friction.slip2)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Friction> FrictionPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Friction const> ConstFrictionPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_friction_2eproto__INCLUDED
