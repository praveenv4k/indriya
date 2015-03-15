// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: planegeom.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "planegeom.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace experimot {
namespace msgs {

namespace {

const ::google::protobuf::Descriptor* PlaneGeom_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PlaneGeom_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_planegeom_2eproto() {
  protobuf_AddDesc_planegeom_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "planegeom.proto");
  GOOGLE_CHECK(file != NULL);
  PlaneGeom_descriptor_ = file->message_type(0);
  static const int PlaneGeom_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlaneGeom, normal_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlaneGeom, size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlaneGeom, d_),
  };
  PlaneGeom_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      PlaneGeom_descriptor_,
      PlaneGeom::default_instance_,
      PlaneGeom_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlaneGeom, _has_bits_[0]),
      -1,
      -1,
      sizeof(PlaneGeom),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlaneGeom, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_planegeom_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      PlaneGeom_descriptor_, &PlaneGeom::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_planegeom_2eproto() {
  delete PlaneGeom::default_instance_;
  delete PlaneGeom_reflection_;
}

void protobuf_AddDesc_planegeom_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::experimot::msgs::protobuf_AddDesc_vector3d_2eproto();
  ::experimot::msgs::protobuf_AddDesc_vector2d_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017planegeom.proto\022\016experimot.msgs\032\016vecto"
    "r3d.proto\032\016vector2d.proto\"k\n\tPlaneGeom\022("
    "\n\006normal\030\001 \002(\0132\030.experimot.msgs.Vector3d"
    "\022&\n\004size\030\002 \002(\0132\030.experimot.msgs.Vector2d"
    "\022\014\n\001d\030\003 \001(\001:\0010", 174);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "planegeom.proto", &protobuf_RegisterTypes);
  PlaneGeom::default_instance_ = new PlaneGeom();
  PlaneGeom::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_planegeom_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_planegeom_2eproto {
  StaticDescriptorInitializer_planegeom_2eproto() {
    protobuf_AddDesc_planegeom_2eproto();
  }
} static_descriptor_initializer_planegeom_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int PlaneGeom::kNormalFieldNumber;
const int PlaneGeom::kSizeFieldNumber;
const int PlaneGeom::kDFieldNumber;
#endif  // !_MSC_VER

PlaneGeom::PlaneGeom()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.PlaneGeom)
}

void PlaneGeom::InitAsDefaultInstance() {
  normal_ = const_cast< ::experimot::msgs::Vector3d*>(&::experimot::msgs::Vector3d::default_instance());
  size_ = const_cast< ::experimot::msgs::Vector2d*>(&::experimot::msgs::Vector2d::default_instance());
}

PlaneGeom::PlaneGeom(const PlaneGeom& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.PlaneGeom)
}

void PlaneGeom::SharedCtor() {
  _cached_size_ = 0;
  normal_ = NULL;
  size_ = NULL;
  d_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PlaneGeom::~PlaneGeom() {
  // @@protoc_insertion_point(destructor:experimot.msgs.PlaneGeom)
  SharedDtor();
}

void PlaneGeom::SharedDtor() {
  if (this != default_instance_) {
    delete normal_;
    delete size_;
  }
}

void PlaneGeom::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PlaneGeom::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PlaneGeom_descriptor_;
}

const PlaneGeom& PlaneGeom::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_planegeom_2eproto();
  return *default_instance_;
}

PlaneGeom* PlaneGeom::default_instance_ = NULL;

PlaneGeom* PlaneGeom::New(::google::protobuf::Arena* arena) const {
  PlaneGeom* n = new PlaneGeom;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void PlaneGeom::Clear() {
  if (_has_bits_[0 / 32] & 7) {
    if (has_normal()) {
      if (normal_ != NULL) normal_->::experimot::msgs::Vector3d::Clear();
    }
    if (has_size()) {
      if (size_ != NULL) size_->::experimot::msgs::Vector2d::Clear();
    }
    d_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool PlaneGeom::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.PlaneGeom)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .experimot.msgs.Vector3d normal = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_normal()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_size;
        break;
      }

      // required .experimot.msgs.Vector2d size = 2;
      case 2: {
        if (tag == 18) {
         parse_size:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_size()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_d;
        break;
      }

      // optional double d = 3 [default = 0];
      case 3: {
        if (tag == 25) {
         parse_d:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &d_)));
          set_has_d();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:experimot.msgs.PlaneGeom)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.PlaneGeom)
  return false;
#undef DO_
}

void PlaneGeom::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.PlaneGeom)
  // required .experimot.msgs.Vector3d normal = 1;
  if (has_normal()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->normal_, output);
  }

  // required .experimot.msgs.Vector2d size = 2;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->size_, output);
  }

  // optional double d = 3 [default = 0];
  if (has_d()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->d(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.PlaneGeom)
}

::google::protobuf::uint8* PlaneGeom::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.PlaneGeom)
  // required .experimot.msgs.Vector3d normal = 1;
  if (has_normal()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, *this->normal_, target);
  }

  // required .experimot.msgs.Vector2d size = 2;
  if (has_size()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, *this->size_, target);
  }

  // optional double d = 3 [default = 0];
  if (has_d()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->d(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.PlaneGeom)
  return target;
}

int PlaneGeom::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_normal()) {
    // required .experimot.msgs.Vector3d normal = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->normal_);
  }

  if (has_size()) {
    // required .experimot.msgs.Vector2d size = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->size_);
  }

  return total_size;
}
int PlaneGeom::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .experimot.msgs.Vector3d normal = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->normal_);

    // required .experimot.msgs.Vector2d size = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->size_);

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // optional double d = 3 [default = 0];
  if (has_d()) {
    total_size += 1 + 8;
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PlaneGeom::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const PlaneGeom* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PlaneGeom*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PlaneGeom::MergeFrom(const PlaneGeom& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_normal()) {
      mutable_normal()->::experimot::msgs::Vector3d::MergeFrom(from.normal());
    }
    if (from.has_size()) {
      mutable_size()->::experimot::msgs::Vector2d::MergeFrom(from.size());
    }
    if (from.has_d()) {
      set_d(from.d());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void PlaneGeom::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PlaneGeom::CopyFrom(const PlaneGeom& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PlaneGeom::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_normal()) {
    if (!this->normal_->IsInitialized()) return false;
  }
  if (has_size()) {
    if (!this->size_->IsInitialized()) return false;
  }
  return true;
}

void PlaneGeom::Swap(PlaneGeom* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PlaneGeom::InternalSwap(PlaneGeom* other) {
  std::swap(normal_, other->normal_);
  std::swap(size_, other->size_);
  std::swap(d_, other->d_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata PlaneGeom::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PlaneGeom_descriptor_;
  metadata.reflection = PlaneGeom_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// PlaneGeom

// required .experimot.msgs.Vector3d normal = 1;
 bool PlaneGeom::has_normal() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void PlaneGeom::set_has_normal() {
  _has_bits_[0] |= 0x00000001u;
}
 void PlaneGeom::clear_has_normal() {
  _has_bits_[0] &= ~0x00000001u;
}
 void PlaneGeom::clear_normal() {
  if (normal_ != NULL) normal_->::experimot::msgs::Vector3d::Clear();
  clear_has_normal();
}
 const ::experimot::msgs::Vector3d& PlaneGeom::normal() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.PlaneGeom.normal)
  return normal_ != NULL ? *normal_ : *default_instance_->normal_;
}
 ::experimot::msgs::Vector3d* PlaneGeom::mutable_normal() {
  set_has_normal();
  if (normal_ == NULL) {
    normal_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.PlaneGeom.normal)
  return normal_;
}
 ::experimot::msgs::Vector3d* PlaneGeom::release_normal() {
  clear_has_normal();
  ::experimot::msgs::Vector3d* temp = normal_;
  normal_ = NULL;
  return temp;
}
 void PlaneGeom::set_allocated_normal(::experimot::msgs::Vector3d* normal) {
  delete normal_;
  normal_ = normal;
  if (normal) {
    set_has_normal();
  } else {
    clear_has_normal();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.PlaneGeom.normal)
}

// required .experimot.msgs.Vector2d size = 2;
 bool PlaneGeom::has_size() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void PlaneGeom::set_has_size() {
  _has_bits_[0] |= 0x00000002u;
}
 void PlaneGeom::clear_has_size() {
  _has_bits_[0] &= ~0x00000002u;
}
 void PlaneGeom::clear_size() {
  if (size_ != NULL) size_->::experimot::msgs::Vector2d::Clear();
  clear_has_size();
}
 const ::experimot::msgs::Vector2d& PlaneGeom::size() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.PlaneGeom.size)
  return size_ != NULL ? *size_ : *default_instance_->size_;
}
 ::experimot::msgs::Vector2d* PlaneGeom::mutable_size() {
  set_has_size();
  if (size_ == NULL) {
    size_ = new ::experimot::msgs::Vector2d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.PlaneGeom.size)
  return size_;
}
 ::experimot::msgs::Vector2d* PlaneGeom::release_size() {
  clear_has_size();
  ::experimot::msgs::Vector2d* temp = size_;
  size_ = NULL;
  return temp;
}
 void PlaneGeom::set_allocated_size(::experimot::msgs::Vector2d* size) {
  delete size_;
  size_ = size;
  if (size) {
    set_has_size();
  } else {
    clear_has_size();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.PlaneGeom.size)
}

// optional double d = 3 [default = 0];
 bool PlaneGeom::has_d() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void PlaneGeom::set_has_d() {
  _has_bits_[0] |= 0x00000004u;
}
 void PlaneGeom::clear_has_d() {
  _has_bits_[0] &= ~0x00000004u;
}
 void PlaneGeom::clear_d() {
  d_ = 0;
  clear_has_d();
}
 double PlaneGeom::d() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.PlaneGeom.d)
  return d_;
}
 void PlaneGeom::set_d(double value) {
  set_has_d();
  d_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.PlaneGeom.d)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.PlaneGeom", PlaneGeom)
// @@protoc_insertion_point(global_scope)
