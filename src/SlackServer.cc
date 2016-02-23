#include "SlackServer.hh"
#include "SlackLog.hh"
#include "SlackConfig.hh"

namespace slack
{

SlackServer::SlackServer(SlackOptions* slack_options,
                         soil::Options* options):
    slack_options_(slack_options)
{
  SLACK_TRACE <<"SlackServer::SlackServer()";

  std::string speed_file = slack_options_->speed_file;
  
  if( !speed_file.empty() )
    speed_file_.reset( new air::MDataFile(speed_file) );
  
  md_service_.reset( sea::MDService::createService(options, this) );

  md_service_->subMarketData( slack_options_->instru );
}

SlackServer::~SlackServer()
{
  SLACK_TRACE <<"SlackServer::~SlackServer()";
}

void SlackServer::onRspSubMarketData(const std::string& instru, bool success)
{
  SLACK_TRACE <<"SlackServer::onRspSubMarketData()";
}

void SlackServer::onRspUnsubMarketData(const std::string& instru, bool success)
{
  SLACK_TRACE <<"SlackServer::onRspUnsubMarketData()";
}

void SlackServer::onRtnMarketData(const sea::DepthMarketData* data)
{
  SLACK_TRACE <<"SlackServer::onRtnMarketData()";

  if( speed_file_.get() )
  {
    speed_file_->putData( toSpeedMData(data) );
  }

}

void SlackServer::onRspError(int errord_id, const std::string& error_msg)
{
  SLACK_TRACE <<"SlackServer::onRspError()";
}

air::SpeedMData* SlackServer::toSpeedMData(const sea::DepthMarketData* data)
{
  std::unique_ptr<air::SpeedMData> speed_data(new air::SpeedMData());
  
  speed_data->instru = data->InstrumentID;
  speed_data->update_time = data->UpdateTime;
  speed_data->update_millisec = data->UpdateMillisec;
  speed_data->time_stamp = data->time_stamp;

  return speed_data.release();
}

};
