// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: model_v.proto

#ifndef PROTOBUF_model_5fv_2eproto__INCLUDED
#define PROTOBUF_model_5fv_2eproto__INCLUDED

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
#include "model.pb.h"
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_model_5fv_2eproto();
void protobuf_AssignDesc_model_5fv_2eproto();
void protobuf_ShutdownFile_model_5fv_2eproto();

class Model_V;

// ===================================================================

class Model_V : public ::google::protobuf::Message {
 public:
  Model_V();
  virtual ~Model_V();

  Model_V(const Model_V& from);

  inline Model_V& operator=(const Model_V& from) {
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
  static const Model_V& default_instance();

  void Swap(Model_V* other);

  // implements Message ----------------------------------------------

  inline Model_V* New() const { return New(NULL); }

  Model_V* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Model_V& from);
  void MergeFrom(const Model_V& from);
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
  void InternalSwap(Model_V* other);
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

  // repeated .experimot.msgs.Model models = 2;
  int models_size() const;
  void clear_models();
  static const int kModelsFieldNumber = 2;
  const ::experimot::msgs::Model& models(int index) const;
  ::experimot::msgs::Model* mutable_models(int index);
  ::experimot::msgs::Model* add_models();
  const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Model >&
      models() const;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Model >*
      mutable_models();

  // @@protoc_insertion_point(class_scope:experimot.msgs.Model_V)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Model > models_;
  friend void  protobuf_AddDesc_model_5fv_2eproto();
  friend void protobuf_AssignDesc_model_5fv_2eproto();
  friend void protobuf_ShutdownFile_model_5fv_2eproto();

  void InitAsDefaultInstance();
  static Model_V* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Model_V

// repeated .experimot.msgs.Model models = 2;
inline int Model_V::models_size() const {
  return models_.size();
}
inline void Model_V::clear_models() {
  models_.Clear();
}
inline const ::experimot::msgs::Model& Model_V::models(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Model_V.models)
  return models_.Get(index);
}
inline ::experimot::msgs::Model* Model_V::mutable_models(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Model_V.models)
  return models_.Mutable(index);
}
inline ::experimot::msgs::Model* Model_V::add_models() {
  // @@protoc_insertion_point(field_add:experimot.msgs.Model_V.models)
  return models_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Model >&
Model_V::models() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.Model_V.models)
  return models_;
}
inline ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Model >*
Model_V::mutable_models() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.Model_V.models)
  return &models_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

typedef boost::shared_ptr<experimot::msgs::Model_V> Model_VPtr;
// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

typedef const boost::shared_ptr<experimot::msgs::Model_V const> ConstModel_VPtr;
// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_model_5fv_2eproto__INCLUDED
