namespace Indriya.Application.Data
{
    /// <summary>
    /// Message extension class
    /// </summary>
    public static class ExperimotMsgsExtenstions
    {
        /// <summary>
        /// To convert a Vector3d object to string
        /// </summary>
        /// <param name="vec">Vector3d object</param>
        /// <returns>string (x,y,z) representation of vector3d</returns>
        public static string ToString(this Indriya.Core.Msgs.Vector3d vec)
        {
            return string.Format("x: {0}, y: {1}, z: {2}", vec.x, vec.y, vec.z);
        }

        /// <summary>
        /// To convert a Quaternion object to string
        /// </summary>
        /// <param name="quat">Quaternion object</param>
        /// <returns>string (w,x,y,z) representation of Quaternion</returns>
        public static string ToString(this Indriya.Core.Msgs.Quaternion quat)
        {
            return string.Format("w: {3}, x: {0}, y: {1}, z: {2}", quat.x, quat.y, quat.z, quat.w);
        }
    }
}
