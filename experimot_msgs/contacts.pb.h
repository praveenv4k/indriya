// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: contacts.proto

#ifndef PROTOBUF_contacts_2eproto__INCLUDED
#define PROTOBUF_contacts_2eproto__INCLUDED

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
#include "contact.pb.h"
#include "time.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_contacts_2eproto();
void protobuf_AssignDesc_contacts_2eproto();
void protobuf_ShutdownFile_contacts_2eproto();

class Contacts;

// ===================================================================

class Contacts : public ::google::protobuf::Message {
 public:
  Contacts();
  virtual ~Contacts();

  Contacts(const Contacts& from);

  inline Contacts& operator=(const Contacts& from) {
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
  static const Contacts& default_instance();

  void Swap(Contacts* other);

  // implements Message ----------------------------------------------

  inline Contacts* New() const { return New(NULL); }

  Contacts* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Contacts& from);
  void MergeFrom(const Contacts& from);
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
  void InternalSwap(Contacts* other);
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

  // repeated .experimot.msgs.Contact contact = 1;
  int contact_size() const;
  void clear_contact();
  static const int kContactFieldNumber = 1;
  const ::experimot::msgs::Contact& contact(int index) const;
  ::experimot::msgs::Contact* mutable_contact(int index);
  ::experimot::msgs::Contact* add_contact();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Contact >&
      contact() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Contact >*
      mutable_contact();

  // required .experimot.msgs.Time time = 2;
  bool has_time() const;
  void clear_time();
  static const int kTimeFieldNumber = 2;
  const ::experimot::msgs::Time& time() const;
  ::experimot::msgs::Time* mutable_time();
  ::experimot::msgs::Time* release_time();
  void set_allocated_time(::experimot::msgs::Time* time);

  // @@protoc_insertion_point(class_scope:experimot.msgs.Contacts)
 private:
  inline void set_has_time();
  inline void clear_has_time();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Contact > contact_;
  ::experimot::msgs::Time* time_;
  friend void  protobuf_AddDesc_contacts_2eproto();
  friend void protobuf_AssignDesc_contacts_2eproto();
  friend void protobuf_ShutdownFile_contacts_2eproto();

  void InitAsDefaultInstance();
  static Contacts* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Contacts

// repeated .experimot.msgs.Contact contact = 1;
inline int Contacts::contact_size() const {
  return contact_.size();
}
inline void Contacts::clear_contact() {
  contact_.Clear();
}
inline const ::experimot::msgs::Contact& Contacts::contact(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Contacts.contact)
  return contact_.Get(index);
}
inline ::experimot::msgs::Contact* Contacts::mutable_contact(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Contacts.contact)
  return contact_.Mutable(index);
}
inline ::experimot::msgs::Contact* Contacts::add_contact() {
  // @@protoc_insertion_point(field_add:experimot.msgs.Contacts.contact)
  return contact_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Contact >&
Contacts::contact() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.Contacts.contact)
  return contact_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Contact >*
Contacts::mutable_contact() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.Contacts.contact)
  return &contact_;
}

// required .experimot.msgs.Time time = 2;
inline bool Contacts::has_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Contacts::set_has_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Contacts::clear_has_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Contacts::clear_time() {
  if (time_ != NULL) time_->::experimot::msgs::Time::Clear();
  clear_has_time();
}
inline const ::experimot::msgs::Time& Contacts::time() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Contacts.time)
  return time_ != NULL ? *time_ : *default_instance_->time_;
}
inline ::experimot::msgs::Time* Contacts::mutable_time() {
  set_has_time();
  if (time_ == NULL) {
    time_ = new ::experimot::msgs::Time;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Contacts.time)
  return time_;
}
inline ::experimot::msgs::Time* Contacts::release_time() {
  clear_has_time();
  ::experimot::msgs::Time* temp = time_;
  time_ = NULL;
  return temp;
}
inline void Contacts::set_allocated_time(::experimot::msgs::Time* time) {
  delete time_;
  time_ = time;
  if (time) {
    set_has_time();
  } else {
    clear_has_time();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Contacts.time)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Contacts> ContactsPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Contacts const> ConstContactsPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_contacts_2eproto__INCLUDED
