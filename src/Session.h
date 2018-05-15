#if !defined(_Session_h_)
#define _Session_h_

#include <asio.hpp>

#include "Message.h"
#include "Client.h"
#include "Session.h"
#include "Context.h"


namespace SmartCache
{

using asio::ip::tcp;

class Session
: public Client, public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, Context& room)
	: 	socket_(std::move(socket)),
		room_(room)
	{
	}

	void
	start()
	{
		room_.join(shared_from_this());
		do_read_header();
	}

	void
	deliver( const Message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress) {
			do_write();
		}
	}
private:
	void
	do_read_header()
	{

		auto self(shared_from_this());
		asio::async_read(
			socket_,
			asio::buffer(read_msg_.data(), Message::header_length),
			[this, self](std::error_code ec, std::size_t )
			{
				if (!ec && read_msg_.decodeHeader()) {
					do_read_body();
				} else {
					room_.leave(shared_from_this());
				}
			}
		);

	}

	void
	do_read_body()
	{

		auto self(shared_from_this());
		asio::async_read(
			socket_,
			asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this, self](std::error_code ec, std::size_t )
			{
				if (!ec) {
					room_.deliver(read_msg_);
					do_read_header();
				} else {
					room_.leave(shared_from_this());
				}
			}
		);

	}

	void
	do_write()
	{

		auto self(shared_from_this());
		asio:async_write(
			socket_,
			asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
			[this, self](std::error_code ec, std::size_t  )
			{
				if (!ec) {
					write_msgs_.pop_front();
					if (!write_msgs_.empty()) {
						do_write();
					}
				} else {
					room_.leave(shared_from_this());
				}
			}
		);

	}

	tcp::socket socket_;
	Context& room_;
	Message read_msg_;
	Message::Queue write_msgs_;
};

} // Namespace SmartCache

#endif

