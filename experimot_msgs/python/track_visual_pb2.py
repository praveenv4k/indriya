# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: track_visual.proto

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
  name='track_visual.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x12track_visual.proto\x12\x0e\x65xperimot.msgs\"h\n\x0bTrackVisual\x12\x0c\n\x04name\x18\x01 \x02(\t\x12\n\n\x02id\x18\x02 \x01(\r\x12\x1b\n\x13inherit_orientation\x18\x03 \x01(\x08\x12\x10\n\x08min_dist\x18\x04 \x01(\x01\x12\x10\n\x08max_dist\x18\x05 \x01(\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_TRACKVISUAL = _descriptor.Descriptor(
  name='TrackVisual',
  full_name='experimot.msgs.TrackVisual',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='experimot.msgs.TrackVisual.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='experimot.msgs.TrackVisual.id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='inherit_orientation', full_name='experimot.msgs.TrackVisual.inherit_orientation', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='min_dist', full_name='experimot.msgs.TrackVisual.min_dist', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='max_dist', full_name='experimot.msgs.TrackVisual.max_dist', index=4,
      number=5, type=1, cpp_type=5, label=1,
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
  serialized_start=38,
  serialized_end=142,
)

DESCRIPTOR.message_types_by_name['TrackVisual'] = _TRACKVISUAL

TrackVisual = _reflection.GeneratedProtocolMessageType('TrackVisual', (_message.Message,), dict(
  DESCRIPTOR = _TRACKVISUAL,
  __module__ = 'track_visual_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.TrackVisual)
  ))
_sym_db.RegisterMessage(TrackVisual)


# @@protoc_insertion_point(module_scope)
