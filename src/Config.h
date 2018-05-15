#if !defined(_Config_h_)
#define _Config_h_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

#include "Auth.h"

namespace SmartCache
{

namespace pt = boost::property_tree;

class Config
{
public:
	int daemon;
	int pause_mode;
	int shutdown;	
	int reboot;
	std::string username;
	std::string config_file;
	std::string listen_addr;
	int listen_port;
	int listen_backlog;
	std::string unix_socket_dir;
	int unix_socket_mode;
	std::string unix_socket_group;
	int pool_mode;
	int sbuf_len;
	int sbuf_loopcnt;
	int tcp_socket_buffer;
	int tcp_defer_accept;
	int tcp_keepalive;
	int tcp_keepidle;
	int tcp_keepintvl;
	AuthType auth_type;
	std::string auth_file;
	std::string auth_hba_file;
	std::string auth_user;
	std::string auth_query;
	int max_client_conn;
	int default_pool_size;
	int min_pool_size;
	int res_pool_size;
	usec_t cf_res_pool_timeout;
	int max_db_connectiosn;
	int max_user_connections;
	std::string server_reset_query;
	int server_reset_query_always;
	std::string server_check_query;
	usec_t server_check_delay;
	int server_round_robin;
	int disable_pqexec;
	usec_t dns_max_ttl;
	usec_t dns_nxdomain_ttl;
	usec_t dns_zone_check_period;
	unsigned int max_packet_size;
	std::string ignore_startup_params;
	std::string autodb_connstr;
	usec_t autodb_idle_timeout;
	usec_t cf_server_lifetime;
	usec_t cf_server_idle_timeout;
	usec_t cf_server_connect_timeout;
	usec_t cf_server_login_retry;
	usec_t cf_query_timeout;
	usec_t cf_query_wait_timeout;
	usec_t cf_client_idle_timeout;
	usec_t cf_client_login_timeout;
	usec_t cf_idle_transaction_timeout;
	usec_t cf_suspend_timeout;
	usec_t g_suspend_start;
	char *cf_pidfile;
	char *cf_jobname;
	char *cf_admin_users;
	char *cf_stats_users;
	int cf_stats_period;
	int cf_log_connections;
	int cf_log_disconnections;
	int cf_log_pooler_errors;
	int cf_application_name_add_host;
	int cf_client_tls_sslmode;
	char *cf_client_tls_protocols;
	char *cf_client_tls_ca_file;
	char *cf_client_tls_cert_file;
	char *cf_client_tls_key_file;
	char *cf_client_tls_ciphers;
	char *cf_client_tls_dheparams;
	char *cf_client_tls_ecdhecurve;
	int cf_server_tls_sslmode;
	char *cf_server_tls_protocols;
	char *cf_server_tls_ca_file;
	char *cf_server_tls_cert_file;
	char *cf_server_tls_key_file;
	char *cf_server_tls_ciphers;


private:
};

};

#endif // _Config_h_
