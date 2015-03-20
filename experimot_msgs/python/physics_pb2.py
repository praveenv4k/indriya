# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: physics.proto

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


DESCRIPTOR = _descriptor.FileDescriptor(
  name='physics.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\rphysics.proto\x12\x0e\x65xperimot.msgs\x1a\x0evector3d.proto\"\xbc\x03\n\x07Physics\x12/\n\x04type\x18\x01 \x01(\x0e\x32\x1c.experimot.msgs.Physics.Type:\x03ODE\x12\x13\n\x0bsolver_type\x18\x02 \x01(\t\x12\x15\n\rmin_step_size\x18\x03 \x01(\x01\x12\x14\n\x0cprecon_iters\x18\x04 \x01(\x05\x12\r\n\x05iters\x18\x05 \x01(\x05\x12\x0b\n\x03sor\x18\x06 \x01(\x01\x12\x0b\n\x03\x63\x66m\x18\x07 \x01(\x01\x12\x0b\n\x03\x65rp\x18\x08 \x01(\x01\x12\"\n\x1a\x63ontact_max_correcting_vel\x18\t \x01(\x01\x12\x1d\n\x15\x63ontact_surface_layer\x18\n \x01(\x01\x12)\n\x07gravity\x18\x0b \x01(\x0b\x32\x18.experimot.msgs.Vector3d\x12\x16\n\x0e\x65nable_physics\x18\x0c \x01(\x08\x12\x18\n\x10real_time_factor\x18\r \x01(\x01\x12\x1d\n\x15real_time_update_rate\x18\x0e \x01(\x01\x12\x15\n\rmax_step_size\x18\x0f \x01(\x01\"2\n\x04Type\x12\x07\n\x03ODE\x10\x01\x12\n\n\x06\x42ULLET\x10\x02\x12\x0b\n\x07SIMBODY\x10\x03\x12\x08\n\x04\x44\x41RT\x10\x04')
  ,
  dependencies=[vector3d__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_PHYSICS_TYPE = _descriptor.EnumDescriptor(
  name='Type',
  full_name='experimot.msgs.Physics.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='ODE', index=0, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BULLET', index=1, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SIMBODY', index=2, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DART', index=3, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=444,
  serialized_end=494,
)
_sym_db.RegisterEnumDescriptor(_PHYSICS_TYPE)


_PHYSICS = _descriptor.Descriptor(
  name='Physics',
  full_name='experimot.msgs.Physics',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='experimot.msgs.Physics.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='solver_type', full_name='experimot.msgs.Physics.solver_type', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='min_step_size', full_name='experimot.msgs.Physics.min_step_size', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='precon_iters', full_name='experimot.msgs.Physics.precon_iters', index=3,
      number=4, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='iters', full_name='experimot.msgs.Physics.iters', index=4,
      number=5, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sor', full_name='experimot.msgs.Physics.sor', index=5,
      number=6, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='cfm', full_name='experimot.msgs.Physics.cfm', index=6,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='erp', full_name='experimot.msgs.Physics.erp', index=7,
      number=8, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='contact_max_correcting_vel', full_name='experimot.msgs.Physics.contact_max_correcting_vel', index=8,
      number=9, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='contact_surface_layer', full_name='experimot.msgs.Physics.contact_surface_layer', index=9,
      number=10, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='gravity', full_name='experimot.msgs.Physics.gravity', index=10,
      number=11, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='enable_physics', full_name='experimot.msgs.Physics.enable_physics', index=11,
      number=12, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='real_time_factor', full_name='experimot.msgs.Physics.real_time_factor', index=12,
      number=13, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='real_time_update_rate', full_name='experimot.msgs.Physics.real_time_update_rate', index=13,
      number=14, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='max_step_size', full_name='experimot.msgs.Physics.max_step_size', index=14,
      number=15, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PHYSICS_TYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=50,
  serialized_end=494,
)

_PHYSICS.fields_by_name['type'].enum_type = _PHYSICS_TYPE
_PHYSICS.fields_by_name['gravity'].message_type = vector3d__pb2._VECTOR3D
_PHYSICS_TYPE.containing_type = _PHYSICS
DESCRIPTOR.message_types_by_name['Physics'] = _PHYSICS

Physics = _reflection.GeneratedProtocolMessageType('Physics', (_message.Message,), dict(
  DESCRIPTOR = _PHYSICS,
  __module__ = 'physics_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Physics)
  ))
_sym_db.RegisterMessage(Physics)


# @@protoc_insertion_point(module_scope)
