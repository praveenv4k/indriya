// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: link_data.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "link_data.pb.h"

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

const ::google::protobuf::Descriptor* LinkData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LinkData_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_link_5fdata_2eproto() {
  protobuf_AddDesc_link_5fdata_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "link_data.proto");
  GOOGLE_CHECK(file != NULL);
  LinkData_descriptor_ = file->message_type(0);
  static const int LinkData_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, linear_velocity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, angular_velocity_),
  };
  LinkData_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      LinkData_descriptor_,
      LinkData::default_instance_,
      LinkData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, _has_bits_[0]),
      -1,
      -1,
      sizeof(LinkData),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LinkData, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_link_5fdata_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      LinkData_descriptor_, &LinkData::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_link_5fdata_2eproto() {
  delete LinkData::default_instance_;
  delete LinkData_reflection_;
}

void protobuf_AddDesc_link_5fdata_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::experimot::msgs::protobuf_AddDesc_vector3d_2eproto();
  ::experimot::msgs::protobuf_AddDesc_time_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017link_data.proto\022\016experimot.msgs\032\016vecto"
    "r3d.proto\032\ntime.proto\"\243\001\n\010LinkData\022\"\n\004ti"
    "me\030\001 \002(\0132\024.experimot.msgs.Time\022\014\n\004name\030\002"
    " \002(\t\0221\n\017linear_velocity\030\003 \001(\0132\030.experimo"
    "t.msgs.Vector3d\0222\n\020angular_velocity\030\004 \001("
    "\0132\030.experimot.msgs.Vector3d", 227);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "link_data.proto", &protobuf_RegisterTypes);
  LinkData::default_instance_ = new LinkData();
  LinkData::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_link_5fdata_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_link_5fdata_2eproto {
  StaticDescriptorInitializer_link_5fdata_2eproto() {
    protobuf_AddDesc_link_5fdata_2eproto();
  }
} static_descriptor_initializer_link_5fdata_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int LinkData::kTimeFieldNumber;
const int LinkData::kNameFieldNumber;
const int LinkData::kLinearVelocityFieldNumber;
const int LinkData::kAngularVelocityFieldNumber;
#endif  // !_MSC_VER

LinkData::LinkData()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.LinkData)
}

void LinkData::InitAsDefaultInstance() {
  time_ = const_cast< ::experimot::msgs::Time*>(&::experimot::msgs::Time::default_instance());
  linear_velocity_ = const_cast< ::experimot::msgs::Vector3d*>(&::experimot::msgs::Vector3d::default_instance());
  angular_velocity_ = const_cast< ::experimot::msgs::Vector3d*>(&::experimot::msgs::Vector3d::default_instance());
}

LinkData::LinkData(const LinkData& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.LinkData)
}

void LinkData::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  time_ = NULL;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  linear_velocity_ = NULL;
  angular_velocity_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LinkData::~LinkData() {
  // @@protoc_insertion_point(destructor:experimot.msgs.LinkData)
  SharedDtor();
}

void LinkData::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
    delete time_;
    delete linear_velocity_;
    delete angular_velocity_;
  }
}

void LinkData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LinkData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LinkData_descriptor_;
}

const LinkData& LinkData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_link_5fdata_2eproto();
  return *default_instance_;
}

LinkData* LinkData::default_instance_ = NULL;

LinkData* LinkData::New(::google::protobuf::Arena* arena) const {
  LinkData* n = new LinkData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void LinkData::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_time()) {
      if (time_ != NULL) time_->::experimot::msgs::Time::Clear();
    }
    if (has_name()) {
      name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_linear_velocity()) {
      if (linear_velocity_ != NULL) linear_velocity_->::experimot::msgs::Vector3d::Clear();
    }
    if (has_angular_velocity()) {
      if (angular_velocity_ != NULL) angular_velocity_->::experimot::msgs::Vector3d::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool LinkData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.LinkData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .experimot.msgs.Time time = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_time()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // required string name = 2;
      case 2: {
        if (tag == 18) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.LinkData.name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_linear_velocity;
        break;
      }

      // optional .experimot.msgs.Vector3d linear_velocity = 3;
      case 3: {
        if (tag == 26) {
         parse_linear_velocity:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_linear_velocity()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_angular_velocity;
        break;
      }

      // optional .experimot.msgs.Vector3d angular_velocity = 4;
      case 4: {
        if (tag == 34) {
         parse_angular_velocity:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_angular_velocity()));
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.LinkData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.LinkData)
  return false;
#undef DO_
}

void LinkData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.LinkData)
  // required .experimot.msgs.Time time = 1;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->time_, output);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.LinkData.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->name(), output);
  }

  // optional .experimot.msgs.Vector3d linear_velocity = 3;
  if (has_linear_velocity()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->linear_velocity_, output);
  }

  // optional .experimot.msgs.Vector3d angular_velocity = 4;
  if (has_angular_velocity()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, *this->angular_velocity_, output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.LinkData)
}

::google::protobuf::uint8* LinkData::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.LinkData)
  // required .experimot.msgs.Time time = 1;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, *this->time_, target);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.LinkData.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  // optional .experimot.msgs.Vector3d linear_velocity = 3;
  if (has_linear_velocity()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, *this->linear_velocity_, target);
  }

  // optional .experimot.msgs.Vector3d angular_velocity = 4;
  if (has_angular_velocity()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, *this->angular_velocity_, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.LinkData)
  return target;
}

int LinkData::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_time()) {
    // required .experimot.msgs.Time time = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->time_);
  }

  if (has_name()) {
    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  return total_size;
}
int LinkData::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .experimot.msgs.Time time = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->time_);

    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_has_bits_[2 / 32] & 12) {
    // optional .experimot.msgs.Vector3d linear_velocity = 3;
    if (has_linear_velocity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->linear_velocity_);
    }

    // optional .experimot.msgs.Vector3d angular_velocity = 4;
    if (has_angular_velocity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->angular_velocity_);
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

void LinkData::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const LinkData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LinkData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LinkData::MergeFrom(const LinkData& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_time()) {
      mutable_time()->::experimot::msgs::Time::MergeFrom(from.time());
    }
    if (from.has_name()) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (from.has_linear_velocity()) {
      mutable_linear_velocity()->::experimot::msgs::Vector3d::MergeFrom(from.linear_velocity());
    }
    if (from.has_angular_velocity()) {
      mutable_angular_velocity()->::experimot::msgs::Vector3d::MergeFrom(from.angular_velocity());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void LinkData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LinkData::CopyFrom(const LinkData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LinkData::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_time()) {
    if (!this->time_->IsInitialized()) return false;
  }
  if (has_linear_velocity()) {
    if (!this->linear_velocity_->IsInitialized()) return false;
  }
  if (has_angular_velocity()) {
    if (!this->angular_velocity_->IsInitialized()) return false;
  }
  return true;
}

void LinkData::Swap(LinkData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LinkData::InternalSwap(LinkData* other) {
  std::swap(time_, other->time_);
  name_.Swap(&other->name_);
  std::swap(linear_velocity_, other->linear_velocity_);
  std::swap(angular_velocity_, other->angular_velocity_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata LinkData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LinkData_descriptor_;
  metadata.reflection = LinkData_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// LinkData

// required .experimot.msgs.Time time = 1;
 bool LinkData::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void LinkData::set_has_time() {
  _has_bits_[0] |= 0x00000001u;
}
 void LinkData::clear_has_time() {
  _has_bits_[0] &= ~0x00000001u;
}
 void LinkData::clear_time() {
  if (time_ != NULL) time_->::experimot::msgs::Time::Clear();
  clear_has_time();
}
 const ::experimot::msgs::Time& LinkData::time() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.LinkData.time)
  return time_ != NULL ? *time_ : *default_instance_->time_;
}
 ::experimot::msgs::Time* LinkData::mutable_time() {
  set_has_time();
  if (time_ == NULL) {
    time_ = new ::experimot::msgs::Time;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.LinkData.time)
  return time_;
}
 ::experimot::msgs::Time* LinkData::release_time() {
  clear_has_time();
  ::experimot::msgs::Time* temp = time_;
  time_ = NULL;
  return temp;
}
 void LinkData::set_allocated_time(::experimot::msgs::Time* time) {
  delete time_;
  time_ = time;
  if (time) {
    set_has_time();
  } else {
    clear_has_time();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.LinkData.time)
}

// required string name = 2;
 bool LinkData::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void LinkData::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
 void LinkData::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
 void LinkData::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
 const ::std::string& LinkData::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.LinkData.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void LinkData::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.LinkData.name)
}
 void LinkData::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.LinkData.name)
}
 void LinkData::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.LinkData.name)
}
 ::std::string* LinkData::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.LinkData.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* LinkData::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void LinkData::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.LinkData.name)
}

// optional .experimot.msgs.Vector3d linear_velocity = 3;
 bool LinkData::has_linear_velocity() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void LinkData::set_has_linear_velocity() {
  _has_bits_[0] |= 0x00000004u;
}
 void LinkData::clear_has_linear_velocity() {
  _has_bits_[0] &= ~0x00000004u;
}
 void LinkData::clear_linear_velocity() {
  if (linear_velocity_ != NULL) linear_velocity_->::experimot::msgs::Vector3d::Clear();
  clear_has_linear_velocity();
}
 const ::experimot::msgs::Vector3d& LinkData::linear_velocity() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.LinkData.linear_velocity)
  return linear_velocity_ != NULL ? *linear_velocity_ : *default_instance_->linear_velocity_;
}
 ::experimot::msgs::Vector3d* LinkData::mutable_linear_velocity() {
  set_has_linear_velocity();
  if (linear_velocity_ == NULL) {
    linear_velocity_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.LinkData.linear_velocity)
  return linear_velocity_;
}
 ::experimot::msgs::Vector3d* LinkData::release_linear_velocity() {
  clear_has_linear_velocity();
  ::experimot::msgs::Vector3d* temp = linear_velocity_;
  linear_velocity_ = NULL;
  return temp;
}
 void LinkData::set_allocated_linear_velocity(::experimot::msgs::Vector3d* linear_velocity) {
  delete linear_velocity_;
  linear_velocity_ = linear_velocity;
  if (linear_velocity) {
    set_has_linear_velocity();
  } else {
    clear_has_linear_velocity();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.LinkData.linear_velocity)
}

// optional .experimot.msgs.Vector3d angular_velocity = 4;
 bool LinkData::has_angular_velocity() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void LinkData::set_has_angular_velocity() {
  _has_bits_[0] |= 0x00000008u;
}
 void LinkData::clear_has_angular_velocity() {
  _has_bits_[0] &= ~0x00000008u;
}
 void LinkData::clear_angular_velocity() {
  if (angular_velocity_ != NULL) angular_velocity_->::experimot::msgs::Vector3d::Clear();
  clear_has_angular_velocity();
}
 const ::experimot::msgs::Vector3d& LinkData::angular_velocity() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.LinkData.angular_velocity)
  return angular_velocity_ != NULL ? *angular_velocity_ : *default_instance_->angular_velocity_;
}
 ::experimot::msgs::Vector3d* LinkData::mutable_angular_velocity() {
  set_has_angular_velocity();
  if (angular_velocity_ == NULL) {
    angular_velocity_ = new ::experimot::msgs::Vector3d;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.LinkData.angular_velocity)
  return angular_velocity_;
}
 ::experimot::msgs::Vector3d* LinkData::release_angular_velocity() {
  clear_has_angular_velocity();
  ::experimot::msgs::Vector3d* temp = angular_velocity_;
  angular_velocity_ = NULL;
  return temp;
}
 void LinkData::set_allocated_angular_velocity(::experimot::msgs::Vector3d* angular_velocity) {
  delete angular_velocity_;
  angular_velocity_ = angular_velocity;
  if (angular_velocity) {
    set_has_angular_velocity();
  } else {
    clear_has_angular_velocity();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.LinkData.angular_velocity)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.LinkData", LinkData)
// @@protoc_insertion_point(global_scope)
