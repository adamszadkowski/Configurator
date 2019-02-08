#include "configurator/web/WebServer.h"

#include <ESP8266WiFi.h>
#include <FS.h>

namespace configurator {
namespace web {

WebServer::WebServer(Configurator& configurator) : configurator(configurator), server(80) {
  SPIFFS.begin();
  configureEndpoints();
  server.begin();
}

void WebServer::run() {
  server.handleClient();
}

void WebServer::configureEndpoints() {
  server.on("/configuration", HTTP_POST, [this]() { handleConfigurationUpdate(); });
  server.on("/configuration", HTTP_GET, [this]() { handleGetConfiguration(); });

  server.onNotFound([this]() { handleRequest(); });
}

void WebServer::handleConfigurationUpdate() {
  for (int i = 0; i < server.args(); i++)  //
    configurator.set(server.argName(i), server.arg(i));
  configurator.commit();

  server.send(200, "text/plain", "");
}

void WebServer::handleGetConfiguration() {
  String json = "{";
  configurator.iterate([&json](const String& name, const String& value) {
    json += "\"" + name + "\":\"" + value + "\",";  //
  });
  if (json.endsWith(",")) {
    json.setCharAt(json.length() - 1, '}');
  }
  server.send(200, "text/plain", json);
}

void WebServer::handleRequest() {
  String path = computePath();
  if (SPIFFS.exists(path))
    streamFile(path);
  else
    server.send(404, "text/plain", "404: Not Found");
}

String WebServer::computePath() {
  String path = server.uri();
  return path.endsWith("/") ? path + "index.html" : path;
}

void WebServer::streamFile(String path) {
  File file = SPIFFS.open(path, "r");
  String contentType = getContentType(path);
  server.streamFile(file, contentType);
  file.close();
}

String WebServer::getContentType(String filename) {
  if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".png"))
    return "image/png";
  else if (filename.endsWith(".woff"))
    return "application/font-woff";
  else if (filename.endsWith(".woff2"))
    return "application/font-woff2";
  else if (filename.endsWith(".ttf"))
    return "application/x-font-ttf";
  else if (filename.endsWith(".eot"))
    return "application/vnd.ms-fontobject";
  else if (filename.endsWith(".svg"))
    return "image/svg+xml";

  return "text/plain";
}

}  // namespace web
}  // namespace configurator
