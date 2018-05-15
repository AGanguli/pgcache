#if !defined(_Server_h_)
#define _Server_h_

#include <asio.hpp>
#include "Session.h"


namespace SmartCache
{

using asio::ip::tcp;

class Server
{
public:
	Server(asio::io_service& io_service, const tcp::endpoint& endpoint)
	:	acceptor_(io_service, endpoint),
		socket_(io_service)
	{
		do_accept();
	}

private:
	void
	do_accept()
	{
		acceptor_.async_accept(
			socket_,
			[this](std::error_code ec)
			{
				if (!ec) {
					std::make_shared<Session>(std::move(socket_), room_)->start();
				}
				do_accept();
			}
		);
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	Context room_;
};

} // Namespace SmartCache

#endif


