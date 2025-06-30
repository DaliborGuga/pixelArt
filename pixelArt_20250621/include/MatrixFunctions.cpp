// Primitivas básicas de uso del panel.
// 

#ifndef MATRIXFUNC_C 
#define MATRIXFUNC_C

#include <MatrixFunctions.h>

// Aprovechar para limpiar pattern y ghost
void clearMatrix() 
{   
    unsigned long i;
    dma_display->clearScreen();

    for(i=0;i<=4095;i++)
    {
        pattern[i] = 0;
        large_canvas_ghost[i] = 0;
    }
    actualIndex = 0;    //Llevar al origen para que no se pierda si suben y bajan de tamaño el canvas
}

// #define VERBOSE_DRAW
void draw(int index, long color) 
{                                //draw one pixel on the matrix Starting at [0,0]
    uint16_t colorformat = 0;
    #ifdef VERBOSE_DRAW
        Serial.println();
        Serial.println("Index:" + String(index));
    #endif
    int row = 0;     //row           
    int column = 0;  //column
    // Canvas size debe coincidir en la Web Page y en la aplicacion para que no se vaya todo
    // a la mierda
    row = index / canvas_size;   
    column = ( index - (row * canvas_size) ) ;
   
    #ifdef VERBOSE_DRAW
    Serial.println("To Row: " + String(row) + "Column: " + String(column));
    Serial.println("To color: "+ String(color) );
    #endif
    //Estos tres juntos funcionan igual que el de abajo solito; pero creo que el resultado es el mismo
    colorformat = dma_display->color565(pgm_read_byte(&gamma8[(color >> 16) & 255]), pgm_read_byte(&gamma8[(color >> 8) & 255]) , pgm_read_byte(&gamma8[(color) & 255]));
    #ifdef VERBOSE_DRAW
    Serial.println("To color formatted:" + String(colorformat) );
    #endif
    //Acomodando el tamaño de los pixwles al lienzo elegido
    if(canvas_size == 32)
    {
        // Serial.println("Canvas 32");    //pixeles al doble
        row = row * 2;
        column = column * 2;
        dma_display->drawPixel(column,row,colorformat);
        dma_display->drawPixel(column,row+1,colorformat);
        dma_display->drawPixel(column+1,row,colorformat);
        dma_display->drawPixel(column+1,row+1,colorformat);
    }
    else if(canvas_size == 16)
    {
        // Serial.println("Canvas 16");    //pixel 4 veces más grandes
        row = row * 4;
        column = column * 4;
        dma_display->drawPixel(column,row,colorformat);
        dma_display->drawPixel(column,row+1,colorformat);
        dma_display->drawPixel(column,row+2,colorformat);
        dma_display->drawPixel(column,row+3,colorformat);

        dma_display->drawPixel(column+1,row,colorformat);
        dma_display->drawPixel(column+1,row+1,colorformat);
        dma_display->drawPixel(column+1,row+2,colorformat);
        dma_display->drawPixel(column+1,row+3,colorformat);

        dma_display->drawPixel(column+2,row,colorformat);
        dma_display->drawPixel(column+2,row+1,colorformat);
        dma_display->drawPixel(column+2,row+2,colorformat);
        dma_display->drawPixel(column+2,row+3,colorformat);

        dma_display->drawPixel(column+3,row,colorformat);
        dma_display->drawPixel(column+3,row+1,colorformat);
        dma_display->drawPixel(column+3,row+2,colorformat);
        dma_display->drawPixel(column+3,row+3,colorformat);        
   
    }
    else if(canvas_size == 64)
    {
        #ifdef VERBOSE_DRAW
        Serial.println("Canvas 64");
        #endif
        dma_display->drawPixel(column,row,colorformat);
    }

}

void showPattern(size_t sizeofcanvas) 
{                                              //display pattern currently stored in pattern[256]
    // long millis_enter = millis();
    int cycle_to = 256;             //default 16x16 canvas
   
    // if(BT_SEND_LOAD_CMD)        //ver si "arregla" lecturas/escrituras desde BT app
    // {
    //  canvas_size = 16;
    // }

    // Serial.println("Pattern Size of file:" + String (sizeofcanvas));
    // 2304 bytes for 16x16
    // 9216 bytes for 32x32
    // 20486 bytes for 64x64
    if(sizeofcanvas >= 2304) //if 32x32 canvas: file size will be greater than..
    {
        cycle_to = 1024;
        // if(BT_SEND_LOAD_CMD)        //ver si "arregla" lecturas/escrituras desde BT app
        // {
        //     canvas_size = 32;   
        // }
    }
    if(sizeofcanvas >= 20000)
    {
         cycle_to = 4096;
        // if(BT_SEND_LOAD_CMD)        //ver si "arregla" lecturas/escrituras desde BT app
        // {
        //     canvas_size = 64;
        // }
    }

    for (int i = 0; i < cycle_to; i++) 
    {
        draw(i,pattern[i]);
        large_canvas_ghost[i] = pattern[i]; //para tener en el ghost y en la pantalla lo mismo!
        // ver qué hacer con canvas_size desde los métodos WEB y los métodos BT!
    }
    // if(BT_SEND_LOAD_CMD)        //ver si "arregla" lecturas/escrituras desde BT app
    // {
    //    BT_SEND_LOAD_CMD = false; 
    // }

    // long millis_leave = millis();
    // Serial.println("Task showPattern took:" + String (millis_leave-millis_enter) + "ms");  
}

#define VERBOSE_BLINK
// Find cursor a False, suspenderá el blinkeo. Dejar los pixeles como
// estaban al momento de recibir FIND_CURSOR = false!!!!!!
void blink_cursor(int index, long color)
{
    uint16_t colorformat = 0;
    int row = 0;     //row           
    int column = 0;  //column
    // Canvas size debe coincidir en la Web Page y en la aplicacion para que no se vaya todo
    // a la mierda
    row = index / canvas_size;   
    column = ( index - (row * canvas_size) ) ;

    if(FIND_CURSOR == false)
    {
        //Cuando ocultan el cursor, debo verificar qué color dejar en el pixel!
        // if(PASAR_AL_OCULTAR_CURSOR == true)
        // {
        //     PASAR_AL_OCULTAR_CURSOR = false;
        //     Serial.println("Dibujar el patron una vez, para limpiar cursor espurio");
        //     // Poner el estado correct en pixel_color_when_selected , si hicieron click en el pixel
        //     // si no; dejar el que tenía cuando lo pisaron por primera vez
        //     //colorformat = dma_display->color565(pgm_read_byte(&gamma8[(pixel_color_when_selected >> 16) & 255]), pgm_read_byte(&gamma8[(pixel_color_when_selected >> 8) & 255]) , pgm_read_byte(&gamma8[(pixel_color_when_selected) & 255]));
        // }
        //colorformat = dma_display->color565(pgm_read_byte(&gamma8[(pixel_color_when_selected >> 16) & 255]), pgm_read_byte(&gamma8[(pixel_color_when_selected >> 8) & 255]) , pgm_read_byte(&gamma8[(pixel_color_when_selected) & 255]));
        return;
    }
    if(millis() - currentBlink >= 250)
    {
        PASAR_AL_OCULTAR_CURSOR = true;
        currentBlink = millis();
        colorformat = dma_display->color565(pgm_read_byte(&gamma8[(color >> 16) & 255]), pgm_read_byte(&gamma8[(color >> 8) & 255]) , pgm_read_byte(&gamma8[(color) & 255]));
        // El cursor blinkea con blanco y negro (y el color que quieran depositar)
        // blinkeo de tres estads Color-blanco-negro: así blanco y negro se verán
        // Si quieren depositarlo
        // O blinkeo siempre a blanco y si quieren blanco NO blinkeará y a la M - dejo 2 state con blanco!
        if(blink_tri_state == 0)
        {
            blink_tri_state = 1;
        }
        else if(blink_tri_state == 1)
        {
            blink_tri_state =0;
            colorformat = 0xffff; // & colorformat; //ver si este togleo resulta
        }
        else
        {
            colorformat = 0;
            blink_tri_state = 0;
        }
        
        // #ifdef VERBOSE_BLINK
        // Serial.println("Blink To color formatted:" + String(colorformat) );
        // #endif
        //Acomodando el tamaño de los pixwles al lienzo elegido
        if(canvas_size == 32)
        {
            // Serial.println("Canvas 32");    //pixeles al doble
            row = row * 2;
            column = column * 2;
            dma_display->drawPixel(column,row,colorformat);
            dma_display->drawPixel(column,row+1,colorformat);
            dma_display->drawPixel(column+1,row,colorformat);
            dma_display->drawPixel(column+1,row+1,colorformat);
        }
        else if(canvas_size == 16)
        {
            // Serial.println("Canvas 16");    //pixel 4 veces más grandes
            row = row * 4;
            column = column * 4;
            dma_display->drawPixel(column,row,colorformat);
            dma_display->drawPixel(column,row+1,colorformat);
            dma_display->drawPixel(column,row+2,colorformat);
            dma_display->drawPixel(column,row+3,colorformat);

            dma_display->drawPixel(column+1,row,colorformat);
            dma_display->drawPixel(column+1,row+1,colorformat);
            dma_display->drawPixel(column+1,row+2,colorformat);
            dma_display->drawPixel(column+1,row+3,colorformat);

            dma_display->drawPixel(column+2,row,colorformat);
            dma_display->drawPixel(column+2,row+1,colorformat);
            dma_display->drawPixel(column+2,row+2,colorformat);
            dma_display->drawPixel(column+2,row+3,colorformat);

            dma_display->drawPixel(column+3,row,colorformat);
            dma_display->drawPixel(column+3,row+1,colorformat);
            dma_display->drawPixel(column+3,row+2,colorformat);
            dma_display->drawPixel(column+3,row+3,colorformat);        

        }
        else if(canvas_size == 64)
        {
            #ifdef VERBOSE_DRAW
            Serial.println("Canvas 64");
            #endif
            dma_display->drawPixel(column,row,colorformat);
        }
    }
}

// Hacer las comparaciones necesarias para que actualindex se mueva lindo
// entre los extremos del canvas. Ver si hacer un método que devuelva x,y
// que es más feliz
// La ideas es ir dibujando sobre pattern y refrescarlo cuando se mueven
// y/o depositen color y o borren
void check_cursor_movements()
{
    int limit = canvas_size;
    actualPixelRow = actualIndex / canvas_size;
    actualPixelColumn = ( actualIndex - (actualPixelRow * canvas_size) ) ;
    int estimated_size_to_recycle = 400;
    int scroll_Vsize = 240;             //para scrollear en los límites del canvas de un extremo a otro
    int scroll_Hsize = 15;

    // Reciclo métodos  - números raros por lo que da el tamaño de archivo al leer
    if (canvas_size == 32)
    {
        estimated_size_to_recycle = 2305;
        scroll_Vsize = 992;             
        scroll_Hsize = 31;
    }
    else if(canvas_size == 64)
    { 
        estimated_size_to_recycle = 20001;  
        scroll_Vsize = 4032;             
        scroll_Hsize = 63;
    }

    if(FIND_CURSOR == false)
    {
        //Cuando ocultan el cursor, debo verificar qué color dejar en el pixel!
        if(PASAR_AL_OCULTAR_CURSOR == true)
        {
            PASAR_AL_OCULTAR_CURSOR = false;
            Serial.println("Dibujar el patron una vez, para limpiar cursor espurio");
            showPattern(estimated_size_to_recycle);
            // Poner el estado correct en pixel_color_when_selected , si hicieron click en el pixel
            // si no; dejar el que tenía cuando lo pisaron por primera vez
            //colorformat = dma_display->color565(pgm_read_byte(&gamma8[(pixel_color_when_selected >> 16) & 255]), pgm_read_byte(&gamma8[(pixel_color_when_selected >> 8) & 255]) , pgm_read_byte(&gamma8[(pixel_color_when_selected) & 255]));
        }
        //colorformat = dma_display->color565(pgm_read_byte(&gamma8[(pixel_color_when_selected >> 16) & 255]), pgm_read_byte(&gamma8[(pixel_color_when_selected >> 8) & 255]) , pgm_read_byte(&gamma8[(pixel_color_when_selected) & 255]));
        return;
    }

    // Si Depositan color sobre el pixel actual; lo hago efectivo
    if(DEPOSIT_COLOR)                                   
    {                                                   
        pattern[actualIndex] = color_to_deposit;    
        large_canvas_ghost[actualIndex] = color_to_deposit; //lo pongo en ambos arrays, ver como funciona guardar y eso
        // DEPOSIT_COLOR = false;
    }

    if(UP_REQ)
    {
        UP_REQ = false;
        if(actualPixelRow > 0)
        {
            actualIndex = actualIndex - limit;
        }
        else if(actualPixelRow == 0)
        {

            actualIndex = actualIndex + scroll_Vsize  ;  //
            Serial.println("Canvas size:"+ String(canvas_size));
            Serial.print("Scroll up to bottom, index:");
            Serial.println(actualIndex);
        }

    }
    if(DOWN_REQ)
    {
        DOWN_REQ = false;
        if(actualPixelRow < (limit-1))
        {
            actualIndex = actualIndex + limit;  
        }
        else if(actualPixelRow == (limit-1))
        {
            Serial.println("Canvas size:"+ String(canvas_size));
            actualIndex = actualIndex - scroll_Vsize;  //
            Serial.print("Scroll bottom to up, index:");
            Serial.println(actualIndex);
        }        
    }
    if(LEFT_REQ)
    {
        LEFT_REQ = false;
        if(actualPixelColumn > 0)
        {
            actualIndex--;  
        }    
        else if(actualPixelColumn == 0)
        {
             Serial.println("Canvas size:"+ String(canvas_size));
            actualIndex = actualIndex + scroll_Hsize;  //
            Serial.print("Scroll left to right, index:");
            Serial.println(actualIndex);            
        }    
    }
    if(RIGHT_REQ)
    {
        //Serial.printf("%u\r\n",actualPixelColumn);
        if(actualPixelColumn < (limit-1))
        {
            actualIndex++;  
        }    
        else if(actualPixelColumn == (limit-1))
        {
             Serial.println("Canvas size:"+ String(canvas_size));
            actualIndex = actualIndex - scroll_Hsize;  //
            Serial.print("Scroll right to left, index:");
            Serial.println(actualIndex);            
        }                  
        RIGHT_REQ = false;
    }            

    // Si el cursor se ha movido; debo verificar si depositaron o no el color
    // para dejarlo pintado en el pixel y, además, tomar el valor el nuevo pixel seleccionado
    // por si no lo pintan: ver si uedo usar pattern (el array) para dicho propósito
    // trabajar en large_canvas_ghost para que funcionen canvas de 64!!!!
    if( actualIndex != previous_index || DEPOSIT_COLOR )
    {
        DEPOSIT_COLOR = false;
        showPattern(estimated_size_to_recycle);
    }
    previous_index = actualIndex;
}


#endif