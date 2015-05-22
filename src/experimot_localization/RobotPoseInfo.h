#ifndef __ROBOT_POSE_INFO_H__
#define __ROBOT_POSE_INFO_H__

#include <boost\shared_ptr.hpp>
#include <openrave-core.h>

using namespace OpenRAVE;

#include "experimot\common\Common.h"
//#include <zmq.hpp>
//#include <zhelpers.hpp>
//
//typedef boost::shared_ptr<zmq::context_t> ZmqContextPtr;
//typedef boost::shared_ptr<zmq::socket_t> ZmqSocketPtr;
//typedef boost::shared_ptr<zmq::message_t> ZmqMessagePtr;

class RobotPoseInfo;

typedef boost::shared_ptr<RobotPoseInfo> RobotPoseInfoPtr;
typedef boost::recursive_try_mutex RobotPoseInfoMutex;
typedef std::map<int, Transform>::iterator TransformMapIterator;
typedef std::map<int, Transform>::const_iterator TransformMapConstIterator;

#define CALIB_FILE			"camera_calibration_kinect_1600.xml"
#define MARKER_SIZE			55
#define CUBE_SIZE			64
#define NEW_MARKER_ERROR	0.8
#define MARKER_TRACK_ERROR	0.2

#define FRONT_MARKER_ID		7
#define LEFT_MARKER_ID		0
#define RIGHT_MARKER_ID		13
#define REAR_MARKER_ID		10
#define TOP_MARKER_ID		14

#define FRONT_MARKER_FLIP_ID		3
#define LEFT_MARKER_FLIP_ID			0
#define RIGHT_MARKER_FLIP_ID		2
#define REAR_MARKER_FLIP_ID			1
#define TOP_MARKER_FLIP_ID			5

class RobotPoseInfo : public boost::enable_shared_from_this < RobotPoseInfo > {
public:
	RobotPoseInfo(){
	}
	virtual ~RobotPoseInfo(){
	}
	const Transform& GetMarkerTransform() const{
		return m_MarkerTransform;
	}
	bool GetMarkerTransform(int id, Transform& tf) const{
		TransformMapConstIterator it = m_MarkerTransforms.find(id);
		if (it != m_MarkerTransforms.end()){
			tf = it->second;
			return true;
		}
		return false;
	}
	bool SetMarkerTransform(int id, const Transform& tf){
		TransformMapIterator it = m_MarkerTransforms.find(id);
		if (it != m_MarkerTransforms.end()){
			it->second = tf;
			return true;
		}
		return false;
	}
	void SetMarkerTransform(const Transform& transform){
		m_MarkerTransform = transform;
		m_MarkerInit = true;
	}
	const std::vector<dReal>& GetJointValueVector() const{
		return m_JointValueVector;
	}
	void SetJointValueVector(const std::vector<dReal>& jointvals){
		m_JointValueVector = jointvals;
		m_JointValuesInit = true;
	}
	const Transform& GetTorsoTransform() const{
		return m_TorsoTransform;
	}
	void SetTorsoTransform(Transform& pose){
		m_TorsoTransform = pose;
		m_TorsoInit = true;
	}
	RobotPoseInfoMutex& GetMutex() {
		return _mutexRobotPoseInfo;
	}
	bool IsMarkerTransformInit() const { return m_MarkerInit; }
	bool IsJointValuesInit() const { return m_JointValuesInit; }
	bool IsTorsoTransformInit() const { return m_TorsoInit; }
private:
	Transform m_MarkerTransform;
	std::map<int,Transform> m_MarkerTransforms;
	std::vector<dReal> m_JointValueVector;
	Transform m_TorsoTransform;
	mutable RobotPoseInfoMutex _mutexRobotPoseInfo;          
	bool m_MarkerInit;
	bool m_JointValuesInit;
	bool m_TorsoInit;
};

#endif