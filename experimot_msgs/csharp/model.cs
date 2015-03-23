//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/model.proto
// Note: requires additional types generated from: joint.proto
// Note: requires additional types generated from: link.proto
// Note: requires additional types generated from: pose.proto
// Note: requires additional types generated from: visual.proto
// Note: requires additional types generated from: vector3d.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Model")]
  public partial class Model : global::ProtoBuf.IExtensible
  {
    public Model() {}
    
    private string _name;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"name", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    private uint _id = default(uint);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"id", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint id
    {
      get { return _id; }
      set { _id = value; }
    }
    private bool _is_static = default(bool);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"is_static", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool is_static
    {
      get { return _is_static; }
      set { _is_static = value; }
    }
    private experimot.msgs.Pose _pose = null;
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"pose", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Pose pose
    {
      get { return _pose; }
      set { _pose = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Joint> _joint = new global::System.Collections.Generic.List<experimot.msgs.Joint>();
    [global::ProtoBuf.ProtoMember(5, Name=@"joint", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Joint> joint
    {
      get { return _joint; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Link> _link = new global::System.Collections.Generic.List<experimot.msgs.Link>();
    [global::ProtoBuf.ProtoMember(6, Name=@"link", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Link> link
    {
      get { return _link; }
    }
  
    private bool _deleted = default(bool);
    [global::ProtoBuf.ProtoMember(7, IsRequired = false, Name=@"deleted", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool deleted
    {
      get { return _deleted; }
      set { _deleted = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Visual> _visual = new global::System.Collections.Generic.List<experimot.msgs.Visual>();
    [global::ProtoBuf.ProtoMember(8, Name=@"visual", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Visual> visual
    {
      get { return _visual; }
    }
  
    private experimot.msgs.Vector3d _scale = null;
    [global::ProtoBuf.ProtoMember(9, IsRequired = false, Name=@"scale", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Vector3d scale
    {
      get { return _scale; }
      set { _scale = value; }
    }
    private bool _self_collide = default(bool);
    [global::ProtoBuf.ProtoMember(10, IsRequired = false, Name=@"self_collide", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool self_collide
    {
      get { return _self_collide; }
      set { _self_collide = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}