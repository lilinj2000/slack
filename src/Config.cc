// Copyright (c) 2010
// All rights reserved.

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "Config.hh"
#include "Log.hh"
#include "sea/MDService.hh"

namespace slack {

Options::Options():
    config_options_("SlackConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("slack.instru", po::value<std::string>(&instru),
       "instrument")
      ("slack.speed_file", po::value<std::string>(&speed_file),
       "speed file")
      ("slack.log_cfg", po::value<std::string>(&log_cfg),
       "log config file");

  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  slack_options_.reset(new Options());

  sea_md_options_.reset(sea::MDService::createOptions());

std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(slack_options_.get());
  config->registerOptions(sea_md_options_.get());

  config->configFile() = "slack.cfg";
  config->loadConfig(argc, argv);

  // init the log
  SLACK_LOG_INIT(slack_options_->log_cfg);

  return;
}

Config::~Config() {
}

}  // namespace slack
