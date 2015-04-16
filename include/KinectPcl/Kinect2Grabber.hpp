// Kinect2Grabber is pcl::Grabber to retrieve the point cloud data from Kinect v2 using Kinect for Windows SDK 2.x.
// This source code is licensed under the MIT license. Please see the License in License.txt.

#ifndef KINECT2_GRABBER
#define KINECT2_GRABBER

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <Kinect.h>

#include <opencv2\opencv.hpp>
#include <pcl/io/boost.h>
#include <pcl/io/grabber.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

typedef boost::shared_ptr<cv::Mat> CvMatPtr;

namespace pcl
{
	struct pcl::PointXYZ;
	struct pcl::PointXYZRGB;
	template <typename T> class pcl::PointCloud;

	template<class Interface>
	inline void SafeRelease2(Interface *& IRelease)
	{
		if (IRelease != NULL){
			IRelease->Release();
			IRelease = NULL;
		}
	}

	class Kinect2Grabber : public pcl::Grabber
	{
	public:
		Kinect2Grabber();
		virtual ~Kinect2Grabber() throw ();
		virtual void start();
		virtual void stop();
		virtual bool isRunning() const;
		virtual std::string getName() const;
		virtual float getFramesPerSecond() const;

		typedef void (signal_Kinect2_PointXYZ)(const boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZ>>&);
		typedef void (signal_Kinect2_PointXYZRGB)(const boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZRGB>>&);
		typedef void (signal_Kinect2_PointXYZRGB_CV)(const boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZRGB>>&, const CvMatPtr&);
		typedef void (signal_Kinect2_PointXYZRGB_CV2)(const boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZRGB>>&, const cv::Mat&);
	protected:
		boost::signals2::signal<signal_Kinect2_PointXYZ>* signal_PointXYZ;
		boost::signals2::signal<signal_Kinect2_PointXYZRGB>* signal_PointXYZRGB;
		boost::signals2::signal<signal_Kinect2_PointXYZRGB_CV>* signal_PointXYZRGB_CV;
		boost::signals2::signal<signal_Kinect2_PointXYZRGB_CV2>* signal_PointXYZRGB_CV2;

		pcl::PointCloud<pcl::PointXYZ>::Ptr convertDepthToPointXYZ(UINT16* depthBuffer);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr convertRGBDepthToPointXYZRGB(RGBQUAD* colorBuffer, UINT16* depthBuffer);
		CvMatPtr convertRGBBufferToCvMat(RGBQUAD* pBuffer);
		void convertRGBDepthToPointXYZRGB2(RGBQUAD* colorBuffer, UINT16* depthBuffer, pcl::PointCloud<pcl::PointXYZRGB>& cloud);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr convertRGBDepthToPointXYZRGB(bool dummy, RGBQUAD* colorBuffer, UINT16* depthBuffer);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr convertRGBDepthToPointXYZRGB(RGBQUAD* colorBuffer, CameraSpacePoint* cameraBuffer);

		boost::thread thread;
		mutable boost::mutex mutex;

		void threadFunction();

		bool quit;
		bool running;

		HRESULT result;
		IKinectSensor* sensor;
		ICoordinateMapper* mapper;
		IColorFrameSource* colorSource;
		IColorFrameReader* colorReader;
		IDepthFrameSource* depthSource;
		IDepthFrameReader* depthReader;

		int colorWidth;
		int colorHeight;
		std::vector<RGBQUAD> colorBuffer;

		int depthWidth;
		int depthHeight;
		std::vector<UINT16> depthBuffer;

		//DepthSpacePoint*        m_pDepthCoordinates;
		CameraSpacePoint* m_pCameraCoordinates;
		
	};

	pcl::Kinect2Grabber::Kinect2Grabber()
		: sensor(nullptr)
		, mapper(nullptr)
		, colorSource(nullptr)
		, colorReader(nullptr)
		, depthSource(nullptr)
		, depthReader(nullptr)
		, result(S_OK)
		, colorWidth(1920)
		, colorHeight(1080)
		, colorBuffer()
		, depthWidth(512)
		, depthHeight(424)
		, depthBuffer()
		, running(false)
		, quit(false)
		, signal_PointXYZ(nullptr)
		, signal_PointXYZRGB(nullptr)
		, m_pCameraCoordinates(NULL)
		//, m_pDepthCoordinates(NULL)
	{
		// Create Sensor Instance
		result = GetDefaultKinectSensor(&sensor);
		if (FAILED(result)){
			throw std::exception("Exception : GetDefaultKinectSensor()");
		}

		// Open Sensor
		result = sensor->Open();
		if (FAILED(result)){
			throw std::exception("Exception : IKinectSensor::Open()");
		}

		// Retrieved Coordinate Mapper
		result = sensor->get_CoordinateMapper(&mapper);
		if (FAILED(result)){
			throw std::exception("Exception : IKinectSensor::get_CoordinateMapper()");
		}

		// Retrieved Color Frame Source
		result = sensor->get_ColorFrameSource(&colorSource);
		if (FAILED(result)){
			throw std::exception("Exception : IKinectSensor::get_ColorFrameSource()");
		}

		// Retrieved Depth Frame Source
		result = sensor->get_DepthFrameSource(&depthSource);
		if (FAILED(result)){
			throw std::exception("Exception : IKinectSensor::get_DepthFrameSource()");
		}

		// Retrieved Color Frame Size
		IFrameDescription* colorDescription;
		result = colorSource->get_FrameDescription(&colorDescription);
		if (FAILED(result)){
			throw std::exception("Exception : IColorFrameSource::get_FrameDescription()");
		}

		result = colorDescription->get_Width(&colorWidth); // 1920
		if (FAILED(result)){
			throw std::exception("Exception : IFrameDescription::get_Width()");
		}

		result = colorDescription->get_Height(&colorHeight); // 1080
		if (FAILED(result)){
			throw std::exception("Exception : IFrameDescription::get_Height()");
		}

		SafeRelease2(colorDescription);

		// To Reserve Color Frame Buffer
		colorBuffer.resize(colorWidth * colorHeight);

		// Retrieved Depth Frame Size
		IFrameDescription* depthDescription;
		result = depthSource->get_FrameDescription(&depthDescription);
		if (FAILED(result)){
			throw std::exception("Exception : IDepthFrameSource::get_FrameDescription()");
		}

		result = depthDescription->get_Width(&depthWidth); // 512
		if (FAILED(result)){
			throw std::exception("Exception : IFrameDescription::get_Width()");
		}

		result = depthDescription->get_Height(&depthHeight); // 424
		if (FAILED(result)){
			throw std::exception("Exception : IFrameDescription::get_Height()");
		}

		SafeRelease2(depthDescription);

		// To Reserve Depth Frame Buffer
		depthBuffer.resize(depthWidth * depthHeight);

		// create heap storage for the coorinate mapping from color to depth
		//m_pDepthCoordinates = new DepthSpacePoint[colorWidth * colorHeight];
		m_pCameraCoordinates = new CameraSpacePoint[colorWidth * colorHeight];

		signal_PointXYZ = createSignal<signal_Kinect2_PointXYZ>();
		signal_PointXYZRGB = createSignal<signal_Kinect2_PointXYZRGB>();
		signal_PointXYZRGB_CV = createSignal<signal_Kinect2_PointXYZRGB_CV>();
		signal_PointXYZRGB_CV2 = createSignal<signal_Kinect2_PointXYZRGB_CV2>();
	}

	pcl::Kinect2Grabber::~Kinect2Grabber() throw()
	{
		stop();

		disconnect_all_slots<signal_Kinect2_PointXYZ>();
		disconnect_all_slots<signal_Kinect2_PointXYZRGB>();
		disconnect_all_slots<signal_Kinect2_PointXYZRGB_CV>();
		disconnect_all_slots<signal_Kinect2_PointXYZRGB_CV2>();
		/*if (m_pDepthCoordinates)
		{
			delete[] m_pDepthCoordinates;
			m_pDepthCoordinates = NULL;
		}*/
		if (m_pCameraCoordinates)
		{
			delete[] m_pCameraCoordinates;
			m_pCameraCoordinates = NULL;
		}
		// End Processing
		if (sensor){
			sensor->Close();
		}
		pcl::SafeRelease2(sensor);
		pcl::SafeRelease2(mapper);
		pcl::SafeRelease2(colorSource);
		pcl::SafeRelease2(colorReader);
		pcl::SafeRelease2(depthSource);
		pcl::SafeRelease2(depthReader);

		thread.join();
	}

	void pcl::Kinect2Grabber::start()
	{
		// Open Color Frame Reader
		result = colorSource->OpenReader(&colorReader);
		if (FAILED(result)){
			throw std::exception("Exception : IColorFrameSource::OpenReader()");
		}

		// Open Depth Frame Reader
		result = depthSource->OpenReader(&depthReader);
		if (FAILED(result)){
			throw std::exception("Exception : IDepthFrameSource::OpenReader()");
		}

		running = true;

		thread = boost::thread(&Kinect2Grabber::threadFunction, this);
	}

	void pcl::Kinect2Grabber::stop()
	{
		boost::unique_lock<boost::mutex> lock(mutex);

		quit = true;
		running = false;
		lock.unlock();
	}

	bool pcl::Kinect2Grabber::isRunning() const
	{
		boost::unique_lock<boost::mutex> lock(mutex);

		return running;

		lock.unlock();
	}

	std::string pcl::Kinect2Grabber::getName() const{
		return std::string("Kinect2Grabber");
	}

	float pcl::Kinect2Grabber::getFramesPerSecond() const {
		return 30.0f;
	}


	void pcl::Kinect2Grabber::threadFunction()
	{
		//pcl::visualization::CloudViewer viewer("Point Cloud Viewer");
		//cvNamedWindow("Image View", 1);
		while (!quit){
			boost::unique_lock<boost::mutex> lock(mutex);

			// Acquire Latest Color Frame
			IColorFrame* colorFrame = nullptr;
			result = colorReader->AcquireLatestFrame(&colorFrame);
			if (SUCCEEDED(result)){
				// Retrieved Color Data
				result = colorFrame->CopyConvertedFrameDataToArray(colorBuffer.size() * sizeof(RGBQUAD), reinterpret_cast<BYTE*>(&colorBuffer[0]), ColorImageFormat::ColorImageFormat_Bgra);
				if (FAILED(result)){
					throw std::exception("Exception : IColorFrame::CopyConvertedFrameDataToArray()");
				}
			}
			SafeRelease2(colorFrame);

			// Acquire Latest Depth Frame
			IDepthFrame* depthFrame = nullptr;
			result = depthReader->AcquireLatestFrame(&depthFrame);
			if (SUCCEEDED(result)){
				// Retrieved Depth Data
				result = depthFrame->CopyFrameDataToArray(depthBuffer.size(), &depthBuffer[0]);
				if (FAILED(result)){
					throw std::exception("Exception : IDepthFrame::CopyFrameDataToArray()");
				}
			}
			SafeRelease2(depthFrame);

			lock.unlock();

			if (signal_PointXYZ->num_slots() > 0) {
				signal_PointXYZ->operator()(convertDepthToPointXYZ(&depthBuffer[0]));
			}

			if (signal_PointXYZRGB->num_slots() > 0) {
				signal_PointXYZRGB->operator()(convertRGBDepthToPointXYZRGB(&colorBuffer[0], &depthBuffer[0]));
			}

			if (signal_PointXYZRGB_CV->num_slots() > 0) {
				CvMatPtr img = convertRGBBufferToCvMat(&colorBuffer[0]);
				signal_PointXYZRGB_CV->operator()(convertRGBDepthToPointXYZRGB(&colorBuffer[0], &depthBuffer[0]), img);
				//cv::imshow("Image View", *img);
				//cv::waitKey(1);
			}
			if (signal_PointXYZRGB_CV2->num_slots() > 0) {
				cv::Mat mat(colorHeight, colorWidth, CV_8UC4, &colorBuffer[0]);
#if 1

#if 0
				boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud = convertRGBDepthToPointXYZRGB(false,&colorBuffer[0], &depthBuffer[0]);
				signal_PointXYZRGB_CV2->operator()(cloud, mat);
#else
				if (mapper != NULL){
					HRESULT hr = mapper->MapColorFrameToCameraSpace(depthWidth*depthHeight, &depthBuffer[0], colorWidth*colorHeight, m_pCameraCoordinates);
					if (SUCCEEDED(hr)){
						std::cout << "Cloud generation ... " << endl;
						boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud = convertRGBDepthToPointXYZRGB(&colorBuffer[0], m_pCameraCoordinates);
						signal_PointXYZRGB_CV2->operator()(cloud, mat);
					}
				}
#endif

#else
				pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud = convertRGBDepthToPointXYZRGB(&colorBuffer[0], &depthBuffer[0]);
				viewer.showCloud(cloud);
#endif
				//cv::imshow("Image View", mat);
				//cv::waitKey(1);
			}
		}
	}

	CvMatPtr pcl::Kinect2Grabber::convertRGBBufferToCvMat(RGBQUAD* pBuffer){
		CvMatPtr cvImg;
		if (pBuffer)
		{
			return CvMatPtr(new cv::Mat(colorHeight, colorWidth, CV_8UC4, pBuffer));
			//bufMat.copyTo(*cvImg);
		}
		return cvImg;
	}

	pcl::PointCloud<pcl::PointXYZ>::Ptr pcl::Kinect2Grabber::convertDepthToPointXYZ(UINT16* depthBuffer)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());

		cloud->width = static_cast<uint32_t>(depthWidth);
		cloud->height = static_cast<uint32_t>(depthHeight);
		cloud->is_dense = false;

		for (int y = 0; y < depthHeight; y++){
			for (int x = 0; x < depthWidth; x++){
				pcl::PointXYZ point;

				DepthSpacePoint depthSpacePoint = { static_cast<float>(x), static_cast<float>(y) };
				UINT16 depth = depthBuffer[y * depthWidth + x];

				// Coordinate Mapping Depth to Camera Space, and Setting PointCloud XYZ
				CameraSpacePoint cameraSpacePoint = { 0.0f, 0.0f, 0.0f };
				mapper->MapDepthPointToCameraSpace(depthSpacePoint, depth, &cameraSpacePoint);
				point.x = cameraSpacePoint.X;
				point.y = cameraSpacePoint.Y;
				point.z = cameraSpacePoint.Z;

				cloud->push_back(point);
			}
		}

		return cloud;
	}

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl::Kinect2Grabber::convertRGBDepthToPointXYZRGB(RGBQUAD* colorBuffer, UINT16* depthBuffer)
	{
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
		bool ptexist = false;
		cloud->width = static_cast<uint32_t>(depthWidth);
		cloud->height = static_cast<uint32_t>(depthHeight);
		cloud->is_dense = false;

		for (int y = 0; y < depthHeight; y++){
			for (int x = 0; x < depthWidth; x++){
				pcl::PointXYZRGB point;

				DepthSpacePoint depthSpacePoint = { static_cast<float>(x), static_cast<float>(y) };
				UINT16 depth = depthBuffer[y * depthWidth + x];

				// Coordinate Mapping Depth to Color Space, and Setting PointCloud RGB
				ColorSpacePoint colorSpacePoint = { 0.0f, 0.0f };
				mapper->MapDepthPointToColorSpace(depthSpacePoint, depth, &colorSpacePoint);
				
				int colorX = static_cast<int>(std::floor(colorSpacePoint.X + 0.5f));
				int colorY = static_cast<int>(std::floor(colorSpacePoint.Y + 0.5f));
				if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
					RGBQUAD color = colorBuffer[colorY * colorWidth + colorX];
					point.b = color.rgbBlue;
					point.g = color.rgbGreen;
					point.r = color.rgbRed;
				}

				// Coordinate Mapping Depth to Camera Space, and Setting PointCloud XYZ
				CameraSpacePoint cameraSpacePoint = { 0.0f, 0.0f, 0.0f };
				mapper->MapDepthPointToCameraSpace(depthSpacePoint, depth, &cameraSpacePoint);
				if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
#if 0
					point.x = cameraSpacePoint.X;
					point.y = cameraSpacePoint.Y;
					point.z = cameraSpacePoint.Z;
#else // meter to mm
					point.x = cameraSpacePoint.X * 1000;
					point.y = cameraSpacePoint.Y * 1000;
					point.z = cameraSpacePoint.Z * 1000;
#endif
					if (!ptexist){
						ptexist = true;
						std::cout << point.x << ", " << point.y << ", " << point.z << std::endl;
					}
				}

				cloud->push_back(point);
			}
		}

		return cloud;
	}

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl::Kinect2Grabber::convertRGBDepthToPointXYZRGB(bool dummy, RGBQUAD* colorBuffer, UINT16* depthBuffer)
	{
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>(colorWidth, colorHeight));
		bool ptexist = false;
		//cloud->width = static_cast<uint32_t>(depthWidth);
		//cloud->height = static_cast<uint32_t>(depthHeight);
		cloud->is_dense = false;

		if (!dummy){
			for (int y = 0; y < depthHeight; y++){
				for (int x = 0; x < depthWidth; x++){
					pcl::PointXYZRGB point;

					DepthSpacePoint depthSpacePoint = { static_cast<float>(x), static_cast<float>(y) };
					UINT16 depth = depthBuffer[y * depthWidth + x];

					// Coordinate Mapping Depth to Color Space, and Setting PointCloud RGB
					ColorSpacePoint colorSpacePoint = { 0.0f, 0.0f };
					mapper->MapDepthPointToColorSpace(depthSpacePoint, depth, &colorSpacePoint);

					int colorX = static_cast<int>(std::floor(colorSpacePoint.X + 0.5f));
					int colorY = static_cast<int>(std::floor(colorSpacePoint.Y + 0.5f));
					if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
						RGBQUAD color = colorBuffer[colorY * colorWidth + colorX];
						point.b = color.rgbBlue;
						point.g = color.rgbGreen;
						point.r = color.rgbRed;
					}

					// Coordinate Mapping Depth to Camera Space, and Setting PointCloud XYZ
					CameraSpacePoint cameraSpacePoint = { 0.0f, 0.0f, 0.0f };
					mapper->MapDepthPointToCameraSpace(depthSpacePoint, depth, &cameraSpacePoint);
					if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
#if 0
						point.x = cameraSpacePoint.X;
						point.y = cameraSpacePoint.Y;
						point.z = cameraSpacePoint.Z;
#else // meter to mm
						point.x = cameraSpacePoint.X * 1000;
						point.y = cameraSpacePoint.Y * 1000;
						point.z = cameraSpacePoint.Z * 1000;
#endif
						if (!ptexist){
							ptexist = true;
							std::cout << point.x << ", " << point.y << ", " << point.z << std::endl;
						}
						//cloud->points[colorX * this->colorWidth + colorY] = point;
						cloud->points[colorY * this->colorWidth + colorX] = point;
					}
					//points.at(row * this->width + column)

					//cloud->push_back(point);
				}
			}
		}
		else{
			if (colorBuffer != NULL && depthBuffer != NULL){
				
			}
		}

		return cloud;
	}

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl::Kinect2Grabber::convertRGBDepthToPointXYZRGB(RGBQUAD* colorBuffer, CameraSpacePoint* cameraBuffer)
	{
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>(colorWidth, colorHeight));
		bool ptexist = false;
		cloud->is_dense = false;

		if (colorBuffer != NULL && cameraBuffer != NULL){

			for (int y = 0; y < colorHeight; y++){
				for (int x = 0; x < colorWidth; x++){
					pcl::PointXYZRGB point;

					RGBQUAD color = colorBuffer[y * colorWidth + x];
					point.b = color.rgbBlue;
					point.g = color.rgbGreen;
					point.r = color.rgbRed;

					CameraSpacePoint cameraSpacePoint = cameraBuffer[y * colorWidth + x];

					point.x = cameraSpacePoint.X * 1000;
					point.y = cameraSpacePoint.Y * 1000;
					point.z = cameraSpacePoint.Z * 1000;

					cloud->points[y * this->colorWidth + x] = point;
				}
			}
		}
		return cloud;
	}

	void pcl::Kinect2Grabber::convertRGBDepthToPointXYZRGB2(RGBQUAD* colorBuffer, UINT16* depthBuffer, pcl::PointCloud<pcl::PointXYZRGB>& cloud)
	{
		bool ptexist = false;
		cloud.width = static_cast<uint32_t>(depthWidth);
		cloud.height = static_cast<uint32_t>(depthHeight);
		cloud.is_dense = false;

		for (int y = 0; y < depthHeight; y++){
			for (int x = 0; x < depthWidth; x++){
				pcl::PointXYZRGB point;

				DepthSpacePoint depthSpacePoint = { static_cast<float>(x), static_cast<float>(y) };
				UINT16 depth = depthBuffer[y * depthWidth + x];

				// Coordinate Mapping Depth to Color Space, and Setting PointCloud RGB
				ColorSpacePoint colorSpacePoint = { 0.0f, 0.0f };
				mapper->MapDepthPointToColorSpace(depthSpacePoint, depth, &colorSpacePoint);
				int colorX = static_cast<int>(std::floor(colorSpacePoint.X + 0.5f));
				int colorY = static_cast<int>(std::floor(colorSpacePoint.Y + 0.5f));
				if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
					RGBQUAD color = colorBuffer[colorY * colorWidth + colorX];
					point.b = color.rgbBlue;
					point.g = color.rgbGreen;
					point.r = color.rgbRed;
				}

				// Coordinate Mapping Depth to Camera Space, and Setting PointCloud XYZ
				CameraSpacePoint cameraSpacePoint = { 0.0f, 0.0f, 0.0f };
				mapper->MapDepthPointToCameraSpace(depthSpacePoint, depth, &cameraSpacePoint);
				if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)){
#if 0
					point.x = cameraSpacePoint.X;
					point.y = cameraSpacePoint.Y;
					point.z = cameraSpacePoint.Z;
#else // meter to mm
					point.x = cameraSpacePoint.X * 1000;
					point.y = cameraSpacePoint.Y * 1000;
					point.z = cameraSpacePoint.Z * 1000;
#endif
					if (!ptexist){
						ptexist = true;
						std::cout << point.x << ", " << point.y << ", " << point.z << std::endl;
					}
				}

				cloud.push_back(point);
			}
		}
	}
}

#endif KINECT2_GRABBER
