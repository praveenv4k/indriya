#ifndef __MESSAGE_SUBSCRIBER_BASE_H__
#define __MESSAGE_SUBSCRIBER_BASE_H__

#include <Indriya\Common\Common.h>
#include "Indriya\Common\CallbackBase.h"

using namespace std;

template <typename T>
class MessageSubscriber :public CallbackBase
{
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	uint m_nPort;
	std::string m_strHost;
	std::string m_strTopic;
	std::string m_strAddr;
	volatile bool m_bStopThread;
	bool m_bThreadStarted;
	boost::thread m_SubscriberThread;
	int m_nPeriod;
	int m_nTimeout;
	void InitZmq()
	{
		if (m_pContext == 0)
		{
			m_pContext = ZmqContextPtr(new zmq::context_t(1));
			m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));

			m_pSocket->connect(m_strAddr.c_str());
			m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strTopic.c_str(), m_strTopic.size());
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

	void RunThread(){
		while (!m_bStopThread){
			zmq::message_t address;
			m_pSocket->recv(&address);
			zmq::message_t data;
			m_pSocket->recv(&data);
			T msg;
			if (msg.ParseFromArray(data.data(), data.size())){
				if (signal_message->num_slots() > 0) {
					signal_message->operator()(msg);
				}
			}
		}
	}
public:
	typedef void (signal_indriya_message)(const T&);
	MessageSubscriber(string host, uint port, string topic) :m_bStopThread(false), m_bThreadStarted(false), m_nPeriod(100), m_nTimeout(100)
	{
		m_strHost = host;
		m_nPort = port;
		m_strTopic = topic;

		std::stringstream ss;
		ss << m_strHost << ":" << m_nPort;

		m_strAddr = ss.str();
	}

	~MessageSubscriber(){
		Stop();
		disconnect_all_slots<signal_indriya_message>();
	}

	void Initialize()
	{
		InitZmq();
		signal_message = createSignal<signal_indriya_message>();
	}

	void Terminate()
	{
		TerminateZmq();
	}

	virtual void Run(int periodMilliSeconds, int timeout){
		m_nPeriod = periodMilliSeconds;
		m_nTimeout = timeout;
		if (!m_bThreadStarted){
			m_SubscriberThread = boost::thread(&MessageSubscriber::RunThread, this);
			m_bThreadStarted = true;
		}
	}

	virtual void Stop(){
		if (m_bThreadStarted){
			m_bStopThread = true;
			if (m_SubscriberThread.joinable()){
				m_SubscriberThread.join();
			}
			m_bThreadStarted = false;
		}
	}

	virtual void WaitCompletion(){
		if (m_bThreadStarted){
			if (m_SubscriberThread.joinable()){
				m_SubscriberThread.join();
			}
		}
	}

protected:
	boost::signals2::signal<signal_indriya_message>* signal_message;
};

#endif