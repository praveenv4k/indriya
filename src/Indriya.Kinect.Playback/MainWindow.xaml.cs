// Author: Praveenkumar Vasudevan
// Description: To playback the Kinect Streams (XEF File) recorded using Kinect Studio

using System;
using System.ComponentModel;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;
using Microsoft.Kinect.Tools;
using Microsoft.Win32;

namespace Indriya.Kinect.Playback
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    // ReSharper disable once RedundantExtendsListEntry
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private readonly byte[] _depthPixels;
        private readonly WriteableBitmap _depthBitmap;
        private readonly WriteableBitmap _bodyIndexBitmap;
        private readonly WriteableBitmap _irBitmap;
        private readonly WriteableBitmap _colorBitmap;

        private readonly uint[] _bodyIndexPixels;
        //private readonly uint[] _irIndexPixels;

        private const int MapDepthToByte = 8000/256;
        private const int DepthWidth = 512;
        private const int DepthHeight = 424;
        private const int DepthMinReliableDistance = 500;
        private const int DepthBytesPerPixel = 2;
        private const int MaxDepth = 65535;

        private const int ColorWidth = 1920;
        private const int ColorHeight = 1080;
        // ReSharper disable once UnusedMember.Local
        private const int ColorBytesPerPixel = 2;

        private readonly byte[] _colorPixels;

        private string _fileName;
        private const float InfraredSourceValueMaximum = ushort.MaxValue;
        private const float InfraredSourceScale = 0.75f;
        private const float InfraredOutputValueMinimum = 0.01f;
        private const float InfraredOutputValueMaximum = 1.0f;

        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BodyBytesPerPixel = 4;

        private const int IrBytesPerPixel = 2;

        private readonly BackgroundWorker _worker;

        /// <summary>
        /// Collection of colors to be used to display the BodyIndexFrame data.
        /// </summary>
        private static readonly uint[] BodyColor =
        {
            0x0000FF00,
            0x00FF0000,
            0xFFFF4000,
            0x40FFFF00,
            0xFF40FF00,
            0xFF808000
        };

        public MainWindow()
        {
            _depthPixels = new byte[DepthWidth*DepthHeight];
            _depthBitmap = new WriteableBitmap(DepthWidth, DepthHeight, 96.0, 96.0, PixelFormats.Gray8, null);

            _bodyIndexPixels = new uint[DepthWidth*DepthHeight];
            _bodyIndexBitmap = new WriteableBitmap(DepthWidth, DepthHeight, 96.0, 96.0, PixelFormats.Bgr32, null);

            //_drawingGroup = new DrawingGroup();
            //_skeletonSource = new DrawingImage(_drawingGroup);

            //_irIndexPixels = new uint[DepthWidth*DepthHeight];
            _irBitmap = new WriteableBitmap(DepthWidth, DepthHeight, 96.0, 96.0, PixelFormats.Gray32Float, null);

            _colorPixels = new byte[ColorWidth*ColorHeight*4];
            _colorBitmap = new WriteableBitmap(ColorWidth, ColorHeight, 96.0, 96.0, PixelFormats.Bgr32, null);

            DataContext = this;

            InitializeComponent();

            ButtonText = "Play";

            _worker = new BackgroundWorker();
            _worker.DoWork += WorkerDoWork;
            _worker.WorkerSupportsCancellation = true;
            _worker.WorkerReportsProgress = true;
            _worker.RunWorkerCompleted += WorkerOnRunWorkerCompleted;
            _worker.ProgressChanged += OnWorkerProgressChanged;
        }

        private void WorkerOnRunWorkerCompleted(object sender, RunWorkerCompletedEventArgs runWorkerCompletedEventArgs)
        {
            playButton.IsEnabled = true;
            openButton.IsEnabled = true;
        }

        private void OnWorkerProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            
        }

        private void WorkerDoWork(object sender, DoWorkEventArgs e)
        {
            var worker = sender as BackgroundWorker;
            EventPlaybackBackgroundWork(worker, e.Argument.ToString());
        }

        public ImageSource DepthImageSource
        {
            get { return _depthBitmap; }
        }

        public ImageSource BodyImageSource
        {
            get { return _bodyIndexBitmap; }
        }

        //public ImageSource SkeletonImageSource
        //{
        //    get { return _skeletonSource; }
        //}

        public ImageSource IrImageSource
        {
            get { return _irBitmap; }
        }

        public ImageSource ColorImageSource
        {
            get { return _colorBitmap; }
        }

        public static void RecordClip(string filePath, TimeSpan duration)
        {
            using (KStudioClient client = KStudio.CreateClient())
            {
                client.ConnectToService();

                KStudioEventStreamSelectorCollection streamCollection = new KStudioEventStreamSelectorCollection
                {
                    KStudioEventStreamDataTypeIds.Ir,
                    KStudioEventStreamDataTypeIds.Depth,
                    KStudioEventStreamDataTypeIds.Body,
                    KStudioEventStreamDataTypeIds.BodyIndex
                };

                using (KStudioRecording recording = client.CreateRecording(filePath, streamCollection))
                {
                    recording.StartTimed(duration);
                    while (recording.State == KStudioRecordingState.Recording)
                    {
                        Thread.Sleep(500);
                    }

                    if (recording.State == KStudioRecordingState.Error)
                    {
                        throw new InvalidOperationException("Error: Recording failed!");
                    }
                }

                client.DisconnectFromService();
            }
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            if (_worker != null)
            {
                _worker.CancelAsync();
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //InitKStudioClient();
        }


        public string TimeStamp
        {
            get { return _timeStamp; }

            set
            {
                if (_timeStamp != value)
                {
                    _timeStamp = value;

                    // notify any bound elements that the text has changed
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("TimeStamp"));
                    }
                }
            }
        }


        public string StatusText
        {
            get { return _statusText; }

            set
            {
                if (_statusText != value)
                {
                    _statusText = value;

                    // notify any bound elements that the text has changed
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("StatusText"));
                    }
                }
            }
        }

        public void EventPlaybackBackgroundWork(BackgroundWorker worker, string filePath)
        {
            using (var client = KStudio.CreateClient())
            {
                client.ConnectToService();

                using (var reader = client.CreateEventReader(filePath))
                {
                    var evt = reader.GetNextEvent();
                    while (evt != null)
                    {
                        if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Ir)
                        {
                            var evt1 = evt;
                            Application.Current.Dispatcher.Invoke(
                                DispatcherPriority.Background,
                                new Action(() =>
                                {
                                    uint size;
                                    IntPtr buffer;
                                    evt1.AccessUnderlyingEventDataBuffer(out size, out buffer);
                                    ProcessInfraredFrameData(buffer, size);
                                    TimeStamp = evt1.RelativeTime.ToString();
                                }));
                        }
                        if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Depth)
                        {
                            var evt1 = evt;
                            Application.Current.Dispatcher.Invoke(
                                DispatcherPriority.Background,
                                new Action(() =>
                                {
                                    uint size;
                                    IntPtr buffer;
                                    evt1.AccessUnderlyingEventDataBuffer(out size, out buffer);
                                    ProcessDepthFrameData(buffer, size, DepthMinReliableDistance, MaxDepth);
                                    RenderDepthPixels();
                                    TimeStamp = evt1.RelativeTime.ToString();
                                }));
                        }
                        if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.UncompressedColor)
                        {
                            var evt1 = evt;
                            Application.Current.Dispatcher.Invoke(
                                DispatcherPriority.Background,
                                new Action(() =>
                                {
                                    uint size;
                                    IntPtr buffer;
                                    evt1.AccessUnderlyingEventDataBuffer(out size, out buffer);
                                    ProcessColorFrameData(buffer, size);
                                    RenderColorPixels();
                                    TimeStamp = evt1.RelativeTime.ToString();
                                }));
                        }
                        if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.BodyIndex)
                        {
                            var evt1 = evt;
                            Application.Current.Dispatcher.Invoke(
                                DispatcherPriority.Background,
                                new Action(() =>
                                {
                                    uint size;
                                    IntPtr buffer;
                                    evt1.AccessUnderlyingEventDataBuffer(out size, out buffer);
                                    ProcessBodyIndexFrameData(buffer, size);
                                    RenderBodyIndexPixels();
                                    TimeStamp = evt1.RelativeTime.ToString();
                                }));
                        }
                        evt = reader.GetNextEvent();
                    }
                }

                client.DisconnectFromService();
            }
        }

        public struct Rgb
        {
            public int Red;
            public int Green;
            public int Blue;
        }

        public static Rgb YuvToRgb(double y, double u, double v)
        {
            Rgb rgb = new Rgb
            {
                Red = Convert.ToInt32((y + 1.139837398373983740*v)*255),
                Green = Convert.ToInt32((
                    y - 0.3946517043589703515*u - 0.5805986066674976801*v)*255),
                Blue = Convert.ToInt32((y + 2.032110091743119266*u)*255)
            };


            return rgb;
        }

        //private void RenderBodyPixels()
        //{
        //    _irBitmap.WritePixels(
        //        new Int32Rect(0, 0, _irBitmap.PixelWidth, _irBitmap.PixelHeight),
        //        _bodyIndexPixels,
        //        _bodyIndexBitmap.PixelWidth * 1,
        //        0);
        //}

        //private unsafe void ProcessBodyFrameData(IntPtr buffer, uint size)
        //{
        //    byte* frameData = (byte*)buffer;

        //    // convert body index to a visual representation
        //    for (int i = 0; i < (int)size; ++i)
        //    {
        //        // the BodyColor array has been sized to match
        //        // BodyFrameSource.BodyCount
        //        if (frameData[i] < BodyColor.Length)
        //        {
        //            // this pixel is part of a player,
        //            // display the appropriate color
        //            _irIndexPixels[i] = BodyColor[frameData[i]];
        //        }
        //        else
        //        {
        //            // this pixel is not part of a player
        //            // display black
        //            _irIndexPixels[i] = 0x00000000;
        //        }
        //    }
        //}

        /// <summary>
        /// Directly accesses the underlying image buffer of the BodyIndexFrame to 
        /// create a displayable bitmap.
        /// This function requires the /unsafe compiler option as we make use of direct
        /// access to the native memory pointed to by the bodyIndexFrameData pointer.
        /// </summary>
        /// <param name="bodyIndexFrameData">Pointer to the BodyIndexFrame image data</param>
        /// <param name="bodyIndexFrameDataSize">Size of the BodyIndexFrame image data</param>
        private unsafe void ProcessBodyIndexFrameData(IntPtr bodyIndexFrameData, uint bodyIndexFrameDataSize)
        {
            byte* frameData = (byte*) bodyIndexFrameData;

            // convert body index to a visual representation
            for (int i = 0; i < (int) bodyIndexFrameDataSize; ++i)
            {
                // the BodyColor array has been sized to match
                // BodyFrameSource.BodyCount
                if (frameData[i] < BodyColor.Length)
                {
                    // this pixel is part of a player,
                    // display the appropriate color
                    _bodyIndexPixels[i] = BodyColor[frameData[i]];
                }
                else
                {
                    // this pixel is not part of a player
                    // display black
                    _bodyIndexPixels[i] = 0x00000000;
                }
            }
        }

        /// <summary>
        /// Renders color pixels into the writeableBitmap.
        /// </summary>
        private void RenderBodyIndexPixels()
        {
            _bodyIndexBitmap.WritePixels(
                new Int32Rect(0, 0, _bodyIndexBitmap.PixelWidth, _bodyIndexBitmap.PixelHeight),
                _bodyIndexPixels,
                _bodyIndexBitmap.PixelWidth*BodyBytesPerPixel,
                0);
        }

        private unsafe void ProcessDepthFrameData(IntPtr depthFrameData, uint depthFrameDataSize, ushort minDepth,
            ushort maxDepth)
        {
            // depth frame data is a 16 bit value
            ushort* frameData = (ushort*) depthFrameData;

            // convert depth to a visual representation
            for (int i = 0; i < (int) (depthFrameDataSize/DepthBytesPerPixel); ++i)
            {
                // Get the depth for this pixel
                ushort depth = frameData[i];

                // To convert to a byte, we're mapping the depth value to the byte range.
                // Values outside the reliable depth range are mapped to 0 (black).
                _depthPixels[i] = (byte) (depth >= minDepth && depth <= maxDepth ? (depth/MapDepthToByte) : 0);
            }
        }




        /// <summary>
        /// Renders color pixels into the writeableBitmap.
        /// </summary>
        private void RenderDepthPixels()
        {
            _depthBitmap.WritePixels(
                new Int32Rect(0, 0, _depthBitmap.PixelWidth, _depthBitmap.PixelHeight),
                _depthPixels,
                _depthBitmap.PixelWidth,
                0);
        }

        private unsafe void ProcessInfraredFrameData(IntPtr infraredFrameData, uint infraredFrameDataSize)
        {
            // infrared frame data is a 16 bit value
            ushort* frameData = (ushort*) infraredFrameData;

            // lock the target bitmap
            _irBitmap.Lock();

            // get the pointer to the bitmap's back buffer
            float* backBuffer = (float*) _irBitmap.BackBuffer;

            // process the infrared data
            for (int i = 0; i < (int) (infraredFrameDataSize/IrBytesPerPixel); ++i)
            {
                // since we are displaying the image as a normalized grey scale image, we need to convert from
                // the ushort data (as provided by the InfraredFrame) to a value from [InfraredOutputValueMinimum, InfraredOutputValueMaximum]
                backBuffer[i] = Math.Min(InfraredOutputValueMaximum,
                    ((frameData[i]/InfraredSourceValueMaximum*InfraredSourceScale)*(1.0f - InfraredOutputValueMinimum)) +
                    InfraredOutputValueMinimum);
            }

            // mark the entire bitmap as needing to be drawn
            _irBitmap.AddDirtyRect(new Int32Rect(0, 0, _irBitmap.PixelWidth, _irBitmap.PixelHeight));

            // unlock the bitmap
            _irBitmap.Unlock();
        }



        private unsafe void ProcessColorFrameData(IntPtr colorFrameData, uint colorFrameDataSize)
        {
            byte* frameData = (byte*) colorFrameData;

            int j = 0;
            for (int i = 0; i < (int) colorFrameDataSize; i += 4)
            {
                // Extract yuv data
                byte y0 = frameData[i];
                byte u0 = frameData[i + 1];
                byte y1 = frameData[i + 2];
                byte v0 = frameData[i + 3];

                Rgb d1, d2;
                ConvertYuy2ToRgb(y0, u0, y1, v0, out d1, out d2);

                _colorPixels[j++] = (byte) d1.Red;
                _colorPixels[j++] = (byte) d1.Green;
                _colorPixels[j++] = (byte) d1.Blue;
                _colorPixels[j++] = 128;

                _colorPixels[j++] = (byte) d2.Red;
                _colorPixels[j++] = (byte) d2.Green;
                _colorPixels[j++] = (byte) d2.Blue;
                _colorPixels[j++] = 128;
            }
        }

        /// <summary>
        /// Convert the Yuy2 data to RGB data. The raw buffer stored by Kinect Studio is in the format of Yuy2. 
        /// </summary>
        /// <param name="y0"></param>
        /// <param name="u0"></param>
        /// <param name="y1"></param>
        /// <param name="v0"></param>
        /// <param name="rgb1"></param>
        /// <param name="rgb2"></param>
        private static void ConvertYuy2ToRgb(byte y0, byte u0, byte y1, byte v0, out Rgb rgb1, out Rgb rgb2)
        {
            rgb1 = new Rgb();
            rgb2 = new Rgb();

            int c = y0 - 16;
            int d = u0 - 128;
            int e = v0 - 128;

            rgb1.Red = ClipValue((298*c + 516*d + 128) >> 8); // blue
            rgb1.Green = ClipValue((298*c - 100*d - 208*e + 128) >> 8); // green
            rgb1.Blue = ClipValue((298*c + 409*e + 128) >> 8); // red
            c = y1 - 16;

            rgb2.Red = ClipValue((298*c + 516*d + 128) >> 8); // blue
            rgb2.Green = ClipValue((298*c - 100*d - 208*e + 128) >> 8); // green
            rgb2.Blue = ClipValue((298*c + 409*e + 128) >> 8); // red
        }


        public static int ClipValue(int n)
        {
            return Math.Max(byte.MinValue, Math.Min(n, byte.MaxValue));
        }

        private void RenderColorPixels()
        {

            _colorBitmap.WritePixels(
                new Int32Rect(0, 0, _colorBitmap.PixelWidth, _colorBitmap.PixelHeight),
                _colorPixels,
                _colorBitmap.PixelWidth*4,
                0);
        }



        public string ButtonText
        {
            get { return _buttonText; }

            set
            {
                if (_buttonText != value)
                {
                    _buttonText = value;

                    // notify any bound elements that the text has changed
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("ButtonText"));
                    }
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private string _timeStamp;
        private string _buttonText;
        //private readonly DrawingGroup _drawingGroup;
        //private readonly ImageSource _skeletonSource;
        private string _statusText;

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (_worker == null) return;
            playButton.IsEnabled = false;
            openButton.IsEnabled = false;
            _worker.RunWorkerAsync(_fileName);
        }

        private void openButton_Click(object sender, RoutedEventArgs e)
        {
            var fo = new OpenFileDialog();
            fo.Title = "Open Kinect Studio recorded XEF File";
            fo.Multiselect = false;
            fo.Filter = "Kinect Studio Clips (*.xef)|*.xef";
                //"Image files (*.bmp, *.jpg)|*.bmp;*.jpg|All files (*.*)|*.*"
            var ret = fo.ShowDialog(this);
            if (!ret.Value) return;
            FileName = fo.FileName;
            ButtonText = "Play";
            playButton.IsEnabled = true;
            openButton.IsEnabled = true;
        }

        public string FileName
        {
            get { return _fileName; }
            set
            {
                if (_fileName != value)
                {
                    _fileName = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("FileName"));
                    }
                }
            }
        }
    }
}
