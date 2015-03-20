# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: images_stamped.proto

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
import image_pb2 as image__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='images_stamped.proto',
  package='experimot.msgs',
  syntax='proto2',
  serialized_pb=_b('\n\x14images_stamped.proto\x12\x0e\x65xperimot.msgs\x1a\ntime.proto\x1a\x0bimage.proto\"Y\n\rImagesStamped\x12\"\n\x04time\x18\x01 \x02(\x0b\x32\x14.experimot.msgs.Time\x12$\n\x05image\x18\x02 \x03(\x0b\x32\x15.experimot.msgs.Image')
  ,
  dependencies=[time__pb2.DESCRIPTOR,image__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_IMAGESSTAMPED = _descriptor.Descriptor(
  name='ImagesStamped',
  full_name='experimot.msgs.ImagesStamped',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='time', full_name='experimot.msgs.ImagesStamped.time', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='image', full_name='experimot.msgs.ImagesStamped.image', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=65,
  serialized_end=154,
)

_IMAGESSTAMPED.fields_by_name['time'].message_type = time__pb2._TIME
_IMAGESSTAMPED.fields_by_name['image'].message_type = image__pb2._IMAGE
DESCRIPTOR.message_types_by_name['ImagesStamped'] = _IMAGESSTAMPED

ImagesStamped = _reflection.GeneratedProtocolMessageType('ImagesStamped', (_message.Message,), dict(
  DESCRIPTOR = _IMAGESSTAMPED,
  __module__ = 'images_stamped_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.ImagesStamped)
  ))
_sym_db.RegisterMessage(ImagesStamped)


# @@protoc_insertion_point(module_scope)
