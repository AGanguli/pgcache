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
	config->username 		= tree.get<std::string>		("user", "");
	config->listen_addr 		= tree.get<std::string> 	("listen_addr", "");
	config->listen_port		= tree.get			("listen_port", 6432);
	config->listen_backlog		= tree.get			("listen_backlog", 128);
	config->unix_socket_dir		= tree.get<std::string>		("unix_socket_dir", "/tmp");
	config->unix_socket_mode	= tree.get<std::string>		("unix_socket_mode", "0777");
	config->unix_socket_group	= tree.get<std::string>		("unix_socket_group", "");
	config->auth_type		= Auth::stringToAuthType(tree.get<std::string>("auth_type", "md5"));
	config->auth_file		= tree.get<std::string>		("auth_file", "");
	config->auth_hba_file		= tree.get<std::string>		("auth_hba_file", "");
	config->auth_user		= tree.get<std::string>         ("auth_user", "");
	config->auth_query		= tree.get<std::string>         ("auth_query", "SELECT usename, passwd FROM pg_shadow WHERE usename=$1");
	config->pool_mode		= Pool::stringToPoolMode(tree.get<std::string>("pool_mode", "session"));
	config->max_client_conn		= tree.get			("max_client_conn", 100);
	config->default_pool_size	= tree.get			("default_pool_size", 20);
	config->min_pool_size		= tree.get			("min_pool_size", 0);
	config->reserve_pool_size	= tree.get			("reserve_pool_size", 0);
	config->reserve_pool_timeout	= std::chrono::milliseconds(tree.get("reserve_pool_timeout", 5));
	config->max_db_connections	= tree.get			("max_db_connections", 0);
	config->max_user_connections	= tree.get			("max_user_connections", 0);
	config->syslog			= tree.get			("syslog", 0);
	config->syslog_facility		= tree.get<std::string>		("syslog_facility", "daemon");
	config->syslog_ident		= tree.get<std::string>		("syslog_ident", "smartcache");
	config->autodb_idle_timeout	= std::chrono::milliseconds(tree.get("autodb_idle_timeout", 0));
	config->server_reset_query	= tree.get<std::string>		("server_reset_query", "DISCARD ALL");
	config->server_reset_query_always	= tree.get		("server_reset_query_always", false);
	config->server_check_query	= tree.get<std::string>		("server_check_query", "SELECT 1");	
	config->server_check_delay	= std::chrono::milliseconds(tree.get("server_check_delay", 30));
	config->query_timeout		= std::chrono::milliseconds(tree.get("query_timeout", 0));
	config->query_wait_timeout	= std::chrono::milliseconds(tree.get("query_wait_timeout", 120));
	config->client_idle_timeout	= std::chrono::milliseconds(tree.get("client_idle_timeout", 0));
	config->idle_transaction_timeout = std::chrono::milliseconds(tree.get("idle_transaction_timeout", 0));
	config->server_lifetime		= std::chrono::milliseconds(tree.get("server_lifetime", 3600));
	config->server_idle_timeout	= std::chrono::milliseconds(tree.get("server_idle_timeout", 600));
	config->server_connect_timeout	= std::chrono::milliseconds(tree.get("server_connect_timeout", 15));
	config->server_login_retry	= std::chrono::milliseconds(tree.get("server_login_retry", 15));
	config->server_round_robin	= tree.get			("server_round_robin", false);
	config->suspend_timeout		= std::chrono::milliseconds(tree.get("suspend_timeout", 10));
	config->ignore_startup_parameters	= tree.get<std::string>	("ignore_startup_parameters", "");
	config->disable_pqexec		= tree.get			("disable_pqexec", false);
	config->dns_max_ttl		= std::chrono::milliseconds(tree.get("dns_max_ttl", 15));
	config->dns_nxdomain_ttl	= std::chrono::milliseconds(tree.get("dns_nxdomain_ttl", 15));
	config->dns_zone_check_period	= std::chrono::milliseconds(tree.get("dns_zone_check_period", 0));
	
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

