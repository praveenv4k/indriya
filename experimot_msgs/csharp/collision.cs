//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/collision.proto
// Note: requires additional types generated from: pose.proto
// Note: requires additional types generated from: geometry.proto
// Note: requires additional types generated from: surface.proto
// Note: requires additional types generated from: visual.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Collision")]
  public partial class Collision : global::ProtoBuf.IExtensible
  {
    public Collision() {}
    
    private uint _id;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"id", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
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
    private double _laser_retro = default(double);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"laser_retro", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(double))]
    public double laser_retro
    {
      get { return _laser_retro; }
      set { _laser_retro = value; }
    }
    private double _max_contacts = default(double);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"max_contacts", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(double))]
    public double max_contacts
    {
      get { return _max_contacts; }
      set { _max_contacts = value; }
    }
    private experimot.msgs.Pose _pose = null;
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"pose", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Pose pose
    {
      get { return _pose; }
      set { _pose = value; }
    }
    private experimot.msgs.Geometry _geometry = null;
    [global::ProtoBuf.ProtoMember(6, IsRequired = false, Name=@"geometry", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Geometry geometry
    {
      get { return _geometry; }
      set { _geometry = value; }
    }
    private experimot.msgs.Surface _surface = null;
    [global::ProtoBuf.ProtoMember(7, IsRequired = false, Name=@"surface", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Surface surface
    {
      get { return _surface; }
      set { _surface = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Visual> _visual = new global::System.Collections.Generic.List<experimot.msgs.Visual>();
    [global::ProtoBuf.ProtoMember(8, Name=@"visual", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Visual> visual
    {
      get { return _visual; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}