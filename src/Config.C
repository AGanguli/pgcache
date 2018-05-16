#include "Config.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;

namespace SmartCache
{

static Config::Ptr current_;

void
Config::load(const std::string& filename)
{
	Config::Ptr config(new Config());
	pt::ptree tree;
	pt::read_ini(filename, tree);

	config->daemon 			= tree.get			("daemon", true);
	config->job_name		= tree.get<std::string>		("job_name", "smartcache");
	config->logfile			= tree.get<std::string>		("logfile", "");
	config->pidfile			= tree.get<std::string>		("pidfile", "");
	config->username 		= tree.get<std::string>		("username", "");
	config->listen_addr 		= tree.get<std::string> 	("listen_addr", "");
	config->listen_port		= tree.get			("listen_port", 6432);
	config->listen_backlog		= tree.get			("listen_backlog", 128);
	config->unix_socket_dir		= tree.get<std::string>		("unix_socket_dir", "/tmp");
	config->unix_socket_mode	= tree.get<std::string>		("unix_socket_mode", "0777");
	config->unix_socket_group	= tree.get<std::string>		("unix_socket_group", "");

	config->auth_type		= Auth::stringToAuthType(tree.get<std::string>         ("auth_type", "md5"));
	
	current_ = config;
}

Config::Ptr
Config::current()
{
	return current_;
}

void
Config::save(const std::string& filename)
{
	pt::ptree tree;
	tree.put("daemon", daemon);
	pt::write_ini(filename, tree);
}

} // namespace SmartCache

