# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: world_control.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import world_reset_pb2 as world__reset__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='world_control.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x13world_control.proto\x12\x0e\x65xperimot.msgs\x1a\x11world_reset.proto\"x\n\x0cWorldControl\x12\r\n\x05pause\x18\x01 \x01(\x08\x12\x0c\n\x04step\x18\x02 \x01(\x08\x12\x12\n\nmulti_step\x18\x03 \x01(\r\x12)\n\x05reset\x18\x04 \x01(\x0b\x32\x1a.experimot.msgs.WorldReset\x12\x0c\n\x04seed\x18\x05 \x01(\r')
  ,
  dependencies=[world__reset__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_WORLDCONTROL = _descriptor.Descriptor(
  name='WorldControl',
  full_name='experimot.msgs.WorldControl',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='pause', full_name='experimot.msgs.WorldControl.pause', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='step', full_name='experimot.msgs.WorldControl.step', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='multi_step', full_name='experimot.msgs.WorldControl.multi_step', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='reset', full_name='experimot.msgs.WorldControl.reset', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='seed', full_name='experimot.msgs.WorldControl.seed', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
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
  serialized_start=58,
  serialized_end=178,
)

_WORLDCONTROL.fields_by_name['reset'].message_type = world__reset__pb2._WORLDRESET
DESCRIPTOR.message_types_by_name['WorldControl'] = _WORLDCONTROL

WorldControl = _reflection.GeneratedProtocolMessageType('WorldControl', (_message.Message,), dict(
  DESCRIPTOR = _WORLDCONTROL,
  __module__ = 'world_control_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.WorldControl)
  ))
_sym_db.RegisterMessage(WorldControl)


# @@protoc_insertion_point(module_scope)
