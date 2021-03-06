# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: sim_event.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import world_stats_pb2 as world__stats__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='sim_event.proto',
  package='Indriya.Core.Msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x0fsim_event.proto\x12\x11Indriya.Core.Msgs\x1a\x11world_stats.proto\"r\n\x08SimEvent\x12\x0c\n\x04type\x18\x01 \x02(\t\x12\x0c\n\x04name\x18\x02 \x02(\t\x12<\n\x10world_statistics\x18\x03 \x02(\x0b\x32\".Indriya.Core.Msgs.WorldStatistics\x12\x0c\n\x04\x64\x61ta\x18\x04 \x01(\t')
  ,
  dependencies=[world__stats__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_SIMEVENT = _descriptor.Descriptor(
  name='SimEvent',
  full_name='Indriya.Core.Msgs.SimEvent',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Indriya.Core.Msgs.SimEvent.type', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='Indriya.Core.Msgs.SimEvent.name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='world_statistics', full_name='Indriya.Core.Msgs.SimEvent.world_statistics', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data', full_name='Indriya.Core.Msgs.SimEvent.data', index=3,
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
  serialized_start=57,
  serialized_end=171,
)

_SIMEVENT.fields_by_name['world_statistics'].message_type = world__stats__pb2._WORLDSTATISTICS
DESCRIPTOR.message_types_by_name['SimEvent'] = _SIMEVENT

SimEvent = _reflection.GeneratedProtocolMessageType('SimEvent', (_message.Message,), dict(
  DESCRIPTOR = _SIMEVENT,
  __module__ = 'sim_event_pb2'
  # @@protoc_insertion_point(class_scope:Indriya.Core.Msgs.SimEvent)
  ))
_sym_db.RegisterMessage(SimEvent)


# @@protoc_insertion_point(module_scope)
