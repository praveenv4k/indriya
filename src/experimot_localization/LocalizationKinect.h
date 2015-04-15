#ifndef __LOCALIZATION_KINECT_H__
#define __LOCALIZATION_KINECT_H__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "CvKinectCapture.h"
#include "RobotStateListener.h"
#include "TorsoPosePublisher.h"
#include "MarkerDetection.h"
#include "MarkerDetectionKinect.h"
#include "NaoHeadTransformHelper.h"
#include "LocalizationResponder.h"

#include "experimot\common\ParameterHelper.h"

#include "TorsoPoseFilter.h"
#include <bullet\Bullet3Common\b3Matrix3x3.h>

#include "MedianFilter.h"

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

#define TDM_ADDRESS			"tcp://*"
#define TDM_PORT			5700
#define TDM_TIMEOUT			100

#define NEW_MARKER_ERROR	0.8
#define MARKER_TRACK_ERROR	0.2

class LocalizationKinect;

typedef boost::shared_ptr<LocalizationKinect> LocalizationKinectPtr;

class LocalizationKinect{
public:
	LocalizationKinect(boost::asio::io_service& io, experimot::msgs::NodePtr& pNode)
		: strand_(io),
		m_RobotTimer(io, boost::posix_time::milliseconds(40)),
		m_PoseTimer(io, boost::posix_time::milliseconds(80)),
		m_TdmTimer(io, boost::posix_time::milliseconds(40)),
		m_MedianFilter(25)
	{
		m_pNode = pNode;

		if (m_pNode != 0){
			int cubeSize = ParameterHelper::GetParam<int>(m_pNode->param(), "cube_size", CUBE_SIZE);
			int markerSize = ParameterHelper::GetParam<int>(m_pNode->param(), "marker_size", MARKER_SIZE);
			std::string calibFile = ParameterHelper::GetParam<std::string>(m_pNode->param(), "calib_file", CALIB_FILE);
			int conn_timeout = ParameterHelper::GetParam<int>(m_pNode->param(), "comm_timeout", COMM_TIMEOUT);
			m_nSensorCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "sensor_process_cycle", 30);
			m_nRobotCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "robot_listener_cycle", 40);
			m_nPoseCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "pose_publisher_cycle", 80);
			m_nTdmCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "tdm_server_cycle", 40);

			double fNewMarkerError = ParameterHelper::GetParam<double>(m_pNode->param(), "max_new_marker_error", NEW_MARKER_ERROR);
			double fTrackError = ParameterHelper::GetParam<double>(m_pNode->param(), "max_track_error", MARKER_TRACK_ERROR);

			int tdm_port = ParameterHelper::GetParam<int>(m_pNode->param(), "tdm_server_port", TDM_PORT);

			m_pMarkerDetectionKinectPtr = MarkerDetectionKinectPtr(new MarkerDetectionKinect(calibFile, markerSize, cubeSize,fNewMarkerError,fTrackError));
			
			boost::function<void(const Transform&)> function =
				[this](const Transform &tfm){
				UpdateMarkerTransform(tfm);
			};

			m_pMarkerDetectionKinectPtr->registerCallback(function);

			for (int i = 0; i < m_pNode->publisher_size(); i++){
				auto& pub = m_pNode->publisher(i);
				if (pub.msg_type() == std::string("Pose")){
					m_pTorsoPosePublisherPtr = TorsoPosePublisherPtr(new TorsoPosePublisher(pub.host(), pub.port(), conn_timeout, pub.topic()));
				}
			}
			for (int i = 0; i < m_pNode->subscriber_size(); i++){
				auto& sub = m_pNode->subscriber(i);
				if (sub.msg_type() == std::string("JointValueVector")){
					m_pRobotStateListenerPtr = RobotStateListenerPtr(new RobotStateListener(sub.host(), sub.port(), conn_timeout, sub.topic()));
				}
			}

			m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
			m_pLocalizationResponderPtr = LocalizationResponderPtr(new LocalizationResponder(TDM_ADDRESS, tdm_port, TDM_TIMEOUT));

			m_RobotTimer.expires_at(m_RobotTimer.expires_at() + boost::posix_time::milliseconds(m_nRobotCycle));
			m_PoseTimer.expires_at(m_PoseTimer.expires_at() + boost::posix_time::milliseconds(m_nPoseCycle));
			m_TdmTimer.expires_at(m_TdmTimer.expires_at() + boost::posix_time::milliseconds(m_nTdmCycle));

			m_bVisualize = ParameterHelper::GetParam<int>(m_pNode->param(), "visualize", 1) > 0;

			_init();

			std::cout << "Localization node initialization complete !" << std::endl;
		}
	}

	LocalizationKinect(boost::asio::io_service& io)
		: strand_(io), m_nSensorCycle(30), m_nRobotCycle(40), m_nPoseCycle(80), m_nTdmCycle(40), m_bVisualize(true),
		m_RobotTimer(io, boost::posix_time::milliseconds(m_nRobotCycle)),
		m_PoseTimer(io, boost::posix_time::milliseconds(m_nPoseCycle)),
		m_TdmTimer(io, boost::posix_time::milliseconds(m_nTdmCycle)),
		m_MedianFilter(25)
	{
		m_pRobotStateListenerPtr = RobotStateListenerPtr(new RobotStateListener(std::string(COMM_PROTOCOL), std::string(COMM_SUBIPADDRESS), COMM_SUBPORT, COMM_TIMEOUT, std::string(COMM_SUBTOID)));
		m_pTorsoPosePublisherPtr = TorsoPosePublisherPtr(new TorsoPosePublisher(std::string(COMM_PROTOCOL), std::string(COMM_PUBIPADDRESS), COMM_PUBPORT, COMM_TIMEOUT, std::string(COMM_PUBTOID)));
		m_pMarkerDetectionKinectPtr = MarkerDetectionKinectPtr(new MarkerDetectionKinect(std::string(CALIB_FILE), MARKER_SIZE, CUBE_SIZE, NEW_MARKER_ERROR, MARKER_TRACK_ERROR));
		m_pLocalizationResponderPtr = LocalizationResponderPtr(new LocalizationResponder(TDM_ADDRESS, TDM_PORT, TDM_TIMEOUT));
		m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
		_init();
	}

	~LocalizationKinect()
	{
	}

	// decompose Transform into x,y,z,Rx,Ry,Rz
	void decomposeTransform(const OpenRAVE::Transform& trans, double&Rx, double& Ry, double& Rz){
		Vector quat = trans.rot;
		b3Quaternion b3quat(quat[1], quat[2], quat[3], quat[0]);
		b3Matrix3x3 b3Mat(b3quat);
		float roll, pitch, yaw;
		b3Mat.getEulerYPR(yaw, pitch, roll);
		Rx = roll; Ry = pitch; Rz = yaw;
	}

	void composeTransform(double rx, double ry, double rz, Vector& rot){
		b3Quaternion q;
		q.setEulerZYX(rz, ry, rx);

		rot = Vector(q.w, q.x, q.y, q.z);
	}

	void ToKinectFrame(const Transform& alvar, Transform& kinect){
		double roll, pitch, yaw;
		// Decompose the transform into roll,pitch and yaw
		decomposeTransform(alvar, roll, pitch, yaw);
		// Compose again the transform with mirrored angles to transform from ALVAR to Kinect Frame
		composeTransform(-roll, pitch, -yaw, kinect.rot);
		// Also mirror the Y axis position direction in order to match Kinect Frame
		Vector trans = alvar.trans;
		trans.z = alvar.trans.z;
		trans.y = -alvar.trans.y;
		trans.x = alvar.trans.x;
		kinect.trans = trans;
	}

	void ConvertToRightHandFrame(const Transform& in, Transform& out){
		Pose temp;
		TransformationHelper::TransformToPose(in, temp);
		dReal gl_mat[16];
		temp.GetMatrixGL(gl_mat);
		/*for (int i = 0; i < 4; i++){
		cout << gl_mat[4 * i] << " , " << gl_mat[4 * i + 1] << " , " << gl_mat[4 * i + 2] << " , " << gl_mat[4 * i + 3] << " , " << std::endl;
		}*/
		TransformMatrix mat;
		mat.rotfrommat(gl_mat[0], gl_mat[1], gl_mat[2], gl_mat[4], gl_mat[5], gl_mat[6], gl_mat[8], gl_mat[9], gl_mat[10]);
		mat.trans = Vector(gl_mat[12], gl_mat[13], gl_mat[14]);
		//cout << mat.inverse() << std::endl;

		out = mat.inverse();
	}

	void UpdateMarkerTransform(const Transform& markerTfm)
	{
		if (m_pRobotPoseInfoPtr != 0){
			RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
			const std::vector<double>& jointVals = m_pRobotPoseInfoPtr->GetJointValueVector();
			std::vector<double> headJoints;

			if (jointVals.size() >= 2){
				headJoints.push_back(jointVals[0]);
				headJoints.push_back(jointVals[1]);
				//std::cout << "Received values from Naoqi" << std::endl;
			}
			else{
				headJoints.push_back(0);
				headJoints.push_back(0);
			}
			Transform eef;
			Transform out;
			NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

			m_MedianFilter.addPose(markerTfm);
			m_MedianFilter.getMedian(out);
			m_pRobotPoseInfoPtr->SetMarkerTransform(out);
		}
	}

	void JointDataReceive()
	{
		m_RobotTimer.expires_at(m_RobotTimer.expires_at() + boost::posix_time::milliseconds(m_nRobotCycle));
		//TODO Call Joint data reception here
		if (m_pRobotStateListenerPtr != 0 && m_pRobotPoseInfoPtr != 0){
			std::vector<double> jointValues;
			if (m_pRobotStateListenerPtr->Listen(jointValues)){
				RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
				m_pRobotPoseInfoPtr->SetJointValueVector(jointValues);
			}
		}
		m_RobotTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::JointDataReceive, this)));
	}

	void PublishTransform(){
		m_PoseTimer.expires_at(m_PoseTimer.expires_at() + boost::posix_time::milliseconds(m_nPoseCycle));
		//TODO Publish Torso transform here
		if (m_pTorsoPosePublisherPtr != 0 && m_pRobotPoseInfoPtr != 0){
			RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
			//if (m_pRobotPoseInfoPtr->IsJointValuesInit() && m_pRobotPoseInfoPtr->IsMarkerTransformInit()){
			if (m_pRobotPoseInfoPtr->IsMarkerTransformInit()){
				//NaoHeadTransformHelper::instance()->
				const std::vector<double>& jointVals = m_pRobotPoseInfoPtr->GetJointValueVector();
				std::vector<double> headJoints;
				if (jointVals.size() >= 2){
					headJoints.push_back(jointVals[0]);
					headJoints.push_back(jointVals[1]);
				}
				else{
					headJoints.push_back(0);
					headJoints.push_back(0);
				}
#if 1
				Transform eef;
				NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

				const Transform& markerTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();

				Transform torsoTfm;
				TransformationHelper::ComputeTorsoFrame(markerTfm, eef, torsoTfm);

				//Transform filterTfm;
				//m_poseFilter.getEstimate(filterTfm);

				Transform kinectTfm;
				ToKinectFrame(torsoTfm, kinectTfm);

#if 1
				cout << "*********************************************" << std::endl;
				cout << "End Effector w.r.t Torso   : " << eef << std::endl;
				cout << "Top Marker w.r.t ALVAR     : " << markerTfm << std::endl;
				cout << "Torso w.r.t ALVAR          : " << torsoTfm << std::endl << std::endl;
				cout << "Torso w.r.t Kinect         : " << kinectTfm << std::endl << std::endl;
#else
				cout << "*********************************************" << std::endl;
				cout << "Actual marker Transform      : " << markerTfm << std::endl;
				cout << "Filtered marker Transform    : " << filterTfm << std::endl;
#endif
#else 
				const Transform& markerTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();
				Transform torsoTfm;
				NaoHeadTransformHelper::instance()->GetTorsoTransform(headJoints, markerTfm, torsoTfm);
#endif
				m_pTorsoPosePublisherPtr->Publish(kinectTfm);
			}
		}
		m_PoseTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::PublishTransform, this)));
	}


	void LocalizationRespond(){
		m_TdmTimer.expires_at(m_TdmTimer.expires_at() + boost::posix_time::milliseconds(m_nTdmCycle));
		if (m_pTorsoPosePublisherPtr != 0 && m_pRobotPoseInfoPtr != 0){
			RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
			//if (m_pRobotPoseInfoPtr->IsJointValuesInit() && m_pRobotPoseInfoPtr->IsMarkerTransformInit()){
			if (m_pRobotPoseInfoPtr->IsMarkerTransformInit()){

				const std::vector<double>& jointVals = m_pRobotPoseInfoPtr->GetJointValueVector();
				std::vector<double> headJoints;
				if (jointVals.size() >= 2){
					headJoints.push_back(jointVals[0]);
					headJoints.push_back(jointVals[1]);
				}
				else{
					headJoints.push_back(0);
					headJoints.push_back(0);
				}
				Transform eef;
				NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

				const Transform& markerTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();

				Transform torsoTfm;
				TransformationHelper::ComputeTorsoFrame(markerTfm, eef, torsoTfm);

				//Transform filterTfm;
				//m_poseFilter.getEstimate(filterTfm);
				//std::cout << "Responding to localization request" << std::endl;
				//m_pLocalizationResponderPtr->Respond(torsoTfm);
				Transform kinectTfm;

				// For testing
#if 0
				ToKinectFrame(torsoTfm, kinectTfm);
#else
				ToKinectFrame(markerTfm, kinectTfm);
#endif


				m_pLocalizationResponderPtr->Respond(kinectTfm);
			}
		}
		m_TdmTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::LocalizationRespond, this)));
	}

private:
	void _init(){
		m_VideoCapture.open(0);
		Sleep(3000);

		if (m_bVisualize){
			cvNamedWindow("Image View", 1);
		}

		m_RobotTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::JointDataReceive, this)));
		m_PoseTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::PublishTransform, this)));
		m_TdmTimer.async_wait(strand_.wrap(boost::bind(&LocalizationKinect::LocalizationRespond, this)));
	}
private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer m_RobotTimer;
	boost::asio::deadline_timer m_PoseTimer;
	boost::asio::deadline_timer m_TdmTimer;

	int m_nSensorCycle;
	int m_nRobotCycle;
	int m_nPoseCycle;
	int m_nTdmCycle;

	bool m_bVisualize;
	experimot::msgs::NodePtr m_pNode;
	RobotStateListenerPtr m_pRobotStateListenerPtr;
	TorsoPosePublisherPtr m_pTorsoPosePublisherPtr;
	LocalizationResponderPtr m_pLocalizationResponderPtr;
	RobotPoseInfoPtr m_pRobotPoseInfoPtr;
	KinectVideoCapture m_VideoCapture;
	TorsoPoseFilter m_poseFilter;

	MedianFilter m_MedianFilter;
	MarkerDetectionKinectPtr m_pMarkerDetectionKinectPtr;
};

#endif