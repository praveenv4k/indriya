using System.IO;
using experimot.msgs;

namespace Experimot.Core.Util
{
    public static class IoUtils
    {
        public static KinectBodies ReadSkeletonBinFile(string filename)
        {
            var bodies = new KinectBodies();
            if (File.Exists(filename))
            {
                using (var memStream = new MemoryStream(File.ReadAllBytes(filename)))
                {
                    bodies = ProtoBuf.Serializer.Deserialize<KinectBodies>(memStream);
                }
            }
            return bodies;
        }

    }
}
