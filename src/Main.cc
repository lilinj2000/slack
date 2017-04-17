// Copyright (c) 2010
// All rights reserved.

#include <memory>

#include "Config.hh"
#include "Server.hh"
#include "soil/Pause.hh"

int main(int argc, char* argv[]) {
  std::unique_ptr<slack::Config> config;
  config.reset(new slack::Config(argc, argv));

  std::unique_ptr<slack::Server> server;
  server.reset(new slack::Server(config->slackOptions(),
                                 config->seaMDOptions()));

  std::unique_ptr<soil::Pause> pause;
  pause.reset(soil::Pause::create());

  return 0;
}
