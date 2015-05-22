using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Experimot.Core.Annotations;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Data
{
    public class Robot : INotifyPropertyChanged
    {
        private string _name;
        private string _version;
        private string _description;
        private string _filePath;
        private Localization _localization;
        private SensorData _sensorData;
        private readonly ObservableCollection<Behavior> _behaviors;

        public Robot()
        {
            _sensorData = new SensorData();
            _localization = new Localization();

            _behaviors = new ObservableCollection<Behavior>();
            _behaviors.Add(new Behavior()
            {
                Mode = BehaviorMode.Blocking,
                Name = "Wave",
                State = BehaviorState.Idle
            });

        }

        public string Name
        {
            get { return _name; }
            set
            {
                if (value == _name) return;
                _name = value;
                OnPropertyChanged();
            }
        }

        public string Version
        {
            get { return _version; }
            set
            {
                if (value == _version) return;
                _version = value;
                OnPropertyChanged();
            }
        }

        public string Description
        {
            get { return _description; }
            set
            {
                if (value == _description) return;
                _description = value;
                OnPropertyChanged();
            }
        }

        public string FilePath
        {
            get { return _filePath; }
            set
            {
                if (value == _filePath) return;
                _filePath = value;
                OnPropertyChanged();
            }
        }

        public SensorData SensorData
        {
            get { return _sensorData; }
            set
            {
                if (Equals(value, _sensorData)) return;
                _sensorData = value;
                OnPropertyChanged();
            }
        }

        [ExpandableObject]
        public Localization Localization
        {
            get { return _localization; }
            set
            {
                if (Equals(value, _localization)) return;
                _localization = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public ObservableCollection<Behavior> Behaviors
        {
            get { return _behaviors; }
        }


    }
}