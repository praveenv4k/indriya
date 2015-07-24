// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: wrench.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "wrench.pb.h"

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

namespace Indriya {
namespace Core {
namespace Msgs {

namespace {

const ::google::protobuf::Descriptor* Wrench_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Wrench_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_wrench_2eproto() {
  protobuf_AddDesc_wrench_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "wrench.proto");
  GOOGLE_CHECK(file != NULL);
  Wrench_descriptor_ = file->message_type(0);
  static const int Wrench_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wrench, force_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wrench, torque_),
  };
  Wrench_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Wrench_descriptor_,
      Wrench::default_instance_,
      Wrench_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wrench, _has_bits_[0]),
      -1,
      -1,
      sizeof(Wrench),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wrench, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_wrench_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Wrench_descriptor_, &Wrench::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_wrench_2eproto() {
  delete Wrench::default_instance_;
  delete Wrench_reflection_;
}

void protobuf_AddDesc_wrench_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Indriya::Core::Msgs::protobuf_AddDesc_vector3d_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014wrench.proto\022\021Indriya.Core.Msgs\032\016vecto"
    "r3d.proto\"a\n\006Wrench\022*\n\005force\030\001 \002(\0132\033.Ind"
    "riya.Core.Msgs.Vector3d\022+\n\006torque\030\002 \002(\0132"
    "\033.Indriya.Core.Msgs.Vector3d", 148);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "wrench.proto", &protobuf_RegisterTypes);
  Wrench::default_instance_ = new Wrench();
  Wrench::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_wrench_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_wrench_2eproto {
  StaticDescriptorInitializer_wrench_2eproto() {
    protobuf_AddDesc_wrench_2eproto();
  }
} static_descriptor_initializer_wrench_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Wrench::kForceFieldNumber;
const int Wrench::kTorqueFieldNumber;
#endif  // !_MSC_VER

Wrench::Wrench()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Indriya.Core.Msgs.Wrench)
}

void Wrench::InitAsDefaultInstance() {
  force_ = const_cast< ::Indriya::Core::Msgs::Vector3d*>(&::Indriya::Core::Msgs::Vector3d::default_instance());
  torque_ = const_cast< ::Indriya::Core::Msgs::Vector3d*>(&::Indriya::Core::Msgs::Vector3d::default_instance());
}

Wrench::Wrench(const Wrench& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Indriya.Core.Msgs.Wrench)
}

void Wrench::SharedCtor() {
  _cached_size_ = 0;
  force_ = NULL;
  torque_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Wrench::~Wrench() {
  // @@protoc_insertion_point(destructor:Indriya.Core.Msgs.Wrench)
  SharedDtor();
}

void Wrench::SharedDtor() {
  if (this != default_instance_) {
    delete force_;
    delete torque_;
  }
}

void Wrench::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Wrench::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Wrench_descriptor_;
}

const Wrench& Wrench::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_wrench_2eproto();
  return *default_instance_;
}

Wrench* Wrench::default_instance_ = NULL;

Wrench* Wrench::New(::google::protobuf::Arena* arena) const {
  Wrench* n = new Wrench;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Wrench::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_force()) {
      if (force_ != NULL) force_->::Indriya::Core::Msgs::Vector3d::Clear();
    }
    if (has_torque()) {
      if (torque_ != NULL) torque_->::Indriya::Core::Msgs::Vector3d::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Wrench::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Indriya.Core.Msgs.Wrench)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .Indriya.Core.Msgs.Vector3d force = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_force()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_torque;
        break;
      }

      // required .Indriya.Core.Msgs.Vector3d torque = 2;
      case 2: {
        if (tag == 18) {
         parse_torque:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_torque()));
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
  // @@protoc_insertion_point(parse_success:Indriya.Core.Msgs.Wrench)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Indriya.Core.Msgs.Wrench)
  return false;
#undef DO_
}

void Wrench::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Indriya.Core.Msgs.Wrench)
  // required .Indriya.Core.Msgs.Vector3d force = 1;
  if (has_force()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->force_, output);
  }

  // required .Indriya.Core.Msgs.Vector3d torque = 2;
  if (has_torque()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->torque_, output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Indriya.Core.Msgs.Wrench)
}

::google::protobuf::uint8* Wrench::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Indriya.Core.Msgs.Wrench)
  // required .Indriya.Core.Msgs.Vector3d force = 1;
  if (has_force()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, *this->force_, target);
  }

  // required .Indriya.Core.Msgs.Vector3d torque = 2;
  if (has_torque()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, *this->torque_, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Indriya.Core.Msgs.Wrench)
  return target;
}

int Wrench::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_force()) {
    // required .Indriya.Core.Msgs.Vector3d force = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->force_);
  }

  if (has_torque()) {
    // required .Indriya.Core.Msgs.Vector3d torque = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->torque_);
  }

  return total_size;
}
int Wrench::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .Indriya.Core.Msgs.Vector3d force = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->force_);

    // required .Indriya.Core.Msgs.Vector3d torque = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->torque_);

  } else {
    total_size += RequiredFieldsByteSizeFallback();
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

void Wrench::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Wrench* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Wrench*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Wrench::MergeFrom(const Wrench& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_force()) {
      mutable_force()->::Indriya::Core::Msgs::Vector3d::MergeFrom(from.force());
    }
    if (from.has_torque()) {
      mutable_torque()->::Indriya::Core::Msgs::Vector3d::MergeFrom(from.torque());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void Wrench::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Wrench::CopyFrom(const Wrench& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Wrench::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_force()) {
    if (!this->force_->IsInitialized()) return false;
  }
  if (has_torque()) {
    if (!this->torque_->IsInitialized()) return false;
  }
  return true;
}

void Wrench::Swap(Wrench* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Wrench::InternalSwap(Wrench* other) {
  std::swap(force_, other->force_);
  std::swap(torque_, other->torque_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Wrench::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Wrench_descriptor_;
  metadata.reflection = Wrench_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Wrench

// required .Indriya.Core.Msgs.Vector3d force = 1;
 bool Wrench::has_force() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Wrench::set_has_force() {
  _has_bits_[0] |= 0x00000001u;
}
 void Wrench::clear_has_force() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Wrench::clear_force() {
  if (force_ != NULL) force_->::Indriya::Core::Msgs::Vector3d::Clear();
  clear_has_force();
}
 const ::Indriya::Core::Msgs::Vector3d& Wrench::force() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Wrench.force)
  return force_ != NULL ? *force_ : *default_instance_->force_;
}
 ::Indriya::Core::Msgs::Vector3d* Wrench::mutable_force() {
  set_has_force();
  if (force_ == NULL) {
    force_ = new ::Indriya::Core::Msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Wrench.force)
  return force_;
}
 ::Indriya::Core::Msgs::Vector3d* Wrench::release_force() {
  clear_has_force();
  ::Indriya::Core::Msgs::Vector3d* temp = force_;
  force_ = NULL;
  return temp;
}
 void Wrench::set_allocated_force(::Indriya::Core::Msgs::Vector3d* force) {
  delete force_;
  force_ = force;
  if (force) {
    set_has_force();
  } else {
    clear_has_force();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Wrench.force)
}

// required .Indriya.Core.Msgs.Vector3d torque = 2;
 bool Wrench::has_torque() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Wrench::set_has_torque() {
  _has_bits_[0] |= 0x00000002u;
}
 void Wrench::clear_has_torque() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Wrench::clear_torque() {
  if (torque_ != NULL) torque_->::Indriya::Core::Msgs::Vector3d::Clear();
  clear_has_torque();
}
 const ::Indriya::Core::Msgs::Vector3d& Wrench::torque() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Wrench.torque)
  return torque_ != NULL ? *torque_ : *default_instance_->torque_;
}
 ::Indriya::Core::Msgs::Vector3d* Wrench::mutable_torque() {
  set_has_torque();
  if (torque_ == NULL) {
    torque_ = new ::Indriya::Core::Msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Wrench.torque)
  return torque_;
}
 ::Indriya::Core::Msgs::Vector3d* Wrench::release_torque() {
  clear_has_torque();
  ::Indriya::Core::Msgs::Vector3d* temp = torque_;
  torque_ = NULL;
  return temp;
}
 void Wrench::set_allocated_torque(::Indriya::Core::Msgs::Vector3d* torque) {
  delete torque_;
  torque_ = torque;
  if (torque) {
    set_has_torque();
  } else {
    clear_has_torque();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Wrench.torque)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Msgs
}  // namespace Core
}  // namespace Indriya

EX_REGISTER_STATIC_MSG("Indriya.Core.Msgs.Wrench", Wrench)
// @@protoc_insertion_point(global_scope)