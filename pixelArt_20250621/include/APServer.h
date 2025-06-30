#ifndef APSERVER_H 
#define APSERVER_H

// #include "FS.h"
#include "../src/main.h"
#include "LittleFS.h"
#include <WiFi.h>
#include <AsyncTCP.h>
// #include <WiFiClient.h>
#include "ESPAsyncWebServer.h"
#include <DNSServer.h>
// #define ARDUINOJSON_ENABLE_STRING_VIEW 1
#include "AsyncJson.h"
#include "ArduinoJson.h"
 #include <string>
 
// We are hosting a webserver on the NodeMCU that communicates with the client (the website you see in your browser) over http POST und GET requests.
// These requests are handled in the "server handles" section
AsyncWebServer server(80);        //start the webserver on port 80 (standard html port)
// AsyncWebSocket ws("/ws");

// AsyncEventSource events("/events");

// StaticJsonDocument<5000> responsedoc;    //el doc lo haré dynamc y definido adentro del callback
char pixelartconverter_json_string[2500]; 

// File html;                        //file to read the html and push it to the client
// File patterns;                    //file to read one of the patterns stored on the sd
const byte DNS_PORT = 53;
DNSServer dnsServer;
IPAddress apIP(192, 168, 2, 1);
// IPAddress netMsk(255, 255, 255, 0);

//StaticJsonDocument<5000> doc;
// DynamicJsonDocument doc(5000);

bool ANALIZAR_JSON;
static size_t total_size_of_portion;
static size_t total_bytes_received;
bool UPDATE_MATRIX_DEFERRED;

//char pixelartconverter_json_string[2500];
// char pixelartconverter_json_string[2500];

// const char *pntr_json = pixelartconverter_json_string;
// char pixelartconverter_json_string[800];
//StaticJsonDocument<612> jsonarray;    //a ver si global y grande hace que el callback web /load no se cuelgue NO! y me mata el BT

volatile int chunked_start; 
long offset_of_pixel;
DeserializationError err;
bool BACK_FROM_CONVERTER_EXECUTED;
bool WS_CLIENT_CONNECTED;

// chunks para recibirtodo el pattern de una
std::vector<String> receivedPatternChunks;
int expectedTotalChunks = -1;
int receivedChunks = 0;


void handleRoot();
void handleNotFound();
void handlePlain();
void handleGetNames();
void handleLoad();
void handleSave();
void handleDelete();
void handleMode();
void handleChangeCanvas();
void handleJsonFromConverter();
void handleBackFromConverter();
void handle_OpenConv();
// serving android app from SD
// AsyncWebServer server2(81); //ver si usar otra instancia ara servir el file
size_t load_data(File f, uint8_t *buffer, size_t maxLen, size_t index);
void handleAPKDownload();
void register_events();
#endif