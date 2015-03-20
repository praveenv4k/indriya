# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: contacts.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import contact_pb2 as contact__pb2
import time_pb2 as time__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='contacts.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x0e\x63ontacts.proto\x12\x0e\x65xperimot.msgs\x1a\rcontact.proto\x1a\ntime.proto\"X\n\x08\x43ontacts\x12(\n\x07\x63ontact\x18\x01 \x03(\x0b\x32\x17.experimot.msgs.Contact\x12\"\n\x04time\x18\x02 \x02(\x0b\x32\x14.experimot.msgs.Time')
  ,
  dependencies=[contact__pb2.DESCRIPTOR,time__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CONTACTS = _descriptor.Descriptor(
  name='Contacts',
  full_name='experimot.msgs.Contacts',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='contact', full_name='experimot.msgs.Contacts.contact', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time', full_name='experimot.msgs.Contacts.time', index=1,
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
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=61,
  serialized_end=149,
)

_CONTACTS.fields_by_name['contact'].message_type = contact__pb2._CONTACT
_CONTACTS.fields_by_name['time'].message_type = time__pb2._TIME
DESCRIPTOR.message_types_by_name['Contacts'] = _CONTACTS

Contacts = _reflection.GeneratedProtocolMessageType('Contacts', (_message.Message,), dict(
  DESCRIPTOR = _CONTACTS,
  __module__ = 'contacts_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.Contacts)
  ))
_sym_db.RegisterMessage(Contacts)


# @@protoc_insertion_point(module_scope)
