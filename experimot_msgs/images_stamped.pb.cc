// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: images_stamped.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "images_stamped.pb.h"

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

const ::google::protobuf::Descriptor* ImagesStamped_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ImagesStamped_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_images_5fstamped_2eproto() {
  protobuf_AddDesc_images_5fstamped_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "images_stamped.proto");
  GOOGLE_CHECK(file != NULL);
  ImagesStamped_descriptor_ = file->message_type(0);
  static const int ImagesStamped_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagesStamped, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagesStamped, image_),
  };
  ImagesStamped_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      ImagesStamped_descriptor_,
      ImagesStamped::default_instance_,
      ImagesStamped_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagesStamped, _has_bits_[0]),
      -1,
      -1,
      sizeof(ImagesStamped),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagesStamped, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_images_5fstamped_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      ImagesStamped_descriptor_, &ImagesStamped::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_images_5fstamped_2eproto() {
  delete ImagesStamped::default_instance_;
  delete ImagesStamped_reflection_;
}

void protobuf_AddDesc_images_5fstamped_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::experimot::msgs::protobuf_AddDesc_time_2eproto();
  ::experimot::msgs::protobuf_AddDesc_image_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024images_stamped.proto\022\016experimot.msgs\032\n"
    "time.proto\032\013image.proto\"Y\n\rImagesStamped"
    "\022\"\n\004time\030\001 \002(\0132\024.experimot.msgs.Time\022$\n\005"
    "image\030\002 \003(\0132\025.experimot.msgs.Image", 154);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "images_stamped.proto", &protobuf_RegisterTypes);
  ImagesStamped::default_instance_ = new ImagesStamped();
  ImagesStamped::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_images_5fstamped_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_images_5fstamped_2eproto {
  StaticDescriptorInitializer_images_5fstamped_2eproto() {
    protobuf_AddDesc_images_5fstamped_2eproto();
  }
} static_descriptor_initializer_images_5fstamped_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int ImagesStamped::kTimeFieldNumber;
const int ImagesStamped::kImageFieldNumber;
#endif  // !_MSC_VER

ImagesStamped::ImagesStamped()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.ImagesStamped)
}

void ImagesStamped::InitAsDefaultInstance() {
  time_ = const_cast< ::experimot::msgs::Time*>(&::experimot::msgs::Time::default_instance());
}

ImagesStamped::ImagesStamped(const ImagesStamped& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.ImagesStamped)
}

void ImagesStamped::SharedCtor() {
  _cached_size_ = 0;
  time_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ImagesStamped::~ImagesStamped() {
  // @@protoc_insertion_point(destructor:experimot.msgs.ImagesStamped)
  SharedDtor();
}

void ImagesStamped::SharedDtor() {
  if (this != default_instance_) {
    delete time_;
  }
}

void ImagesStamped::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ImagesStamped::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ImagesStamped_descriptor_;
}

const ImagesStamped& ImagesStamped::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_images_5fstamped_2eproto();
  return *default_instance_;
}

ImagesStamped* ImagesStamped::default_instance_ = NULL;

ImagesStamped* ImagesStamped::New(::google::protobuf::Arena* arena) const {
  ImagesStamped* n = new ImagesStamped;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ImagesStamped::Clear() {
  if (has_time()) {
    if (time_ != NULL) time_->::experimot::msgs::Time::Clear();
  }
  image_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool ImagesStamped::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.ImagesStamped)
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
        if (input->ExpectTag(18)) goto parse_image;
        break;
      }

      // repeated .experimot.msgs.Image image = 2;
      case 2: {
        if (tag == 18) {
         parse_image:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_image()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_image;
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.ImagesStamped)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.ImagesStamped)
  return false;
#undef DO_
}

void ImagesStamped::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.ImagesStamped)
  // required .experimot.msgs.Time time = 1;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->time_, output);
  }

  // repeated .experimot.msgs.Image image = 2;
  for (unsigned int i = 0, n = this->image_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->image(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.ImagesStamped)
}

::google::protobuf::uint8* ImagesStamped::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.ImagesStamped)
  // required .experimot.msgs.Time time = 1;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, *this->time_, target);
  }

  // repeated .experimot.msgs.Image image = 2;
  for (unsigned int i = 0, n = this->image_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->image(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.ImagesStamped)
  return target;
}

int ImagesStamped::ByteSize() const {
  int total_size = 0;

  // required .experimot.msgs.Time time = 1;
  if (has_time()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->time_);
  }
  // repeated .experimot.msgs.Image image = 2;
  total_size += 1 * this->image_size();
  for (int i = 0; i < this->image_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->image(i));
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

void ImagesStamped::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const ImagesStamped* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ImagesStamped*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ImagesStamped::MergeFrom(const ImagesStamped& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  image_.MergeFrom(from.image_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_time()) {
      mutable_time()->::experimot::msgs::Time::MergeFrom(from.time());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void ImagesStamped::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ImagesStamped::CopyFrom(const ImagesStamped& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImagesStamped::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (has_time()) {
    if (!this->time_->IsInitialized()) return false;
  }
  if (!::google::protobuf::internal::AllAreInitialized(this->image())) return false;
  return true;
}

void ImagesStamped::Swap(ImagesStamped* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ImagesStamped::InternalSwap(ImagesStamped* other) {
  std::swap(time_, other->time_);
  image_.UnsafeArenaSwap(&other->image_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ImagesStamped::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ImagesStamped_descriptor_;
  metadata.reflection = ImagesStamped_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ImagesStamped

// required .experimot.msgs.Time time = 1;
 bool ImagesStamped::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void ImagesStamped::set_has_time() {
  _has_bits_[0] |= 0x00000001u;
}
 void ImagesStamped::clear_has_time() {
  _has_bits_[0] &= ~0x00000001u;
}
 void ImagesStamped::clear_time() {
  if (time_ != NULL) time_->::experimot::msgs::Time::Clear();
  clear_has_time();
}
 const ::experimot::msgs::Time& ImagesStamped::time() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImagesStamped.time)
  return time_ != NULL ? *time_ : *default_instance_->time_;
}
 ::experimot::msgs::Time* ImagesStamped::mutable_time() {
  set_has_time();
  if (time_ == NULL) {
    time_ = new ::experimot::msgs::Time;
  }
  // @@protoc_insertion_point(field_mutable:experimot.msgs.ImagesStamped.time)
  return time_;
}
 ::experimot::msgs::Time* ImagesStamped::release_time() {
  clear_has_time();
  ::experimot::msgs::Time* temp = time_;
  time_ = NULL;
  return temp;
}
 void ImagesStamped::set_allocated_time(::experimot::msgs::Time* time) {
  delete time_;
  time_ = time;
  if (time) {
    set_has_time();
  } else {
    clear_has_time();
  }
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.ImagesStamped.time)
}

// repeated .experimot.msgs.Image image = 2;
 int ImagesStamped::image_size() const {
  return image_.size();
}
 void ImagesStamped::clear_image() {
  image_.Clear();
}
 const ::experimot::msgs::Image& ImagesStamped::image(int index) const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImagesStamped.image)
  return image_.Get(index);
}
 ::experimot::msgs::Image* ImagesStamped::mutable_image(int index) {
  // @@protoc_insertion_point(field_mutable:experimot.msgs.ImagesStamped.image)
  return image_.Mutable(index);
}
 ::experimot::msgs::Image* ImagesStamped::add_image() {
  // @@protoc_insertion_point(field_add:experimot.msgs.ImagesStamped.image)
  return image_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Image >&
ImagesStamped::image() const {
  // @@protoc_insertion_point(field_list:experimot.msgs.ImagesStamped.image)
  return image_;
}
 ::google::protobuf::RepeatedPtrField< ::experimot::msgs::Image >*
ImagesStamped::mutable_image() {
  // @@protoc_insertion_point(field_mutable_list:experimot.msgs.ImagesStamped.image)
  return &image_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.ImagesStamped", ImagesStamped)
// @@protoc_insertion_point(global_scope)
