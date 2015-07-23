#ifndef __ROBOT_STATE_LISTENER_H__
#define __ROBOT_STATE_LISTENER_H__

#include <vector>
#include <cstring>
#include <sstream>

#include <boost/atomic.hpp>
#include <boost\shared_ptr.hpp>

#include <zmq.hpp>
#include <zhelpers.hpp>
#include "RobotPoseInfo.h"

#include "Indriya\Msgs\MessageTypes.h"

class RobotStateListener;

typedef boost::shared_ptr<RobotStateListener> RobotStateListenerPtr;

class RobotStateListener{
public:
	//  Prepare our context and subscriber
	RobotStateListener(const std::string& protocol, const std::string& ip, int port, int timeoutMilliSec, const std::string& subscribeTo) :m_strSubsribeTo(subscribeTo), m_nTimeOut(timeoutMilliSec){
		std::stringstream ss;
		ss << protocol << "://" << ip << ":" << port;
		m_strAddr = ss.str();
		m_bInit = false;
		_init();
	}

	RobotStateListener(const std::string& host, int port, int timeoutMilliSec, const std::string& subscribeTo) :m_strSubsribeTo(subscribeTo), m_nTimeOut(timeoutMilliSec) {
		std::stringstream ss;
		ss << host << ":" << port;
		m_strAddr = ss.str();
		m_bInit = false;
		_init();
	}

	bool Listen(std::vector<double>& jointValues){
		bool ret = false;
		
		if (!m_bInit){
			return ret;
		}
		
		zmq::message_t address;
		if (m_pSocket->recv(&address)){
			zmq::message_t data;
			if (m_pSocket->recv(&data))
			{
				Indriya::Core::Msgs::JointValueVector jVector;
				if (jVector.ParseFromArray(data.data(), data.size())){
					jointValues.resize(jVector.jointvalues_size());
					for (google::protobuf::int32 i = 0; i < jVector.jointvalues_size(); i++){
						const Indriya::Core::Msgs::JointValue& jVal = jVector.jointvalues(i);
						jointValues[jVal.id()] = jVal.value();
					}
					//jVector.PrintDebugString();
					ret = true;
				}

			}
		}
		return ret;
	}

private:
	void _init(){
		if (!m_bInit){
			m_pContext = ZmqContextPtr(new zmq::context_t(1));
			m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
			std::stringstream ss;
			m_pSocket->connect(m_strAddr.c_str());
			m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
			int to = m_nTimeOut;
			m_pSocket->setsockopt(ZMQ_RCVTIMEO, &to, sizeof(to));
			m_bInit = true;
		}
	}

private:
	bool m_bInit;
	int m_nTimeOut;
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
	std::string m_strAddr;
};

#endif