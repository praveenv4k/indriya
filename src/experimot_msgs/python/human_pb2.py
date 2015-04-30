# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: human.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import vector3d_pb2 as vector3d__pb2
import quaternion_pb2 as quaternion__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='human.proto',
  package='experimot.msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x0bhuman.proto\x12\x0e\x65xperimot.msgs\x1a\x0evector3d.proto\x1a\x10quaternion.proto\"\xb8\x01\n\x05Human\x12\n\n\x02id\x18\x01 \x02(\x05\x12\x0f\n\x07tracked\x18\x02 \x02(\x08\x12\x30\n\x0etorso_position\x18\x03 \x02(\x0b\x32\x18.experimot.msgs.Vector3d\x12/\n\rhead_position\x18\x04 \x02(\x0b\x32\x18.experimot.msgs.Vector3d\x12/\n\x0borientation\x18\x05 \x02(\x0b\x32\x1a.experimot.msgs.Quaternion\".\n\x06Humans\x12$\n\x05human\x18\x01 \x03(\x0b\x32\x15.experimot.msgs.Human')
  ,
  dependencies=[vector3d__pb2.DESCRIPTOR,quaternion__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_HUMAN = _descriptor.Descriptor(
  name='Human',
  full_name='experimot.msgs.Human',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='experimot.msgs.Human.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='tracked', full_name='experimot.msgs.Human.tracked', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='torso_position', full_name='experimot.msgs.Human.torso_position', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='head_position', full_name='experimot.msgs.Human.head_position', index=3,
      number=4, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='orientation', full_name='experimot.msgs.Human.orientation', index=4,
      number=5, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
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
  serialized_start=66,
  serialized_end=250,
)


_HUMANS = _descriptor.Descriptor(
  name='Humans',
  full_name='experimot.msgs.Humans',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='human', full_name='experimot.msgs.Humans.human', index=0,
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
  serialized_start=252,
  serialized_end=298,
)

_HUMAN.fields_by_name['torso_position'].message_type = vector3d__pb2._VECTOR3D
_HUMAN.fields_by_name['head_position'].message_type = vector3d__pb2._VECTOR3D
_HUMAN.fields_by_name['orientation'].message_type = quaternion__pb2._QUATERNION
_HUMANS.fields_by_name['human'].message_type = _HUMAN
DESCRIPTOR.message_types_by_name['Human'] = _HUMAN
DESCRIPTOR.message_types_by_name['Humans'] = _HUMANS

Human = _reflection.GeneratedProtocolMessageType('Human', (_message.Message,), dict(
  DESCRIPTOR = _HUMAN,
  __module__ = 'human_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Human)
  ))
_sym_db.RegisterMessage(Human)

Humans = _reflection.GeneratedProtocolMessageType('Humans', (_message.Message,), dict(
  DESCRIPTOR = _HUMANS,
  __module__ = 'human_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Humans)
  ))
_sym_db.RegisterMessage(Humans)


# @@protoc_insertion_point(module_scope)
