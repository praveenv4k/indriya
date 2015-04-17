# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: joint_wrench_stamped.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import joint_wrench_pb2 as joint__wrench__pb2
import time_pb2 as time__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='joint_wrench_stamped.proto',
  package='experimot.msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x1ajoint_wrench_stamped.proto\x12\x0e\x65xperimot.msgs\x1a\x12joint_wrench.proto\x1a\ntime.proto\"^\n\x0b\x46orceTorque\x12+\n\x06wrench\x18\x01 \x03(\x0b\x32\x1b.experimot.msgs.JointWrench\x12\"\n\x04time\x18\x02 \x02(\x0b\x32\x14.experimot.msgs.Time')
  ,
  dependencies=[joint__wrench__pb2.DESCRIPTOR,time__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_FORCETORQUE = _descriptor.Descriptor(
  name='ForceTorque',
  full_name='experimot.msgs.ForceTorque',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='wrench', full_name='experimot.msgs.ForceTorque.wrench', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time', full_name='experimot.msgs.ForceTorque.time', index=1,
      number=2, type=11, cpp_type=10, label=2,
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
  serialized_start=78,
  serialized_end=172,
)

_FORCETORQUE.fields_by_name['wrench'].message_type = joint__wrench__pb2._JOINTWRENCH
_FORCETORQUE.fields_by_name['time'].message_type = time__pb2._TIME
DESCRIPTOR.message_types_by_name['ForceTorque'] = _FORCETORQUE

ForceTorque = _reflection.GeneratedProtocolMessageType('ForceTorque', (_message.Message,), dict(
  DESCRIPTOR = _FORCETORQUE,
  __module__ = 'joint_wrench_stamped_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.ForceTorque)
  ))
_sym_db.RegisterMessage(ForceTorque)


# @@protoc_insertion_point(module_scope)
