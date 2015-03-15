// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sim_event.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "sim_event.pb.h"

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

const ::google::protobuf::Descriptor* SimEvent_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SimEvent_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_sim_5fevent_2eproto() {
  protobuf_AddDesc_sim_5fevent_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "sim_event.proto");
  GOOGLE_CHECK(file != NULL);
  SimEvent_descriptor_ = file->message_type(0);
  static const int SimEvent_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, world_statistics_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, data_),
  };
  SimEvent_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      SimEvent_descriptor_,
      SimEvent::default_instance_,
      SimEvent_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, _has_bits_[0]),
      -1,
      -1,
      sizeof(SimEvent),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SimEvent, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_sim_5fevent_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      SimEvent_descriptor_, &SimEvent::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_sim_5fevent_2eproto() {
  delete SimEvent::default_instance_;
  delete SimEvent_reflection_;
}

void protobuf_AddDesc_sim_5fevent_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::experimot::msgs::protobuf_AddDesc_world_5fstats_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017sim_event.proto\022\016experimot.msgs\032\021world"
    "_stats.proto\"o\n\010SimEvent\022\014\n\004type\030\001 \002(\t\022\014"
    "\n\004name\030\002 \002(\t\0229\n\020world_statistics\030\003 \002(\0132\037"
    ".experimot.msgs.WorldStatistics\022\014\n\004data\030"
    "\004 \001(\t", 165);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "sim_event.proto", &protobuf_RegisterTypes);
  SimEvent::default_instance_ = new SimEvent();
  SimEvent::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_sim_5fevent_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_sim_5fevent_2eproto {
  StaticDescriptorInitializer_sim_5fevent_2eproto() {
    protobuf_AddDesc_sim_5fevent_2eproto();
  }
} static_descriptor_initializer_sim_5fevent_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int SimEvent::kTypeFieldNumber;
const int SimEvent::kNameFieldNumber;
const int SimEvent::kWorldStatisticsFieldNumber;
const int SimEvent::kDataFieldNumber;
#endif  // !_MSC_VER

SimEvent::SimEvent()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.SimEvent)
}

void SimEvent::InitAsDefaultInstance() {
  world_statistics_ = const_cast< ::experimot::msgs::WorldStatistics*>(&::experimot::msgs::WorldStatistics::default_instance());
}

SimEvent::SimEvent(const SimEvent& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.SimEvent)
}

void SimEvent::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  type_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  world_statistics_ = NULL;
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SimEvent::~SimEvent() {
  // @@protoc_insertion_point(destructor:experimot.msgs.SimEvent)
  SharedDtor();
}

void SimEvent::SharedDtor() {
  type_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
    delete world_statistics_;
  }
}

void SimEvent::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SimEvent::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SimEvent_descriptor_;
}

const SimEvent& SimEvent::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_sim_5fevent_2eproto();
  return *default_instance_;
}

SimEvent* SimEvent::default_instance_ = NULL;

SimEvent* SimEvent::New(::google::protobuf::Arena* arena) const {
  SimEvent* n = new SimEvent;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void SimEvent::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_type()) {
      type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_name()) {
      name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_world_statistics()) {
      if (world_statistics_ != NULL) world_statistics_->::experimot::msgs::WorldStatistics::Clear();
    }
    if (has_data()) {
      data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool SimEvent::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.SimEvent)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string type = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->type().data(), this->type().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.SimEvent.type");
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
            "experimot.msgs.SimEvent.name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_world_statistics;
        break;
      }

      // required .experimot.msgs.WorldStatistics world_statistics = 3;
      case 3: {
        if (tag == 26) {
         parse_world_statistics:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_world_statistics()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_data;
        break;
      }

      // optional string data = 4;
      case 4: {
        if (tag == 34) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_data()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->data().data(), this->data().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.SimEvent.data");
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.SimEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.SimEvent)
  return false;
#undef DO_
}

void SimEvent::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.SimEvent)
  // required string type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.type");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->type(), output);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->name(), output);
  }

  // required .experimot.msgs.WorldStatistics world_statistics = 3;
  if (has_world_statistics()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->world_statistics_, output);
  }

  // optional string data = 4;
  if (has_data()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->data().data(), this->data().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.data");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->data(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.SimEvent)
}

::google::protobuf::uint8* SimEvent::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.SimEvent)
  // required string type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.type");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->type(), target);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  // required .experimot.msgs.WorldStatistics world_statistics = 3;
  if (has_world_statistics()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, *this->world_statistics_, target);
  }

  // optional string data = 4;
  if (has_data()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->data().data(), this->data().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.SimEvent.data");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->data(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.SimEvent)
  return target;
}

int SimEvent::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_type()) {
    // required string type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->type());
  }

  if (has_name()) {
    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  if (has_world_statistics()) {
    // required .experimot.msgs.WorldStatistics world_statistics = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->world_statistics_);
  }

  return total_size;
}
int SimEvent::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required string type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->type());

    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

    // required .experimot.msgs.WorldStatistics world_statistics = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->world_statistics_);

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // optional string data = 4;
  if (has_data()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->data());
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

void SimEvent::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const SimEvent* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SimEvent*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SimEvent::MergeFrom(const SimEvent& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_has_type();
      type_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.type_);
    }
    if (from.has_name()) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (from.has_world_statistics()) {
      mutable_world_statistics()->::experimot::msgs::WorldStatistics::MergeFrom(from.world_statistics());
    }
    if (from.has_data()) {
      set_has_data();
      data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void SimEvent::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SimEvent::CopyFrom(const SimEvent& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SimEvent::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (has_world_statistics()) {
    if (!this->world_statistics_->IsInitialized()) return false;
  }
  return true;
}

void SimEvent::Swap(SimEvent* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SimEvent::InternalSwap(SimEvent* other) {
  type_.Swap(&other->type_);
  name_.Swap(&other->name_);
  std::swap(world_statistics_, other->world_statistics_);
  data_.Swap(&other->data_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata SimEvent::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SimEvent_descriptor_;
  metadata.reflection = SimEvent_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// SimEvent

// required string type = 1;
 bool SimEvent::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void SimEvent::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
 void SimEvent::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
 void SimEvent::clear_type() {
  type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_type();
}
 const ::std::string& SimEvent::type() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.SimEvent.type)
  return type_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_type(const ::std::string& value) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.SimEvent.type)
}
 void SimEvent::set_type(const char* value) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.SimEvent.type)
}
 void SimEvent::set_type(const char* value, size_t size) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.SimEvent.type)
}
 ::std::string* SimEvent::mutable_type() {
  set_has_type();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.SimEvent.type)
  return type_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* SimEvent::release_type() {
  clear_has_type();
  return type_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_allocated_type(::std::string* type) {
  if (type != NULL) {
    set_has_type();
  } else {
    clear_has_type();
  }
  type_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), type);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.SimEvent.type)
}

// required string name = 2;
 bool SimEvent::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void SimEvent::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
 void SimEvent::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
 void SimEvent::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
 const ::std::string& SimEvent::name() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.SimEvent.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.SimEvent.name)
}
 void SimEvent::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.SimEvent.name)
}
 void SimEvent::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.SimEvent.name)
}
 ::std::string* SimEvent::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.SimEvent.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* SimEvent::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.SimEvent.name)
}

// required .experimot.msgs.WorldStatistics world_statistics = 3;
 bool SimEvent::has_world_statistics() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void SimEvent::set_has_world_statistics() {
  _has_bits_[0] |= 0x00000004u;
}
 void SimEvent::clear_has_world_statistics() {
  _has_bits_[0] &= ~0x00000004u;
}
 void SimEvent::clear_world_statistics() {
  if (world_statistics_ != NULL) world_statistics_->::experimot::msgs::WorldStatistics::Clear();
  clear_has_world_statistics();
}
 const ::experimot::msgs::WorldStatistics& SimEvent::world_statistics() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.SimEvent.world_statistics)
  return world_statistics_ != NULL ? *world_statistics_ : *default_instance_->world_statistics_;
}
 ::experimot::msgs::WorldStatistics* SimEvent::mutable_world_statistics() {
  set_has_world_statistics();
  if (world_statistics_ == NULL) {
    world_statistics_ = new ::experimot::msgs::WorldStatistics;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.SimEvent.world_statistics)
  return world_statistics_;
}
 ::experimot::msgs::WorldStatistics* SimEvent::release_world_statistics() {
  clear_has_world_statistics();
  ::experimot::msgs::WorldStatistics* temp = world_statistics_;
  world_statistics_ = NULL;
  return temp;
}
 void SimEvent::set_allocated_world_statistics(::experimot::msgs::WorldStatistics* world_statistics) {
  delete world_statistics_;
  world_statistics_ = world_statistics;
  if (world_statistics) {
    set_has_world_statistics();
  } else {
    clear_has_world_statistics();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.SimEvent.world_statistics)
}

// optional string data = 4;
 bool SimEvent::has_data() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void SimEvent::set_has_data() {
  _has_bits_[0] |= 0x00000008u;
}
 void SimEvent::clear_has_data() {
  _has_bits_[0] &= ~0x00000008u;
}
 void SimEvent::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
 const ::std::string& SimEvent::data() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.SimEvent.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.SimEvent.data)
}
 void SimEvent::set_data(const char* value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.SimEvent.data)
}
 void SimEvent::set_data(const char* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.SimEvent.data)
}
 ::std::string* SimEvent::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.SimEvent.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* SimEvent::release_data() {
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void SimEvent::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.SimEvent.data)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.SimEvent", SimEvent)
// @@protoc_insertion_point(global_scope)
