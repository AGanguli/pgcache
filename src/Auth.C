#include "Auth.h"
#include <boost/algorithm/string.hpp>

namespace SmartCache
{

namespace Auth
{

Type
stringToAuthType(const std::string& s)
{
	if (boost::iequals(s, "any")) 		return Type::ANY;
	if (boost::iequals(s, "trust"))		return Type::TRUST;
	if (boost::iequals(s, "ok"))		return Type::OK;
	if (boost::iequals(s, "krb"))		return Type::KRB;
	if (boost::iequals(s, "plain"))		return Type::PLAIN;
	if (boost::iequals(s, "crypt"))		return Type::CRYPT;
	if (boost::iequals(s, "md5"))		return Type::MD5;
	if (boost::iequals(s, "creds"))		return Type::CREDS;
	if (boost::iequals(s, "cert"))		return Type::CERT;
	if (boost::iequals(s, "peer"))		return Type::PEER;
	if (boost::iequals(s, "hba"))		return Type::HBA;
	if (boost::iequals(s, "reject"))	return Type::REJECT;
	if (boost::iequals(s, "pam"))		return Type::PAM;
	return Type::INVALID;
}

} // namespace Auth

} // namespace SmartCache
