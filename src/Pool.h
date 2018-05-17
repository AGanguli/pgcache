#if !defined(_Pool_h_)
#define _Pool_h_

#include <string>

namespace SmartCache
{
namespace Pool
{
	enum class Mode {
		INVALID 	= -1,
		SESSION		= 0,
		TRANSACTION 	= 1,
		STATEMENT	= 2
	};
	Mode stringToPoolMode(const std::string& s);
}

} // Namespace CacheServer

#endif
