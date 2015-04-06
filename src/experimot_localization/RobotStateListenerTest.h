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

class RobotStateListenerTest{
public:
	RobotStateListenerTest(boost::asio::io_service& io)
		: strand_(io),
		timer2_(io, boost::posix_time::milliseconds(40))
	{

		m_pRobotStateListenerPtr = RobotStateListenerPtr(new RobotStateListener(std::string(COMM_PROTOCOL), std::string(COMM_SUBIPADDRESS), COMM_SUBPORT, COMM_TIMEOUT, std::string(COMM_SUBTOID)));
		m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
		_init();

		timer2_.async_wait(strand_.wrap(boost::bind(&RobotStateListenerTest::JointDataReceive, this)));

	}

	~RobotStateListenerTest()
	{
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
				//std::cout << "Received values from Naoqi : [" << jointValues[0] << ", " << jointValues[1] << " ] " << std::endl;
			}
		}
		timer2_.async_wait(strand_.wrap(boost::bind(&RobotStateListenerTest::JointDataReceive, this)));
	}

private:
	void _init(){
	}
private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer2_;

	RobotStateListenerPtr m_pRobotStateListenerPtr;
	RobotPoseInfoPtr m_pRobotPoseInfoPtr;
};

#endif