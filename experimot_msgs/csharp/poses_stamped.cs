//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/poses_stamped.proto
// Note: requires additional types generated from: time.proto
// Note: requires additional types generated from: pose.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"PosesStamped")]
  public partial class PosesStamped : global::ProtoBuf.IExtensible
  {
    public PosesStamped() {}
    
    private experimot.msgs.Time _time;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"time", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public experimot.msgs.Time time
    {
      get { return _time; }
      set { _time = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Pose> _pose = new global::System.Collections.Generic.List<experimot.msgs.Pose>();
    [global::ProtoBuf.ProtoMember(2, Name=@"pose", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Pose> pose
    {
      get { return _pose; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}