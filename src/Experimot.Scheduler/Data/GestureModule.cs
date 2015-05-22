using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Data
{
    [ExpandableObject]
    public class GestureModule : INotifyPropertyChanged
    {
        private string _name;
        public event PropertyChangedEventHandler PropertyChanged;

        [Annotations.NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
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

        [ExpandableObject]
        public ObservableCollection<Gesture> Gestures
        {
            get { return _gestures; }
        }

        private readonly ObservableCollection<Gesture> _gestures;

        public GestureModule(GestureRecognitionModule module)
        {
            _gestures = new ObservableCollection<Gesture>();
            if (module != null)
            {
                Name = module.name;
                foreach (var gestureDescription in module.motions)
                {
                    _gestures.Add(new Gesture(
                        gestureDescription.name,
                        (GestureMode) gestureDescription.type
                        ));
                }
            }
        }
    }
}