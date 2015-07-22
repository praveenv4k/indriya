#ifndef __MARKER_DETECTION_TEST_H__
#define __MARKER_DETECTION_TEST_H__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "CvKinectCapture.h"
#include "RobotStateListener.h"
#include "TorsoPosePublisher.h"
#include "MarkerDetection.h"
#include "NaoHeadTransformHelper.h"

#define COMM_PROTOCOL		"tcp"
#define COMM_SUBIPADDRESS	"127.0.0.1"
#define COMM_SUBPORT		5563
#define COMM_SUBTOID		"RSP"
#define COMM_PUBIPADDRESS	"*"
#define COMM_PUBPORT		5566
#define COMM_PUBTOID		"TPP"

#define COMM_TIMEOUT		100

#define CALIB_FILE			"camera_calibration_kinect_1600.xml"
#define MARKER_SIZE			55
#define CUBE_SIZE			64

#define DEADLINE_TIMER1		30

class MarkerDetectionTest{
public:
	MarkerDetectionTest(boost::asio::io_service& io)
		: strand_(io),
		timer1_(io, boost::posix_time::milliseconds(DEADLINE_TIMER1))
	{

		m_pMarkerDetectionPtr = MarkerDetectionPtr(new MarkerDetection(std::string(CALIB_FILE), MARKER_SIZE, CUBE_SIZE));
		m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
		_init();

		timer1_.async_wait(strand_.wrap(boost::bind(&MarkerDetectionTest::SensorDataProcess, this)));
	}

	~MarkerDetectionTest()
	{
	}

	void SensorDataProcess()
	{
		bool quit = false;
		timer1_.expires_at(timer1_.expires_at() + boost::posix_time::milliseconds(DEADLINE_TIMER1));
		//TODO Call marker detection here
		if (m_VideoCapture.isOpened()){
			cv::Mat view0;
			m_VideoCapture >> view0;
			//cv::Mat viewGray;
			//cv::cvtColor(view0, viewGray, CV_RGB2GRAY);
			IplImage* img = cvCloneImage(&(IplImage)view0);
			if (img != NULL && m_pMarkerDetectionPtr != 0 && m_pRobotPoseInfoPtr != 0){
				RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
				
				std::vector<double> headJoints;
				headJoints.push_back(0);
				headJoints.push_back(0);
				Transform eef;
				NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

				Transform markerTfm;
				m_pMarkerDetectionPtr->Videocallback(img, eef, markerTfm,true);
				cv::Mat temp(img);
				cvShowImage("Image View", img);
				cvRelease((void**)&img);
			}
			int c = 0xff & cv::waitKey(1);
			if ((c & 255) == 27 || c == 'q' || c == 'Q')
			{
				quit = true;
			}
		}
		if (!quit){
			timer1_.async_wait(strand_.wrap(boost::bind(&MarkerDetectionTest::SensorDataProcess, this)));
		}
		else{
		}
	}

private:
	void _init(){
		m_VideoCapture.open(0);
		Sleep(3000);
		cvNamedWindow("Image View", 1);
	}
private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer1_;

	MarkerDetectionPtr m_pMarkerDetectionPtr;
	RobotPoseInfoPtr m_pRobotPoseInfoPtr;
	KinectVideoCapture m_VideoCapture;
};

#endif