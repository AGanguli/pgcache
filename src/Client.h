#if !defined(_Client_h_)
#define _Client_h_

#include <memory>
#include "Message.h"

namespace SmartCache
{

class Client
{
public:
	typedef std::shared_ptr<Client> Ptr;

	virtual ~Client() {}
	virtual void deliver(const Message& msg) = 0;
};

} // Namespace SmartCache

#endif

