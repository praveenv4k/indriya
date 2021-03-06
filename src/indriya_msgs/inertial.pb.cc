// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: inertial.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "inertial.pb.h"

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

const ::google::protobuf::Descriptor* Inertial_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Inertial_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_inertial_2eproto() {
  protobuf_AddDesc_inertial_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "inertial.proto");
  GOOGLE_CHECK(file != NULL);
  Inertial_descriptor_ = file->message_type(0);
  static const int Inertial_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, mass_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, pose_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, ixx_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, ixy_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, ixz_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, iyy_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, iyz_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, izz_),
  };
  Inertial_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Inertial_descriptor_,
      Inertial::default_instance_,
      Inertial_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, _has_bits_[0]),
      -1,
      -1,
      sizeof(Inertial),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Inertial, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_inertial_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Inertial_descriptor_, &Inertial::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_inertial_2eproto() {
  delete Inertial::default_instance_;
  delete Inertial_reflection_;
}

void protobuf_AddDesc_inertial_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Indriya::Core::Msgs::protobuf_AddDesc_pose_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016inertial.proto\022\021Indriya.Core.Msgs\032\npos"
    "e.proto\"\215\001\n\010Inertial\022\014\n\004mass\030\001 \001(\001\022%\n\004po"
    "se\030\002 \001(\0132\027.Indriya.Core.Msgs.Pose\022\013\n\003ixx"
    "\030\003 \001(\001\022\013\n\003ixy\030\004 \001(\001\022\013\n\003ixz\030\005 \001(\001\022\013\n\003iyy\030"
    "\006 \001(\001\022\013\n\003iyz\030\007 \001(\001\022\013\n\003izz\030\010 \001(\001", 191);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "inertial.proto", &protobuf_RegisterTypes);
  Inertial::default_instance_ = new Inertial();
  Inertial::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_inertial_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_inertial_2eproto {
  StaticDescriptorInitializer_inertial_2eproto() {
    protobuf_AddDesc_inertial_2eproto();
  }
} static_descriptor_initializer_inertial_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Inertial::kMassFieldNumber;
const int Inertial::kPoseFieldNumber;
const int Inertial::kIxxFieldNumber;
const int Inertial::kIxyFieldNumber;
const int Inertial::kIxzFieldNumber;
const int Inertial::kIyyFieldNumber;
const int Inertial::kIyzFieldNumber;
const int Inertial::kIzzFieldNumber;
#endif  // !_MSC_VER

Inertial::Inertial()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Indriya.Core.Msgs.Inertial)
}

void Inertial::InitAsDefaultInstance() {
  pose_ = const_cast< ::Indriya::Core::Msgs::Pose*>(&::Indriya::Core::Msgs::Pose::default_instance());
}

Inertial::Inertial(const Inertial& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Indriya.Core.Msgs.Inertial)
}

void Inertial::SharedCtor() {
  _cached_size_ = 0;
  mass_ = 0;
  pose_ = NULL;
  ixx_ = 0;
  ixy_ = 0;
  ixz_ = 0;
  iyy_ = 0;
  iyz_ = 0;
  izz_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Inertial::~Inertial() {
  // @@protoc_insertion_point(destructor:Indriya.Core.Msgs.Inertial)
  SharedDtor();
}

void Inertial::SharedDtor() {
  if (this != default_instance_) {
    delete pose_;
  }
}

void Inertial::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Inertial::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Inertial_descriptor_;
}

const Inertial& Inertial::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_inertial_2eproto();
  return *default_instance_;
}

Inertial* Inertial::default_instance_ = NULL;

Inertial* Inertial::New(::google::protobuf::Arena* arena) const {
  Inertial* n = new Inertial;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Inertial::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<Inertial*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(ixx_, izz_);
    mass_ = 0;
    if (has_pose()) {
      if (pose_ != NULL) pose_->::Indriya::Core::Msgs::Pose::Clear();
    }
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Inertial::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Indriya.Core.Msgs.Inertial)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double mass = 1;
      case 1: {
        if (tag == 9) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &mass_)));
          set_has_mass();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_pose;
        break;
      }

      // optional .Indriya.Core.Msgs.Pose pose = 2;
      case 2: {
        if (tag == 18) {
         parse_pose:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_pose()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_ixx;
        break;
      }

      // optional double ixx = 3;
      case 3: {
        if (tag == 25) {
         parse_ixx:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ixx_)));
          set_has_ixx();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_ixy;
        break;
      }

      // optional double ixy = 4;
      case 4: {
        if (tag == 33) {
         parse_ixy:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ixy_)));
          set_has_ixy();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_ixz;
        break;
      }

      // optional double ixz = 5;
      case 5: {
        if (tag == 41) {
         parse_ixz:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ixz_)));
          set_has_ixz();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_iyy;
        break;
      }

      // optional double iyy = 6;
      case 6: {
        if (tag == 49) {
         parse_iyy:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &iyy_)));
          set_has_iyy();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_iyz;
        break;
      }

      // optional double iyz = 7;
      case 7: {
        if (tag == 57) {
         parse_iyz:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &iyz_)));
          set_has_iyz();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(65)) goto parse_izz;
        break;
      }

      // optional double izz = 8;
      case 8: {
        if (tag == 65) {
         parse_izz:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &izz_)));
          set_has_izz();
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
  // @@protoc_insertion_point(parse_success:Indriya.Core.Msgs.Inertial)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Indriya.Core.Msgs.Inertial)
  return false;
#undef DO_
}

void Inertial::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Indriya.Core.Msgs.Inertial)
  // optional double mass = 1;
  if (has_mass()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->mass(), output);
  }

  // optional .Indriya.Core.Msgs.Pose pose = 2;
  if (has_pose()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->pose_, output);
  }

  // optional double ixx = 3;
  if (has_ixx()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->ixx(), output);
  }

  // optional double ixy = 4;
  if (has_ixy()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->ixy(), output);
  }

  // optional double ixz = 5;
  if (has_ixz()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->ixz(), output);
  }

  // optional double iyy = 6;
  if (has_iyy()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->iyy(), output);
  }

  // optional double iyz = 7;
  if (has_iyz()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->iyz(), output);
  }

  // optional double izz = 8;
  if (has_izz()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(8, this->izz(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Indriya.Core.Msgs.Inertial)
}

::google::protobuf::uint8* Inertial::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Indriya.Core.Msgs.Inertial)
  // optional double mass = 1;
  if (has_mass()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->mass(), target);
  }

  // optional .Indriya.Core.Msgs.Pose pose = 2;
  if (has_pose()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, *this->pose_, target);
  }

  // optional double ixx = 3;
  if (has_ixx()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->ixx(), target);
  }

  // optional double ixy = 4;
  if (has_ixy()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->ixy(), target);
  }

  // optional double ixz = 5;
  if (has_ixz()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->ixz(), target);
  }

  // optional double iyy = 6;
  if (has_iyy()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->iyy(), target);
  }

  // optional double iyz = 7;
  if (has_iyz()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->iyz(), target);
  }

  // optional double izz = 8;
  if (has_izz()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(8, this->izz(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Indriya.Core.Msgs.Inertial)
  return target;
}

int Inertial::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & 255) {
    // optional double mass = 1;
    if (has_mass()) {
      total_size += 1 + 8;
    }

    // optional .Indriya.Core.Msgs.Pose pose = 2;
    if (has_pose()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->pose_);
    }

    // optional double ixx = 3;
    if (has_ixx()) {
      total_size += 1 + 8;
    }

    // optional double ixy = 4;
    if (has_ixy()) {
      total_size += 1 + 8;
    }

    // optional double ixz = 5;
    if (has_ixz()) {
      total_size += 1 + 8;
    }

    // optional double iyy = 6;
    if (has_iyy()) {
      total_size += 1 + 8;
    }

    // optional double iyz = 7;
    if (has_iyz()) {
      total_size += 1 + 8;
    }

    // optional double izz = 8;
    if (has_izz()) {
      total_size += 1 + 8;
    }

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

void Inertial::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Inertial* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Inertial*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Inertial::MergeFrom(const Inertial& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_mass()) {
      set_mass(from.mass());
    }
    if (from.has_pose()) {
      mutable_pose()->::Indriya::Core::Msgs::Pose::MergeFrom(from.pose());
    }
    if (from.has_ixx()) {
      set_ixx(from.ixx());
    }
    if (from.has_ixy()) {
      set_ixy(from.ixy());
    }
    if (from.has_ixz()) {
      set_ixz(from.ixz());
    }
    if (from.has_iyy()) {
      set_iyy(from.iyy());
    }
    if (from.has_iyz()) {
      set_iyz(from.iyz());
    }
    if (from.has_izz()) {
      set_izz(from.izz());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void Inertial::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Inertial::CopyFrom(const Inertial& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Inertial::IsInitialized() const {

  if (has_pose()) {
    if (!this->pose_->IsInitialized()) return false;
  }
  return true;
}

void Inertial::Swap(Inertial* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Inertial::InternalSwap(Inertial* other) {
  std::swap(mass_, other->mass_);
  std::swap(pose_, other->pose_);
  std::swap(ixx_, other->ixx_);
  std::swap(ixy_, other->ixy_);
  std::swap(ixz_, other->ixz_);
  std::swap(iyy_, other->iyy_);
  std::swap(iyz_, other->iyz_);
  std::swap(izz_, other->izz_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Inertial::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Inertial_descriptor_;
  metadata.reflection = Inertial_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Inertial

// optional double mass = 1;
 bool Inertial::has_mass() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Inertial::set_has_mass() {
  _has_bits_[0] |= 0x00000001u;
}
 void Inertial::clear_has_mass() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Inertial::clear_mass() {
  mass_ = 0;
  clear_has_mass();
}
 double Inertial::mass() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.mass)
  return mass_;
}
 void Inertial::set_mass(double value) {
  set_has_mass();
  mass_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.mass)
}

// optional .Indriya.Core.Msgs.Pose pose = 2;
 bool Inertial::has_pose() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Inertial::set_has_pose() {
  _has_bits_[0] |= 0x00000002u;
}
 void Inertial::clear_has_pose() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Inertial::clear_pose() {
  if (pose_ != NULL) pose_->::Indriya::Core::Msgs::Pose::Clear();
  clear_has_pose();
}
 const ::Indriya::Core::Msgs::Pose& Inertial::pose() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.pose)
  return pose_ != NULL ? *pose_ : *default_instance_->pose_;
}
 ::Indriya::Core::Msgs::Pose* Inertial::mutable_pose() {
  set_has_pose();
  if (pose_ == NULL) {
    pose_ = new ::Indriya::Core::Msgs::Pose;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Inertial.pose)
  return pose_;
}
 ::Indriya::Core::Msgs::Pose* Inertial::release_pose() {
  clear_has_pose();
  ::Indriya::Core::Msgs::Pose* temp = pose_;
  pose_ = NULL;
  return temp;
}
 void Inertial::set_allocated_pose(::Indriya::Core::Msgs::Pose* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    set_has_pose();
  } else {
    clear_has_pose();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Inertial.pose)
}

// optional double ixx = 3;
 bool Inertial::has_ixx() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void Inertial::set_has_ixx() {
  _has_bits_[0] |= 0x00000004u;
}
 void Inertial::clear_has_ixx() {
  _has_bits_[0] &= ~0x00000004u;
}
 void Inertial::clear_ixx() {
  ixx_ = 0;
  clear_has_ixx();
}
 double Inertial::ixx() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.ixx)
  return ixx_;
}
 void Inertial::set_ixx(double value) {
  set_has_ixx();
  ixx_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.ixx)
}

// optional double ixy = 4;
 bool Inertial::has_ixy() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void Inertial::set_has_ixy() {
  _has_bits_[0] |= 0x00000008u;
}
 void Inertial::clear_has_ixy() {
  _has_bits_[0] &= ~0x00000008u;
}
 void Inertial::clear_ixy() {
  ixy_ = 0;
  clear_has_ixy();
}
 double Inertial::ixy() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.ixy)
  return ixy_;
}
 void Inertial::set_ixy(double value) {
  set_has_ixy();
  ixy_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.ixy)
}

// optional double ixz = 5;
 bool Inertial::has_ixz() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
 void Inertial::set_has_ixz() {
  _has_bits_[0] |= 0x00000010u;
}
 void Inertial::clear_has_ixz() {
  _has_bits_[0] &= ~0x00000010u;
}
 void Inertial::clear_ixz() {
  ixz_ = 0;
  clear_has_ixz();
}
 double Inertial::ixz() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.ixz)
  return ixz_;
}
 void Inertial::set_ixz(double value) {
  set_has_ixz();
  ixz_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.ixz)
}

// optional double iyy = 6;
 bool Inertial::has_iyy() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
 void Inertial::set_has_iyy() {
  _has_bits_[0] |= 0x00000020u;
}
 void Inertial::clear_has_iyy() {
  _has_bits_[0] &= ~0x00000020u;
}
 void Inertial::clear_iyy() {
  iyy_ = 0;
  clear_has_iyy();
}
 double Inertial::iyy() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.iyy)
  return iyy_;
}
 void Inertial::set_iyy(double value) {
  set_has_iyy();
  iyy_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.iyy)
}

// optional double iyz = 7;
 bool Inertial::has_iyz() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
 void Inertial::set_has_iyz() {
  _has_bits_[0] |= 0x00000040u;
}
 void Inertial::clear_has_iyz() {
  _has_bits_[0] &= ~0x00000040u;
}
 void Inertial::clear_iyz() {
  iyz_ = 0;
  clear_has_iyz();
}
 double Inertial::iyz() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.iyz)
  return iyz_;
}
 void Inertial::set_iyz(double value) {
  set_has_iyz();
  iyz_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.iyz)
}

// optional double izz = 8;
 bool Inertial::has_izz() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
 void Inertial::set_has_izz() {
  _has_bits_[0] |= 0x00000080u;
}
 void Inertial::clear_has_izz() {
  _has_bits_[0] &= ~0x00000080u;
}
 void Inertial::clear_izz() {
  izz_ = 0;
  clear_has_izz();
}
 double Inertial::izz() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Inertial.izz)
  return izz_;
}
 void Inertial::set_izz(double value) {
  set_has_izz();
  izz_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Inertial.izz)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Msgs
}  // namespace Core
}  // namespace Indriya

EX_REGISTER_STATIC_MSG("Indriya.Core.Msgs.Inertial", Inertial)
// @@protoc_insertion_point(global_scope)
