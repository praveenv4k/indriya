# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: joint_animation.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import time_pb2 as time__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='joint_animation.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x15joint_animation.proto\x12\x0e\x65xperimot.msgs\x1a\ntime.proto\"\xa3\x01\n\x0eJointAnimation\x12\x12\n\nmodel_name\x18\x01 \x02(\t\x12\x33\n\x05joint\x18\x02 \x03(\x0b\x32$.experimot.msgs.JointAnimation.Joint\x12\"\n\x04time\x18\x03 \x03(\x0b\x32\x14.experimot.msgs.Time\x1a$\n\x05Joint\x12\x0c\n\x04name\x18\x01 \x03(\t\x12\r\n\x05\x61ngle\x18\x02 \x03(\x01')
  ,
  dependencies=[time__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_JOINTANIMATION_JOINT = _descriptor.Descriptor(
  name='Joint',
  full_name='experimot.msgs.JointAnimation.Joint',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='experimot.msgs.JointAnimation.Joint.name', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='angle', full_name='experimot.msgs.JointAnimation.Joint.angle', index=1,
      number=2, type=1, cpp_type=5, label=3,
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
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=181,
  serialized_end=217,
)

_JOINTANIMATION = _descriptor.Descriptor(
  name='JointAnimation',
  full_name='experimot.msgs.JointAnimation',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='model_name', full_name='experimot.msgs.JointAnimation.model_name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='joint', full_name='experimot.msgs.JointAnimation.joint', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time', full_name='experimot.msgs.JointAnimation.time', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_JOINTANIMATION_JOINT, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=54,
  serialized_end=217,
)

_JOINTANIMATION_JOINT.containing_type = _JOINTANIMATION
_JOINTANIMATION.fields_by_name['joint'].message_type = _JOINTANIMATION_JOINT
_JOINTANIMATION.fields_by_name['time'].message_type = time__pb2._TIME
DESCRIPTOR.message_types_by_name['JointAnimation'] = _JOINTANIMATION

JointAnimation = _reflection.GeneratedProtocolMessageType('JointAnimation', (_message.Message,), dict(

  Joint = _reflection.GeneratedProtocolMessageType('Joint', (_message.Message,), dict(
    DESCRIPTOR = _JOINTANIMATION_JOINT,
    __module__ = 'joint_animation_pb2'
    # @@protoc_insertion_point(class_scope:experimot.msgs.JointAnimation.Joint)
    ))
  ,
  DESCRIPTOR = _JOINTANIMATION,
  __module__ = 'joint_animation_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.JointAnimation)
  ))
_sym_db.RegisterMessage(JointAnimation)
_sym_db.RegisterMessage(JointAnimation.Joint)


# @@protoc_insertion_point(module_scope)
