#ifndef __TORSO_POSE_PUBLISHER_H__
#define __TORSO_POSE_PUBLISHER_H__

#include "RobotPoseInfo.h"
#include "TransformationHelper.h"

class TorsoPosePublisher;

typedef boost::shared_ptr<TorsoPosePublisher> TorsoPosePublisherPtr;

class TorsoPosePublisher{
public:
	TorsoPosePublisher(std::string& protocol, std::string& ip, int port, int timeoutMilliSec, std::string& publisherId) :m_strPublisherId(publisherId){
		//  Prepare our context and publisher
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_PUB));
		std::stringstream ss;
		ss << protocol << "://" << ip << ":" << port;
		m_strAddr = ss.str();
		m_pSocket->bind(m_strAddr.c_str());
		int to = timeoutMilliSec;
		m_pSocket->setsockopt(ZMQ_SNDTIMEO, &to, sizeof(to));
	}

	~TorsoPosePublisher(){
		m_pSocket->close();
	}

	void Publish(Transform& torsoTransform){
		experimot::msgs::Pose pose;
		TransformationHelper::RaveToProto(torsoTransform, pose);
		std::string str;
		pose.SerializeToString(&str);
		//pose.PrintDebugString();
		//std::cout << "Mat:  " << TransformMatrix(torsoTransform) << std::endl;
		//std::cout << "Publishing : ( " << pose.position().x() << ", " << pose.position().y() << ", " << pose.position().z() << " )" << std::endl;
		if (s_sendmore(*m_pSocket, m_strPublisherId)){
			s_send(*m_pSocket, str);
		}
	}

private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strPublisherId;
	std::string m_strAddr;
};

#endif