//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: proto/heightmapgeom.proto
// Note: requires additional types generated from: image.proto
// Note: requires additional types generated from: vector3d.proto
namespace experimot.msgs
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"HeightmapGeom")]
  public partial class HeightmapGeom : global::ProtoBuf.IExtensible
  {
    public HeightmapGeom() {}
    
    private experimot.msgs.Image _image = null;
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"image", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Image image
    {
      get { return _image; }
      set { _image = value; }
    }
    private experimot.msgs.Vector3d _size;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"size", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public experimot.msgs.Vector3d size
    {
      get { return _size; }
      set { _size = value; }
    }
    private experimot.msgs.Vector3d _origin = null;
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"origin", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public experimot.msgs.Vector3d origin
    {
      get { return _origin; }
      set { _origin = value; }
    }
    private readonly global::System.Collections.Generic.List<float> _heights = new global::System.Collections.Generic.List<float>();
    [global::ProtoBuf.ProtoMember(4, Name=@"heights", DataFormat = global::ProtoBuf.DataFormat.FixedSize)]
    public global::System.Collections.Generic.List<float> heights
    {
      get { return _heights; }
    }
  
    private int _width = default(int);
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"width", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int width
    {
      get { return _width; }
      set { _width = value; }
    }
    private int _height = default(int);
    [global::ProtoBuf.ProtoMember(6, IsRequired = false, Name=@"height", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int height
    {
      get { return _height; }
      set { _height = value; }
    }
    private readonly global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Texture> _texture = new global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Texture>();
    [global::ProtoBuf.ProtoMember(7, Name=@"texture", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Texture> texture
    {
      get { return _texture; }
    }
  
    private readonly global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Blend> _blend = new global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Blend>();
    [global::ProtoBuf.ProtoMember(8, Name=@"blend", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<experimot.msgs.HeightmapGeom.Blend> blend
    {
      get { return _blend; }
    }
  
    private bool _use_terrain_paging = default(bool);
    [global::ProtoBuf.ProtoMember(9, IsRequired = false, Name=@"use_terrain_paging", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool use_terrain_paging
    {
      get { return _use_terrain_paging; }
      set { _use_terrain_paging = value; }
    }
    private string _filename = "";
    [global::ProtoBuf.ProtoMember(10, IsRequired = false, Name=@"filename", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string filename
    {
      get { return _filename; }
      set { _filename = value; }
    }
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Texture")]
  public partial class Texture : global::ProtoBuf.IExtensible
  {
    public Texture() {}
    
    private string _diffuse;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"diffuse", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string diffuse
    {
      get { return _diffuse; }
      set { _diffuse = value; }
    }
    private string _normal;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"normal", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string normal
    {
      get { return _normal; }
      set { _normal = value; }
    }
    private double _size;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"size", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public double size
    {
      get { return _size; }
      set { _size = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Blend")]
  public partial class Blend : global::ProtoBuf.IExtensible
  {
    public Blend() {}
    
    private double _min_height;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"min_height", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public double min_height
    {
      get { return _min_height; }
      set { _min_height = value; }
    }
    private double _fade_dist;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"fade_dist", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public double fade_dist
    {
      get { return _fade_dist; }
      set { _fade_dist = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}