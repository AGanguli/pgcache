#include "SSL.h"
#include <boost/algorithm/string.hpp>

namespace SmartCache
{

namespace SSL
{

Mode
stringToSSLMode(const std::string& s)
{
	if (boost::iequals(s, "disable")) 		return Mode::DISABLED;
	if (boost::iequals(s, "allow"))			return Mode::ALLOW;
	if (boost::iequals(s, "prefer"))		return Mode::PREFER;
	if (boost::iequals(s, "require"))		return Mode::REQUIRE;
	if (boost::iequals(s, "verify-ca"))		return Mode::VERIFY_CA;
	if (boost::iequals(s, "verify-full"))		return Mode::VERIFY_FULL;
	return Mode::INVALID;
}

} // namespace SSL

} // namespace SmartCache
