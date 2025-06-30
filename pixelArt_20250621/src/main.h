
#ifndef MAIN_H
#define MAIN_H
// #include <FastLED.h>
// Vamos a ver si el super define salvavidas es este señor!
// Para
// #define	FD_SETSIZE	128  // original 64

#include <FS.h> 
#include "LittleFS.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <../include/blink/Fadinglight.h>
#include <../include/blink/Blinkenlight.h>

#include <string.h> 
#include <vector>
std::vector<String> v;
volatile uint16_t files_found;
String name_to_deferred;
String name_to_load;
String ruta;

// // Display settings
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 64     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another
//MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;

// #define AP_NOT_WIFI //Si quiero que sea AP o que se conecte a alguna red
                    // Como AP queda en 192.168.2.1
                    // En una Red: hay que ver donde queda. Usar DNS!
// #ifdef AP_NOT_WIFI
//     #define STASSID "LylaArtToy"         //SSID of your WIFI
//     #define STAPSK ""      //password of your WIFI
// #else
// // WiFi settings
//     #define STASSID "ReplicaGuGa"         //SSID of your WIFI
//     #define STAPSK  "Ilegalisimo"      //password of your WIFI
// #endif

// Mientras depuro, entro por cualquier lado
#define APSSID "LylaArtToy"
#define APPSK ""
#define STASSID "ReplicaGuGa"         //SSID of your WIFI
#define STAPSK  "Ilegalisimo"      //password of your WIFI
// #define STASSID "ESP"
// #define STAPSK  "87654321"

#define NUM_LEDS 4096                //16*16 matrix = 256 leds / 64*64=4096
const char* ssid = STASSID;
const char* password = STAPSK;
const char* APssid = APSSID;
const char* APpassword = APPSK;

// // We are hosting a webserver on the NodeMCU that communicates with the client (the website you see in your browser) over http POST und GET requests.
// // These requests are handled in the "server handles" section
// WiFiServer server(80);        //start the webserver on port 80 (standard html port)
// File html;                          //file to read the html and push it to the client
// File patterns;                      //file to read one of the patterns stored on the sd

//CRGB leds[NUM_LEDS];                //initalise the array of the leds that we can later assign colorvalues
extern const uint8_t gamma8[];      //this is a forward declaration for the gamma correction (used to make the colors look more natural)
long pattern[NUM_LEDS];             //array of the current displayed led pattern
bool live = true;                   //determines if NodeMCU is in live draw mode or shows the saved patterns in a loop
long currentMillis = 0;             //we all know these variables.. blink without delay...
long prevMillis = millis();
int interval = 7000;
int loopIndex = 0;                  //index of the loop for displaying the saved images
long large_canvas_ghost[NUM_LEDS];  //trampita pa grabar canvas que no entra en el POST
volatile bool SAVE_LARGE_FILE;
volatile bool SAVE_16_FILE;
volatile bool SAVE_32_FILE;
// volatile int file_to_save_to;
volatile bool FALLA_SD = false;
volatile int falla_lectura_sd = 0;
volatile bool PRINT_SCREEN_DIFERIDO = false;
volatile int file_to_print_deferred = 0;
volatile int estimated_size_for_deferred_print=0;
volatile int extinguir_solicitud_load;
volatile bool FILL_DEFERRED;
volatile long fill_color_current_color;
volatile long fill_color_reference_color;
volatile int max_iterations;

volatile int fill_x;
volatile int fill_y;

#define PIN_INPUT_BT_CONTROL_ENABLE 3 //(Uart RX)//Ver pin de conveniecia; hacer input con ull up si se puede
#define PIN_OUTPUT_LED_OPERATION_MODE 23  //Ver pin de output para avisar modo de operación 

Blinkenlight statusLed(PIN_OUTPUT_LED_OPERATION_MODE);
SpeedSetting statusLedSettings;

volatile bool BT_CONTROL_ACTIVE;
volatile bool CLIENTE_BT_CONECTADO;
volatile bool BT_CONNECTED;

volatile int web_page_selected;

volatile long currentBlink;

volatile long millis_inactivity;
volatile bool ACTIVITY_BIT;
volatile bool SKIP_NAMES_CREATION;

//Just in case constants
uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myGREEN = dma_display->color565(0, 255, 0);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

bool prepare_read_and_draw(int Index);

void print_heap(int k); //para poder usarlo global

#endif
