//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/contact.proto
// Note: requires additional types generated from: vector3d.proto
// Note: requires additional types generated from: time.proto
// Note: requires additional types generated from: joint_wrench.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Contact")]
  public partial class Contact : global::ProtoBuf.IExtensible
  {
    public Contact() {}
    
    private string _collision1;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"collision1", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string collision1
    {
      get { return _collision1; }
      set { _collision1 = value; }
    }
    private string _collision2;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"collision2", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string collision2
    {
      get { return _collision2; }
      set { _collision2 = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Vector3d> _position = new global::System.Collections.Generic.List<experimot.msgs.Vector3d>();
    [global::ProtoBuf.ProtoMember(3, Name=@"position", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Vector3d> position
    {
      get { return _position; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Vector3d> _normal = new global::System.Collections.Generic.List<experimot.msgs.Vector3d>();
    [global::ProtoBuf.ProtoMember(4, Name=@"normal", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Vector3d> normal
    {
      get { return _normal; }
    }
  
    private readonly global::System.Collections.Generic.List<double> _depth = new global::System.Collections.Generic.List<double>();
    [global::ProtoBuf.ProtoMember(5, Name=@"depth", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public global::System.Collections.Generic.List<double> depth
    {
      get { return _depth; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.JointWrench> _wrench = new global::System.Collections.Generic.List<experimot.msgs.JointWrench>();
    [global::ProtoBuf.ProtoMember(6, Name=@"wrench", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.JointWrench> wrench
    {
      get { return _wrench; }
    }
  
    private experimot.msgs.Time _time;
    [global::ProtoBuf.ProtoMember(7, IsRequired = true, Name=@"time", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public experimot.msgs.Time time
    {
      get { return _time; }
      set { _time = value; }
    }
    private string _world;
    [global::ProtoBuf.ProtoMember(8, IsRequired = true, Name=@"world", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string world
    {
      get { return _world; }
      set { _world = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}