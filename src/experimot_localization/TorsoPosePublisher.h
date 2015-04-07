#ifndef __TORSO_POSE_PUBLISHER_H__
#define __TORSO_POSE_PUBLISHER_H__

#include "RobotPoseInfo.h"
#include "TransformationHelper.h"

class TorsoPosePublisher;

typedef boost::shared_ptr<TorsoPosePublisher> TorsoPosePublisherPtr;

class TorsoPosePublisher{
public:
	TorsoPosePublisher(const std::string& protocol, const std::string& ip, int port, int timeoutMilliSec, const std::string& publisherId) :m_strPublisherId(publisherId), m_nTimeOut(timeoutMilliSec) {
		//  Prepare our context and publisher
		std::stringstream ss;
		ss << protocol << "://" << ip << ":" << port;
		m_strAddr = ss.str();
		_init();
	}

	TorsoPosePublisher(const std::string& host, int port, int timeoutMilliSec, const std::string& publisherId) :m_strPublisherId(publisherId), m_nTimeOut(timeoutMilliSec) {
		std::stringstream ss;
		ss << host << ":" << port;
		m_strAddr = ss.str();
		_init();
	}

	~TorsoPosePublisher(){
		if (m_pSocket != 0){
			m_pSocket->close();
		}
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
	void _init(){
		if (!m_bInit){
			m_pContext = ZmqContextPtr(new zmq::context_t(1));
			m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_PUB));
			std::stringstream ss;
			m_pSocket->bind(m_strAddr.c_str());
			int to = m_nTimeOut;
			m_pSocket->setsockopt(ZMQ_SNDTIMEO, &to, sizeof(to));
			m_bInit = true;
		}
	}

private:
	int m_nTimeOut;
	bool m_bInit;
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strPublisherId;
	std::string m_strAddr;
};

#endif