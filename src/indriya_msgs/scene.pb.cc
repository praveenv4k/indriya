// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: scene.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "scene.pb.h"

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

const ::google::protobuf::Descriptor* Scene_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Scene_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_scene_2eproto() {
  protobuf_AddDesc_scene_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "scene.proto");
  GOOGLE_CHECK(file != NULL);
  Scene_descriptor_ = file->message_type(0);
  static const int Scene_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, ambient_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, background_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, sky_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, shadows_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, fog_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, grid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, model_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, light_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, joint_),
  };
  Scene_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Scene_descriptor_,
      Scene::default_instance_,
      Scene_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, _has_bits_[0]),
      -1,
      -1,
      sizeof(Scene),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Scene, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_scene_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Scene_descriptor_, &Scene::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_scene_2eproto() {
  delete Scene::default_instance_;
  delete Scene_reflection_;
}

void protobuf_AddDesc_scene_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Indriya::Core::Msgs::protobuf_AddDesc_color_2eproto();
  ::Indriya::Core::Msgs::protobuf_AddDesc_fog_2eproto();
  ::Indriya::Core::Msgs::protobuf_AddDesc_sky_2eproto();
  ::Indriya::Core::Msgs::protobuf_AddDesc_light_2eproto();
  ::Indriya::Core::Msgs::protobuf_AddDesc_joint_2eproto();
  ::Indriya::Core::Msgs::protobuf_AddDesc_model_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013scene.proto\022\021Indriya.Core.Msgs\032\013color."
    "proto\032\tfog.proto\032\tsky.proto\032\013light.proto"
    "\032\013joint.proto\032\013model.proto\"\330\002\n\005Scene\022\014\n\004"
    "name\030\001 \002(\t\022)\n\007ambient\030\002 \001(\0132\030.Indriya.Co"
    "re.Msgs.Color\022,\n\nbackground\030\003 \001(\0132\030.Indr"
    "iya.Core.Msgs.Color\022#\n\003sky\030\004 \001(\0132\026.Indri"
    "ya.Core.Msgs.Sky\022\025\n\007shadows\030\005 \001(\010:\004true\022"
    "#\n\003fog\030\006 \001(\0132\026.Indriya.Core.Msgs.Fog\022\014\n\004"
    "grid\030\007 \001(\010\022\'\n\005model\030\010 \003(\0132\030.Indriya.Core"
    ".Msgs.Model\022\'\n\005light\030\t \003(\0132\030.Indriya.Cor"
    "e.Msgs.Light\022\'\n\005joint\030\n \003(\0132\030.Indriya.Co"
    "re.Msgs.Joint", 453);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "scene.proto", &protobuf_RegisterTypes);
  Scene::default_instance_ = new Scene();
  Scene::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_scene_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_scene_2eproto {
  StaticDescriptorInitializer_scene_2eproto() {
    protobuf_AddDesc_scene_2eproto();
  }
} static_descriptor_initializer_scene_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int Scene::kNameFieldNumber;
const int Scene::kAmbientFieldNumber;
const int Scene::kBackgroundFieldNumber;
const int Scene::kSkyFieldNumber;
const int Scene::kShadowsFieldNumber;
const int Scene::kFogFieldNumber;
const int Scene::kGridFieldNumber;
const int Scene::kModelFieldNumber;
const int Scene::kLightFieldNumber;
const int Scene::kJointFieldNumber;
#endif  // !_MSC_VER

Scene::Scene()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Indriya.Core.Msgs.Scene)
}

void Scene::InitAsDefaultInstance() {
  ambient_ = const_cast< ::Indriya::Core::Msgs::Color*>(&::Indriya::Core::Msgs::Color::default_instance());
  background_ = const_cast< ::Indriya::Core::Msgs::Color*>(&::Indriya::Core::Msgs::Color::default_instance());
  sky_ = const_cast< ::Indriya::Core::Msgs::Sky*>(&::Indriya::Core::Msgs::Sky::default_instance());
  fog_ = const_cast< ::Indriya::Core::Msgs::Fog*>(&::Indriya::Core::Msgs::Fog::default_instance());
}

Scene::Scene(const Scene& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Indriya.Core.Msgs.Scene)
}

void Scene::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ambient_ = NULL;
  background_ = NULL;
  sky_ = NULL;
  shadows_ = true;
  fog_ = NULL;
  grid_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Scene::~Scene() {
  // @@protoc_insertion_point(destructor:Indriya.Core.Msgs.Scene)
  SharedDtor();
}

void Scene::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
    delete ambient_;
    delete background_;
    delete sky_;
    delete fog_;
  }
}

void Scene::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Scene::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Scene_descriptor_;
}

const Scene& Scene::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_scene_2eproto();
  return *default_instance_;
}

Scene* Scene::default_instance_ = NULL;

Scene* Scene::New(::google::protobuf::Arena* arena) const {
  Scene* n = new Scene;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Scene::Clear() {
  if (_has_bits_[0 / 32] & 127) {
    if (has_name()) {
      name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_ambient()) {
      if (ambient_ != NULL) ambient_->::Indriya::Core::Msgs::Color::Clear();
    }
    if (has_background()) {
      if (background_ != NULL) background_->::Indriya::Core::Msgs::Color::Clear();
    }
    if (has_sky()) {
      if (sky_ != NULL) sky_->::Indriya::Core::Msgs::Sky::Clear();
    }
    shadows_ = true;
    if (has_fog()) {
      if (fog_ != NULL) fog_->::Indriya::Core::Msgs::Fog::Clear();
    }
    grid_ = false;
  }
  model_.Clear();
  light_.Clear();
  joint_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool Scene::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Indriya.Core.Msgs.Scene)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "Indriya.Core.Msgs.Scene.name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ambient;
        break;
      }

      // optional .Indriya.Core.Msgs.Color ambient = 2;
      case 2: {
        if (tag == 18) {
         parse_ambient:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_ambient()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_background;
        break;
      }

      // optional .Indriya.Core.Msgs.Color background = 3;
      case 3: {
        if (tag == 26) {
         parse_background:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_background()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_sky;
        break;
      }

      // optional .Indriya.Core.Msgs.Sky sky = 4;
      case 4: {
        if (tag == 34) {
         parse_sky:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_sky()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_shadows;
        break;
      }

      // optional bool shadows = 5 [default = true];
      case 5: {
        if (tag == 40) {
         parse_shadows:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &shadows_)));
          set_has_shadows();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_fog;
        break;
      }

      // optional .Indriya.Core.Msgs.Fog fog = 6;
      case 6: {
        if (tag == 50) {
         parse_fog:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_fog()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_grid;
        break;
      }

      // optional bool grid = 7;
      case 7: {
        if (tag == 56) {
         parse_grid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &grid_)));
          set_has_grid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_model;
        break;
      }

      // repeated .Indriya.Core.Msgs.Model model = 8;
      case 8: {
        if (tag == 66) {
         parse_model:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_model()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_model;
        if (input->ExpectTag(74)) goto parse_light;
        break;
      }

      // repeated .Indriya.Core.Msgs.Light light = 9;
      case 9: {
        if (tag == 74) {
         parse_light:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_light()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(74)) goto parse_light;
        if (input->ExpectTag(82)) goto parse_joint;
        break;
      }

      // repeated .Indriya.Core.Msgs.Joint joint = 10;
      case 10: {
        if (tag == 82) {
         parse_joint:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_joint()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(82)) goto parse_joint;
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
  // @@protoc_insertion_point(parse_success:Indriya.Core.Msgs.Scene)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Indriya.Core.Msgs.Scene)
  return false;
#undef DO_
}

void Scene::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Indriya.Core.Msgs.Scene)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Indriya.Core.Msgs.Scene.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // optional .Indriya.Core.Msgs.Color ambient = 2;
  if (has_ambient()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->ambient_, output);
  }

  // optional .Indriya.Core.Msgs.Color background = 3;
  if (has_background()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->background_, output);
  }

  // optional .Indriya.Core.Msgs.Sky sky = 4;
  if (has_sky()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, *this->sky_, output);
  }

  // optional bool shadows = 5 [default = true];
  if (has_shadows()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->shadows(), output);
  }

  // optional .Indriya.Core.Msgs.Fog fog = 6;
  if (has_fog()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, *this->fog_, output);
  }

  // optional bool grid = 7;
  if (has_grid()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->grid(), output);
  }

  // repeated .Indriya.Core.Msgs.Model model = 8;
  for (unsigned int i = 0, n = this->model_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      8, this->model(i), output);
  }

  // repeated .Indriya.Core.Msgs.Light light = 9;
  for (unsigned int i = 0, n = this->light_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      9, this->light(i), output);
  }

  // repeated .Indriya.Core.Msgs.Joint joint = 10;
  for (unsigned int i = 0, n = this->joint_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      10, this->joint(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Indriya.Core.Msgs.Scene)
}

::google::protobuf::uint8* Scene::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Indriya.Core.Msgs.Scene)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Indriya.Core.Msgs.Scene.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // optional .Indriya.Core.Msgs.Color ambient = 2;
  if (has_ambient()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, *this->ambient_, target);
  }

  // optional .Indriya.Core.Msgs.Color background = 3;
  if (has_background()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, *this->background_, target);
  }

  // optional .Indriya.Core.Msgs.Sky sky = 4;
  if (has_sky()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, *this->sky_, target);
  }

  // optional bool shadows = 5 [default = true];
  if (has_shadows()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->shadows(), target);
  }

  // optional .Indriya.Core.Msgs.Fog fog = 6;
  if (has_fog()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, *this->fog_, target);
  }

  // optional bool grid = 7;
  if (has_grid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->grid(), target);
  }

  // repeated .Indriya.Core.Msgs.Model model = 8;
  for (unsigned int i = 0, n = this->model_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        8, this->model(i), target);
  }

  // repeated .Indriya.Core.Msgs.Light light = 9;
  for (unsigned int i = 0, n = this->light_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        9, this->light(i), target);
  }

  // repeated .Indriya.Core.Msgs.Joint joint = 10;
  for (unsigned int i = 0, n = this->joint_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        10, this->joint(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Indriya.Core.Msgs.Scene)
  return target;
}

int Scene::ByteSize() const {
  int total_size = 0;

  // required string name = 1;
  if (has_name()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }
  if (_has_bits_[1 / 32] & 126) {
    // optional .Indriya.Core.Msgs.Color ambient = 2;
    if (has_ambient()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->ambient_);
    }

    // optional .Indriya.Core.Msgs.Color background = 3;
    if (has_background()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->background_);
    }

    // optional .Indriya.Core.Msgs.Sky sky = 4;
    if (has_sky()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->sky_);
    }

    // optional bool shadows = 5 [default = true];
    if (has_shadows()) {
      total_size += 1 + 1;
    }

    // optional .Indriya.Core.Msgs.Fog fog = 6;
    if (has_fog()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *this->fog_);
    }

    // optional bool grid = 7;
    if (has_grid()) {
      total_size += 1 + 1;
    }

  }
  // repeated .Indriya.Core.Msgs.Model model = 8;
  total_size += 1 * this->model_size();
  for (int i = 0; i < this->model_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->model(i));
  }

  // repeated .Indriya.Core.Msgs.Light light = 9;
  total_size += 1 * this->light_size();
  for (int i = 0; i < this->light_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->light(i));
  }

  // repeated .Indriya.Core.Msgs.Joint joint = 10;
  total_size += 1 * this->joint_size();
  for (int i = 0; i < this->joint_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->joint(i));
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

void Scene::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Scene* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Scene*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Scene::MergeFrom(const Scene& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  model_.MergeFrom(from.model_);
  light_.MergeFrom(from.light_);
  joint_.MergeFrom(from.joint_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (from.has_ambient()) {
      mutable_ambient()->::Indriya::Core::Msgs::Color::MergeFrom(from.ambient());
    }
    if (from.has_background()) {
      mutable_background()->::Indriya::Core::Msgs::Color::MergeFrom(from.background());
    }
    if (from.has_sky()) {
      mutable_sky()->::Indriya::Core::Msgs::Sky::MergeFrom(from.sky());
    }
    if (from.has_shadows()) {
      set_shadows(from.shadows());
    }
    if (from.has_fog()) {
      mutable_fog()->::Indriya::Core::Msgs::Fog::MergeFrom(from.fog());
    }
    if (from.has_grid()) {
      set_grid(from.grid());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void Scene::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Scene::CopyFrom(const Scene& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Scene::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (has_ambient()) {
    if (!this->ambient_->IsInitialized()) return false;
  }
  if (has_background()) {
    if (!this->background_->IsInitialized()) return false;
  }
  if (has_sky()) {
    if (!this->sky_->IsInitialized()) return false;
  }
  if (has_fog()) {
    if (!this->fog_->IsInitialized()) return false;
  }
  if (!::google::protobuf::internal::AllAreInitialized(this->model())) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->light())) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->joint())) return false;
  return true;
}

void Scene::Swap(Scene* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Scene::InternalSwap(Scene* other) {
  name_.Swap(&other->name_);
  std::swap(ambient_, other->ambient_);
  std::swap(background_, other->background_);
  std::swap(sky_, other->sky_);
  std::swap(shadows_, other->shadows_);
  std::swap(fog_, other->fog_);
  std::swap(grid_, other->grid_);
  model_.UnsafeArenaSwap(&other->model_);
  light_.UnsafeArenaSwap(&other->light_);
  joint_.UnsafeArenaSwap(&other->joint_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Scene::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Scene_descriptor_;
  metadata.reflection = Scene_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Scene

// required string name = 1;
 bool Scene::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void Scene::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
 void Scene::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
 void Scene::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
 const ::std::string& Scene::name() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Scene::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Scene.name)
}
 void Scene::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Indriya.Core.Msgs.Scene.name)
}
 void Scene::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Indriya.Core.Msgs.Scene.name)
}
 ::std::string* Scene::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Scene::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Scene::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Scene.name)
}

// optional .Indriya.Core.Msgs.Color ambient = 2;
 bool Scene::has_ambient() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void Scene::set_has_ambient() {
  _has_bits_[0] |= 0x00000002u;
}
 void Scene::clear_has_ambient() {
  _has_bits_[0] &= ~0x00000002u;
}
 void Scene::clear_ambient() {
  if (ambient_ != NULL) ambient_->::Indriya::Core::Msgs::Color::Clear();
  clear_has_ambient();
}
 const ::Indriya::Core::Msgs::Color& Scene::ambient() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.ambient)
  return ambient_ != NULL ? *ambient_ : *default_instance_->ambient_;
}
 ::Indriya::Core::Msgs::Color* Scene::mutable_ambient() {
  set_has_ambient();
  if (ambient_ == NULL) {
    ambient_ = new ::Indriya::Core::Msgs::Color;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.ambient)
  return ambient_;
}
 ::Indriya::Core::Msgs::Color* Scene::release_ambient() {
  clear_has_ambient();
  ::Indriya::Core::Msgs::Color* temp = ambient_;
  ambient_ = NULL;
  return temp;
}
 void Scene::set_allocated_ambient(::Indriya::Core::Msgs::Color* ambient) {
  delete ambient_;
  ambient_ = ambient;
  if (ambient) {
    set_has_ambient();
  } else {
    clear_has_ambient();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Scene.ambient)
}

// optional .Indriya.Core.Msgs.Color background = 3;
 bool Scene::has_background() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void Scene::set_has_background() {
  _has_bits_[0] |= 0x00000004u;
}
 void Scene::clear_has_background() {
  _has_bits_[0] &= ~0x00000004u;
}
 void Scene::clear_background() {
  if (background_ != NULL) background_->::Indriya::Core::Msgs::Color::Clear();
  clear_has_background();
}
 const ::Indriya::Core::Msgs::Color& Scene::background() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.background)
  return background_ != NULL ? *background_ : *default_instance_->background_;
}
 ::Indriya::Core::Msgs::Color* Scene::mutable_background() {
  set_has_background();
  if (background_ == NULL) {
    background_ = new ::Indriya::Core::Msgs::Color;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.background)
  return background_;
}
 ::Indriya::Core::Msgs::Color* Scene::release_background() {
  clear_has_background();
  ::Indriya::Core::Msgs::Color* temp = background_;
  background_ = NULL;
  return temp;
}
 void Scene::set_allocated_background(::Indriya::Core::Msgs::Color* background) {
  delete background_;
  background_ = background;
  if (background) {
    set_has_background();
  } else {
    clear_has_background();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Scene.background)
}

// optional .Indriya.Core.Msgs.Sky sky = 4;
 bool Scene::has_sky() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void Scene::set_has_sky() {
  _has_bits_[0] |= 0x00000008u;
}
 void Scene::clear_has_sky() {
  _has_bits_[0] &= ~0x00000008u;
}
 void Scene::clear_sky() {
  if (sky_ != NULL) sky_->::Indriya::Core::Msgs::Sky::Clear();
  clear_has_sky();
}
 const ::Indriya::Core::Msgs::Sky& Scene::sky() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.sky)
  return sky_ != NULL ? *sky_ : *default_instance_->sky_;
}
 ::Indriya::Core::Msgs::Sky* Scene::mutable_sky() {
  set_has_sky();
  if (sky_ == NULL) {
    sky_ = new ::Indriya::Core::Msgs::Sky;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.sky)
  return sky_;
}
 ::Indriya::Core::Msgs::Sky* Scene::release_sky() {
  clear_has_sky();
  ::Indriya::Core::Msgs::Sky* temp = sky_;
  sky_ = NULL;
  return temp;
}
 void Scene::set_allocated_sky(::Indriya::Core::Msgs::Sky* sky) {
  delete sky_;
  sky_ = sky;
  if (sky) {
    set_has_sky();
  } else {
    clear_has_sky();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Scene.sky)
}

// optional bool shadows = 5 [default = true];
 bool Scene::has_shadows() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
 void Scene::set_has_shadows() {
  _has_bits_[0] |= 0x00000010u;
}
 void Scene::clear_has_shadows() {
  _has_bits_[0] &= ~0x00000010u;
}
 void Scene::clear_shadows() {
  shadows_ = true;
  clear_has_shadows();
}
 bool Scene::shadows() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.shadows)
  return shadows_;
}
 void Scene::set_shadows(bool value) {
  set_has_shadows();
  shadows_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Scene.shadows)
}

// optional .Indriya.Core.Msgs.Fog fog = 6;
 bool Scene::has_fog() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
 void Scene::set_has_fog() {
  _has_bits_[0] |= 0x00000020u;
}
 void Scene::clear_has_fog() {
  _has_bits_[0] &= ~0x00000020u;
}
 void Scene::clear_fog() {
  if (fog_ != NULL) fog_->::Indriya::Core::Msgs::Fog::Clear();
  clear_has_fog();
}
 const ::Indriya::Core::Msgs::Fog& Scene::fog() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.fog)
  return fog_ != NULL ? *fog_ : *default_instance_->fog_;
}
 ::Indriya::Core::Msgs::Fog* Scene::mutable_fog() {
  set_has_fog();
  if (fog_ == NULL) {
    fog_ = new ::Indriya::Core::Msgs::Fog;
  }
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.fog)
  return fog_;
}
 ::Indriya::Core::Msgs::Fog* Scene::release_fog() {
  clear_has_fog();
  ::Indriya::Core::Msgs::Fog* temp = fog_;
  fog_ = NULL;
  return temp;
}
 void Scene::set_allocated_fog(::Indriya::Core::Msgs::Fog* fog) {
  delete fog_;
  fog_ = fog;
  if (fog) {
    set_has_fog();
  } else {
    clear_has_fog();
  }
  // @@protoc_insertion_point(field_set_allocated:Indriya.Core.Msgs.Scene.fog)
}

// optional bool grid = 7;
 bool Scene::has_grid() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
 void Scene::set_has_grid() {
  _has_bits_[0] |= 0x00000040u;
}
 void Scene::clear_has_grid() {
  _has_bits_[0] &= ~0x00000040u;
}
 void Scene::clear_grid() {
  grid_ = false;
  clear_has_grid();
}
 bool Scene::grid() const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.grid)
  return grid_;
}
 void Scene::set_grid(bool value) {
  set_has_grid();
  grid_ = value;
  // @@protoc_insertion_point(field_set:Indriya.Core.Msgs.Scene.grid)
}

// repeated .Indriya.Core.Msgs.Model model = 8;
 int Scene::model_size() const {
  return model_.size();
}
 void Scene::clear_model() {
  model_.Clear();
}
 const ::Indriya::Core::Msgs::Model& Scene::model(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.model)
  return model_.Get(index);
}
 ::Indriya::Core::Msgs::Model* Scene::mutable_model(int index) {
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.model)
  return model_.Mutable(index);
}
 ::Indriya::Core::Msgs::Model* Scene::add_model() {
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.Scene.model)
  return model_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Model >&
Scene::model() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.Scene.model)
  return model_;
}
 ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Model >*
Scene::mutable_model() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.Scene.model)
  return &model_;
}

// repeated .Indriya.Core.Msgs.Light light = 9;
 int Scene::light_size() const {
  return light_.size();
}
 void Scene::clear_light() {
  light_.Clear();
}
 const ::Indriya::Core::Msgs::Light& Scene::light(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.light)
  return light_.Get(index);
}
 ::Indriya::Core::Msgs::Light* Scene::mutable_light(int index) {
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.light)
  return light_.Mutable(index);
}
 ::Indriya::Core::Msgs::Light* Scene::add_light() {
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.Scene.light)
  return light_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Light >&
Scene::light() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.Scene.light)
  return light_;
}
 ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Light >*
Scene::mutable_light() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.Scene.light)
  return &light_;
}

// repeated .Indriya.Core.Msgs.Joint joint = 10;
 int Scene::joint_size() const {
  return joint_.size();
}
 void Scene::clear_joint() {
  joint_.Clear();
}
 const ::Indriya::Core::Msgs::Joint& Scene::joint(int index) const {
  // @@protoc_insertion_point(field_get:Indriya.Core.Msgs.Scene.joint)
  return joint_.Get(index);
}
 ::Indriya::Core::Msgs::Joint* Scene::mutable_joint(int index) {
  // @@protoc_insertion_point(field_mutable:Indriya.Core.Msgs.Scene.joint)
  return joint_.Mutable(index);
}
 ::Indriya::Core::Msgs::Joint* Scene::add_joint() {
  // @@protoc_insertion_point(field_add:Indriya.Core.Msgs.Scene.joint)
  return joint_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Joint >&
Scene::joint() const {
  // @@protoc_insertion_point(field_list:Indriya.Core.Msgs.Scene.joint)
  return joint_;
}
 ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Joint >*
Scene::mutable_joint() {
  // @@protoc_insertion_point(field_mutable_list:Indriya.Core.Msgs.Scene.joint)
  return &joint_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Msgs
}  // namespace Core
}  // namespace Indriya

EX_REGISTER_STATIC_MSG("Indriya.Core.Msgs.Scene", Scene)
// @@protoc_insertion_point(global_scope)
