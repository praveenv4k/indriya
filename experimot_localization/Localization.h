#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

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

class Localization{
public:
	Localization(boost::asio::io_service& io)
		: strand_(io),
		timer1_(io, boost::posix_time::milliseconds(30)),
		timer2_(io, boost::posix_time::milliseconds(40)),
		timer3_(io, boost::posix_time::milliseconds(80))
	{

		m_pRobotStateListenerPtr = RobotStateListenerPtr(new RobotStateListener(std::string(COMM_PROTOCOL), std::string(COMM_SUBIPADDRESS), COMM_SUBPORT, COMM_TIMEOUT, std::string(COMM_SUBTOID)));
		m_pTorsoPosePublisherPtr = TorsoPosePublisherPtr(new TorsoPosePublisher(std::string(COMM_PROTOCOL), std::string(COMM_PUBIPADDRESS), COMM_PUBPORT, COMM_TIMEOUT, std::string(COMM_PUBTOID)));
		m_pMarkerDetectionPtr = MarkerDetectionPtr(new MarkerDetection(std::string(CALIB_FILE), MARKER_SIZE, CUBE_SIZE));
		m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
		_init();

		timer1_.async_wait(strand_.wrap(boost::bind(&Localization::SensorDataProcess, this)));
		timer2_.async_wait(strand_.wrap(boost::bind(&Localization::JointDataReceive, this)));
		timer3_.async_wait(strand_.wrap(boost::bind(&Localization::PublishTransform, this)));

	}

	~Localization()
	{
	}

	void SensorDataProcess()
	{
		bool quit = false;
		timer1_.expires_at(timer1_.expires_at() + boost::posix_time::milliseconds(30));
		//TODO Call marker detection here
		if (m_VideoCapture.isOpened()){
			cv::Mat view0;
			m_VideoCapture >> view0;
			IplImage* img = cvCloneImage(&(IplImage)view0);
			if (img != NULL && m_pMarkerDetectionPtr != 0 && m_pRobotPoseInfoPtr != 0){
				RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
				const std::vector<double>& jointVals = m_pRobotPoseInfoPtr->GetJointValueVector();
				if (jointVals.size() >= 2){
					std::vector<double> headJoints;
					headJoints.push_back(jointVals[0]);
					headJoints.push_back(jointVals[1]);

					Transform eef;
					NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

					Transform markerTfm;
					m_pMarkerDetectionPtr->Videocallback(img, eef, markerTfm);
					cv::Mat temp(img);
					cvShowImage("Image View", img);
					cvRelease((void**)&img);
				}
			}
			int c = 0xff & cv::waitKey(1);
			if ((c & 255) == 27 || c == 'q' || c == 'Q')
			{
				quit = true;
			}
		}
		if (!quit){
			timer1_.async_wait(strand_.wrap(boost::bind(&Localization::SensorDataProcess, this)));
		}
		else{
		}
	}

	void JointDataReceive()
	{
		timer2_.expires_at(timer2_.expires_at() + boost::posix_time::milliseconds(40));
		//TODO Call Joint data reception here
		if (m_pRobotStateListenerPtr != 0 && m_pRobotPoseInfoPtr != 0){
			std::vector<double> jointValues;
			if (m_pRobotStateListenerPtr->Listen(jointValues)){
				RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
				m_pRobotPoseInfoPtr->SetJointValueVector(jointValues);
			}
		}
		timer2_.async_wait(strand_.wrap(boost::bind(&Localization::JointDataReceive, this)));
	}

	void PublishTransform(){
		timer3_.expires_at(timer3_.expires_at() + boost::posix_time::milliseconds(80));
		//TODO Publish Torso transform here
		if (m_pTorsoPosePublisherPtr != 0 && m_pRobotPoseInfoPtr != 0){
				RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
				if (m_pRobotPoseInfoPtr->IsJointValuesInit() && m_pRobotPoseInfoPtr->IsMarkerTransformInit()){
					//NaoHeadTransformHelper::instance()->
					const std::vector<double>& jointVals = m_pRobotPoseInfoPtr->GetJointValueVector();
					if (jointVals.size() >= 2){
						std::vector<double> headJoints;
						headJoints.push_back(jointVals[0]);
						headJoints.push_back(jointVals[1]);

						Transform eef;
						NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

						const Transform& markerTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();

						Transform torsoTfm;
						TransformationHelper::ComputeTorsoFrame(markerTfm, eef, torsoTfm);
					}
				}
		}
		timer3_.async_wait(strand_.wrap(boost::bind(&Localization::PublishTransform, this)));
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
	boost::asio::deadline_timer timer2_;
	boost::asio::deadline_timer timer3_;

	RobotStateListenerPtr m_pRobotStateListenerPtr;
	TorsoPosePublisherPtr m_pTorsoPosePublisherPtr;
	MarkerDetectionPtr m_pMarkerDetectionPtr;
	RobotPoseInfoPtr m_pRobotPoseInfoPtr;
	KinectVideoCapture m_VideoCapture;
};

#endif