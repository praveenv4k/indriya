// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: image.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "image.pb.h"

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

const ::google::protobuf::Descriptor* Image_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Image_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_image_2eproto() {
  protobuf_AddDesc_image_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "image.proto");
  GOOGLE_CHECK(file != NULL);
  Image_descriptor_ = file->message_type(0);
  static const int Image_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, pixel_format_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, step_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, data_),
  };
  Image_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Image_descriptor_,
      Image::default_instance_,
      Image_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, _has_bits_[0]),
      -1,
      -1,
      sizeof(Image),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Image, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_image_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Image_descriptor_, &Image::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_image_2eproto() {
  delete Image::default_instance_;
  delete Image_reflection_;
}

void protobuf_AddDesc_image_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013image.proto\022\016experimot.msgs\"X\n\005Image\022\r"
    "\n\005width\030\001 \002(\r\022\016\n\006height\030\002 \002(\r\022\024\n\014pixel_f"
    "ormat\030\003 \002(\r\022\014\n\004step\030\004 \002(\r\022\014\n\004data\030\005 \002(\014", 119);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "image.proto", &protobuf_RegisterTypes);
  Image::default_instance_ = new Image();
  Image::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_image_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_image_2eproto {
  StaticDescriptorInitializer_image_2eproto() {
    protobuf_AddDesc_image_2eproto();
  }
} static_descriptor_initializer_image_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Image::kWidthFieldNumber;
const int Image::kHeightFieldNumber;
const int Image::kPixelFormatFieldNumber;
const int Image::kStepFieldNumber;
const int Image::kDataFieldNumber;
#endif  // !_MSC_VER

Image::Image()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.Image)
}

void Image::InitAsDefaultInstance() {
}

Image::Image(const Image& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.Image)
}

void Image::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  width_ = 0u;
  height_ = 0u;
  pixel_format_ = 0u;
  step_ = 0u;
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Image::~Image() {
  // @@protoc_insertion_point(destructor:experimot.msgs.Image)
  SharedDtor();
}

void Image::SharedDtor() {
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void Image::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Image::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Image_descriptor_;
}

const Image& Image::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_image_2eproto();
  return *default_instance_;
}

Image* Image::default_instance_ = NULL;

Image* Image::New(::google::protobuf::Arena* arena) const {
  Image* n = new Image;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Image::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<Image*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(width_, step_);
    if (has_data()) {
      data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Image::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.Image)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 width = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &width_)));
          set_has_width();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_height;
        break;
      }

      // required uint32 height = 2;
      case 2: {
        if (tag == 16) {
         parse_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &height_)));
          set_has_height();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_pixel_format;
        break;
      }

      // required uint32 pixel_format = 3;
      case 3: {
        if (tag == 24) {
         parse_pixel_format:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &pixel_format_)));
          set_has_pixel_format();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_step;
        break;
      }

      // required uint32 step = 4;
      case 4: {
        if (tag == 32) {
         parse_step:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &step_)));
          set_has_step();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_data;
        break;
      }

      // required bytes data = 5;
      case 5: {
        if (tag == 42) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.Image)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.Image)
  return false;
#undef DO_
}

void Image::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.Image)
  // required uint32 width = 1;
  if (has_width()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->width(), output);
  }

  // required uint32 height = 2;
  if (has_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->height(), output);
  }

  // required uint32 pixel_format = 3;
  if (has_pixel_format()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->pixel_format(), output);
  }

  // required uint32 step = 4;
  if (has_step()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->step(), output);
  }

  // required bytes data = 5;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      5, this->data(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.Image)
}

::google::protobuf::uint8* Image::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.Image)
  // required uint32 width = 1;
  if (has_width()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->width(), target);
  }

  // required uint32 height = 2;
  if (has_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->height(), target);
  }

  // required uint32 pixel_format = 3;
  if (has_pixel_format()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->pixel_format(), target);
  }

  // required uint32 step = 4;
  if (has_step()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->step(), target);
  }

  // required bytes data = 5;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        5, this->data(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.Image)
  return target;
}

int Image::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_width()) {
    // required uint32 width = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->width());
  }

  if (has_height()) {
    // required uint32 height = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->height());
  }

  if (has_pixel_format()) {
    // required uint32 pixel_format = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->pixel_format());
  }

  if (has_step()) {
    // required uint32 step = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->step());
  }

  if (has_data()) {
    // required bytes data = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->data());
  }

  return total_size;
}
int Image::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x0000001f) ^ 0x0000001f) == 0) {  // All required fields are present.
    // required uint32 width = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->width());

    // required uint32 height = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->height());

    // required uint32 pixel_format = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->pixel_format());

    // required uint32 step = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->step());

    // required bytes data = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->data());

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

void Image::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Image* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Image*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Image::MergeFrom(const Image& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_width()) {
      set_width(from.width());
    }
    if (from.has_height()) {
      set_height(from.height());
    }
    if (from.has_pixel_format()) {
      set_pixel_format(from.pixel_format());
    }
    if (from.has_step()) {
      set_step(from.step());
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

void Image::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Image::CopyFrom(const Image& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Image::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  return true;
}

void Image::Swap(Image* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Image::InternalSwap(Image* other) {
  std::swap(width_, other->width_);
  std::swap(height_, other->height_);
  std::swap(pixel_format_, other->pixel_format_);
  std::swap(step_, other->step_);
  data_.Swap(&other->data_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Image::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Image_descriptor_;
  metadata.reflection = Image_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Image

// required uint32 width = 1;
 bool Image::has_width() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Image::set_has_width() {
  _has_bits_[0] |= 0x00000001u;
}
 void Image::clear_has_width() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Image::clear_width() {
  width_ = 0u;
  clear_has_width();
}
 ::google::protobuf::uint32 Image::width() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Image.width)
  return width_;
}
 void Image::set_width(::google::protobuf::uint32 value) {
  set_has_width();
  width_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Image.width)
}

// required uint32 height = 2;
 bool Image::has_height() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Image::set_has_height() {
  _has_bits_[0] |= 0x00000002u;
}
 void Image::clear_has_height() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Image::clear_height() {
  height_ = 0u;
  clear_has_height();
}
 ::google::protobuf::uint32 Image::height() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Image.height)
  return height_;
}
 void Image::set_height(::google::protobuf::uint32 value) {
  set_has_height();
  height_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Image.height)
}

// required uint32 pixel_format = 3;
 bool Image::has_pixel_format() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void Image::set_has_pixel_format() {
  _has_bits_[0] |= 0x00000004u;
}
 void Image::clear_has_pixel_format() {
  _has_bits_[0] &= ~0x00000004u;
}
 void Image::clear_pixel_format() {
  pixel_format_ = 0u;
  clear_has_pixel_format();
}
 ::google::protobuf::uint32 Image::pixel_format() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Image.pixel_format)
  return pixel_format_;
}
 void Image::set_pixel_format(::google::protobuf::uint32 value) {
  set_has_pixel_format();
  pixel_format_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Image.pixel_format)
}

// required uint32 step = 4;
 bool Image::has_step() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void Image::set_has_step() {
  _has_bits_[0] |= 0x00000008u;
}
 void Image::clear_has_step() {
  _has_bits_[0] &= ~0x00000008u;
}
 void Image::clear_step() {
  step_ = 0u;
  clear_has_step();
}
 ::google::protobuf::uint32 Image::step() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Image.step)
  return step_;
}
 void Image::set_step(::google::protobuf::uint32 value) {
  set_has_step();
  step_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.Image.step)
}

// required bytes data = 5;
 bool Image::has_data() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
 void Image::set_has_data() {
  _has_bits_[0] |= 0x00000010u;
}
 void Image::clear_has_data() {
  _has_bits_[0] &= ~0x00000010u;
}
 void Image::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
 const ::std::string& Image::data() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.Image.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Image::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.Image.data)
}
 void Image::set_data(const char* value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.Image.data)
}
 void Image::set_data(const void* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.Image.data)
}
 ::std::string* Image::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.Image.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Image::release_data() {
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Image::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.Image.data)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.Image", Image)
// @@protoc_insertion_point(global_scope)