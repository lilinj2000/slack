#include <memory>

#include "SlackConfig.hh"
#include "SlackServer.hh"
#include "soil/STimer.hh"

int main(int argc, char* argv[])
{

  std::unique_ptr<slack::SlackConfig> config;
  config.reset(new slack::SlackConfig(argc, argv));

  std::unique_ptr<slack::SlackServer> server;
  server.reset(new slack::SlackServer(config->slackOptions(),
                                      config->seaMDOptions()) );
  
  std::unique_ptr<soil::STimer> cond;
  cond.reset( soil::STimer::create() );

  do
  {
    cond->wait(2000);
  }while(true);
  
  return 0;
}
