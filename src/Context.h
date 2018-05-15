#if !defined(_Context_h_)
#define _Context_h_

#include <set>
#include "Client.h"
#include "Message.h"

using asio::ip::tcp;

std::string
make_daytime_string()
{
	using namespace std;
	time_t now = time(0);
	return ctime(&now);
}

namespace SmartCache
{

class Context
{
public:
	void
	join(Client::Ptr participant)
	{
		participants_.insert(participant);
		for (auto msg: recent_msgs_) {
			participant->deliver(msg);
		}
	}

	void
	leave(Client::Ptr participant)
	{
		participants_.erase(participant);
	}

	void
	deliver(const Message& msg)
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs) {
			recent_msgs_.pop_front();
		}
		for (auto participant: participants_) {
			participant->deliver(msg);
		}
	}
private:
	std::set<Client::Ptr> participants_;
	enum { max_recent_msgs = 100 };
	Message::Queue recent_msgs_;
};

} // Namespace SmartCache

#endif // !defined(_Context_h_)

