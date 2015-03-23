//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/link.proto
// Note: requires additional types generated from: inertial.proto
// Note: requires additional types generated from: collision.proto
// Note: requires additional types generated from: visual.proto
// Note: requires additional types generated from: sensor.proto
// Note: requires additional types generated from: projector.proto
// Note: requires additional types generated from: pose.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Link")]
  public partial class Link : global::ProtoBuf.IExtensible
  {
    public Link() {}
    
    private uint _id = default(uint);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"id", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint id
    {
      get { return _id; }
      set { _id = value; }
    }
    private string _name;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"name", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    private bool _self_collide = default(bool);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"self_collide", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool self_collide
    {
      get { return _self_collide; }
      set { _self_collide = value; }
    }
    private bool _gravity = default(bool);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"gravity", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool gravity
    {
      get { return _gravity; }
      set { _gravity = value; }
    }
    private bool _kinematic = default(bool);
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"kinematic", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool kinematic
    {
      get { return _kinematic; }
      set { _kinematic = value; }
    }
    private bool _enabled = default(bool);
    [global::ProtoBuf.ProtoMember(6, IsRequired = false, Name=@"enabled", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool enabled
    {
      get { return _enabled; }
      set { _enabled = value; }
    }
    private experimot.msgs.Inertial _inertial = null;
    [global::ProtoBuf.ProtoMember(7, IsRequired = false, Name=@"inertial", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Inertial inertial
    {
      get { return _inertial; }
      set { _inertial = value; }
    }
    private experimot.msgs.Pose _pose = null;
    [global::ProtoBuf.ProtoMember(8, IsRequired = false, Name=@"pose", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Pose pose
    {
      get { return _pose; }
      set { _pose = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Visual> _visual = new global::System.Collections.Generic.List<experimot.msgs.Visual>();
    [global::ProtoBuf.ProtoMember(9, Name=@"visual", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Visual> visual
    {
      get { return _visual; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Collision> _collision = new global::System.Collections.Generic.List<experimot.msgs.Collision>();
    [global::ProtoBuf.ProtoMember(10, Name=@"collision", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Collision> collision
    {
      get { return _collision; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Sensor> _sensor = new global::System.Collections.Generic.List<experimot.msgs.Sensor>();
    [global::ProtoBuf.ProtoMember(11, Name=@"sensor", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Sensor> sensor
    {
      get { return _sensor; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Projector> _projector = new global::System.Collections.Generic.List<experimot.msgs.Projector>();
    [global::ProtoBuf.ProtoMember(12, Name=@"projector", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Projector> projector
    {
      get { return _projector; }
    }
  
    private bool _canonical = default(bool);
    [global::ProtoBuf.ProtoMember(13, IsRequired = false, Name=@"canonical", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool canonical
    {
      get { return _canonical; }
      set { _canonical = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}