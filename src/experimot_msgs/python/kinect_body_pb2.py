# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: kinect_body.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import vector2d_pb2 as vector2d__pb2
import kinect_joint_pb2 as kinect__joint__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='kinect_body.proto',
  package='experimot.msgs',
  #syntax='proto2',
  serialized_pb=_b('\n\x11kinect_body.proto\x12\x0e\x65xperimot.msgs\x1a\x0evector2d.proto\x1a\x12kinect_joint.proto\"\xc8\x07\n\nKinectBody\x12\x12\n\nTrackingId\x18\x01 \x02(\x05\x12\x11\n\tIsTracked\x18\x02 \x02(\x08\x12\x12\n\nJointCount\x18\x03 \x02(\x05\x12+\n\x06Joints\x18\x04 \x03(\x0b\x32\x1b.experimot.msgs.KinectJoint\x12;\n\x0c\x43lippedEdges\x18\x05 \x01(\x0e\x32%.experimot.msgs.KinectBody.FrameEdges\x12I\n\x12HandLeftConfidence\x18\x06 \x01(\x0e\x32-.experimot.msgs.KinectBody.TrackingConfidence\x12;\n\rHandLeftState\x18\x07 \x01(\x0e\x32$.experimot.msgs.KinectBody.HandState\x12J\n\x13HandRightConfidence\x18\x08 \x01(\x0e\x32-.experimot.msgs.KinectBody.TrackingConfidence\x12<\n\x0eHandRightState\x18\t \x01(\x0e\x32$.experimot.msgs.KinectBody.HandState\x12\x14\n\x0cIsRestricted\x18\n \x01(\x08\x12&\n\x04Lean\x18\x0b \x01(\x0b\x32\x18.experimot.msgs.Vector2d\x12\x19\n\x11LeanTrackingState\x18\x0c \x01(\x05\"a\n\x08\x41\x63tivity\x12\x11\n\rEyeLeftClosed\x10\x00\x12\x12\n\x0e\x45yeRightClosed\x10\x01\x12\r\n\tMouthOpen\x10\x02\x12\x0e\n\nMouthMoved\x10\x03\x12\x0f\n\x0bLookingAway\x10\x04\" \n\nAppearance\x12\x12\n\x0eWearingGlasses\x10\x00\":\n\x0f\x44\x65tectionResult\x12\x0b\n\x07Unknown\x10\x00\x12\x06\n\x02No\x10\x01\x12\t\n\x05Maybe\x10\x02\x12\x07\n\x03Yes\x10\x03\"@\n\nFrameEdges\x12\x08\n\x04None\x10\x00\x12\t\n\x05Right\x10\x01\x12\x08\n\x04Left\x10\x02\x12\x07\n\x03Top\x10\x04\x12\n\n\x06\x42ottom\x10\x08\"$\n\nExpression\x12\x0b\n\x07Neutral\x10\x00\x12\t\n\x05Happy\x10\x01\"\'\n\x12TrackingConfidence\x12\x07\n\x03Low\x10\x00\x12\x08\n\x04High\x10\x01\"X\n\tHandState\x12\x0e\n\nHS_Unknown\x10\x00\x12\x11\n\rHS_NotTracked\x10\x01\x12\x0b\n\x07HS_Open\x10\x02\x12\r\n\tHS_Closed\x10\x03\x12\x0c\n\x08HS_Lasso\x10\x04\"8\n\x0cKinectBodies\x12(\n\x04\x42ody\x18\x01 \x03(\x0b\x32\x1a.experimot.msgs.KinectBody')
  ,
  dependencies=[vector2d__pb2.DESCRIPTOR,kinect__joint__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_KINECTBODY_ACTIVITY = _descriptor.EnumDescriptor(
  name='Activity',
  full_name='experimot.msgs.KinectBody.Activity',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='EyeLeftClosed', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EyeRightClosed', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MouthOpen', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MouthMoved', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LookingAway', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=616,
  serialized_end=713,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_ACTIVITY)

_KINECTBODY_APPEARANCE = _descriptor.EnumDescriptor(
  name='Appearance',
  full_name='experimot.msgs.KinectBody.Appearance',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='WearingGlasses', index=0, number=0,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=715,
  serialized_end=747,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_APPEARANCE)

_KINECTBODY_DETECTIONRESULT = _descriptor.EnumDescriptor(
  name='DetectionResult',
  full_name='experimot.msgs.KinectBody.DetectionResult',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Unknown', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='No', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Maybe', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Yes', index=3, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=749,
  serialized_end=807,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_DETECTIONRESULT)

_KINECTBODY_FRAMEEDGES = _descriptor.EnumDescriptor(
  name='FrameEdges',
  full_name='experimot.msgs.KinectBody.FrameEdges',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='None', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Right', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Left', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Top', index=3, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Bottom', index=4, number=8,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=809,
  serialized_end=873,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_FRAMEEDGES)

_KINECTBODY_EXPRESSION = _descriptor.EnumDescriptor(
  name='Expression',
  full_name='experimot.msgs.KinectBody.Expression',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Neutral', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Happy', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=875,
  serialized_end=911,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_EXPRESSION)

_KINECTBODY_TRACKINGCONFIDENCE = _descriptor.EnumDescriptor(
  name='TrackingConfidence',
  full_name='experimot.msgs.KinectBody.TrackingConfidence',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Low', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='High', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=913,
  serialized_end=952,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_TRACKINGCONFIDENCE)

_KINECTBODY_HANDSTATE = _descriptor.EnumDescriptor(
  name='HandState',
  full_name='experimot.msgs.KinectBody.HandState',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='HS_Unknown', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HS_NotTracked', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HS_Open', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HS_Closed', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HS_Lasso', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=954,
  serialized_end=1042,
)
_sym_db.RegisterEnumDescriptor(_KINECTBODY_HANDSTATE)


_KINECTBODY = _descriptor.Descriptor(
  name='KinectBody',
  full_name='experimot.msgs.KinectBody',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='TrackingId', full_name='experimot.msgs.KinectBody.TrackingId', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='IsTracked', full_name='experimot.msgs.KinectBody.IsTracked', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='JointCount', full_name='experimot.msgs.KinectBody.JointCount', index=2,
      number=3, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Joints', full_name='experimot.msgs.KinectBody.Joints', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ClippedEdges', full_name='experimot.msgs.KinectBody.ClippedEdges', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HandLeftConfidence', full_name='experimot.msgs.KinectBody.HandLeftConfidence', index=5,
      number=6, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HandLeftState', full_name='experimot.msgs.KinectBody.HandLeftState', index=6,
      number=7, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HandRightConfidence', full_name='experimot.msgs.KinectBody.HandRightConfidence', index=7,
      number=8, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HandRightState', full_name='experimot.msgs.KinectBody.HandRightState', index=8,
      number=9, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='IsRestricted', full_name='experimot.msgs.KinectBody.IsRestricted', index=9,
      number=10, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Lean', full_name='experimot.msgs.KinectBody.Lean', index=10,
      number=11, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LeanTrackingState', full_name='experimot.msgs.KinectBody.LeanTrackingState', index=11,
      number=12, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _KINECTBODY_ACTIVITY,
    _KINECTBODY_APPEARANCE,
    _KINECTBODY_DETECTIONRESULT,
    _KINECTBODY_FRAMEEDGES,
    _KINECTBODY_EXPRESSION,
    _KINECTBODY_TRACKINGCONFIDENCE,
    _KINECTBODY_HANDSTATE,
  ],
  options=None,
  is_extendable=False,
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=74,
  serialized_end=1042,
)


_KINECTBODIES = _descriptor.Descriptor(
  name='KinectBodies',
  full_name='experimot.msgs.KinectBodies',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Body', full_name='experimot.msgs.KinectBodies.Body', index=0,
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
  #syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1044,
  serialized_end=1100,
)

_KINECTBODY.fields_by_name['Joints'].message_type = kinect__joint__pb2._KINECTJOINT
_KINECTBODY.fields_by_name['ClippedEdges'].enum_type = _KINECTBODY_FRAMEEDGES
_KINECTBODY.fields_by_name['HandLeftConfidence'].enum_type = _KINECTBODY_TRACKINGCONFIDENCE
_KINECTBODY.fields_by_name['HandLeftState'].enum_type = _KINECTBODY_HANDSTATE
_KINECTBODY.fields_by_name['HandRightConfidence'].enum_type = _KINECTBODY_TRACKINGCONFIDENCE
_KINECTBODY.fields_by_name['HandRightState'].enum_type = _KINECTBODY_HANDSTATE
_KINECTBODY.fields_by_name['Lean'].message_type = vector2d__pb2._VECTOR2D
_KINECTBODY_ACTIVITY.containing_type = _KINECTBODY
_KINECTBODY_APPEARANCE.containing_type = _KINECTBODY
_KINECTBODY_DETECTIONRESULT.containing_type = _KINECTBODY
_KINECTBODY_FRAMEEDGES.containing_type = _KINECTBODY
_KINECTBODY_EXPRESSION.containing_type = _KINECTBODY
_KINECTBODY_TRACKINGCONFIDENCE.containing_type = _KINECTBODY
_KINECTBODY_HANDSTATE.containing_type = _KINECTBODY
_KINECTBODIES.fields_by_name['Body'].message_type = _KINECTBODY
DESCRIPTOR.message_types_by_name['KinectBody'] = _KINECTBODY
DESCRIPTOR.message_types_by_name['KinectBodies'] = _KINECTBODIES

KinectBody = _reflection.GeneratedProtocolMessageType('KinectBody', (_message.Message,), dict(
  DESCRIPTOR = _KINECTBODY,
  __module__ = 'kinect_body_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.KinectBody)
  ))
_sym_db.RegisterMessage(KinectBody)

KinectBodies = _reflection.GeneratedProtocolMessageType('KinectBodies', (_message.Message,), dict(
  DESCRIPTOR = _KINECTBODIES,
  __module__ = 'kinect_body_pb2'
  # @@protoc_insertion_point(class_scope:experimot.msgs.KinectBodies)
  ))
_sym_db.RegisterMessage(KinectBodies)


# @@protoc_insertion_point(module_scope)
