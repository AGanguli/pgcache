#if !defined(_Auth_h_)
#define _Auth_h_

#include <string>

namespace SmartCache
{
namespace Auth
{
	enum class Type {
		INVALID	= -2,
		ANY 	= -1,
		TRUST	= 0,
		OK	= 1,
		KRB	= 2,
		PLAIN	= 3,
		CRYPT	= 4,
		MD5	= 5,
		CREDS	= 6,
		CERT	= 7,
		PEER	= 8,
		HBA	= 9,
		REJECT	= 10,
		PAM	= 11
	};
	Type stringToAuthType(const std::string& s);
}

} // Namespace CacheServer

#endif
