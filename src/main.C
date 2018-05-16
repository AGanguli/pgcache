#include <iostream>
#include <list>
#include <string>
#include <asio.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>
#include <boost/system/error_code.hpp>
#include <unistd.h>
#include <syslog.h>

#include "Server.h"
#include "Config.h"

namespace po = boost::program_options;

void
reloadConfig(asio::signal_set* this_)
{
	std::cout << "Reload config" << std::endl;
	this_->async_wait(boost::bind(reloadConfig, this_));	
}

int
main(int argc, char* argv[])
{
	std::string config_file;
	po::options_description desc("Usage");
	desc.add_options()
		("help", 	"display command line options")
		("daemon",	"become a daemon")
		("verbose",	po::value<int>(), 	"Set verbosity: 0 = quiet, 10 = firehose;  default = 3")
		("reboot",	"no idea what this does")
		("user",	"become the given user")
		(
			"config",
			po::value<std::string>(&config_file)->default_value(""),
			"Config file"
		)
	;
	po::variables_map args;
	po::store(po::parse_command_line(argc, argv, desc), args);
	po::notify(args);

	if (args.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

	if (config_file.length()) {
		try {
			SmartCache::Config::load(config_file);
			SmartCache::Config::Ptr config = SmartCache::Config::current();
			config->save("out.ini");
		} catch( std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}

	asio::io_service io;

	asio::signal_set stop_signals(io, SIGINT, SIGTERM);
	stop_signals.async_wait(boost::bind(&asio::io_service::stop, &io)); 

	asio::signal_set reload_signal(io, SIGHUP);
	reload_signal.async_wait(boost::bind(reloadConfig, &reload_signal));

	// Well and truly daemonize.
	// 
	if (args.count("daemon")) {
		io.notify_fork(asio::io_service::fork_prepare);
		if (pid_t pid = fork()) {
			if (pid > 0) {
				// Parent.
				// 
				io.notify_fork(asio::io_service::fork_parent);
				exit(0);
			} 
			std::cerr << "First fork failed.  Unable to daemonize." << std::endl;
			exit(1);
		}
		setsid();
		chdir("/");
		umask(0);
		if (pid_t pid = fork()) {
			if (pid > 0) {
				exit(0);
			}
			std::cerr << "Second fork failed.  Unable to daemonize." << std::endl;
			return 1;
		}
		close(0);
		close(1);
		close(2);
		if (open("/dev/null", O_RDONLY) < 0) {
			syslog(LOG_ERR | LOG_USER, "Unable to open /dev/null: %m");
			return 1;
		}
		syslog(LOG_ERR | LOG_USER, "Second fork failed: %m");
	}

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <port> [<port> ..]\n";
		return 1;
	}
	
	try
	{

		std::list<SmartCache::Server> servers;
		for (int i = 1; i < argc; i ++) {
			tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
			servers.emplace_back(io, endpoint);
		}

		asio::thread t(boost::bind(&asio::io_service::run, &io));

		io.run();
		t.join();
	} catch( std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}


