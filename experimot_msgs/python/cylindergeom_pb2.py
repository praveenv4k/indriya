# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cylindergeom.proto

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
  name='cylindergeom.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x12\x63ylindergeom.proto\x12\x0e\x65xperimot.msgs\".\n\x0c\x43ylinderGeom\x12\x0e\n\x06radius\x18\x01 \x02(\x01\x12\x0e\n\x06length\x18\x02 \x02(\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CYLINDERGEOM = _descriptor.Descriptor(
  name='CylinderGeom',
  full_name='experimot.msgs.CylinderGeom',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='radius', full_name='experimot.msgs.CylinderGeom.radius', index=0,
      number=1, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='length', full_name='experimot.msgs.CylinderGeom.length', index=1,
      number=2, type=1, cpp_type=5, label=2,
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
  serialized_end=84,
)

DESCRIPTOR.message_types_by_name['CylinderGeom'] = _CYLINDERGEOM

CylinderGeom = _reflection.GeneratedProtocolMessageType('CylinderGeom', (_message.Message,), dict(
  DESCRIPTOR = _CYLINDERGEOM,
  __module__ = 'cylindergeom_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.CylinderGeom)
  ))
_sym_db.RegisterMessage(CylinderGeom)


# @@protoc_insertion_point(module_scope)
