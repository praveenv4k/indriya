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

        /// <summary>
        /// Bitmap to display
        /// </summary>
        private WriteableBitmap bodyIndexBitmap = null;

        /// <summary>
        /// Intermediate storage for frame data converted to color
        /// </summary>
        private uint[] bodyIndexPixels = null;
        private uint[] irIndexPixels = null;
        private WriteableBitmap irBitmap;
        private const int MapDepthToByte = 8000 / 256;
        private const int depthWidth = 512;
        private const int depthHeight = 424;
        private const int DepthMinReliableDistance = 500;
        private const int BytesPerPixel = 2;
        private const int maxDepth = 65535;
        private DispatcherTimer _timer;
        private string _fileName;
        private uint _loopCount = 1;
        private KStudioClient _client;
        private KStudioEventReader _reader;

        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BodyBytesPerPixel = 4;

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
            // allocate space to put the pixels being received and converted
            this.depthPixels = new byte[depthWidth * depthHeight];

            // create the bitmap to display
            this.depthBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Gray8, null);

            // allocate space to put the pixels being converted
            this.bodyIndexPixels = new uint[depthWidth * depthHeight];

            // create the bitmap to display
            this.bodyIndexBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Bgr32, null);

            // Create the drawing group we'll use for drawing
            this.drawingGroup = new DrawingGroup();

            // Create an image source that we can use in our image control
            this.skeletonSource = new DrawingImage(this.drawingGroup);

            this.irIndexPixels = new uint[depthWidth * depthHeight];
            this.irBitmap = new WriteableBitmap(depthWidth, depthHeight, 96.0, 96.0, PixelFormats.Gray8, null);

            this.DataContext = this;

            InitializeComponent();

            ButtonText = "Play";
        }

        /// <summary>
        /// Gets the bitmap to display
        /// </summary>
        public ImageSource DepthImageSource
        {
            get
            {
                return this.depthBitmap;
            }
        }

        /// <summary>
        /// Gets the bitmap to display
        /// </summary>
        public ImageSource BodyImageSource
        {
            get
            {
                return this.bodyIndexBitmap;
            }
        }

        /// <summary>
        /// Gets the bitmap to display
        /// </summary>
        public ImageSource SkeletonImageSource
        {
            get
            {
                return this.skeletonSource;
            }
        }

        /// <summary>
        /// Gets the bitmap to display
        /// </summary>
        public ImageSource IrImageSource
        {
            get
            {
                return this.irBitmap;
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

                KStudioEventStreamSelectorCollection streamCollection = new KStudioEventStreamSelectorCollection();
                streamCollection.Add(KStudioEventStreamDataTypeIds.Ir);
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
                //_reader.LoopCount = _loopCount;
                _timer = new DispatcherTimer();
                _timer.Interval = new TimeSpan(0, 0, 0, 0, (int)(1000 / (5)));
                //_timer.Interval = new TimeSpan(30000);
                _timer.Tick += _timer_Tick;
                //_timer.IsEnabled = true;
            }
        }

        /// <summary>
        /// Gets or sets the current status text to display
        /// </summary>
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
                                uint _size;
                                IntPtr _buffer;
                                evt.AccessUnderlyingEventDataBuffer(out _size, out _buffer);
                                ProcessBodyFrameData(_buffer, _size);
                                RenderBodyPixels();
                                StatusText = _size.ToString();
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
            for (int i = 0; i < (int)(depthFrameDataSize / BytesPerPixel); ++i)
            {
                // Get the depth for this pixel
                ushort depth = frameData[i];

                // To convert to a byte, we're mapping the depth value to the byte range.
                // Values outside the reliable depth range are mapped to 0 (black).
                this.depthPixels[i] = (byte)(depth >= minDepth && depth <= maxDepth ? (depth / MapDepthToByte) : 0);
            }
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
