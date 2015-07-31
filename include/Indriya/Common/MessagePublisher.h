#ifndef __MESSAGE_PUBLISHER_BASE_H__
#define __MESSAGE_PUBLISHER_BASE_H__

#include <Indriya\Common\Common.h>

template <typename T>
class MessagePublisher
{
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	uint m_nPort;
	std::string m_strHost;
	std::string m_strTopic;
	std::string m_strAddr;

	void InitZmq()
	{
		if (m_pContext == 0)
		{
			m_pContext = ZmqContextPtr(new zmq::context_t(1));
			m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_PUB));


			m_pSocket->bind(m_strAddr.c_str());
		}
	}

	void TerminateZmq()
	{
		if (m_pSocket != null)
		{
			m_pSocket->close();
			if (m_pContext != null)
			{
				m_pContext->close();
			}
		}
	}

public:
	MessagePublisher(string host, uint port, string topic)
	{
		m_strHost = host;
		m_nPort = port;
		m_strTopic = topic;

		std::stringstream ss;
		ss << m_strHost << ":" << m_nPort;

		m_strAddr = ss.str();
	}


	void Initialize()
	{
		InitZmq();
	}

	void Terminate()
	{
		TerminateZmq();
	}

	virtual void Update(T& msg)
	{
		Publish(msg);
	}

protected:
	virtual bool IsValid(T& msg)
	{
		return true;
	}

	virtual void Publish(T& msg){
		if (m_pSocket != 0 && IsValid(msg))
		{
			std::string str;
			msg.SerializeToString(&str);
			if (s_sendmore(*m_pSocket, m_strTopic)){
				s_send(*m_pSocket, str);
			}
		}
	}
};

#endif