#if !defined(_SSL_h_)
#define _SSL_h_

#include <string>

namespace SmartCache
{
namespace SSL 
{
	enum class Mode {
		INVALID 	= -1,
		DISABLED	= 0,
		ALLOW 		= 1,
		PREFER		= 2,
		REQUIRE		= 3,
		VERIFY_CA	= 4,
		VERIFY_FULL	= 5
	};
	Mode stringToSSLMode(const std::string& s);
}

} // Namespace CacheServer

#endif
