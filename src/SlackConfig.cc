#include "SlackConfig.hh"
#include "SlackLog.hh"
#include "sea/MDService.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace slack
{

SlackOptions::SlackOptions():
    config_options_("SlackConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("slack.instru", po::value<std::string>(&instru), 
       "instrument")
      ("slack.speed_file", po::value<std::string>(&speed_file), 
       "speed file")

      ("slack.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

SlackOptions::~SlackOptions()
{
}

po::options_description* SlackOptions::configOptions()
{
  return &config_options_;
}

SlackConfig::SlackConfig(int argc, char* argv[])
{
  slack_options_.reset(new SlackOptions());

  sea_md_options_.reset( sea::MDService::createOptions() );
      
  std::auto_ptr<soil::Config> config( soil::Config::create() );
  config->registerOptions( slack_options_.get() );
  config->registerOptions( sea_md_options_.get() );

  config->configFile() = "slack.cfg";
  config->loadConfig(argc, argv);
  
  // init the log
  SLACK_LOG_INIT( slack_options_->log_cfg );
  
  return;
}

SlackConfig::~SlackConfig()
{
}

};  
