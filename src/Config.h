#if !defined(_Config_h_)
#define _Config_h_

#include <memory>
#include <string>
#include <set>
#include <chrono>

#include "Auth.h"
#include "Pool.h"
#include "SSL.h"

namespace SmartCache
{

struct Config 
{
	typedef std::shared_ptr<Config> Ptr;
	static void load(const std::string& filename);
	static Ptr current();
	void save(const std::string& filename);

	bool daemon;
	std::string job_name;
	std::string logfile;
	std::string pidfile;
	std::string listen_addr;
	std::string username;
	int listen_port;
	int listen_backlog;
	std::string unix_socket_dir;
	std::string unix_socket_mode;
	std::string unix_socket_group;
	Auth::Type auth_type;
	std::string auth_file;
	std::string auth_hba_file;
	std::string auth_user;
	std::string auth_query;
	Pool::Mode pool_mode;
	int max_client_conn;
	int default_pool_size;
	int min_pool_size;
	int reserve_pool_size;
	std::chrono::milliseconds reserve_pool_timeout;
	int max_db_connections;
	int max_user_connections;
	int syslog;
	std::string syslog_facility;
	std::string syslog_ident;
	std::chrono::milliseconds autodb_idle_timeout;
	std::string server_reset_query;
	bool server_reset_query_always;
	std::string server_check_query;
	std::chrono::milliseconds server_check_delay;
	std::chrono::milliseconds query_timeout;
	std::chrono::milliseconds query_wait_timeout;
	std::chrono::milliseconds client_idle_timeout;
	std::chrono::milliseconds client_login_timeout;
	std::chrono::milliseconds idle_transaction_timeout;
	std::chrono::milliseconds server_lifetime;
	std::chrono::milliseconds server_idle_timeout;
	std::chrono::milliseconds server_connect_timeout;
	std::chrono::milliseconds server_login_retry;
	bool server_round_robin;
	std::chrono::milliseconds suspend_timeout;
	std::string ignore_startup_parameters;
	bool disable_pqexec;
	std::chrono::milliseconds dns_nxdomain_ttl;
	std::chrono::milliseconds dns_zone_check_period;
	

	int sbuf_len;
	int sbuf_loopcnt;
	int tcp_socket_buffer;
	int tcp_defer_accept;
	int tcp_keepalive;
	int tcp_keepidle;
	int tcp_keepintvl;
	int res_pool_size;
	int max_db_connectiosn;
	std::chrono::microseconds dns_max_ttl;
	unsigned int max_packet_size;
	std::string ignore_startup_params;
	std::string autodb_connstr;
	std::chrono::microseconds cf_server_lifetime;
	std::chrono::microseconds cf_server_idle_timeout;
	std::chrono::microseconds cf_server_connect_timeout;
	std::chrono::microseconds cf_server_login_retry;
	std::chrono::microseconds cf_query_timeout;
	std::chrono::microseconds cf_query_wait_timeout;
	std::chrono::microseconds cf_client_idle_timeout;
	std::chrono::microseconds cf_client_login_timeout;
	std::chrono::microseconds cf_idle_transaction_timeout;
	std::chrono::microseconds cf_suspend_timeout;
	std::chrono::microseconds g_suspend_start;
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

};

};

#endif // _Config_h_
