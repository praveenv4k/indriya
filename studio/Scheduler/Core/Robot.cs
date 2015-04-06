using System.Collections.Generic;
using experimot.msgs;

namespace Scheduler.Core
{
    public class SensorData
    {
        private JointValueVector _jointValues;
        private IMU _imu;
        private readonly IDictionary<string, object> _sensorValues;

        public SensorData()
        {
            _jointValues = new JointValueVector();
            _imu = new IMU();
            _sensorValues = new Dictionary<string, object>();
        }

        public IDictionary<string, object> SensorValues
        {
            get { return _sensorValues; }
        }

        public IMU Imu
        {
            get { return _imu; }
            set { _imu = value; }
        }

        public JointValueVector JointValues
        {
            get { return _jointValues; }
            set { _jointValues = value; }
        }
    }

    public class Robot
    {
        private string _name;
        private string _version;
        private string _description;
        private string _filePath;
        private readonly Localization _localization;
        private readonly SensorData _sensorData;

        public Robot()
        {
            _sensorData = new SensorData();
            _localization = new Localization();
        }

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public string Version
        {
            get { return _version; }
            set { _version = value; }
        }

        public string Description
        {
            get { return _description; }
            set { _description = value; }
        }

        public string FilePath
        {
            get { return _filePath; }
            set { _filePath = value; }
        }

        public SensorData SensorData
        {
            get { return _sensorData; }
        }

        public Localization Localization
        {
            get { return _localization; }
        }
    }
}