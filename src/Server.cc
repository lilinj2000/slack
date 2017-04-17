// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "Config.hh"

namespace slack {

Server::Server(Options* slack_options,
               soil::Options* options):
    options_(slack_options) {
  SLACK_TRACE <<"Server::Server()";

  std::string speed_file = options_->speed_file;

  if (!speed_file.empty()) {
    speed_file_.reset(new air::MDataFile(speed_file));
  }

  md_service_.reset(sea::MDService::createService(options, this));

  md_service_->subMarketData(options_->instru);
}

Server::~Server() {
  SLACK_TRACE <<"Server::~Server()";
}

void Server::onRspSubMarketData(const std::string& instru, bool success) {
  SLACK_TRACE <<"Server::onRspSubMarketData()";
}

void Server::onRspUnsubMarketData(const std::string& instru, bool success) {
  SLACK_TRACE <<"Server::onRspUnsubMarketData()";
}

void Server::onRtnMarketData(const sea::DepthMarketData* data) {
  SLACK_TRACE <<"Server::onRtnMarketData()";

  if (speed_file_.get()) {
    speed_file_->putData(toSpeedMData(data));
  }
}

void Server::onRspError(int errord_id, const std::string& error_msg) {
  SLACK_TRACE <<"Server::onRspError()";
}

air::SpeedMData* Server::toSpeedMData(const sea::DepthMarketData* data) {
  std::unique_ptr<air::SpeedMData> speed_data(new air::SpeedMData());

  speed_data->instru = data->InstrumentID;
  speed_data->update_time = data->UpdateTime;
  speed_data->update_millisec = data->UpdateMillisec;
  speed_data->time_stamp = data->time_stamp;

  return speed_data.release();
}

}  // namespace slack
