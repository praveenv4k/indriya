#ifndef __PARAMETER_CLIENT_H__
#define __PARAMETER_CLIENT_H__

#include <vector>
#include <cstring>
#include <sstream>

#include <boost/atomic.hpp>
#include <boost\shared_ptr.hpp>

#include "Common.h"
#include "experimot\msgs\MessageTypes.h"

class ParameterClient{
public:
	static bool Get(std::string& addr, std::string& req, experimot::msgs::NodePtr& nodeInfo, int timeout)
	{
		bool ret = false;
		try{
			zmq::context_t ctx(1);
			zmq::socket_t socket(ctx, ZMQ_REQ);
			socket.connect(addr.c_str());
			int to = timeout;
			socket.setsockopt(ZMQ_RCVTIMEO, &to, sizeof(to));
			if (socket.connected()){
				std::cout << "Sending request " << std::endl;
				if (s_send(socket, req)){
					zmq::message_t data;
					if (socket.recv(&data) && nodeInfo != 0)
					{
						if (nodeInfo->ParseFromArray(data.data(), data.size())){
							ret = true;
						}

					}
				}
			}
		}
		catch (std::exception& ex){
			std::cout << "Error retrieving params : " << ex.what() << std::endl;
			ret = false;
		}
		return ret;
	}
};

#endif