// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: imagegeom.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "imagegeom.pb.h"

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

const ::google::protobuf::Descriptor* ImageGeom_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ImageGeom_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_imagegeom_2eproto() {
  protobuf_AddDesc_imagegeom_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "imagegeom.proto");
  GOOGLE_CHECK(file != NULL);
  ImageGeom_descriptor_ = file->message_type(0);
  static const int ImageGeom_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, uri_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, threshold_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, granularity_),
  };
  ImageGeom_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      ImageGeom_descriptor_,
      ImageGeom::default_instance_,
      ImageGeom_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, _has_bits_[0]),
      -1,
      -1,
      sizeof(ImageGeom),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImageGeom, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_imagegeom_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      ImageGeom_descriptor_, &ImageGeom::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_imagegeom_2eproto() {
  delete ImageGeom::default_instance_;
  delete ImageGeom_reflection_;
}

void protobuf_AddDesc_imagegeom_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017imagegeom.proto\022\016experimot.msgs\"d\n\tIma"
    "geGeom\022\013\n\003uri\030\001 \002(\t\022\r\n\005scale\030\002 \001(\001\022\026\n\tth"
    "reshold\030\003 \001(\005:\003255\022\016\n\006height\030\004 \001(\001\022\023\n\013gr"
    "anularity\030\005 \001(\005", 135);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "imagegeom.proto", &protobuf_RegisterTypes);
  ImageGeom::default_instance_ = new ImageGeom();
  ImageGeom::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_imagegeom_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_imagegeom_2eproto {
  StaticDescriptorInitializer_imagegeom_2eproto() {
    protobuf_AddDesc_imagegeom_2eproto();
  }
} static_descriptor_initializer_imagegeom_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int ImageGeom::kUriFieldNumber;
const int ImageGeom::kScaleFieldNumber;
const int ImageGeom::kThresholdFieldNumber;
const int ImageGeom::kHeightFieldNumber;
const int ImageGeom::kGranularityFieldNumber;
#endif  // !_MSC_VER

ImageGeom::ImageGeom()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:experimot.msgs.ImageGeom)
}

void ImageGeom::InitAsDefaultInstance() {
}

ImageGeom::ImageGeom(const ImageGeom& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:experimot.msgs.ImageGeom)
}

void ImageGeom::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  uri_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  scale_ = 0;
  threshold_ = 255;
  height_ = 0;
  granularity_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ImageGeom::~ImageGeom() {
  // @@protoc_insertion_point(destructor:experimot.msgs.ImageGeom)
  SharedDtor();
}

void ImageGeom::SharedDtor() {
  uri_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void ImageGeom::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ImageGeom::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ImageGeom_descriptor_;
}

const ImageGeom& ImageGeom::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_imagegeom_2eproto();
  return *default_instance_;
}

ImageGeom* ImageGeom::default_instance_ = NULL;

ImageGeom* ImageGeom::New(::google::protobuf::Arena* arena) const {
  ImageGeom* n = new ImageGeom;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ImageGeom::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<ImageGeom*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(scale_, height_);
    if (has_uri()) {
      uri_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    threshold_ = 255;
    granularity_ = 0;
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool ImageGeom::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:experimot.msgs.ImageGeom)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string uri = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_uri()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->uri().data(), this->uri().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "experimot.msgs.ImageGeom.uri");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_scale;
        break;
      }

      // optional double scale = 2;
      case 2: {
        if (tag == 17) {
         parse_scale:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &scale_)));
          set_has_scale();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_threshold;
        break;
      }

      // optional int32 threshold = 3 [default = 255];
      case 3: {
        if (tag == 24) {
         parse_threshold:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &threshold_)));
          set_has_threshold();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_height;
        break;
      }

      // optional double height = 4;
      case 4: {
        if (tag == 33) {
         parse_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &height_)));
          set_has_height();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_granularity;
        break;
      }

      // optional int32 granularity = 5;
      case 5: {
        if (tag == 40) {
         parse_granularity:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &granularity_)));
          set_has_granularity();
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
  // @@protoc_insertion_point(parse_success:experimot.msgs.ImageGeom)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:experimot.msgs.ImageGeom)
  return false;
#undef DO_
}

void ImageGeom::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:experimot.msgs.ImageGeom)
  // required string uri = 1;
  if (has_uri()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->uri().data(), this->uri().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.ImageGeom.uri");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->uri(), output);
  }

  // optional double scale = 2;
  if (has_scale()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->scale(), output);
  }

  // optional int32 threshold = 3 [default = 255];
  if (has_threshold()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->threshold(), output);
  }

  // optional double height = 4;
  if (has_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->height(), output);
  }

  // optional int32 granularity = 5;
  if (has_granularity()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->granularity(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:experimot.msgs.ImageGeom)
}

::google::protobuf::uint8* ImageGeom::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:experimot.msgs.ImageGeom)
  // required string uri = 1;
  if (has_uri()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->uri().data(), this->uri().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "experimot.msgs.ImageGeom.uri");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->uri(), target);
  }

  // optional double scale = 2;
  if (has_scale()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->scale(), target);
  }

  // optional int32 threshold = 3 [default = 255];
  if (has_threshold()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->threshold(), target);
  }

  // optional double height = 4;
  if (has_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->height(), target);
  }

  // optional int32 granularity = 5;
  if (has_granularity()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->granularity(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:experimot.msgs.ImageGeom)
  return target;
}

int ImageGeom::ByteSize() const {
  int total_size = 0;

  // required string uri = 1;
  if (has_uri()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->uri());
  }
  if (_has_bits_[1 / 32] & 30) {
    // optional double scale = 2;
    if (has_scale()) {
      total_size += 1 + 8;
    }

    // optional int32 threshold = 3 [default = 255];
    if (has_threshold()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->threshold());
    }

    // optional double height = 4;
    if (has_height()) {
      total_size += 1 + 8;
    }

    // optional int32 granularity = 5;
    if (has_granularity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->granularity());
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

void ImageGeom::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const ImageGeom* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ImageGeom*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ImageGeom::MergeFrom(const ImageGeom& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uri()) {
      set_has_uri();
      uri_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.uri_);
    }
    if (from.has_scale()) {
      set_scale(from.scale());
    }
    if (from.has_threshold()) {
      set_threshold(from.threshold());
    }
    if (from.has_height()) {
      set_height(from.height());
    }
    if (from.has_granularity()) {
      set_granularity(from.granularity());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void ImageGeom::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ImageGeom::CopyFrom(const ImageGeom& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImageGeom::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ImageGeom::Swap(ImageGeom* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ImageGeom::InternalSwap(ImageGeom* other) {
  uri_.Swap(&other->uri_);
  std::swap(scale_, other->scale_);
  std::swap(threshold_, other->threshold_);
  std::swap(height_, other->height_);
  std::swap(granularity_, other->granularity_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ImageGeom::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ImageGeom_descriptor_;
  metadata.reflection = ImageGeom_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ImageGeom

// required string uri = 1;
 bool ImageGeom::has_uri() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void ImageGeom::set_has_uri() {
  _has_bits_[0] |= 0x00000001u;
}
 void ImageGeom::clear_has_uri() {
  _has_bits_[0] &= ~0x00000001u;
}
 void ImageGeom::clear_uri() {
  uri_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_uri();
}
 const ::std::string& ImageGeom::uri() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImageGeom.uri)
  return uri_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ImageGeom::set_uri(const ::std::string& value) {
  set_has_uri();
  uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:experimot.msgs.ImageGeom.uri)
}
 void ImageGeom::set_uri(const char* value) {
  set_has_uri();
  uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:experimot.msgs.ImageGeom.uri)
}
 void ImageGeom::set_uri(const char* value, size_t size) {
  set_has_uri();
  uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:experimot.msgs.ImageGeom.uri)
}
 ::std::string* ImageGeom::mutable_uri() {
  set_has_uri();
  // @@protoc_insertion_point(field_mutable:experimot.msgs.ImageGeom.uri)
  return uri_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* ImageGeom::release_uri() {
  clear_has_uri();
  return uri_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ImageGeom::set_allocated_uri(::std::string* uri) {
  if (uri != NULL) {
    set_has_uri();
  } else {
    clear_has_uri();
  }
  uri_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), uri);
  // @@protoc_insertion_point(field_set_allocated:experimot.msgs.ImageGeom.uri)
}

// optional double scale = 2;
 bool ImageGeom::has_scale() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void ImageGeom::set_has_scale() {
  _has_bits_[0] |= 0x00000002u;
}
 void ImageGeom::clear_has_scale() {
  _has_bits_[0] &= ~0x00000002u;
}
 void ImageGeom::clear_scale() {
  scale_ = 0;
  clear_has_scale();
}
 double ImageGeom::scale() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImageGeom.scale)
  return scale_;
}
 void ImageGeom::set_scale(double value) {
  set_has_scale();
  scale_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.ImageGeom.scale)
}

// optional int32 threshold = 3 [default = 255];
 bool ImageGeom::has_threshold() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void ImageGeom::set_has_threshold() {
  _has_bits_[0] |= 0x00000004u;
}
 void ImageGeom::clear_has_threshold() {
  _has_bits_[0] &= ~0x00000004u;
}
 void ImageGeom::clear_threshold() {
  threshold_ = 255;
  clear_has_threshold();
}
 ::google::protobuf::int32 ImageGeom::threshold() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImageGeom.threshold)
  return threshold_;
}
 void ImageGeom::set_threshold(::google::protobuf::int32 value) {
  set_has_threshold();
  threshold_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.ImageGeom.threshold)
}

// optional double height = 4;
 bool ImageGeom::has_height() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void ImageGeom::set_has_height() {
  _has_bits_[0] |= 0x00000008u;
}
 void ImageGeom::clear_has_height() {
  _has_bits_[0] &= ~0x00000008u;
}
 void ImageGeom::clear_height() {
  height_ = 0;
  clear_has_height();
}
 double ImageGeom::height() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImageGeom.height)
  return height_;
}
 void ImageGeom::set_height(double value) {
  set_has_height();
  height_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.ImageGeom.height)
}

// optional int32 granularity = 5;
 bool ImageGeom::has_granularity() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
 void ImageGeom::set_has_granularity() {
  _has_bits_[0] |= 0x00000010u;
}
 void ImageGeom::clear_has_granularity() {
  _has_bits_[0] &= ~0x00000010u;
}
 void ImageGeom::clear_granularity() {
  granularity_ = 0;
  clear_has_granularity();
}
 ::google::protobuf::int32 ImageGeom::granularity() const {
  // @@protoc_insertion_point(field_get:experimot.msgs.ImageGeom.granularity)
  return granularity_;
}
 void ImageGeom::set_granularity(::google::protobuf::int32 value) {
  set_has_granularity();
  granularity_ = value;
  // @@protoc_insertion_point(field_set:experimot.msgs.ImageGeom.granularity)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace experimot

EX_REGISTER_STATIC_MSG("experimot.msgs.ImageGeom", ImageGeom)
// @@protoc_insertion_point(global_scope)
