//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/topic_info.proto
// Note: requires additional types generated from: publish.proto
// Note: requires additional types generated from: subscribe.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"TopicInfo")]
  public partial class TopicInfo : global::ProtoBuf.IExtensible
  {
    public TopicInfo() {}
    
    private string _msg_type;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"msg_type", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string msg_type
    {
      get { return _msg_type; }
      set { _msg_type = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.Publish> _publisher = new global::System.Collections.Generic.List<experimot.msgs.Publish>();
    [global::ProtoBuf.ProtoMember(2, Name=@"publisher", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Publish> publisher
    {
      get { return _publisher; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.Subscribe> _subscriber = new global::System.Collections.Generic.List<experimot.msgs.Subscribe>();
    [global::ProtoBuf.ProtoMember(3, Name=@"subscriber", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.Subscribe> subscriber
    {
      get { return _subscriber; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}