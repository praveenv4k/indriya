# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: world_reset.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='world_reset.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x11world_reset.proto\x12\x0e\x65xperimot.msgs\"T\n\nWorldReset\x12\x11\n\x03\x61ll\x18\x01 \x01(\x08:\x04true\x12\x18\n\ttime_only\x18\x02 \x01(\x08:\x05\x66\x61lse\x12\x19\n\nmodel_only\x18\x03 \x01(\x08:\x05\x66\x61lse')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_WORLDRESET = _descriptor.Descriptor(
  name='WorldReset',
  full_name='experimot.msgs.WorldReset',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='all', full_name='experimot.msgs.WorldReset.all', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time_only', full_name='experimot.msgs.WorldReset.time_only', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='model_only', full_name='experimot.msgs.WorldReset.model_only', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
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
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=37,
  serialized_end=121,
)

DESCRIPTOR.message_types_by_name['WorldReset'] = _WORLDRESET

WorldReset = _reflection.GeneratedProtocolMessageType('WorldReset', (_message.Message,), dict(
  DESCRIPTOR = _WORLDRESET,
  __module__ = 'world_reset_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.WorldReset)
  ))
_sym_db.RegisterMessage(WorldReset)


# @@protoc_insertion_point(module_scope)
