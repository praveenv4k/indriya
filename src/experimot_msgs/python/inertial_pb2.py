# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: inertial.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import pose_pb2 as pose__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='inertial.proto',
  package='experimot.msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x0einertial.proto\x12\x0e\x65xperimot.msgs\x1a\npose.proto\"\x8a\x01\n\x08Inertial\x12\x0c\n\x04mass\x18\x01 \x01(\x01\x12\"\n\x04pose\x18\x02 \x01(\x0b\x32\x14.experimot.msgs.Pose\x12\x0b\n\x03ixx\x18\x03 \x01(\x01\x12\x0b\n\x03ixy\x18\x04 \x01(\x01\x12\x0b\n\x03ixz\x18\x05 \x01(\x01\x12\x0b\n\x03iyy\x18\x06 \x01(\x01\x12\x0b\n\x03iyz\x18\x07 \x01(\x01\x12\x0b\n\x03izz\x18\x08 \x01(\x01')
  ,
  dependencies=[pose__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_INERTIAL = _descriptor.Descriptor(
  name='Inertial',
  full_name='experimot.msgs.Inertial',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='mass', full_name='experimot.msgs.Inertial.mass', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pose', full_name='experimot.msgs.Inertial.pose', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ixx', full_name='experimot.msgs.Inertial.ixx', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ixy', full_name='experimot.msgs.Inertial.ixy', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ixz', full_name='experimot.msgs.Inertial.ixz', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='iyy', full_name='experimot.msgs.Inertial.iyy', index=5,
      number=6, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='iyz', full_name='experimot.msgs.Inertial.iyz', index=6,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='izz', full_name='experimot.msgs.Inertial.izz', index=7,
      number=8, type=1, cpp_type=5, label=1,
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
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=47,
  serialized_end=185,
)

_INERTIAL.fields_by_name['pose'].message_type = pose__pb2._POSE
DESCRIPTOR.message_types_by_name['Inertial'] = _INERTIAL

Inertial = _reflection.GeneratedProtocolMessageType('Inertial', (_message.Message,), dict(
  DESCRIPTOR = _INERTIAL,
  __module__ = 'inertial_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Inertial)
  ))
_sym_db.RegisterMessage(Inertial)


# @@protoc_insertion_point(module_scope)
