using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Common.Logging;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace Experimot.Kinect.Perception
{
    internal static class GestureNames
    {
        public static readonly string None = "None";
        public static readonly string NotTracked = "NotTracked";
    }


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
                new BitmapImage(new Uri(@"Images\Handwave_None.png", UriKind.Relative)));
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

    public class CameraSpacePointToStringConverter : IValueConverter
    {
        private static readonly ILog Log = LogManager.GetLogger<CameraSpacePointToStringConverter>();

        public object Convert(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            string ret = string.Empty;
            try
            {
                var point = (CameraSpacePoint) value;
                ret = string.Format("X:{0}, Y:{1}, Z:{2}", point.X, point.Y, point.Z);
            }
            catch (Exception ex)
            {
                Log.Warn(ex.Message);
            }
            return ret;
        }

        public object ConvertBack(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            return null;
        }
    }

    public class Vector4ToStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            string ret = string.Empty;
            try
            {
                var point = (Vector4) value;
                ret = string.Format("W:{0}, X:{1}, Y:{2}, Z:{3}", point.W, point.X, point.Y, point.Z);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
            return ret;
        }

        public object ConvertBack(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}
