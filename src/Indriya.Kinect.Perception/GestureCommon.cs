using System;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Data;
using Common.Logging;
using Microsoft.Kinect;

namespace Experimot.Kinect.Perception
{
    internal static class GestureNames
    {
        public static readonly string None = "None";
        public static readonly string NotTracked = "NotTracked";
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
