// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: propagation_grid.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "propagation_grid.pb.h"

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

const ::google::protobuf::Descriptor* PropagationGrid_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PropagationGrid_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_propagation_5fgrid_2eproto() {
  protobuf_AddDesc_propagation_5fgrid_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "propagation_grid.proto");
  GOOGLE_CHECK(file != NULL);
  PropagationGrid_descriptor_ = file->message_type(0);
  static const int PropagationGrid_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropagationGrid, particle_),
  };
  PropagationGrid_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      PropagationGrid_descriptor_,
      PropagationGrid::default_instance_,
      PropagationGrid_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropagationGrid, _has_bits_[0]),
      -1,
      -1,
      sizeof(PropagationGrid),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PropagationGrid, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_propagation_5fgrid_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      PropagationGrid_descriptor_, &PropagationGrid::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_propagation_5fgrid_2eproto() {
  delete PropagationGrid::default_instance_;
  delete PropagationGrid_reflection_;
}

void protobuf_AddDesc_propagation_5fgrid_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Indriya::Core::Msgs::protobuf_AddDesc_propagation_5fparticle_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026propagation_grid.proto\022\021Indriya.Core.M"
    "sgs\032\032propagation_particle.proto\"K\n\017Propa"
    "gationGrid\0228\n\010particle\030\001 \003(\0132&.Indriya.C"
    "ore.Msgs.PropagationParticle", 148);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "propagation_grid.proto", &protobuf_RegisterTypes);
  PropagationGrid::default_instance_ = new PropagationGrid();
  PropagationGrid::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_propagation_5fgrid_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_propagation_5fgrid_2eproto {
  StaticDescriptorInitializer_propagation_5fgrid_2eproto() {
    protobuf_AddDesc_propagation_5fgrid_2eproto();
  }
} static_descriptor_initializer_propagation_5fgrid_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int PropagationGrid::kParticleFieldNumber;
#endif  // !_MSC_VER

PropagationGrid::PropagationGrid()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Indriya.Core.Msgs.PropagationGrid)
}

void PropagationGrid::InitAsDefaultInstance() {
}

PropagationGrid::PropagationGrid(const PropagationGrid& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Indriya.Core.Msgs.PropagationGrid)
}

void PropagationGrid::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PropagationGrid::~PropagationGrid() {
  // @@protoc_insertion_point(destructor:Indriya.Core.Msgs.PropagationGrid)
  SharedDtor();
}

void PropagationGrid::SharedDtor() {
  if (this != default_instance_) {
  }
}

void PropagationGrid::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PropagationGrid::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PropagationGrid_descriptor_;
}

const PropagationGrid& PropagationGrid::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_propagation_5fgrid_2eproto();
  return *default_instance_;
}

PropagationGrid* PropagationGrid::default_instance_ = NULL;

PropagationGrid* PropagationGrid::New(::google::protobuf::Arena* arena) const {
  PropagationGrid* n = new PropagationGrid;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void PropagationGrid::Clear() {
  particle_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool PropagationGrid::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Indriya.Core.Msgs.PropagationGrid)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Indriya.Core.Msgs.PropagationParticle particle = 1;
      case 1: {
        if (tag == 10) {
         parse_particle:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_particle()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_particle;
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
  // @@protoc_insertion_point(parse_success:Indriya.Core.Msgs.PropagationGrid)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Indriya.Core.Msgs.PropagationGrid)
  return false;
#undef DO_
}

void PropagationGrid::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Indriya.Core.Msgs.PropagationGrid)
  // repeated .Indriya.Core.Msgs.PropagationParticle particle = 1;
  for (unsigned int i = 0, n = this->particle_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->particle(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Indriya.Core.Msgs.PropagationGrid)
}

::google::protobuf::uint8* PropagationGrid::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Indriya.Core.Msgs.PropagationGrid)
  // repeated .Indriya.Core.Msgs.PropagationParticle particle = 1;
  for (unsigned int i = 0, n = this->particle_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->particle(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Indriya.Core.Msgs.PropagationGrid)
  return target;
}

int PropagationGrid::ByteSize() const {
  int total_size = 0;

  // repeated .Indriya.Core.Msgs.PropagationParticle particle = 1;
  total_size += 1 * this->particle_size();
  for (int i = 0; i < this->particle_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->particle(i));
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

void PropagationGrid::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const PropagationGrid* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PropagationGrid*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PropagationGrid::MergeFrom(const PropagationGrid& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  particle_.MergeFrom(from.particle_);
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void PropagationGrid::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PropagationGrid::CopyFrom(const PropagationGrid& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PropagationGrid::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->particle())) return false;
  return true;
}

void PropagationGrid::Swap(PropagationGrid* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PropagationGrid::InternalSwap(PropagationGrid* other) {
  particle_.UnsafeArenaSwap(&other->particle_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata PropagationGrid::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PropagationGrid_descriptor_;
  metadata.reflection = PropagationGrid_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// PropagationGrid

// repeated .Indriya.Core.Msgs.PropagationParticle particle = 1;
 int PropagationGrid::particle_size() const {
  return particle_.size();
}
 void PropagationGrid::clear_particle() {
  particle_.Clear();
}
 const ::Indriya::Core::Msgs::PropagationParticle& PropagationGrid::particle(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.PropagationGrid.particle)
  return particle_.Get(index);
}
 ::Indriya::Core::Msgs::PropagationParticle* PropagationGrid::mutable_particle(int index) {
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.PropagationGrid.particle)
  return particle_.Mutable(index);
}
 ::Indriya::Core::Msgs::PropagationParticle* PropagationGrid::add_particle() {
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.PropagationGrid.particle)
  return particle_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::PropagationParticle >&
PropagationGrid::particle() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.PropagationGrid.particle)
  return particle_;
}
 ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::PropagationParticle >*
PropagationGrid::mutable_particle() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.PropagationGrid.particle)
  return &particle_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Msgs
}  // namespace Core
}  // namespace Indriya

EX_REGISTER_STATIC_MSG("Indriya.Core.Msgs.PropagationGrid", PropagationGrid)
// @@protoc_insertion_point(global_scope)
