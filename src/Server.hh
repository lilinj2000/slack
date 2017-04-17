// Copyright (c) 2010
// All rights reserved.

#ifndef SLACK_SERVER_HH
#define SLACK_SERVER_HH

#include <string>
#include "sea/MDService.hh"
#include "air/MDataFile.hh"

namespace slack {

class Options;

class Server : public sea::MDServiceCallback {
 public:
  Server(Options* slack_options,
         soil::Options* options);

  virtual ~Server();

 protected:
  virtual void onRspSubMarketData(const std::string& instru, bool success);

  virtual void onRspUnsubMarketData(const std::string& instru, bool success);

  virtual void onRtnMarketData(const sea::DepthMarketData*);

  virtual void onRspError(int errord_id, const std::string& error_msg);

  air::SpeedMData* toSpeedMData(const sea::DepthMarketData* data);

 private:
  Options* options_;
  std::unique_ptr<sea::MDService> md_service_;
  std::unique_ptr<air::MDataFile> speed_file_;
};

}  // namespace slack

#endif
