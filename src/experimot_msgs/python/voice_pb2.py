# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: voice.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import param_pb2 as param__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='voice.proto',
  package='experimot.msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x0bvoice.proto\x12\x0e\x65xperimot.msgs\x1a\x0bparam.proto\"`\n\x17VoiceCommandDescription\x12\x0f\n\x07\x63ommand\x18\x01 \x02(\t\x12\x0e\n\x06\x61\x63tive\x18\x02 \x01(\x08\x12\x12\n\nconfidence\x18\x03 \x01(\x05\x12\x10\n\x08language\x18\x04 \x01(\t\"\x88\x01\n\x16VoiceRecognitionModule\x12\x0c\n\x04name\x18\x01 \x02(\t\x12%\n\x06params\x18\x02 \x03(\x0b\x32\x15.experimot.msgs.Param\x12\x39\n\x08\x63ommands\x18\x03 \x03(\x0b\x32\'.experimot.msgs.VoiceCommandDescription\"R\n\x17VoiceRecognitionModules\x12\x37\n\x07modules\x18\x01 \x03(\x0b\x32&.experimot.msgs.VoiceRecognitionModule')
  ,
  dependencies=[param__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_VOICECOMMANDDESCRIPTION = _descriptor.Descriptor(
  name='VoiceCommandDescription',
  full_name='experimot.msgs.VoiceCommandDescription',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='command', full_name='experimot.msgs.VoiceCommandDescription.command', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='active', full_name='experimot.msgs.VoiceCommandDescription.active', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='confidence', full_name='experimot.msgs.VoiceCommandDescription.confidence', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='language', full_name='experimot.msgs.VoiceCommandDescription.language', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=44,
  serialized_end=140,
)


_VOICERECOGNITIONMODULE = _descriptor.Descriptor(
  name='VoiceRecognitionModule',
  full_name='experimot.msgs.VoiceRecognitionModule',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='experimot.msgs.VoiceRecognitionModule.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='params', full_name='experimot.msgs.VoiceRecognitionModule.params', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='commands', full_name='experimot.msgs.VoiceRecognitionModule.commands', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=143,
  serialized_end=279,
)


_VOICERECOGNITIONMODULES = _descriptor.Descriptor(
  name='VoiceRecognitionModules',
  full_name='experimot.msgs.VoiceRecognitionModules',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='modules', full_name='experimot.msgs.VoiceRecognitionModules.modules', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=281,
  serialized_end=363,
)

_VOICERECOGNITIONMODULE.fields_by_name['params'].message_type = param__pb2._PARAM
_VOICERECOGNITIONMODULE.fields_by_name['commands'].message_type = _VOICECOMMANDDESCRIPTION
_VOICERECOGNITIONMODULES.fields_by_name['modules'].message_type = _VOICERECOGNITIONMODULE
DESCRIPTOR.message_types_by_name['VoiceCommandDescription'] = _VOICECOMMANDDESCRIPTION
DESCRIPTOR.message_types_by_name['VoiceRecognitionModule'] = _VOICERECOGNITIONMODULE
DESCRIPTOR.message_types_by_name['VoiceRecognitionModules'] = _VOICERECOGNITIONMODULES

VoiceCommandDescription = _reflection.GeneratedProtocolMessageType('VoiceCommandDescription', (_message.Message,), dict(
  DESCRIPTOR = _VOICECOMMANDDESCRIPTION,
  __module__ = 'voice_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.VoiceCommandDescription)
  ))
_sym_db.RegisterMessage(VoiceCommandDescription)

VoiceRecognitionModule = _reflection.GeneratedProtocolMessageType('VoiceRecognitionModule', (_message.Message,), dict(
  DESCRIPTOR = _VOICERECOGNITIONMODULE,
  __module__ = 'voice_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.VoiceRecognitionModule)
  ))
_sym_db.RegisterMessage(VoiceRecognitionModule)

VoiceRecognitionModules = _reflection.GeneratedProtocolMessageType('VoiceRecognitionModules', (_message.Message,), dict(
  DESCRIPTOR = _VOICERECOGNITIONMODULES,
  __module__ = 'voice_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.VoiceRecognitionModules)
  ))
_sym_db.RegisterMessage(VoiceRecognitionModules)


# @@protoc_insertion_point(module_scope)
