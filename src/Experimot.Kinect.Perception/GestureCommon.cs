using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace Experimot.Kinect.GestureRecognition
{
    static class GestureNames
    {
        public static readonly string None = "None";
        public static readonly string HandwaveRight = "Greet_Right";
        public static readonly string HandwaveLeft = "Greet_Left";
    }

    public class CameraSpacePointToStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            string ret = string.Empty;
            try
            {
                var point = (CameraSpacePoint)value;
                if (point != null)
                {
                    ret = string.Format("X:{0}, Y:{1}, Z:{2}", point.X, point.Y, point.Z);
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
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
                var point = (Vector4)value;
                if (point != null)
                {
                    ret = string.Format("W:{0}, X:{1}, Y:{2}, Z:{3}", point.W, point.X, point.Y, point.Z);
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
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
