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
	config->daemon = tree.get("daemon", true);
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

