// Copyright (c) 2010
// All rights reserved.

#ifndef SLACK_CONFIG_HH
#define SLACK_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace slack {

namespace po = boost::program_options;

class Options : public soil::Options {
 public:
  Options();

  virtual ~Options();

  virtual po::options_description* configOptions();

  std::string instru;
  std::string speed_file;
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class Config {
 public:
  explicit Config(int argc = 0, char* argv[] = nullptr);

  ~Config();

  Options* slackOptions() {
    return slack_options_.get();
  }

  soil::Options* seaMDOptions() {
    return sea_md_options_.get();
  }

 private:
  std::unique_ptr<Options> slack_options_;

  std::unique_ptr<soil::Options> sea_md_options_;
};

}  // namespace slack

#endif
