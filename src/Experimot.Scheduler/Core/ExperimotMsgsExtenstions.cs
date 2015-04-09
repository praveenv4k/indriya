using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Experimot.Scheduler.Core
{
    public static class ExperimotMsgsExtenstions
    {
        public static string ToString(this experimot.msgs.Vector3d vec)
        {
            return string.Format("x: {0}, y: {1}, z: {2}", vec.x, vec.y, vec.z);
        }

        public static string ToString(this experimot.msgs.Quaternion quat)
        {
            return string.Format("w: {3}, x: {0}, y: {1}, z: {2}", quat.x, quat.y, quat.z, quat.w);
        }

        //public static string ToString(this experimot.msgs.Vector3d vec)
        //{
        //    return string.Format("x: {0}, y: {1}, z: {2}", vec.x, vec.y, vec.z);
        //}

        //public static string ToString(this experimot.msgs.Vector3d vec)
        //{
        //    return string.Format("x: {0}, y: {1}, z: {2}", vec.x, vec.y, vec.z);
        //}
    }
}
