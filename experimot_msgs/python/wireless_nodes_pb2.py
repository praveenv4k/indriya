# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: wireless_nodes.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import wireless_node_pb2 as wireless__node__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='wireless_nodes.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x14wireless_nodes.proto\x12\x0e\x65xperimot.msgs\x1a\x13wireless_node.proto\";\n\rWirelessNodes\x12*\n\x04node\x18\x01 \x03(\x0b\x32\x1c.experimot.msgs.WirelessNode')
  ,
  dependencies=[wireless__node__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_WIRELESSNODES = _descriptor.Descriptor(
  name='WirelessNodes',
  full_name='experimot.msgs.WirelessNodes',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='node', full_name='experimot.msgs.WirelessNodes.node', index=0,
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
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=61,
  serialized_end=120,
)

_WIRELESSNODES.fields_by_name['node'].message_type = wireless__node__pb2._WIRELESSNODE
DESCRIPTOR.message_types_by_name['WirelessNodes'] = _WIRELESSNODES

WirelessNodes = _reflection.GeneratedProtocolMessageType('WirelessNodes', (_message.Message,), dict(
  DESCRIPTOR = _WIRELESSNODES,
  __module__ = 'wireless_nodes_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.WirelessNodes)
  ))
_sym_db.RegisterMessage(WirelessNodes)


# @@protoc_insertion_point(module_scope)
