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

#include "experimot\msgs\MessageTypes.h"

typedef boost::shared_ptr<zmq::context_t> ZmqContextPtr;
typedef boost::shared_ptr<zmq::socket_t> ZmqSocketPtr;
typedef boost::shared_ptr<zmq::message_t> ZmqMessagePtr;

class RobotStateListener;

typedef boost::shared_ptr<RobotStateListener> RobotStateListenerPtr;

class RobotStateListener{
public:
	//  Prepare our context and subscriber
	RobotStateListener(std::string& protocol, std::string& ip, int port, int timeoutMilliSec, std::string& subscribeTo) :m_strSubsribeTo(subscribeTo) {
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		std::stringstream ss;
		ss << protocol << "://" << ip << ":" << port;
		m_strAddr = ss.str();
		m_pSocket->connect(m_strAddr.c_str());
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
		int to = timeoutMilliSec;
		m_pSocket->setsockopt(ZMQ_RCVTIMEO, &to, sizeof(to));
	}

	bool Listen(std::vector<double>& jointValues){
		bool ret = false;
		zmq::message_t address;
		if (m_pSocket->recv(&address)){
			zmq::message_t data;
			if (m_pSocket->recv(&data))
			{
				experimot::msgs::JointValueVector jVector;
				if (jVector.ParseFromArray(data.data(), data.size())){
					jointValues.resize(jVector.jointvalues_size());
					for (google::protobuf::int32 i = 0; i < jVector.jointvalues_size(); i++){
						const experimot::msgs::JointValue& jVal = jVector.jointvalues(i);
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
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
	std::string m_strAddr;
};

#endif