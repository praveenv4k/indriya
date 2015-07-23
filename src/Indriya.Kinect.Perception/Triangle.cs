
using System.Windows.Media.Media3D;

namespace Indriya.Kinect.Perception
{
    internal class Triangle
    {
        private readonly Vector3D _torso;
        private readonly Vector3D _leftShoulder;
        private readonly Vector3D _rightShoulder;

        public Triangle(Vector3D torso, Vector3D leftShoulder, Vector3D rightShoulder)
        {
            _torso = torso;
            _leftShoulder = leftShoulder;
            _rightShoulder = rightShoulder;
        }

        public Vector3D Normal()
        {
            var dir = Vector3D.CrossProduct(_leftShoulder - _torso, _rightShoulder - _torso);
            dir.Normalize();
            return dir;
        }

    }
}
