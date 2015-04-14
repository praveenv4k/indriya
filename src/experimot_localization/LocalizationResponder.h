#ifndef __LOCALIZATION_RESPONDER_H__
#define __LOCALIZATION_RESPONDER_H__

#include "RobotPoseInfo.h"
#include "TransformationHelper.h"

class LocalizationResponder;

typedef boost::shared_ptr<LocalizationResponder> LocalizationResponderPtr;

class LocalizationResponder{
public:
	
	LocalizationResponder(const std::string& host, int port, int timeoutMilliSec) : m_nTimeOut(timeoutMilliSec) {
		std::stringstream ss;
		ss << host << ":" << port;
		m_strAddr = ss.str();
		m_bInit = false;
		_init();
	}

	~LocalizationResponder(){
		if (m_pSocket != 0){
			m_pSocket->close();
		}
	}

	void Respond(Transform& torsoTransform){
		try{
			if (m_pSocket != 0 && m_pSocket->connected()){
				//std::cout << "Receiving request : " << std::endl;
				zmq::message_t msg;
				if (m_pSocket->recv(&msg)){
					std::string req(static_cast<char*>(msg.data()), msg.size());
					//std::cout << "Received request : " << req << std::endl;
					std::string str;
					toJson(torsoTransform, str);
					s_send(*m_pSocket, str);
				}
			}
		}
		catch (std::exception& ex){
			std::cout << "Publish Transform: " << ex.what() << std::endl;
		}
	}

private:
	void _init(){
		if (!m_bInit){
			m_pContext = ZmqContextPtr(new zmq::context_t(1));
			m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_REP));
			std::stringstream ss;
			m_pSocket->bind(m_strAddr.c_str());
			int to = m_nTimeOut;
			m_pSocket->setsockopt(ZMQ_RCVTIMEO, &to, sizeof(to));
			m_bInit = true;
		}
	}

	void toJson(const Transform& tfm, string& str){
		stringstream ss;
		ss << "{ \"pos\" : {\"x\":" << tfm.trans.x << ", \"y\" :" << tfm.trans.y << ", \"z\" :" << tfm.trans.z << "}, \"orient\" : {\"w\":"
			<< tfm.rot[0] << ", \"x\":" << tfm.rot[1] << ", \"y\" :" << tfm.rot[2] << ", \"z\" :" << tfm.rot[3] << "} }";
		str = ss.str();
	}

private:
	int m_nTimeOut;
	bool m_bInit;
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strAddr;
};

#endif