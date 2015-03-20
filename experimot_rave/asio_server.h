#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace pt = boost::posix_time;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_connection(io_service));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		boost::asio::async_write(socket_, boost::asio::buffer(message_),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp_connection(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}

	tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 13))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
			start_accept();
		}
	}

	tcp::acceptor acceptor_;
};

class server_t {
public:
	server_t(boost::asio::io_service & ios,std::string& uri)
		: pimpl_(std::make_shared<impl>())
		, _uri(uri)
		, frontend_(azmq::actor::spawn(ios, run, pimpl_))
	{
		_init = false;
	}

	void ping() {

		frontend_.send(boost::asio::buffer("PING"));
		frontend_.async_receive(boost::asio::buffer(buf_), [this](boost::system::error_code const& ec, size_t bytes_transferred) {
			if (ec)
				return;
			if (boost::string_ref(buf_.data(), bytes_transferred - 1) == "PONG")
				pimpl_->pongs_++;
		});
	}

	friend std::ostream & operator<<(std::ostream & stm, server_t const & that) {
		return stm << "pings=" << that.pimpl_->pings_
			<< ", pongs=" << that.pimpl_->pongs_;
	}

private:
	// for such a simple example, this is overkill, but is a useful pattern for 
	// real servers that need to maintain state
	struct impl {
		std::atomic<unsigned long> pings_;
		std::atomic<unsigned long> pongs_;
		std::array<char, 256> buf_;

		impl()
			: pings_(0)
			, pongs_(0)
		{ }
	};
	using ptr = std::shared_ptr<impl>;
	ptr pimpl_;

	// we schedule async receives for the backend socket here
	static void do_receive(azmq::socket & backend, std::weak_ptr<impl> pimpl) {
		if (auto p = pimpl.lock()) {
			backend.async_receive(boost::asio::buffer(p->buf_), [&backend, pimpl](boost::system::error_code const& ec, size_t bytes_transferred) {
				if (ec)
					return; // exit on error

				if (auto p = pimpl.lock()) {
					if (boost::string_ref(p->buf_.data(), bytes_transferred - 1) != "PING")
						return; // exit if not PING
					p->pings_++;
					backend.send(boost::asio::buffer("PONG"));

					// schedule another receive
					do_receive(backend, pimpl);
				}
			});
		}
	}

	// This is the function run by the background thread
	static void run(azmq::socket & backend, ptr pimpl) {
		do_receive(backend, pimpl);
		backend.get_io_service().run();
	}

	azmq::socket frontend_;
	std::array<char, 256> buf_;
	std::string _uri;
	bool _init;
};

class server2_t {
public:
	server2_t(boost::asio::io_service & ios, std::string& uri)
		: _socket(ios, ZMQ_ROUTER), _uri(uri)
	{
		_socket.bind(_uri);
	}

private:

	// This is the function run by the background thread
	void run(azmq::socket & backend) {
		if (!_init){

		}
		//do_receive(backend);
		backend.get_io_service().run();
	}

	azmq::socket _socket;
	std::array<char, 256> buf_;
	std::string _uri;
	bool _init;
};

class client_t {
public:
	client_t(boost::asio::io_service & ios, std::string& uri)
		: _socket(ios, ZMQ_DEALER), _uri(uri)
	{
		_socket.connect(uri);
	}

	void ping() {
		_socket.send(boost::asio::buffer("PING"));
		_socket.async_receive(boost::asio::buffer(buf_), [this](boost::system::error_code const& ec, size_t bytes_transferred) {
			if (ec)
				return;
			if (boost::string_ref(buf_.data(), bytes_transferred - 1) == "PONG")
			{
				std::cout << "Received response from server" << std::endl;
			}
		});
	}

private:
	azmq::socket _socket;
	std::array<char, 1024> buf_;
	std::string _uri;
};

//class zserver {
//public:
//	zserver(boost::asio::io_service & ios, std::string& uri)
//		: pimpl_(std::make_shared<impl>())
//		, _uri(uri)
//		, _socket(azmq::actor::spawn(ios, run, pimpl_))
//	{
//		auto& t = boost::asio::use_service<azmq::detail::socket_service>(ios);
//		//azmq::detail::socket_service::implementation_type
//		//t.bind()
//		_socket.bind(_uri);
//	}
//
//	void ping() {
//
//		frontend_.send(boost::asio::buffer("PING"));
//		frontend_.async_receive(boost::asio::buffer(buf_), [this](boost::system::error_code const& ec, size_t bytes_transferred) {
//			if (ec)
//				return;
//			if (boost::string_ref(buf_.data(), bytes_transferred - 1) == "PONG")
//				pimpl_->pongs_++;
//		});
//	}
//
//	friend std::ostream & operator<<(std::ostream & stm, server_t const & that) {
//		return stm << "pings=" << that.pimpl_->pings_
//			<< ", pongs=" << that.pimpl_->pongs_;
//	}
//
//private:
//	// for such a simple example, this is overkill, but is a useful pattern for 
//	// real servers that need to maintain state
//	struct impl {
//		std::atomic<unsigned long> pings_;
//		std::atomic<unsigned long> pongs_;
//		std::array<char, 256> buf_;
//
//		impl()
//			: pings_(0)
//			, pongs_(0)
//		{ }
//	};
//	using ptr = std::shared_ptr<impl>;
//	ptr pimpl_;
//
//	// we schedule async receives for the backend socket here
//	static void do_receive(azmq::socket & backend, std::weak_ptr<impl> pimpl) {
//		if (auto p = pimpl.lock()) {
//			backend.async_receive(boost::asio::buffer(p->buf_), [&backend, pimpl](boost::system::error_code const& ec, size_t bytes_transferred) {
//				if (ec)
//					return; // exit on error
//
//				if (auto p = pimpl.lock()) {
//					if (boost::string_ref(p->buf_.data(), bytes_transferred - 1) != "PING")
//						return; // exit if not PING
//					p->pings_++;
//					backend.send(boost::asio::buffer("PONG"));
//
//					// schedule another receive
//					do_receive(backend, pimpl);
//				}
//			});
//		}
//	}
//
//	// This is the function run by the background thread
//	static void run(azmq::socket & backend, ptr pimpl) {
//		do_receive(backend, pimpl);
//		backend.get_io_service().run();
//	}
//
//	azmq::socket _socket;
//	std::array<char, 256> buf_;
//	std::string _uri;
//	bool _init;
//};