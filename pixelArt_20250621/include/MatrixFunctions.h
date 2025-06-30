#ifndef MATRIXFUNC_H 
#define MATRIXFUNC_H

// #include <main.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

volatile int canvas_size = 32;    

const uint8_t PROGMEM gamma8[] = {  //table for gamma correction
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

////////////////////////////////////////
// Para dibujar moviendome con el cursor, retraigo color histórico
// para dejarlo como estaba si no lo cambian
volatile int actualIndex;
volatile int previous_index;
volatile int actualPixelRow;
volatile int actualPixelColumn;
volatile int actual_pixelColor;
// volatile int actualIndex;
volatile int blink_tri_state;
volatile uint16_t pixel_color_when_selected; //
volatile long color_to_deposit;
volatile bool DEPOSIT_COLOR;
volatile bool FIND_CURSOR;
volatile bool PASAR_AL_OCULTAR_CURSOR = true;
volatile bool UP_REQ;
volatile bool DOWN_REQ;
volatile bool LEFT_REQ;
volatile bool RIGHT_REQ;
// volatile bool DOWN_REQ;
// volatile bool DELETE_PIXEL;
////////////////////////////////////////

void clearMatrix();
void draw(int index, long color);
void handlePlain();
void showPattern(size_t sizeofcanvas);
void blink_cursor(int index, long color);
void check_cursor_movements();

#endif