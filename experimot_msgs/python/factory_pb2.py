# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: factory.proto

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
  name='factory.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\rfactory.proto\x12\x0e\x65xperimot.msgs\x1a\npose.proto\"}\n\x07\x46\x61\x63tory\x12\x0b\n\x03sdf\x18\x01 \x01(\t\x12\x14\n\x0csdf_filename\x18\x02 \x01(\t\x12\"\n\x04pose\x18\x03 \x01(\x0b\x32\x14.experimot.msgs.Pose\x12\x11\n\tedit_name\x18\x04 \x01(\t\x12\x18\n\x10\x63lone_model_name\x18\x05 \x01(\t')
  ,
  dependencies=[pose__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_FACTORY = _descriptor.Descriptor(
  name='Factory',
  full_name='experimot.msgs.Factory',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='sdf', full_name='experimot.msgs.Factory.sdf', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sdf_filename', full_name='experimot.msgs.Factory.sdf_filename', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pose', full_name='experimot.msgs.Factory.pose', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='edit_name', full_name='experimot.msgs.Factory.edit_name', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='clone_model_name', full_name='experimot.msgs.Factory.clone_model_name', index=4,
      number=5, type=9, cpp_type=9, label=1,
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
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=45,
  serialized_end=170,
)

_FACTORY.fields_by_name['pose'].message_type = pose__pb2._POSE
DESCRIPTOR.message_types_by_name['Factory'] = _FACTORY

Factory = _reflection.GeneratedProtocolMessageType('Factory', (_message.Message,), dict(
  DESCRIPTOR = _FACTORY,
  __module__ = 'factory_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Factory)
  ))
_sym_db.RegisterMessage(Factory)


# @@protoc_insertion_point(module_scope)
