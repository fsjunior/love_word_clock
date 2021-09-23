#ifndef __REST_SERVER__
#define __REST_SERVER__

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include "Configurator.hpp"


class RESTServer {
private:    
    AsyncWebServer& server;
    Configurator& configurator;

    void replySuccess(AsyncWebServerRequest *request);

    void handlePing(AsyncWebServerRequest *request);

    void handleGetConfig(AsyncWebServerRequest *request);
    void handlePostConfig(AsyncWebServerRequest *request, JsonVariant &json);


public:
    RESTServer(AsyncWebServer& server, Configurator &configurator);


    void begin();
    void handleClient();
};




#endif /* __REST_SERVER__ */