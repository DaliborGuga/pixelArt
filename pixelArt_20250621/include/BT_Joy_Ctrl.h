#ifndef BT_JOY_H
    #define BT_JOY_H

    // #include <main.h>
    #include "BluetoothSerial.h" 
// init Class:
static BluetoothSerial ESP_BT; //si no lo hago static no funciona ni mierda
uint8_t R_color_BT;
uint8_t G_color_BT;
uint8_t B_color_BT;
uint8_t Gamma_color_BT;

uint8_t loop_var;
char msg_rcv[30];
uint8_t button;
bool CLEAN_ARRAY;
int load_next_img = 0;


//
String id_requested2;
File loadPattern2;
size_t estimated_size_canvas2;
int bucle_read_file2;

static uint8_t taskCoreZero = 0;
// void BTcallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
// convertir las funcones a task de FreRtos!
void BT_init(void * pvParameters);
void BT_loop(void);
void BT_init_no_RTOS(void);
// void handlePlainBT(int comando);
String rgbToHex(uint8_t r, uint8_t g,uint8_t b);
void BTcallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
// esp_spp_cb_t BTcallback(esp_spp_cb_event_t event);
#endif