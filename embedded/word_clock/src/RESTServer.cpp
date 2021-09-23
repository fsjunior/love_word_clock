#include "RESTServer.hpp"

#define DATA_ARRAY_SIZE 64

RESTServer::RESTServer(AsyncWebServer& server, Configurator &configurator): server(server), configurator(configurator)
{
}

void RESTServer::handlePing(AsyncWebServerRequest *request)
{
    StaticJsonDocument<DATA_ARRAY_SIZE> doc;
    doc["result"] = "pong";

    AsyncResponseStream *response = request->beginResponseStream("application/json");    
    serializeJson(doc, *response);
    request->send(response);
}

void RESTServer::replySuccess(AsyncWebServerRequest *request) 
{
    StaticJsonDocument<DATA_ARRAY_SIZE> doc;
    doc["result"] = true;

    AsyncResponseStream *response = request->beginResponseStream("application/json");    
    serializeJson(doc, *response);
    request->send(response);
}

void RESTServer::handlePostConfig(AsyncWebServerRequest *request, JsonVariant &json)
{    
    StaticJsonDocument<DATA_ARRAY_SIZE> doc = json.as<JsonObject>();

    uint8_t r = doc["red"];
    uint8_t g = doc["green"];
    uint8_t b = doc["blue"];

    configurator.store_color(r, g, b);


    int8_t offset = doc["offset"];

    configurator.store_time_offset(offset);

    replySuccess(request);
}

void RESTServer::handleGetConfig(AsyncWebServerRequest *request)
{
    uint8_t r, g, b;
    configurator.get_color(r, g, b);

    int8_t offset = configurator.get_time_offset();

    StaticJsonDocument<DATA_ARRAY_SIZE> doc;
    doc["red"] = r;
    doc["green"] = g;
    doc["blue"] = b;

    doc["offset"] = offset;

    AsyncResponseStream *response = request->beginResponseStream("application/json");    
    serializeJson(doc, *response);
    request->send(response);
}


void RESTServer::RESTServer::begin()
{
    server.on("/ping", HTTP_GET, [&] (AsyncWebServerRequest *request) { handlePing(request); });
  
    server.on("/config", HTTP_GET, [&] (AsyncWebServerRequest *request) { handleGetConfig(request); });
  
    server.addHandler(new AsyncCallbackJsonWebHandler("/config", [&](AsyncWebServerRequest *request, JsonVariant &json) {
        handlePostConfig(request, json);
    }));    


    server.begin();
}

