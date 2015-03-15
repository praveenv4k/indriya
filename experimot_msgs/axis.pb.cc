// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: axis.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "axis.pb.h"

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

const ::google::protobuf::Descriptor* Axis_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Axis_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_axis_2eproto() {
  protobuf_AddDesc_axis_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "axis.proto");
  GOOGLE_CHECK(file != NULL);
  Axis_descriptor_ = file->message_type(0);
  static const int Axis_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, xyz_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, limit_lower_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, limit_upper_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, limit_effort_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, limit_velocity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, damping_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, friction_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, use_parent_model_frame_),
  };
  Axis_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Axis_descriptor_,
      Axis::default_instance_,
      Axis_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, _has_bits_[0]),
      -1,
      -1,
      sizeof(Axis),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Axis, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_axis_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Axis_descriptor_, &Axis::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_axis_2eproto() {
  delete Axis::default_instance_;
  delete Axis_reflection_;
}

void protobuf_AddDesc_axis_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::experimot::msgs::protobuf_AddDesc_vector3d_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\naxis.proto\022\016experimot.msgs\032\016vector3d.p"
    "roto\"\310\001\n\004Axis\022%\n\003xyz\030\001 \002(\0132\030.experimot.m"
    "sgs.Vector3d\022\023\n\013limit_lower\030\002 \002(\001\022\023\n\013lim"
    "it_upper\030\003 \002(\001\022\024\n\014limit_effort\030\004 \002(\001\022\026\n\016"
    "limit_velocity\030\005 \002(\001\022\017\n\007damping\030\006 \002(\001\022\020\n"
    "\010friction\030\007 \002(\001\022\036\n\026use_parent_model_fram"
    "e\030\010 \002(\010", 247);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "axis.proto", &protobuf_RegisterTypes);
  Axis::default_instance_ = new Axis();
  Axis::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_axis_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_axis_2eproto {
  StaticDescriptorInitializer_axis_2eproto() {
    protobuf_AddDesc_axis_2eproto();
  }
} static_descriptor_initializer_axis_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Axis::kXyzFieldNumber;
const int Axis::kLimitLowerFieldNumber;
const int Axis::kLimitUpperFieldNumber;
const int Axis::kLimitEffortFieldNumber;
const int Axis::kLimitVelocityFieldNumber;
const int Axis::kDampingFieldNumber;
const int Axis::kFrictionFieldNumber;
const int Axis::kUseParentModelFrameFieldNumber;
#endif  // !_MSC_VER

Axis::Axis()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.Axis)
}

void Axis::InitAsDefaultInstance() {
  xyz_ = const_cast< ::experimot::msgs::Vector3d*>(&::experimot::msgs::Vector3d::default_instance());
}

Axis::Axis(const Axis& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.Axis)
}

void Axis::SharedCtor() {
  _cached_size_ = 0;
  xyz_ = NULL;
  limit_lower_ = 0;
  limit_upper_ = 0;
  limit_effort_ = 0;
  limit_velocity_ = 0;
  damping_ = 0;
  friction_ = 0;
  use_parent_model_frame_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Axis::~Axis() {
  // @@protoc_insertion_point(destructor:experimot.msgs.Axis)
  SharedDtor();
}

void Axis::SharedDtor() {
  if (this != default_instance_) {
    delete xyz_;
  }
}

void Axis::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Axis::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Axis_descriptor_;
}

const Axis& Axis::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_axis_2eproto();
  return *default_instance_;
}

Axis* Axis::default_instance_ = NULL;

Axis* Axis::New(::google::protobuf::Arena* arena) const {
  Axis* n = new Axis;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Axis::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<Axis*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(limit_lower_, use_parent_model_frame_);
    if (has_xyz()) {
      if (xyz_ != NULL) xyz_->::experimot::msgs::Vector3d::Clear();
    }
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Axis::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.Axis)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .experimot.msgs.Vector3d xyz = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_xyz()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_limit_lower;
        break;
      }

      // required double limit_lower = 2;
      case 2: {
        if (tag == 17) {
         parse_limit_lower:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &limit_lower_)));
          set_has_limit_lower();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_limit_upper;
        break;
      }

      // required double limit_upper = 3;
      case 3: {
        if (tag == 25) {
         parse_limit_upper:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &limit_upper_)));
          set_has_limit_upper();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_limit_effort;
        break;
      }

      // required double limit_effort = 4;
      case 4: {
        if (tag == 33) {
         parse_limit_effort:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &limit_effort_)));
          set_has_limit_effort();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_limit_velocity;
        break;
      }

      // required double limit_velocity = 5;
      case 5: {
        if (tag == 41) {
         parse_limit_velocity:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &limit_velocity_)));
          set_has_limit_velocity();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_damping;
        break;
      }

      // required double damping = 6;
      case 6: {
        if (tag == 49) {
         parse_damping:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &damping_)));
          set_has_damping();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_friction;
        break;
      }

      // required double friction = 7;
      case 7: {
        if (tag == 57) {
         parse_friction:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &friction_)));
          set_has_friction();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_use_parent_model_frame;
        break;
      }

      // required bool use_parent_model_frame = 8;
      case 8: {
        if (tag == 64) {
         parse_use_parent_model_frame:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &use_parent_model_frame_)));
          set_has_use_parent_model_frame();
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.Axis)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.Axis)
  return false;
#undef DO_
}

void Axis::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.Axis)
  // required .experimot.msgs.Vector3d xyz = 1;
  if (has_xyz()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->xyz_, output);
  }

  // required double limit_lower = 2;
  if (has_limit_lower()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->limit_lower(), output);
  }

  // required double limit_upper = 3;
  if (has_limit_upper()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->limit_upper(), output);
  }

  // required double limit_effort = 4;
  if (has_limit_effort()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->limit_effort(), output);
  }

  // required double limit_velocity = 5;
  if (has_limit_velocity()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->limit_velocity(), output);
  }

  // required double damping = 6;
  if (has_damping()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->damping(), output);
  }

  // required double friction = 7;
  if (has_friction()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->friction(), output);
  }

  // required bool use_parent_model_frame = 8;
  if (has_use_parent_model_frame()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->use_parent_model_frame(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.Axis)
}

::google::protobuf::uint8* Axis::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.Axis)
  // required .experimot.msgs.Vector3d xyz = 1;
  if (has_xyz()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, *this->xyz_, target);
  }

  // required double limit_lower = 2;
  if (has_limit_lower()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->limit_lower(), target);
  }

  // required double limit_upper = 3;
  if (has_limit_upper()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->limit_upper(), target);
  }

  // required double limit_effort = 4;
  if (has_limit_effort()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->limit_effort(), target);
  }

  // required double limit_velocity = 5;
  if (has_limit_velocity()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->limit_velocity(), target);
  }

  // required double damping = 6;
  if (has_damping()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->damping(), target);
  }

  // required double friction = 7;
  if (has_friction()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->friction(), target);
  }

  // required bool use_parent_model_frame = 8;
  if (has_use_parent_model_frame()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->use_parent_model_frame(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.Axis)
  return target;
}

int Axis::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_xyz()) {
    // required .experimot.msgs.Vector3d xyz = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->xyz_);
  }

  if (has_limit_lower()) {
    // required double limit_lower = 2;
    total_size += 1 + 8;
  }

  if (has_limit_upper()) {
    // required double limit_upper = 3;
    total_size += 1 + 8;
  }

  if (has_limit_effort()) {
    // required double limit_effort = 4;
    total_size += 1 + 8;
  }

  if (has_limit_velocity()) {
    // required double limit_velocity = 5;
    total_size += 1 + 8;
  }

  if (has_damping()) {
    // required double damping = 6;
    total_size += 1 + 8;
  }

  if (has_friction()) {
    // required double friction = 7;
    total_size += 1 + 8;
  }

  if (has_use_parent_model_frame()) {
    // required bool use_parent_model_frame = 8;
    total_size += 1 + 1;
  }

  return total_size;
}
int Axis::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x000000ff) ^ 0x000000ff) == 0) {  // All required fields are present.
    // required .experimot.msgs.Vector3d xyz = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->xyz_);

    // required double limit_lower = 2;
    total_size += 1 + 8;

    // required double limit_upper = 3;
    total_size += 1 + 8;

    // required double limit_effort = 4;
    total_size += 1 + 8;

    // required double limit_velocity = 5;
    total_size += 1 + 8;

    // required double damping = 6;
    total_size += 1 + 8;

    // required double friction = 7;
    total_size += 1 + 8;

    // required bool use_parent_model_frame = 8;
    total_size += 1 + 1;

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

void Axis::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Axis* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Axis*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Axis::MergeFrom(const Axis& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_xyz()) {
      mutable_xyz()->::experimot::msgs::Vector3d::MergeFrom(from.xyz());
    }
    if (from.has_limit_lower()) {
      set_limit_lower(from.limit_lower());
    }
    if (from.has_limit_upper()) {
      set_limit_upper(from.limit_upper());
    }
    if (from.has_limit_effort()) {
      set_limit_effort(from.limit_effort());
    }
    if (from.has_limit_velocity()) {
      set_limit_velocity(from.limit_velocity());
    }
    if (from.has_damping()) {
      set_damping(from.damping());
    }
    if (from.has_friction()) {
      set_friction(from.friction());
    }
    if (from.has_use_parent_model_frame()) {
      set_use_parent_model_frame(from.use_parent_model_frame());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void Axis::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Axis::CopyFrom(const Axis& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Axis::IsInitialized() const {
  if ((_has_bits_[0] & 0x000000ff) != 0x000000ff) return false;

  if (has_xyz()) {
    if (!this->xyz_->IsInitialized()) return false;
  }
  return true;
}

void Axis::Swap(Axis* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Axis::InternalSwap(Axis* other) {
  std::swap(xyz_, other->xyz_);
  std::swap(limit_lower_, other->limit_lower_);
  std::swap(limit_upper_, other->limit_upper_);
  std::swap(limit_effort_, other->limit_effort_);
  std::swap(limit_velocity_, other->limit_velocity_);
  std::swap(damping_, other->damping_);
  std::swap(friction_, other->friction_);
  std::swap(use_parent_model_frame_, other->use_parent_model_frame_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Axis::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Axis_descriptor_;
  metadata.reflection = Axis_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Axis

// required .experimot.msgs.Vector3d xyz = 1;
 bool Axis::has_xyz() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Axis::set_has_xyz() {
  _has_bits_[0] |= 0x00000001u;
}
 void Axis::clear_has_xyz() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Axis::clear_xyz() {
  if (xyz_ != NULL) xyz_->::experimot::msgs::Vector3d::Clear();
  clear_has_xyz();
}
 const ::experimot::msgs::Vector3d& Axis::xyz() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.xyz)
  return xyz_ != NULL ? *xyz_ : *default_instance_->xyz_;
}
 ::experimot::msgs::Vector3d* Axis::mutable_xyz() {
  set_has_xyz();
  if (xyz_ == NULL) {
    xyz_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Axis.xyz)
  return xyz_;
}
 ::experimot::msgs::Vector3d* Axis::release_xyz() {
  clear_has_xyz();
  ::experimot::msgs::Vector3d* temp = xyz_;
  xyz_ = NULL;
  return temp;
}
 void Axis::set_allocated_xyz(::experimot::msgs::Vector3d* xyz) {
  delete xyz_;
  xyz_ = xyz;
  if (xyz) {
    set_has_xyz();
  } else {
    clear_has_xyz();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Axis.xyz)
}

// required double limit_lower = 2;
 bool Axis::has_limit_lower() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Axis::set_has_limit_lower() {
  _has_bits_[0] |= 0x00000002u;
}
 void Axis::clear_has_limit_lower() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Axis::clear_limit_lower() {
  limit_lower_ = 0;
  clear_has_limit_lower();
}
 double Axis::limit_lower() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.limit_lower)
  return limit_lower_;
}
 void Axis::set_limit_lower(double value) {
  set_has_limit_lower();
  limit_lower_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.limit_lower)
}

// required double limit_upper = 3;
 bool Axis::has_limit_upper() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void Axis::set_has_limit_upper() {
  _has_bits_[0] |= 0x00000004u;
}
 void Axis::clear_has_limit_upper() {
  _has_bits_[0] &= ~0x00000004u;
}
 void Axis::clear_limit_upper() {
  limit_upper_ = 0;
  clear_has_limit_upper();
}
 double Axis::limit_upper() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.limit_upper)
  return limit_upper_;
}
 void Axis::set_limit_upper(double value) {
  set_has_limit_upper();
  limit_upper_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.limit_upper)
}

// required double limit_effort = 4;
 bool Axis::has_limit_effort() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void Axis::set_has_limit_effort() {
  _has_bits_[0] |= 0x00000008u;
}
 void Axis::clear_has_limit_effort() {
  _has_bits_[0] &= ~0x00000008u;
}
 void Axis::clear_limit_effort() {
  limit_effort_ = 0;
  clear_has_limit_effort();
}
 double Axis::limit_effort() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.limit_effort)
  return limit_effort_;
}
 void Axis::set_limit_effort(double value) {
  set_has_limit_effort();
  limit_effort_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.limit_effort)
}

// required double limit_velocity = 5;
 bool Axis::has_limit_velocity() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
 void Axis::set_has_limit_velocity() {
  _has_bits_[0] |= 0x00000010u;
}
 void Axis::clear_has_limit_velocity() {
  _has_bits_[0] &= ~0x00000010u;
}
 void Axis::clear_limit_velocity() {
  limit_velocity_ = 0;
  clear_has_limit_velocity();
}
 double Axis::limit_velocity() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.limit_velocity)
  return limit_velocity_;
}
 void Axis::set_limit_velocity(double value) {
  set_has_limit_velocity();
  limit_velocity_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.limit_velocity)
}

// required double damping = 6;
 bool Axis::has_damping() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
 void Axis::set_has_damping() {
  _has_bits_[0] |= 0x00000020u;
}
 void Axis::clear_has_damping() {
  _has_bits_[0] &= ~0x00000020u;
}
 void Axis::clear_damping() {
  damping_ = 0;
  clear_has_damping();
}
 double Axis::damping() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.damping)
  return damping_;
}
 void Axis::set_damping(double value) {
  set_has_damping();
  damping_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.damping)
}

// required double friction = 7;
 bool Axis::has_friction() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
 void Axis::set_has_friction() {
  _has_bits_[0] |= 0x00000040u;
}
 void Axis::clear_has_friction() {
  _has_bits_[0] &= ~0x00000040u;
}
 void Axis::clear_friction() {
  friction_ = 0;
  clear_has_friction();
}
 double Axis::friction() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.friction)
  return friction_;
}
 void Axis::set_friction(double value) {
  set_has_friction();
  friction_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.friction)
}

// required bool use_parent_model_frame = 8;
 bool Axis::has_use_parent_model_frame() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
 void Axis::set_has_use_parent_model_frame() {
  _has_bits_[0] |= 0x00000080u;
}
 void Axis::clear_has_use_parent_model_frame() {
  _has_bits_[0] &= ~0x00000080u;
}
 void Axis::clear_use_parent_model_frame() {
  use_parent_model_frame_ = false;
  clear_has_use_parent_model_frame();
}
 bool Axis::use_parent_model_frame() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Axis.use_parent_model_frame)
  return use_parent_model_frame_;
}
 void Axis::set_use_parent_model_frame(bool value) {
  set_has_use_parent_model_frame();
  use_parent_model_frame_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Axis.use_parent_model_frame)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.Axis", Axis)
// @@protoc_insertion_point(global_scope)
