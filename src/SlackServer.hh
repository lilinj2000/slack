#ifndef SLACK_SERVER_HH
#define SLACK_SERVER_HH

#include "sea/MDService.hh"
#include "air/MDataFile.hh"

namespace slack
{

class SlackOptions;

class SlackServer : public sea::MDServiceCallback
{
 public:
  SlackServer(SlackOptions* slack_options,
              soil::Options* options);

  virtual ~SlackServer();
  
 protected:

  virtual void onRspSubMarketData(const std::string& instru, bool success);

  virtual void onRspUnsubMarketData(const std::string& instru, bool success);

  virtual void onRtnMarketData(const sea::DepthMarketData*);

  virtual void onRspError(int errord_id, const std::string& error_msg);

  air::SpeedMData* toSpeedMData(const sea::DepthMarketData* data);
  
 private:

  SlackOptions* slack_options_;
  
  std::unique_ptr<sea::MDService> md_service_;

  std::unique_ptr<air::MDataFile> speed_file_;

};

};

#endif
