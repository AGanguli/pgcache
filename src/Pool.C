#include "Pool.h"
#include <boost/algorithm/string.hpp>

namespace SmartCache
{

namespace Pool
{

Mode
stringToPoolMode(const std::string& s)
{
	if (boost::iequals(s, "session")) 		return Mode::SESSION;
	if (boost::iequals(s, "transaction"))		return Mode::TRANSACTION;
	if (boost::iequals(s, "statement"))		return Mode::STATEMENT;
	return Mode::INVALID;
}

} // namespace Pool

} // namespace SmartCache
