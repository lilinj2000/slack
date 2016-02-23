#ifndef SLACK_CONFIG_HH
#define SLACK_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace slack
{

namespace po = boost::program_options;

class SlackOptions : public soil::Options
{
 public:

  SlackOptions();
  
  virtual ~SlackOptions();

  virtual po::options_description* configOptions();

  std::string instru;

  std::string speed_file;
  
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class SlackConfig
{
 public:
  
  SlackConfig(int argc=0, char* argv[]=NULL);
  ~SlackConfig();

  SlackOptions* slackOptions()
  {
    return slack_options_.get();
  }

  soil::Options* seaMDOptions()
  {
    return sea_md_options_.get();
  }


 private:
  std::unique_ptr<SlackOptions> slack_options_;

  std::unique_ptr<soil::Options> sea_md_options_;
  
};

}  


#endif 
