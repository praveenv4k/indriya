﻿// Author: Praveenkumar Vasudevan
// Description: To playback the Kinect Streams (XEF File) recorded using Kinect Studio
using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Kinect.Tools;
using System.ComponentModel;
using Microsoft.Win32;
using Microsoft.Kinect;

namespace KinectPlayback
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private byte[] depthPixels;
        private WriteableBitmap depthBitmap;
        private WriteableBitmap bodyIndexBitmap = null;
        private WriteableBitmap irBitmap;
        private WriteableBitmap colorBitmap = null;
        private DispatcherTimer _timer;
        private KStudioClient _client;
        private KStudioEventReader _reader;

        private uint[] bodyIndexPixels = null;
        private uint[] irIndexPixels = null;

        private const int MapDepthToByte = 8000 / 256;
        private const int depthWidth = 512;
        private const int depthHeight = 424;
        private const int DepthMinReliableDistance = 500;
        private const int DepthBytesPerPixel = 2;
        private const int maxDepth = 65535;

        private const int colorWidth = 1920;
        private const int colorHeight = 1080;
        private const int ColorBytesPerPixel = 2;
        private byte[] colorPixels = null;

        private string _fileName;
        private uint _loopCount = 1;
        private const float InfraredSourceValueMaximum = (float)ushort.MaxValue;
        private const float InfraredSourceScale = 0.75f;
        private const float InfraredOutputValueMinimum = 0.01f;
        private const float InfraredOutputValueMaximum = 1.0f;

        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BodyBytesPerPixel = 4;
        private const int IrBytesPerPixel = 2;

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
            0xFF808000,
        };

        public MainWindow()
        {
            this.depthPixels = new byte[depthWidth * depthHeight];
            this.depthBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Gray8, null);

            this.bodyIndexPixels = new uint[depthWidth * depthHeight];
            this.bodyIndexBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Bgr32, null);
    
            this.drawingGroup = new DrawingGroup();
            this.skeletonSource = new DrawingImage(this.drawingGroup);

            this.irIndexPixels = new uint[depthWidth * depthHeight];
            this.irBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Gray32Float, null);

            this.colorPixels = new byte[colorWidth * colorHeight * 4];
            this.colorBitmap = new WriteableBitmap(colorWidth, colorHeight, 96.0, 96.0, PixelFormats.Bgr32, null);

            this.DataContext = this;

            InitializeComponent();

            ButtonText = "Play";
        }

        public ImageSource DepthImageSource
        {
            get
            {
                return this.depthBitmap;
            }
        }

        public ImageSource BodyImageSource
        {
            get
            {
                return this.bodyIndexBitmap;
            }
        }

        public ImageSource SkeletonImageSource
        {
            get
            {
                return this.skeletonSource;
            }
        }

        public ImageSource IrImageSource
        {
            get
            {
                return this.irBitmap;
            }
        }

        public ImageSource ColorImageSource
        {
            get
            {
                return this.colorBitmap;
            }
        }

        public static void RecordClip(string filePath, TimeSpan duration)
        {
            using (KStudioClient client = KStudio.CreateClient())
            {
                client.ConnectToService();

                KStudioEventStreamSelectorCollection streamCollection = new KStudioEventStreamSelectorCollection();
                streamCollection.Add(KStudioEventStreamDataTypeIds.Ir);
                streamCollection.Add(KStudioEventStreamDataTypeIds.Depth);
                streamCollection.Add(KStudioEventStreamDataTypeIds.Body);
                streamCollection.Add(KStudioEventStreamDataTypeIds.BodyIndex);

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

        public void PlaybackEvent(string filePath, uint loopcount)
        {
            using (KStudioClient client = KStudio.CreateClient())
            {
                client.ConnectToService();
                client.EventDataAvailable += client_EventDataAvailable;

                //KStudioEventStreamSelectorCollection streamCollection = new KStudioEventStreamSelectorCollection();
                //streamCollection.Add(KStudioEventStreamDataTypeIds.Ir);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.Depth);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.Body);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.BodyIndex);

                using (var eventReader = client.CreateEventReader(filePath))
                //using (KStudioPlayback playback = client.CreatePlayback(filePath))
                {
                    eventReader.LoopCount = loopcount;
                    var startTime = eventReader.StartRelativeTime;

                    KStudioEvent evt = eventReader.GetNextEvent();
                    while (evt != null)
                    {
                        if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Depth)
                        {
                            System.Diagnostics.Debug.WriteLine(string.Format("Event data {1} size : {0}", evt.EventIndex, evt.RelativeTime));
                        }
                        evt = eventReader.GetNextEvent();
                    }
                }

                client.DisconnectFromService();
            }
        }

        public void PlaybackClip(string filePath, uint loopCount)
        {
            using (KStudioClient client = KStudio.CreateClient())
            {
                client.ConnectToService();
                client.EventDataAvailable +=client_EventDataAvailable;

                KStudioEventStreamSelectorCollection streamCollection = new KStudioEventStreamSelectorCollection();
                streamCollection.Add(KStudioEventStreamDataTypeIds.Ir);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.Depth);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.Body);
                //streamCollection.Add(KStudioEventStreamDataTypeIds.BodyIndex);

                using (KStudioPlayback playback = client.CreatePlayback(filePath,streamCollection))
                //using (KStudioPlayback playback = client.CreatePlayback(filePath))
                {
                    playback.LoopCount = loopCount;
                    playback.Mode = KStudioPlaybackMode.TimingEnabled;
                    
                    var depth = playback.Source.EventStreams.FirstOrDefault(s=>s.DataTypeName=="Nui Depth");

                    if (depth != null)
                    {
                        //playback.Source.GetEventStream(depth.DataTypeId);
                        //depth.
                    }

                    System.Timers.Timer t = new System.Timers.Timer();
                    t.Start();
                    
                    //playback.Flags = KStudioPlaybackFlags.
                    playback.Start();
                    System.Diagnostics.Debug.WriteLine(string.Format("Duration : {0}", playback.Duration));
                    foreach (var item in playback.Source.EventStreams)
                    {
                        System.Diagnostics.Debug.WriteLine(item.DataTypeName);
                        //playback.
                    }
                    
                    while (playback.State == KStudioPlaybackState.Playing)
                    {
                        //System.Diagnostics.Debug.WriteLine("Hello");
                        //foreach (var item in playback.Source.EventStreams)
                        //{
                        //    //System.Diagnostics.Debug.WriteLine(item.DataTypeName);
                        
                        //}
                        //Thread.Sleep(500);
                    }

                    t.Stop();
                    System.Diagnostics.Debug.WriteLine(string.Format("Elapsed Time: {0}", t.Interval)); 

                    if (playback.State == KStudioPlaybackState.Error)
                    {
                        throw new InvalidOperationException("Error: Playback failed!");
                    }
                }

                client.DisconnectFromService();
            }
        }

        void client_EventDataAvailable(object sender, KStudioEventDataEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine(string.Format("Event data {1} size : {0}", e.EventData.EventDataSize,e.EventData.ToString()));
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            DestroyKStudioClient();
        }

        private void DestroyKStudioClient()
        {
            if (_reader != null)
            {
                _reader.Dispose();
                _reader = null;
                if (_client != null)
                {
                    _client.DisconnectFromService();
                    _client.Dispose();
                    _client = null;
                }
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //InitKStudioClient();
        }

        private void ReInitialize()
        {
            DestroyKStudioClient();
            InitKStudioClient();
        }

        private void InitKStudioClient()
        {
            if (_client == null)
            {
                _client = KStudio.CreateClient();
                _client.ConnectToService();
                foreach (var item in _client.EventStreams)
                {
                    System.Diagnostics.Debug.WriteLine(item.Name);
                } 
                _reader = _client.CreateEventReader(_fileName);
                _streamCount = _client.EventStreams.Count;
                foreach (var item in _client.EventStreams)
                {
                    Console.WriteLine(item.DataTypeName);
                }
                //_reader.LoopCount = _loopCount;
                _timer = new DispatcherTimer();
                _timer.Interval = new TimeSpan(0, 0, 0, 0, (int)(1000 / (_streamCount)));
                _timer.Tick += _timer_Tick;
            }
        }

        public string TimeStamp
        {
            get
            {
                return this.timeStamp;
            }

            set
            {
                if (this.timeStamp != value)
                {
                    this.timeStamp = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("TimeStamp"));
                    }
                }
            }
        }


        public string StatusText
        {
            get
            {
                return this.statusText;
            }

            set
            {
                if (this.statusText != value)
                {
                    this.statusText = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("StatusText"));
                    }
                }
            }
        }

        void _timer_Tick(object sender, EventArgs e)
        {
            if (_reader != null)
            {
                string timeStamp = string.Empty;
                for (int i = 0; i < _streamCount; i++)
                {
                    using (KStudioEvent evt = _reader.GetNextEvent())
                    {
                        if (evt != null)
                        {
                            if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Depth)
                            {
                                //System.Diagnostics.Debug.WriteLine(string.Format("Event data {1} size : {0}", evt.EventIndex, evt.RelativeTime));

                                uint _size;
                                IntPtr _buffer;

                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);

                                ProcessDepthFrameData(_buffer, _size, DepthMinReliableDistance, maxDepth);

                                RenderDepthPixels();

                            }
                            if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.BodyIndex)
                            {
                                //System.Diagnostics.Debug.WriteLine("Body Frame");
                                uint _size;
                                IntPtr _buffer;

                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);

                                ProcessBodyIndexFrameData(_buffer, _size);

                                RenderBodyIndexPixels();
                            }
                            if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Body)
                            {
                                //var bodyFrame = (BodyFrame)
                                //System.Diagnostics.Debug.WriteLine(evt.GetType());

                                //TODO
                                uint _size;
                                IntPtr _buffer;
                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);

                                if (evt.EventIndex >= 500 && evt.EventIndex <= 502)
                                {
                                    Console.WriteLine(_size);
                                    byte[] temp = new byte[_size];
                                    evt.CopyEventDataToArray(temp, 0);
                                    System.IO.File.WriteAllBytes(string.Format("temp{0}.bin", evt.EventIndex), temp);
                                }
                                if (evt.EventIndex == 30 || evt.EventIndex == 170)
                                {
                                    Console.WriteLine(_size);
                                    byte[] temp = new byte[_size];
                                    evt.CopyEventDataToArray(temp, 0);
                                    System.IO.File.WriteAllBytes(string.Format("temp{0}.bin", evt.EventIndex), temp);
                                }

                                //ProcessBodyFrameData(_buffer, _size);
                                //RenderBodyPixels();
                                //StatusText = _size.ToString();
                            }
                            if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.Ir)
                            {
                                uint _size;
                                IntPtr _buffer;
                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);
                                ProcessInfraredFrameData(_buffer, _size);
                            }
                            if (evt.EventStreamDataTypeId == KStudioEventStreamDataTypeIds.UncompressedColor)
                            {
                                uint _size;
                                IntPtr _buffer;
                                
                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);

                                ProcessColorFrameData(_buffer, _size);
                                RenderColorPixels();
                            }
                            TimeStamp = evt.RelativeTime.ToString();
                        }
                        else
                        {
                            _timer.IsEnabled = false;
                            _timer.Tick -= _timer_Tick;
                            playButton.IsEnabled = false;
                            openButton.IsEnabled = true;
                            break;
                        }
                    }
                }
                TimeStamp = string.IsNullOrEmpty(timeStamp) ? TimeStamp : timeStamp;
            }
        }

        struct RGB
        {
            public int Red;
            public int Green;
            public int Blue;
        }

        static RGB YUVtoRGB(double y, double u, double v)
        {
            RGB rgb = new RGB();

            rgb.Red = Convert.ToInt32((y + 1.139837398373983740 * v) * 255);
            rgb.Green = Convert.ToInt32((
                y - 0.3946517043589703515 * u - 0.5805986066674976801 * v) * 255);
            rgb.Blue = Convert.ToInt32((y + 2.032110091743119266 * u) * 255);

            return rgb;
        }

        private void RenderBodyPixels()
        {
            this.irBitmap.WritePixels(
                new Int32Rect(0, 0, this.irBitmap.PixelWidth, this.irBitmap.PixelHeight),
                this.bodyIndexPixels,
                this.bodyIndexBitmap.PixelWidth * (int)1,
                0);
        }

        private unsafe void ProcessBodyFrameData(IntPtr buffer, uint size)
        {
            byte* frameData = (byte*)buffer;

            // convert body index to a visual representation
            for (int i = 0; i < (int)size; ++i)
            {
                // the BodyColor array has been sized to match
                // BodyFrameSource.BodyCount
                if (frameData[i] < BodyColor.Length)
                {
                    // this pixel is part of a player,
                    // display the appropriate color
                    this.irIndexPixels[i] = BodyColor[frameData[i]];
                }
                else
                {
                    // this pixel is not part of a player
                    // display black
                    this.irIndexPixels[i] = 0x00000000;
                }
            }
        }

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
            byte* frameData = (byte*)bodyIndexFrameData;

            // convert body index to a visual representation
            for (int i = 0; i < (int)bodyIndexFrameDataSize; ++i)
            {
                // the BodyColor array has been sized to match
                // BodyFrameSource.BodyCount
                if (frameData[i] < BodyColor.Length)
                {
                    // this pixel is part of a player,
                    // display the appropriate color
                    this.bodyIndexPixels[i] = BodyColor[frameData[i]];
                }
                else
                {
                    // this pixel is not part of a player
                    // display black
                    this.bodyIndexPixels[i] = 0x00000000;
                }
            }
        }

        /// <summary>
        /// Renders color pixels into the writeableBitmap.
        /// </summary>
        private void RenderBodyIndexPixels()
        {
            this.bodyIndexBitmap.WritePixels(
                new Int32Rect(0, 0, this.bodyIndexBitmap.PixelWidth, this.bodyIndexBitmap.PixelHeight),
                this.bodyIndexPixels,
                this.bodyIndexBitmap.PixelWidth * (int)BodyBytesPerPixel,
                0);
        }

        private unsafe void ProcessDepthFrameData(IntPtr depthFrameData, uint depthFrameDataSize, ushort minDepth, ushort maxDepth)
        {
            // depth frame data is a 16 bit value
            ushort* frameData = (ushort*)depthFrameData;

            // convert depth to a visual representation
            for (int i = 0; i < (int)(depthFrameDataSize / DepthBytesPerPixel); ++i)
            {
                // Get the depth for this pixel
                ushort depth = frameData[i];

                // To convert to a byte, we're mapping the depth value to the byte range.
                // Values outside the reliable depth range are mapped to 0 (black).
                this.depthPixels[i] = (byte)(depth >= minDepth && depth <= maxDepth ? (depth / MapDepthToByte) : 0);
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
        static void ConvertYuy2ToRgb(byte y0, byte u0, byte y1, byte v0, out RGB rgb1, out RGB rgb2)
        {
            rgb1 = new RGB();
            rgb2 = new RGB();

            int c = y0 - 16;
            int d = u0 - 128;
            int e = v0 - 128;

            rgb1.Red = ClipValue((298 * c + 516 * d + 128) >> 8); // blue
            rgb1.Green = ClipValue((298 * c - 100 * d - 208 * e + 128) >> 8); // green
            rgb1.Blue = ClipValue((298 * c + 409 * e + 128) >> 8); // red
            c = y1 - 16;

            rgb2.Red = ClipValue((298 * c + 516 * d + 128) >> 8); // blue
            rgb2.Green = ClipValue((298 * c - 100 * d - 208 * e + 128) >> 8); // green
            rgb2.Blue = ClipValue((298 * c + 409 * e + 128) >> 8); // red
        }


        public static int ClipValue(int n)
        {
            return Math.Max(byte.MinValue, Math.Min(n, byte.MaxValue));
        }


        /// <summary>
        /// Renders color pixels into the writeableBitmap.
        /// </summary>
        private void RenderDepthPixels()
        {
            this.depthBitmap.WritePixels(
                new Int32Rect(0, 0, this.depthBitmap.PixelWidth, this.depthBitmap.PixelHeight),
                this.depthPixels,
                this.depthBitmap.PixelWidth,
                0);
        }

        private unsafe void ProcessInfraredFrameData(IntPtr infraredFrameData, uint infraredFrameDataSize)
        {
            // infrared frame data is a 16 bit value
            ushort* frameData = (ushort*)infraredFrameData;

            // lock the target bitmap
            this.irBitmap.Lock();

            // get the pointer to the bitmap's back buffer
            float* backBuffer = (float*)this.irBitmap.BackBuffer;

            // process the infrared data
            for (int i = 0; i < (int)(infraredFrameDataSize / IrBytesPerPixel); ++i)
            {
                // since we are displaying the image as a normalized grey scale image, we need to convert from
                // the ushort data (as provided by the InfraredFrame) to a value from [InfraredOutputValueMinimum, InfraredOutputValueMaximum]
                backBuffer[i] = Math.Min(InfraredOutputValueMaximum, (((float)frameData[i] / InfraredSourceValueMaximum * InfraredSourceScale) * (1.0f - InfraredOutputValueMinimum)) + InfraredOutputValueMinimum);
            }

            // mark the entire bitmap as needing to be drawn
            this.irBitmap.AddDirtyRect(new Int32Rect(0, 0, this.irBitmap.PixelWidth, this.irBitmap.PixelHeight));

            // unlock the bitmap
            this.irBitmap.Unlock();
        }

        private unsafe void ProcessColorFrameData(IntPtr colorFrameData, uint colorFrameDataSize)
        {
            byte* frameData = (byte*)colorFrameData;

            int j = 0;
            for (int i = 0; i < (int)colorFrameDataSize; i += 4)
            {
                // Extract yuv data
                byte y0 = frameData[i];
                byte u0 = frameData[i + 1];
                byte y1 = frameData[i + 2];
                byte v0 = frameData[i + 3];

                RGB d1, d2;
                ConvertYuy2ToRgb(y0, u0, y1, v0, out d1, out d2);

                this.colorPixels[j++] = (byte)d1.Red;
                this.colorPixels[j++] = (byte)d1.Green;
                this.colorPixels[j++] = (byte)d1.Blue;
                this.colorPixels[j++] = (byte)128;

                this.colorPixels[j++] = (byte)d2.Red;
                this.colorPixels[j++] = (byte)d2.Green;
                this.colorPixels[j++] = (byte)d2.Blue;
                this.colorPixels[j++] = (byte)128;
            }
        }

        private void RenderColorPixels()
        {

            this.colorBitmap.WritePixels(
               new Int32Rect(0, 0, this.colorBitmap.PixelWidth, this.colorBitmap.PixelHeight),
               this.colorPixels,
               this.colorBitmap.PixelWidth*4,
               0);
        }

        

        public string ButtonText
        {
            get
            {
                return this.buttonText;
            }

            set
            {
                if (this.buttonText != value)
                {
                    this.buttonText = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("ButtonText"));
                    }
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private string timeStamp;
        private string buttonText;
        private int _streamCount;
        private DrawingGroup drawingGroup;
        private ImageSource skeletonSource;
        private string statusText;

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (_timer != null) {
                _timer.IsEnabled = !_timer.IsEnabled;
                ButtonText = _timer.IsEnabled ? "Pause" : "Play";
            }
        }

        private void openButton_Click(object sender, RoutedEventArgs e)
        {
            var fo = new OpenFileDialog();
            fo.Title = "Open Kinect Studio recorded XEF File";
            fo.Multiselect = false;
            fo.Filter = "Kinect Studio Clips (*.xef)|*.xef";//"Image files (*.bmp, *.jpg)|*.bmp;*.jpg|All files (*.*)|*.*"
            var ret = fo.ShowDialog(this);
            if (ret != null && ret.Value == true)
            {
                FileName = fo.FileName;
                ButtonText = "Play";
                playButton.IsEnabled = true;
                openButton.IsEnabled = false;
                ReInitialize();
            }
        }

        public string FileName 
        {
            get { return _fileName; }
            set
            {
                if (_fileName != value)
                {
                    _fileName = value;
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("FileName"));
                    }
                }
            } 
        }
    }
}