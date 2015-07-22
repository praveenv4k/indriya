using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Kinect.VisualGestureBuilder;

namespace Experimot.Kinect.Perception
{
    public class GestureDatabase
    {
        private readonly List<Gesture> _gestures;
        private readonly Dictionary<string, ImageSource> _gestureImageDict;

        public GestureDatabase(IList<string> dbList)
        {
            _gestures = new List<Gesture>();
            _gestureImageDict = new Dictionary<string, ImageSource>();
            foreach (var db in dbList)
            {
                using (var database = new VisualGestureBuilderDatabase(db))
                {
                    foreach (var gesture in database.AvailableGestures)
                    {
                        _gestures.Add(gesture);
                        string uri = string.Concat("Images\\", gesture.Name, ".png");
                        if (CanLoadResource(new Uri(uri, UriKind.Relative)))
                        {
                            _gestureImageDict.Add(gesture.Name, new BitmapImage(new Uri(uri, UriKind.Relative)));
                        }
                    }
                }
            }
            _gestureImageDict.Add(Perception.GestureNames.None,
                new BitmapImage(new Uri(@"Images\None.png", UriKind.Relative)));
            _gestureImageDict.Add(Perception.GestureNames.NotTracked,
                new BitmapImage(new Uri(@"Images\NotTracked.png", UriKind.Relative)));
        }

        public List<Gesture> Gestures
        {
            get { return _gestures; }
        }

        public List<string> GestureNames
        {
            get { return _gestures.Select(s => s.Name).ToList(); }
        }

        public Dictionary<string, ImageSource> GestureImageSource
        {
            get { return _gestureImageDict; }
        }

        public static bool CanLoadResource(Uri uri)
        {
            try
            {
                Application.GetResourceStream(uri);
                return true;
            }
            catch (IOException)
            {
                return false;
            }
        }
    }
}