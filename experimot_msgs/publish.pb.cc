// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: publish.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "publish.pb.h"

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

const ::google::protobuf::Descriptor* Publish_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Publish_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_publish_2eproto() {
  protobuf_AddDesc_publish_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "publish.proto");
  GOOGLE_CHECK(file != NULL);
  Publish_descriptor_ = file->message_type(0);
  static const int Publish_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, topic_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, msg_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, host_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, port_),
  };
  Publish_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Publish_descriptor_,
      Publish::default_instance_,
      Publish_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, _has_bits_[0]),
      -1,
      -1,
      sizeof(Publish),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Publish, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_publish_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Publish_descriptor_, &Publish::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_publish_2eproto() {
  delete Publish::default_instance_;
  delete Publish_reflection_;
}

void protobuf_AddDesc_publish_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rpublish.proto\022\016experimot.msgs\"F\n\007Publi"
    "sh\022\r\n\005topic\030\001 \002(\t\022\020\n\010msg_type\030\002 \002(\t\022\014\n\004h"
    "ost\030\003 \002(\t\022\014\n\004port\030\004 \002(\r", 103);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "publish.proto", &protobuf_RegisterTypes);
  Publish::default_instance_ = new Publish();
  Publish::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_publish_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_publish_2eproto {
  StaticDescriptorInitializer_publish_2eproto() {
    protobuf_AddDesc_publish_2eproto();
  }
} static_descriptor_initializer_publish_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Publish::kTopicFieldNumber;
const int Publish::kMsgTypeFieldNumber;
const int Publish::kHostFieldNumber;
const int Publish::kPortFieldNumber;
#endif  // !_MSC_VER

Publish::Publish()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.Publish)
}

void Publish::InitAsDefaultInstance() {
}

Publish::Publish(const Publish& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.Publish)
}

void Publish::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  topic_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  msg_type_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  host_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  port_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Publish::~Publish() {
  // @@protoc_insertion_point(destructor:experimot.msgs.Publish)
  SharedDtor();
}

void Publish::SharedDtor() {
  topic_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  msg_type_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  host_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void Publish::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Publish::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Publish_descriptor_;
}

const Publish& Publish::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_publish_2eproto();
  return *default_instance_;
}

Publish* Publish::default_instance_ = NULL;

Publish* Publish::New(::google::protobuf::Arena* arena) const {
  Publish* n = new Publish;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Publish::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_topic()) {
      topic_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_msg_type()) {
      msg_type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_host()) {
      host_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    port_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Publish::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.Publish)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string topic = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_topic()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->topic().data(), this->topic().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.Publish.topic");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_msg_type;
        break;
      }

      // required string msg_type = 2;
      case 2: {
        if (tag == 18) {
         parse_msg_type:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_msg_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->msg_type().data(), this->msg_type().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.Publish.msg_type");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_host;
        break;
      }

      // required string host = 3;
      case 3: {
        if (tag == 26) {
         parse_host:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_host()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->host().data(), this->host().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.Publish.host");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_port;
        break;
      }

      // required uint32 port = 4;
      case 4: {
        if (tag == 32) {
         parse_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &port_)));
          set_has_port();
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.Publish)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.Publish)
  return false;
#undef DO_
}

void Publish::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.Publish)
  // required string topic = 1;
  if (has_topic()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->topic().data(), this->topic().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.topic");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->topic(), output);
  }

  // required string msg_type = 2;
  if (has_msg_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->msg_type().data(), this->msg_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.msg_type");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->msg_type(), output);
  }

  // required string host = 3;
  if (has_host()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.host");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->host(), output);
  }

  // required uint32 port = 4;
  if (has_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->port(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.Publish)
}

::google::protobuf::uint8* Publish::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.Publish)
  // required string topic = 1;
  if (has_topic()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->topic().data(), this->topic().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.topic");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->topic(), target);
  }

  // required string msg_type = 2;
  if (has_msg_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->msg_type().data(), this->msg_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.msg_type");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->msg_type(), target);
  }

  // required string host = 3;
  if (has_host()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.Publish.host");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->host(), target);
  }

  // required uint32 port = 4;
  if (has_port()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->port(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.Publish)
  return target;
}

int Publish::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_topic()) {
    // required string topic = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->topic());
  }

  if (has_msg_type()) {
    // required string msg_type = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->msg_type());
  }

  if (has_host()) {
    // required string host = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->host());
  }

  if (has_port()) {
    // required uint32 port = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->port());
  }

  return total_size;
}
int Publish::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x0000000f) ^ 0x0000000f) == 0) {  // All required fields are present.
    // required string topic = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->topic());

    // required string msg_type = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->msg_type());

    // required string host = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->host());

    // required uint32 port = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->port());

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

void Publish::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Publish* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Publish*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Publish::MergeFrom(const Publish& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_topic()) {
      set_has_topic();
      topic_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.topic_);
    }
    if (from.has_msg_type()) {
      set_has_msg_type();
      msg_type_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.msg_type_);
    }
    if (from.has_host()) {
      set_has_host();
      host_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.host_);
    }
    if (from.has_port()) {
      set_port(from.port());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void Publish::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Publish::CopyFrom(const Publish& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Publish::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void Publish::Swap(Publish* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Publish::InternalSwap(Publish* other) {
  topic_.Swap(&other->topic_);
  msg_type_.Swap(&other->msg_type_);
  host_.Swap(&other->host_);
  std::swap(port_, other->port_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Publish::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Publish_descriptor_;
  metadata.reflection = Publish_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Publish

// required string topic = 1;
 bool Publish::has_topic() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Publish::set_has_topic() {
  _has_bits_[0] |= 0x00000001u;
}
 void Publish::clear_has_topic() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Publish::clear_topic() {
  topic_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_topic();
}
 const ::std::string& Publish::topic() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Publish.topic)
  return topic_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_topic(const ::std::string& value) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Publish.topic)
}
 void Publish::set_topic(const char* value) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Publish.topic)
}
 void Publish::set_topic(const char* value, size_t size) {
  set_has_topic();
  topic_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Publish.topic)
}
 ::std::string* Publish::mutable_topic() {
  set_has_topic();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Publish.topic)
  return topic_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Publish::release_topic() {
  clear_has_topic();
  return topic_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_allocated_topic(::std::string* topic) {
  if (topic != NULL) {
    set_has_topic();
  } else {
    clear_has_topic();
  }
  topic_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), topic);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Publish.topic)
}

// required string msg_type = 2;
 bool Publish::has_msg_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Publish::set_has_msg_type() {
  _has_bits_[0] |= 0x00000002u;
}
 void Publish::clear_has_msg_type() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Publish::clear_msg_type() {
  msg_type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_msg_type();
}
 const ::std::string& Publish::msg_type() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Publish.msg_type)
  return msg_type_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_msg_type(const ::std::string& value) {
  set_has_msg_type();
  msg_type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Publish.msg_type)
}
 void Publish::set_msg_type(const char* value) {
  set_has_msg_type();
  msg_type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Publish.msg_type)
}
 void Publish::set_msg_type(const char* value, size_t size) {
  set_has_msg_type();
  msg_type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Publish.msg_type)
}
 ::std::string* Publish::mutable_msg_type() {
  set_has_msg_type();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Publish.msg_type)
  return msg_type_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Publish::release_msg_type() {
  clear_has_msg_type();
  return msg_type_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_allocated_msg_type(::std::string* msg_type) {
  if (msg_type != NULL) {
    set_has_msg_type();
  } else {
    clear_has_msg_type();
  }
  msg_type_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg_type);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Publish.msg_type)
}

// required string host = 3;
 bool Publish::has_host() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void Publish::set_has_host() {
  _has_bits_[0] |= 0x00000004u;
}
 void Publish::clear_has_host() {
  _has_bits_[0] &= ~0x00000004u;
}
 void Publish::clear_host() {
  host_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_host();
}
 const ::std::string& Publish::host() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Publish.host)
  return host_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_host(const ::std::string& value) {
  set_has_host();
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Publish.host)
}
 void Publish::set_host(const char* value) {
  set_has_host();
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Publish.host)
}
 void Publish::set_host(const char* value, size_t size) {
  set_has_host();
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Publish.host)
}
 ::std::string* Publish::mutable_host() {
  set_has_host();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Publish.host)
  return host_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Publish::release_host() {
  clear_has_host();
  return host_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Publish::set_allocated_host(::std::string* host) {
  if (host != NULL) {
    set_has_host();
  } else {
    clear_has_host();
  }
  host_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), host);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Publish.host)
}

// required uint32 port = 4;
 bool Publish::has_port() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void Publish::set_has_port() {
  _has_bits_[0] |= 0x00000008u;
}
 void Publish::clear_has_port() {
  _has_bits_[0] &= ~0x00000008u;
}
 void Publish::clear_port() {
  port_ = 0u;
  clear_has_port();
}
 ::google::protobuf::uint32 Publish::port() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Publish.port)
  return port_;
}
 void Publish::set_port(::google::protobuf::uint32 value) {
  set_has_port();
  port_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Publish.port)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.Publish", Publish)
// @@protoc_insertion_point(global_scope)
