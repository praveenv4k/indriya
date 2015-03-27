#ifndef __ROBOT_STATE_LISTENER_H__
#define __ROBOT_STATE_LISTENER_H__

#include <vector>
#include <cstring>
#include <sstream>

//#include <boost/thread/thread.hpp>
//#include <boost/bind.hpp>
#include <boost/atomic.hpp>
#include <boost\shared_ptr.hpp>

#include "experimot\msgs\MessageTypes.h"
#include <zmq.hpp>
#include <zhelpers.hpp>
#include "RobotPoseInfo.h"

typedef boost::shared_ptr<zmq::context_t> ZmqContextPtr;
typedef boost::shared_ptr<zmq::socket_t> ZmqSocketPtr;
typedef boost::shared_ptr<zmq::message_t> ZmqMessagePtr;

class RobotStateListener{
public:
	//  Prepare our context and subscriber
	RobotStateListener(std::string& protocol, std::string& ip, int port, std::string& subscribeTo) :m_strSubsribeTo(subscribeTo) {
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		std::stringstream ss;
		ss << protocol << "://" << ip << ":" << port;
		m_strAddr = ss.str();
		m_pSocket->connect(m_strAddr.c_str());
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	void Listen(RobotPoseInfoPtr pInfo, boost::atomic<bool>& done){
		if (!!pInfo){
			std::cout << "Robotposeinfo NULL " << std::endl;
			return;
		}
		while (!done) {
			zmq::message_t address;
			m_pSocket->recv(&address);

			zmq::message_t data;
			m_pSocket->recv(&data);

			{
				experimot::msgs::JointValueVector jVector;
				if (jVector.ParseFromArray(data.data(), data.size())){
					std::vector<double> jointValues;
					jointValues.resize(jVector.jointvalues_size());
					for (google::protobuf::int32 i = 0; i < jVector.jointvalues_size(); i++){
						const experimot::msgs::JointValue& jVal = jVector.jointvalues(i);
						jointValues[jVal.id()] = jVal.value();
					}
					{
						RobotPoseInfoMutex::scoped_lock lock(pInfo->GetMutex());
						pInfo->SetJointValueVector(jointValues);
					}
				}

			}
		}
	}
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
	std::string m_strAddr;
};

#endif