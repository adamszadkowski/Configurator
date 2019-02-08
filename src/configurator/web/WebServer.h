#pragma once

#include <ESP8266WebServer.h>
#include <IPAddress.h>
#include <Runnable.h>

#include "configurator/Configurator.h"

namespace configurator {
namespace web {

class WebServer : public Runnable {
 public:
  WebServer(Configurator& configurator);

  virtual void run() override;

 private:
  void configureEndpoints();
  void handleConfigurationUpdate();
  void handleGetConfiguration();
  void handleRequest();
  String computePath();
  void streamFile(String path);
  String getContentType(String filename);

 private:
  Configurator& configurator;
  ESP8266WebServer server;
};

}  // namespace web
}  // namespace configurator
