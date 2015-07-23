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
#include "MarkerDetection2.h"
#include "MarkerDetectionKinect.h"
#include "NaoHeadTransformHelper.h"
#include "LocalizationResponder.h"

#include "experimot\common\ParameterHelper.h"

#include "TorsoPoseFilter.h"
#include <bullet\Bullet3Common\b3Matrix3x3.h>

#include "MedianFilter.h"
#include "MarkerParticleFilter.h"

#include <opencv2/core/core.hpp>
//#include <opencv2\core\utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/video/tracking.hpp>

#define COMM_PROTOCOL		"tcp"
#define COMM_SUBIPADDRESS	"127.0.0.1"
#define COMM_SUBPORT		5563
#define COMM_SUBTOID		"RSP"
#define COMM_PUBIPADDRESS	"*"
#define COMM_PUBPORT		5566
#define COMM_PUBTOID		"TPP"

#define COMM_TIMEOUT		100

#define TDM_ADDRESS			"tcp://*"
#define TDM_PORT			5700
#define TDM_TIMEOUT			100

#define VERBOSE_MODE 0

class Localization;

typedef boost::shared_ptr<Localization> LocalizationPtr;

class Localization{
public:
	Localization(boost::asio::io_service& io, Indriya::Core::Msgs::NodePtr& pNode)
		: strand_(io),
		m_SensorTimer(io, boost::posix_time::milliseconds(20)),
		m_RobotTimer(io, boost::posix_time::milliseconds(40)),
		m_PoseTimer(io, boost::posix_time::milliseconds(80)),
		m_TdmTimer(io, boost::posix_time::milliseconds(40)),
		m_MedianFilter(25)
	{
		m_pNode = pNode;

		if (m_pNode != 0){

			int conn_timeout = ParameterHelper::GetParam<int>(m_pNode->param(), "comm_timeout", COMM_TIMEOUT);
			m_nSensorCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "sensor_process_cycle", 30);
			m_nRobotCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "robot_listener_cycle", 40);
			m_nPoseCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "pose_publisher_cycle", 80);
			m_nTdmCycle = ParameterHelper::GetParam<int>(m_pNode->param(), "tdm_server_cycle", 40);

			double fNewMarkerError = ParameterHelper::GetParam<double>(m_pNode->param(), "max_new_marker_error", NEW_MARKER_ERROR);
			double fTrackError = ParameterHelper::GetParam<double>(m_pNode->param(), "max_track_error", MARKER_TRACK_ERROR);

			int tdm_port = ParameterHelper::GetParam<int>(m_pNode->param(), "tdm_server_port", TDM_PORT);

			m_pMarkerDetectionPtr = MarkerDetection2Ptr(new MarkerDetection2(pNode));

			//m_pMarkerDetectionKinectPtr = MarkerDetectionKinectPtr(new MarkerDetectionKinect(calibFile, markerSize, cubeSize,fNewMarkerError,fTrackError));

			for (int i = 0; i < m_pNode->publisher_size(); i++){
				auto& pub = m_pNode->publisher(i);
				if (pub.msg_type() == std::string("Pose_V")){
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

			m_SensorTimer.expires_at(m_SensorTimer.expires_at() + boost::posix_time::milliseconds(m_nSensorCycle));
			m_RobotTimer.expires_at(m_RobotTimer.expires_at() + boost::posix_time::milliseconds(m_nRobotCycle));
			m_PoseTimer.expires_at(m_PoseTimer.expires_at() + boost::posix_time::milliseconds(m_nPoseCycle));
			m_TdmTimer.expires_at(m_TdmTimer.expires_at() + boost::posix_time::milliseconds(m_nTdmCycle));

			m_bVisualize = ParameterHelper::GetParam<int>(m_pNode->param(), "visualize", 1) > 0;

			_init();

			std::cout << "Localization node initialization complete !" << std::endl;
		}
		m_SensorThreadQuit = false;
	}

	Localization(boost::asio::io_service& io)
		: strand_(io), m_nSensorCycle(20), m_nRobotCycle(40), m_nPoseCycle(80), m_nTdmCycle(40), m_bVisualize(true),
		m_SensorTimer(io, boost::posix_time::milliseconds(m_nSensorCycle)),
		m_RobotTimer(io, boost::posix_time::milliseconds(m_nRobotCycle)),
		m_PoseTimer(io, boost::posix_time::milliseconds(m_nPoseCycle)),
		m_TdmTimer(io, boost::posix_time::milliseconds(m_nTdmCycle)),
		m_MedianFilter(25)
	{
		m_pRobotStateListenerPtr = RobotStateListenerPtr(new RobotStateListener(std::string(COMM_PROTOCOL), std::string(COMM_SUBIPADDRESS), COMM_SUBPORT, COMM_TIMEOUT, std::string(COMM_SUBTOID)));
		m_pTorsoPosePublisherPtr = TorsoPosePublisherPtr(new TorsoPosePublisher(std::string(COMM_PROTOCOL), std::string(COMM_PUBIPADDRESS), COMM_PUBPORT, COMM_TIMEOUT, std::string(COMM_PUBTOID)));
		m_pMarkerDetectionPtr = MarkerDetection2Ptr(new MarkerDetection2(std::string(CALIB_FILE), MARKER_SIZE, CUBE_SIZE));
		m_pLocalizationResponderPtr = LocalizationResponderPtr(new LocalizationResponder(TDM_ADDRESS, TDM_PORT, TDM_TIMEOUT));
		m_pRobotPoseInfoPtr = RobotPoseInfoPtr(new RobotPoseInfo());
		m_SensorThreadQuit = false;
		_init();
	}

	~Localization()
	{
		m_SensorThreadQuit = true;
		m_SensorThread.join();
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

	void ToColumnVector(const Transform& tfm, ColumnVector& filterPose){
		double roll, pitch, yaw;
		decomposeTransform(tfm, roll, pitch, yaw);
		filterPose.resize(STATE_SIZE);
		filterPose(1) = tfm.trans.x;
		filterPose(2) = tfm.trans.y;
		filterPose(3) = tfm.trans.z;
		filterPose(4) = roll;
		filterPose(5) = pitch;
		filterPose(6) = yaw;
	}

	void ToTransform(const ColumnVector& colVector, Transform& tfm){
		if (colVector.size() == STATE_SIZE){
			tfm.trans.x = colVector(1);
			tfm.trans.y = colVector(2);
			tfm.trans.z = colVector(3);
			composeTransform(colVector(4), colVector(5), colVector(6), tfm.rot);
		}
	}

	void SensorDataProcessThread()
	{
		bool quit = false;
		if (m_bVisualize){
			cvNamedWindow("Image View", 1);
		}
		while (true){
			if (m_VideoCapture.isOpened()){
				cv::Mat view0;
				m_VideoCapture >> view0;
				IplImage* img = cvCloneImage(&(IplImage)view0);
				if (img != NULL && m_pMarkerDetectionPtr != 0 && m_pRobotPoseInfoPtr != 0){
					RobotPoseInfoMutex::scoped_lock lock(m_pRobotPoseInfoPtr->GetMutex());
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

					Transform markerTfm;
					Transform prevTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();
					if (m_pMarkerDetectionPtr->Videocallback(prevTfm, img, eef, markerTfm, headJoints, true)){
						m_MedianFilter.addPose(markerTfm);
						m_MedianFilter.getMedian(markerTfm);

#if 0
						double distance = (markerTfm.rot - prevTfm.rot).lengthsqr4();
						if (distance > 1){

							b3Quaternion q1(prevTfm.rot[1], prevTfm.rot[2], prevTfm.rot[3], prevTfm.rot[0]);
							b3Quaternion q2(markerTfm.rot[1], markerTfm.rot[2], markerTfm.rot[3], markerTfm.rot[0]);

							double angle = q1.angle(q2);
							if (fabs(angle) > 10){
								markerTfm = prevTfm;
							}

							/*cout << "Transform : " << TransformMatrix(markerTfm) << endl;
							cout << "Distance : " << distance << endl;*/
							//cout << markerTfm.rot << "\t " << (angle * 180) / B3_PI << "\t " << distance << std::endl;
						}
#endif

						// Interpolate
						markerTfm.trans = 0.5 * (markerTfm.trans + prevTfm.trans);
						Vector temp = OpenRAVE::geometry::quatSlerp(markerTfm.rot, prevTfm.rot, 0.5);
						markerTfm.rot = temp;

#ifdef USE_PARTICLE_FILTER
						{
							MarkerParticleFilterMutex::scoped_lock lock2(m_ParticleFilter.GetMutex());
							ColumnVector particlePose;
							ToColumnVector(markerTfm, particlePose);
							PrintColumnVector(particlePose);
							m_ParticleFilter.Update(particlePose);
						}
#endif
						/*cout << "************* Updating KF *****************" << std::endl;
						m_poseFilter.addMeasurement(markerTfm);

						m_poseFilter.update(boost::posix_time::microsec_clock::local_time());
						if (!m_poseFilter.isInitialized()){
						m_poseFilter.initialize(markerTfm, boost::posix_time::microsec_clock::local_time());
						}*/

						Transform worldTransform;
						bool valid = m_pMarkerDetectionPtr->GetWorldTransform(worldTransform);
						m_pRobotPoseInfoPtr->SetMarkerTransform(markerTfm);
					}
					else{
						//cout << "No markers detected" << endl;
					}
					if (m_bVisualize){
						cv::Mat temp(img);
						cvShowImage("Image View", img);
					}
					cvRelease((void**)&img);
				}
				int c = 0xff & cv::waitKey(1);
				if ((c & 255) == 27 || c == 'q' || c == 'Q' || m_SensorThreadQuit)
				{
					std::cout << "About to quit the sensor process thread : " << m_SensorThreadQuit << std::endl;
					quit = true;
				}
			}
			if (!quit){

			}
			else{
				break;
			}
		}
	}

	void SensorDataProcess()
	{
		return;
		bool quit = false;
		m_SensorTimer.expires_at(m_SensorTimer.expires_at() + boost::posix_time::milliseconds(m_nSensorCycle));
		//TODO Call marker detection here
		if (m_VideoCapture.isOpened()){
			cv::Mat view0;
			m_VideoCapture >> view0;
			IplImage* img = cvCloneImage(&(IplImage)view0);
			if (img != NULL && m_pMarkerDetectionPtr != 0 && m_pRobotPoseInfoPtr != 0){
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
				NaoHeadTransformHelper::instance()->GetEndEffectorTransform(headJoints, eef);

				Transform markerTfm;
				Transform prevTfm = m_pRobotPoseInfoPtr->GetMarkerTransform();
				if (m_pMarkerDetectionPtr->Videocallback(prevTfm, img, eef, markerTfm, headJoints, true)){
					Transform out;
					//ConvertToRightHandFrame(markerTfm, out);

					// Compute Top marker with respect to camera
					//out = markerTfm.inverse();


#if 0
					out = markerTfm;
					m_pRobotPoseInfoPtr->SetMarkerTransform(out);
#else
					m_MedianFilter.addPose(markerTfm);
					m_MedianFilter.getMedian(markerTfm);
					cout << markerTfm << endl;
					m_pRobotPoseInfoPtr->SetMarkerTransform(markerTfm);
#endif

#if 1
					/*cout << "************* Updating KF *****************" << std::endl;
					m_poseFilter.addMeasurement(out);

					m_poseFilter.update(boost::posix_time::microsec_clock::local_time());
					if (!m_poseFilter.isInitialized()){
					m_poseFilter.initialize(out, boost::posix_time::microsec_clock::local_time());
					}*/
#endif
				}
				else{
					m_nMeasuredCount = 0;
					cout << "No markers detected" << endl;
				}
				if (m_bVisualize){
					cv::Mat temp(img);
					cvShowImage("Image View", img);
				}
				cvRelease((void**)&img);
			}
			int c = 0xff & cv::waitKey(1);
			if ((c & 255) == 27 || c == 'q' || c == 'Q')
			{
				quit = true;
			}
		}
		if (!quit){
			m_SensorTimer.async_wait(strand_.wrap(boost::bind(&Localization::SensorDataProcess, this)));
		}
		else{
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
		m_RobotTimer.async_wait(strand_.wrap(boost::bind(&Localization::JointDataReceive, this)));
	}

	void PrintColumnVector(ColumnVector& colVector){
		for (int i = 0; i < colVector.size(); i++){
			cout << colVector(i + 1);
			if (i != colVector.size() - 1){
				cout << "\t";
			}
		}
		cout << std::endl;
	}

	void PublishTransform(){
		boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());

		//cout << "Publishing transform" << endl;
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

				/*Transform filterTfm;
				m_poseFilter.getEstimate(filterTfm);
				cout << "Filter Tfm : " << filterTfm << std::endl;*/

				Transform kinectTfm;
				ToKinectFrame(torsoTfm, kinectTfm);
				Transform worldTfm, worldTfmKinect;
				m_pMarkerDetectionPtr->GetWorldTransform(worldTfm);
				ToKinectFrame(worldTfm, worldTfmKinect);
#ifdef USE_PARTICLE_FILTER
				{
					MarkerParticleFilterMutex::scoped_lock lock2(m_ParticleFilter.GetMutex());
					ColumnVector filteredPose;
					m_ParticleFilter.GetPose(filteredPose);
					PrintColumnVector(filteredPose);
				}
#endif

#if 1

#if 1
#if VERBOSE_MODE
				cout << "*********************************************" << std::endl;
				cout << "End Effector w.r.t Torso   : " << eef << std::endl;
				cout << "Top Marker w.r.t ALVAR     : " << markerTfm << std::endl;
				cout << "Torso w.r.t ALVAR          : " << torsoTfm << std::endl << std::endl;
				cout << "Torso w.r.t Kinect         : " << kinectTfm << std::endl << std::endl;
#endif
#endif

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
				std::map<string, Transform> transforms;
				transforms.insert(std::pair<string, Transform>("torso_frame_kinect", kinectTfm));
				transforms.insert(std::pair<string, Transform>("world_frame_kinect", worldTfmKinect));
				transforms.insert(std::pair<string, Transform>("world_frame", Transform()));
				Transform torsoWorld = worldTfmKinect.inverse() * kinectTfm;
				transforms.insert(std::pair<string, Transform>("torso_frame_world", torsoWorld));
				Transform torsoWorldFiltered;
				if (getFilteredPose(torsoWorld, torsoWorldFiltered)){
					transforms.insert(std::pair<string, Transform>("torso_frame_world_filtered", torsoWorldFiltered));
#if VERBOSE_MODE
#else
					cout << "T   : " << torsoWorld << std::endl;
					cout << "T_F : " << torsoWorldFiltered << std::endl;
#endif
				}
				m_pTorsoPosePublisherPtr->Publish(transforms);

				boost::posix_time::ptime t2(boost::posix_time::microsec_clock::local_time());
				boost::posix_time::time_duration dt = t2 - t1;
				//print formatted date
				std::cout << dt << std::endl;
				//number of elapsed miliseconds
				long msec = dt.total_milliseconds();
				//print elapsed seconds (with millisecond precision)
				std::cout << msec / 1000.0 << std::endl;
			}
		}
		m_PoseTimer.async_wait(strand_.wrap(boost::bind(&Localization::PublishTransform, this)));
	}

	bool getFilteredPose(const Transform& tfm, Transform& filtered){
		m_nMeasuredCount++;
		if (m_nMeasuredCount > 30)
			m_bGoodMeasurements = true;
		else
			return false;
		// GOOD MEASUREMENT
		if (m_bGoodMeasurements)
		{

			// Get the measured translation
			cv::Mat translation_measured(3, 1, CV_64F);
			cv::Mat rotation_measured(3, 3, CV_64F);

			TransformationHelper::RaveToCv(tfm, translation_measured, rotation_measured);

			// fill the measurements vector
			fillMeasurements(m_Measurements, translation_measured, rotation_measured);

			//good_measurement = true;

		}

		// Instantiate estimated translation and rotation
		cv::Mat translation_estimated(3, 1, CV_64F);
		cv::Mat rotation_estimated(3, 3, CV_64F);

		// update the Kalman filter with good measurements
		updateKalmanFilter(m_KalmanFilter, m_Measurements,
			translation_estimated, rotation_estimated);

		TransformationHelper::CvToRave(translation_estimated, rotation_estimated, filtered);

		return true;
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
#if 1
				ToKinectFrame(torsoTfm, kinectTfm);
#else
				ToKinectFrame(markerTfm, kinectTfm);
#endif


				m_pLocalizationResponderPtr->Respond(kinectTfm, m_prevLocalizationTransform, false);

				m_prevLocalizationTransform = kinectTfm;
			}
		}
		m_TdmTimer.async_wait(strand_.wrap(boost::bind(&Localization::LocalizationRespond, this)));
	}

	void initKalmanFilter(cv::KalmanFilter &KF, int nStates, int nMeasurements, int nInputs, double dt){
		KF.init(nStates, nMeasurements, nInputs, CV_64F);                 // init Kalman Filter

		setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));       // set process noise
		//setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-2));   // set measurement noise
		setIdentity(KF.measurementNoiseCov, cv::Scalar::all(5e-3));   // set measurement noise
		setIdentity(KF.errorCovPost, cv::Scalar::all(1));             // error covariance


		/** DYNAMIC MODEL **/

		//  [1 0 0 dt  0  0 dt2   0   0 0 0 0  0  0  0   0   0   0]
		//  [0 1 0  0 dt  0   0 dt2   0 0 0 0  0  0  0   0   0   0]
		//  [0 0 1  0  0 dt   0   0 dt2 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  1  0  0  dt   0   0 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  1  0   0  dt   0 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  0  1   0   0  dt 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  0  0   1   0   0 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  0  0   0   1   0 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  0  0   0   0   1 0 0 0  0  0  0   0   0   0]
		//  [0 0 0  0  0  0   0   0   0 1 0 0 dt  0  0 dt2   0   0]
		//  [0 0 0  0  0  0   0   0   0 0 1 0  0 dt  0   0 dt2   0]
		//  [0 0 0  0  0  0   0   0   0 0 0 1  0  0 dt   0   0 dt2]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  1  0  0  dt   0   0]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  0  1  0   0  dt   0]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  0  0  1   0   0  dt]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  0  0  0   1   0   0]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  0  0  0   0   1   0]
		//  [0 0 0  0  0  0   0   0   0 0 0 0  0  0  0   0   0   1]

		// position
		KF.transitionMatrix.at<double>(0, 3) = dt;
		KF.transitionMatrix.at<double>(1, 4) = dt;
		KF.transitionMatrix.at<double>(2, 5) = dt;
		KF.transitionMatrix.at<double>(3, 6) = dt;
		KF.transitionMatrix.at<double>(4, 7) = dt;
		KF.transitionMatrix.at<double>(5, 8) = dt;
		KF.transitionMatrix.at<double>(0, 6) = 0.5*pow(dt, 2);
		KF.transitionMatrix.at<double>(1, 7) = 0.5*pow(dt, 2);
		KF.transitionMatrix.at<double>(2, 8) = 0.5*pow(dt, 2);

		// orientation
		KF.transitionMatrix.at<double>(9, 12) = dt;
		KF.transitionMatrix.at<double>(10, 13) = dt;
		KF.transitionMatrix.at<double>(11, 14) = dt;
		KF.transitionMatrix.at<double>(12, 15) = dt;
		KF.transitionMatrix.at<double>(13, 16) = dt;
		KF.transitionMatrix.at<double>(14, 17) = dt;
		KF.transitionMatrix.at<double>(9, 15) = 0.5*pow(dt, 2);
		KF.transitionMatrix.at<double>(10, 16) = 0.5*pow(dt, 2);
		KF.transitionMatrix.at<double>(11, 17) = 0.5*pow(dt, 2);


		/** MEASUREMENT MODEL **/

		//  [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
		//  [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
		//  [0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
		//  [0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0]
		//  [0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0]
		//  [0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0]

		KF.measurementMatrix.at<double>(0, 0) = 1;  // x
		KF.measurementMatrix.at<double>(1, 1) = 1;  // y
		KF.measurementMatrix.at<double>(2, 2) = 1;  // z
		KF.measurementMatrix.at<double>(3, 9) = 1;  // roll
		KF.measurementMatrix.at<double>(4, 10) = 1; // pitch
		KF.measurementMatrix.at<double>(5, 11) = 1; // yaw
	}

	void updateKalmanFilter(cv::KalmanFilter &KF, boost::shared_ptr<cv::Mat> &measurement,
		cv::Mat &translation_estimated, cv::Mat &rotation_estimated){

		// First predict, to update the internal statePre variable
		cv::Mat prediction = KF.predict();

		// The "correct" phase that is going to use the predicted value and our measurement
		cv::Mat temp_measured(6, 1, CV_64F);
		
		temp_measured.at<double>(0, 0) = measurement->at<double>(0, 0);  // x
		temp_measured.at<double>(1, 0) = measurement->at<double>(1, 0);  // y
		temp_measured.at<double>(2, 0) = measurement->at<double>(2, 0);  // z
		temp_measured.at<double>(3, 0) = measurement->at<double>(3, 0);  // roll
		temp_measured.at<double>(4, 0) = measurement->at<double>(4, 0);  // pitch
		temp_measured.at<double>(5, 0) = measurement->at<double>(5, 0);  // yaw

		cv::Mat estimated = KF.correct(temp_measured);

		// Estimated translation
		translation_estimated.at<double>(0) = estimated.at<double>(0);
		translation_estimated.at<double>(1) = estimated.at<double>(1);
		translation_estimated.at<double>(2) = estimated.at<double>(2);

		// Estimated euler angles
		cv::Mat eulers_estimated(3, 1, CV_64F);
		eulers_estimated.at<double>(0) = estimated.at<double>(9);
		eulers_estimated.at<double>(1) = estimated.at<double>(10);
		eulers_estimated.at<double>(2) = estimated.at<double>(11);

		// Convert estimated quaternion to rotation matrix
		rotation_estimated = TransformationHelper::euler2rot(eulers_estimated);
	}
	void fillMeasurements(boost::shared_ptr<cv::Mat> &measurements,
		const cv::Mat &translation_measured, const cv::Mat &rotation_measured){
		// Convert rotation matrix to euler angles
		cv::Mat measured_eulers(3, 1, CV_64F);
		measured_eulers = TransformationHelper::rot2euler(rotation_measured);

		// Set measurement to predict
		measurements->at<double>(0) = translation_measured.at<double>(0); // x
		measurements->at<double>(1) = translation_measured.at<double>(1); // y
		measurements->at<double>(2) = translation_measured.at<double>(2); // z
		measurements->at<double>(3) = measured_eulers.at<double>(0);      // roll
		measurements->at<double>(4) = measured_eulers.at<double>(1);      // pitch
		measurements->at<double>(5) = measured_eulers.at<double>(2);      // yaw
	}
private:
	void _init(){
		m_VideoCapture.open(0);
		Sleep(3000);

		/*if (m_bVisualize){
			cvNamedWindow("Image View", 1);
			}*/

		m_SensorTimer.async_wait(strand_.wrap(boost::bind(&Localization::SensorDataProcess, this)));
		m_RobotTimer.async_wait(strand_.wrap(boost::bind(&Localization::JointDataReceive, this)));
		m_PoseTimer.async_wait(strand_.wrap(boost::bind(&Localization::PublishTransform, this)));
		m_TdmTimer.async_wait(strand_.wrap(boost::bind(&Localization::LocalizationRespond, this)));

		//m_poseFilter.initialize(Transform(), PosixTime(boost::posix_time::microsec_clock::local_time()));
#ifdef USE_PARTICLE_FILTER
		m_ParticleFilter.Init();
#endif

		m_SensorThread = boost::thread(&Localization::SensorDataProcessThread, this);

		initKalmanFilter(m_KalmanFilter, m_nStates, m_nMeasurements, m_nInputs, m_dt);    // init function
		m_Measurements = boost::shared_ptr<cv::Mat>(new cv::Mat(m_nMeasurements, 1, CV_64F));
		m_Measurements->setTo(cv::Scalar(0));
		m_bGoodMeasurements = false;
		m_nMeasuredCount = 0;
	}
private:
	boost::thread m_SensorThread;
	volatile bool m_SensorThreadQuit;

	boost::asio::strand strand_;
	boost::asio::deadline_timer m_SensorTimer;
	boost::asio::deadline_timer m_RobotTimer;
	boost::asio::deadline_timer m_PoseTimer;
	boost::asio::deadline_timer m_TdmTimer;

	int m_nSensorCycle;
	int m_nRobotCycle;
	int m_nPoseCycle;
	int m_nTdmCycle;

	bool m_bVisualize;
	Indriya::Core::Msgs::NodePtr m_pNode;
	RobotStateListenerPtr m_pRobotStateListenerPtr;
	TorsoPosePublisherPtr m_pTorsoPosePublisherPtr;
	LocalizationResponderPtr m_pLocalizationResponderPtr;
	MarkerDetection2Ptr m_pMarkerDetectionPtr;
	RobotPoseInfoPtr m_pRobotPoseInfoPtr;
	KinectVideoCapture m_VideoCapture;
	//TorsoPoseFilter m_poseFilter;

	Transform m_prevLocalizationTransform;
	//////////////////////////////////////////////////////////////////////
	cv::KalmanFilter m_KalmanFilter;
	const int m_nStates = 18;            // the number of states
	const int m_nMeasurements = 6;       // the number of measured states
	const int m_nInputs = 0;             // the number of control actions
	const double m_dt = 0.08;             // time between measurements (1/FPS)
	bool m_bGoodMeasurements;			 // Flag to indicate if the measurements are good
	boost::shared_ptr<cv::Mat> m_Measurements;
	int m_nMeasuredCount;
	//////////////////////////////////////////////////////////////////////
	MedianFilter m_MedianFilter;
#ifdef USE_PARTICLE_FILTER
	MarkerParticleFilter m_ParticleFilter;
#endif
	//MarkerDetectionKinectPtr m_pMarkerDetectionKinectPtr;
};

#endif