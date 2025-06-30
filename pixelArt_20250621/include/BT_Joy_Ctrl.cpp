#ifndef BT_JOY_C
#define BT_JOY_C

#include <MatrixFunctions.h>
#include <BT_Joy_Ctrl.h> 
#include <main.h>

// Bluetooth Serial Events callback
// void BTcallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
// // void BTcallback(esp_spp_cb_t event)
// {
//     // Serial.printf("BT_EVNT %lu ",event);
//     if(event == ESP_SPP_SRV_OPEN_EVT){
//         Serial.println("Cliente Conectado");
//         CLIENTE_BT_CONECTADO = true;
//         ACTIVITY_BIT = true;
//     }
//     else if (event == ESP_SPP_CLOSE_EVT)
//     {
//         Serial.println("Cliente DESConectado");
//         CLIENTE_BT_CONECTADO = false;
//     }

// }

//#define VERBOSE_BT_INIT
// Task de Frertos para iniciar BT (ver si lo hace en Core 0)
void BT_init(void * pvParameters)
{
    #ifdef VERBOSE_BT_INIT
    String taskMessage = "Task running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);  //log para o serial monitor
    #endif

    bool returned_val;
    returned_val = ESP_BT.begin("LylArt_BT_Control",false); //Name of your Bluetooth interface -> will show up on your phone
    #ifdef VERBOSE_BT_INIT
        Serial.printf(" BT init Returned %u\r\n",returned_val);
    #endif
    ESP_BT.setTimeout(10); 
    
    // ESP_BT.register_callback(BTcallback);
    // ESP_BT.register_callback(BTcallback2);
    // Serial.flush();

    vTaskDelete( NULL );
}

//
void BT_init_no_RTOS(void)
{
    bool returned_val;
    esp_err_t cb_err_ret;
    returned_val = ESP_BT.begin("LylArt_BT_Control",false); //Name of your Bluetooth interface -> will show up on your phone
    // Serial.printf("BT init Returned %u\r\n",returned_val);
    ESP_BT.setTimeout(10); 
    // cb_err_ret = ESP_BT.register_callback(BTcallback);
    // Serial.printf("CallBack register Returned %u\r\n",cb_err_ret);
}

// Robando del js, la conversion de r,g,b a color para el metodo draw
// Devuelvo como devuelven los métodso del post
String rgbToHex(uint8_t r, uint8_t g,uint8_t b) 
{
    long color_int = (long)r << 16 | (uint16_t)g << 8 | b; 
    // Serial.printf("Color int: %lx\r\n",color_int);
    if (r > 255 || g > 255 || b > 255)
    {
        return("000000");
    }
    return ( String(color_int) ) ;
}

//#define VERBOSE_BT_JOY
//#define VERBOSE_SAVE_BT
bool just_once_msg = 0;
void BT_loop(void)
{
    // cuando hay cliente, pongo variables de activity
    if(ESP_BT.hasClient() != 0 )
    {
        if(just_once_msg == 0)
        {
            just_once_msg = true;
            #ifdef VERBOSE_BT_JOY
            Serial.println("Got BT client!");
            #endif
            CLIENTE_BT_CONECTADO = true;
            ACTIVITY_BIT = true;            
        }
    }
    else if(just_once_msg == true)  //cuando ya no lo haya, una vez que lo hubo
    {
        just_once_msg = 0;
        CLIENTE_BT_CONECTADO = false;
        ACTIVITY_BIT = false;           //si quiero computar tiempo de inactividad
        millis_inactivity = millis();
        #ifdef VERBOSE_BT_JOY
        Serial.println("BT client has gone!");
        #endif
    }
    // -------------------- Receive Bluetooth signal ----------------------
    if (ESP_BT.available()) 
    {
        CLEAN_ARRAY = true;
        while(ESP_BT.available() > 0)
        {
            msg_rcv[loop_var] = ESP_BT.read();
            // Serial.println(msg_rcv[loop_var]);
            loop_var++;
        }

        if(loop_var == 1) //One byte command
        {
            #ifdef VERBOSE_BT_JOY
            Serial.println("Command");
            #endif
            button = msg_rcv[0]; 
            switch (button) 
            {
                // con comando de unsolo bytes, a veces borraba todo por error y era alta paja
            //    case 0:
            //        clearMatrix();
            //    break;
            case 1:  
                UP_REQ = true;
            #ifdef VERBOSE_BT_JOY
                Serial.print("Button 1:arriba"); 
            #endif
                break;
            case 2:  
                DOWN_REQ = true;
            #ifdef VERBOSE_BT_JOY
                Serial.print("Button 2:abajo"); 
            #endif
                break;
            case 3:  
                LEFT_REQ = true;  
            #ifdef VERBOSE_BT_JOY
                Serial.print("Button 3:izquierda"); 
            #endif
                break;
            case 4:  
                RIGHT_REQ = true;
            #ifdef VERBOSE_BT_JOY
                Serial.print("Button 4:derecha"); 
            #endif
                break;
            case 5:  
                //chupar color-verificar métodos
                // color_to_deposit = pattern[actualIndex]; //y lo tomo como para usar por la aplicación
                color_to_deposit = large_canvas_ghost[actualIndex]; //y lo tomo como para usar por la aplicación
                // ver si no hay que sacarlo de ghost!!!
                uint8_t RedC,GreenC,BlueC;
                RedC =(color_to_deposit & 0xFF0000)>>16;
                GreenC = (color_to_deposit & 0x00FF00)>>8;
                BlueC = (color_to_deposit & 0x0000FF);
                #ifdef VERBOSE_BT_JOY
                    Serial.printf("Button 5:Clonar color.R:%x,G:%x,B:%u\r\n",RedC,GreenC,BlueC); 
                #endif
                // ESP_BT.write((uint8_t)(color_to_deposit & 0xFF0000)>>16);   //Ackando R
                // ESP_BT.write((uint8_t)(color_to_deposit & 0x00FF00)>>8 );   //G
                // ESP_BT.write((uint8_t)(color_to_deposit & 0x0000FF)    );   //B
                ESP_BT.write(RedC);
                ESP_BT.write(GreenC);
                ESP_BT.write(BlueC);
                ESP_BT.write(10);       //delimiter!
                ESP_BT.flush();         //spit it out!
                break;  
            case 6:  
                #ifdef VERBOSE_BT_JOY
                    Serial.print("Button 6:Load next image in SD"); 
                #endif            
                //load next
                //depurar
                //buscando si existe el consecutivo (si hay huecos entre los files; no cooperará)
                load_next_img++;
                //id_requested2 = String(load_next_img);
                bool image_error2;
                // BT_SEND_LOAD_CMD = true;
                image_error2 = prepare_read_and_draw(load_next_img);   //ya había escrito el método: reutilizarlo!
                if(image_error2)
                {
                  load_next_img = -1; //pa que de la vuelta y empiece del comienzo!  
                }
                break;
            case 7:  
            //btn mode (ver si hacer cursor o scroll images)
                #ifdef VERBOSE_BT_JOY
                    Serial.print("Button 7:MODE Live-Not Live"); 
                #endif
                live = !live;   //si estan toggleando entre imágenes; no blinkeo el cursor
                if(live == false)
                {
                    FIND_CURSOR = false;
                }
                else
                {
                    FIND_CURSOR = true;
                }
                break;      
            case 8:
                #ifdef VERBOSE_BT_JOY
                    Serial.print("Button 8: canvas size"); 
                #endif   
                //Me muevo entre canvas size (3 tamaños)
                // limpio lienzo y llevo cursor al origen
                if(canvas_size == 16)
                {
                    canvas_size = 32;
                }
                else if (canvas_size == 32)
                {
                    canvas_size = 64;
                }
                else if (canvas_size == 64)
                {
                    canvas_size = 16;
                }
                // cambiar size me rompe lo que ya estuviera dibujado,
                // lamentablemente cambiar de pixel size no es posible tan facilmente
                clearMatrix(); 
                actualIndex = 0;
                break;                      
            default:
                #ifdef VERBOSE_BT_JOY
                    Serial.print("Not recognized cmd:");
                    for (int bucle=0;bucle<loop_var;bucle++)
                    {
                        Serial.printf("%x",msg_rcv[bucle]);
                    }                    
                    Serial.println("");
                #endif
                break;
            }      
        }
        else if (loop_var == 4) //if more bytes, check completeness of message somehow
        { //4 bytes (numeric- asume RGB(gamma))
            R_color_BT = msg_rcv[0]; 
            G_color_BT = msg_rcv[1];
            B_color_BT = msg_rcv[2];
            Gamma_color_BT = msg_rcv[3];
            DEPOSIT_COLOR = true;
            // ver de pasar color como corresponde...
            // String color_str = rgbToHex(msg_rcv[0],msg_rcv[1],msg_rcv[2]);

            // color_to_deposit = strtoul(color_str.c_str(), NULL, 16);
            color_to_deposit = (long)R_color_BT << 16 | (uint16_t)G_color_BT << 8 | B_color_BT;

            large_canvas_ghost[actualIndex] = color_to_deposit; //to see if its true!

            // Serial.printf("Color to deposit %lx\r\n",color_to_deposit);
            // Serial.flush();
            #ifdef VERBOSE_BT_JOY
            Serial.printf("Color R:%u G:%u B:%u\r\n",R_color_BT,G_color_BT,B_color_BT);
            #endif
            //Verificar operación de "chupar color"
        }
        else if (loop_var == 5)  //check completeness of message somehow
        {   //CLEAR MATRIX COMMAND para que no haya confusiones
             if( msg_rcv[0]== 0xAA && msg_rcv[1] == 0x55 && msg_rcv[2] == 0xAA && msg_rcv[3] == 0x55 && msg_rcv[4] == 0xAA )
            {
                #ifdef VERBOSE_BT_JOY
                    Serial.printf("Clear Canvas command");
                #endif  
                clearMatrix();
            }
            else
            {
                #ifdef VERBOSE_BT_JOY
                    Serial.printf("5 bytes command-unrecognized");
                #endif                 
            }
        }        
        else if (loop_var >= 8)    //si es mayor que los 9 chars de "SaveFile:"
        {   
            //Check for "SaveFile:"hasta 15 chars name"
            #ifdef VERBOSE_BT_JOY
            Serial.println("Asume File Save");
            #endif
            // retraerse el nombre usando el indice loop_var y mandar a guardar
            // ackar!
            if(loop_var == 9)       //Null Name-
            {
                ESP_BT.write(3);        //Error, null name
                ESP_BT.write(10);       //delimiter!
                ESP_BT.flush();   
                #ifdef VERBOSE_BT_JOY
                Serial.println("No Name");
                #endif
            }
            else
            {
                ESP_BT.write(1);        // OK!
                ESP_BT.write(10);       //delimiter!
                ESP_BT.flush();    
                // Verificar si se arregla guardada para la BT app!!!!
                name_to_deferred.clear();
                for(int k=9; k<=loop_var; k++)
                {
                    name_to_deferred += String(msg_rcv[k]);
                }  
                #ifdef VERBOSE_SAVE_BT
                    Serial.println("Save file with name:" + String(name_to_deferred));
                #endif
                //El save desde BT app es siempre desde el array ghost!
                // PERO; debo decirle el tamaño si no lo hará SIEMPRE de 64x64!
                if(canvas_size == 16)
                {
                    SAVE_16_FILE = true;
                }
                if(canvas_size == 32)
                {
                    SAVE_32_FILE = true;
                }
                if(canvas_size == 64)
                {
                    SAVE_LARGE_FILE = true;     //en el main guardaré. Ya sé que todo existe y está ahí!
                }
               /////////////////////////////////////  
                // #ifdef VERBOSE_BT_JOY
                // Serial.println("Retrieve name and save!");
                // #endif
                //
            }
        } 
        else
        {
            ESP_BT.write(2);        //Error de tarjeta o mas de n chars o algo así
            ESP_BT.write(10);       //delimiter!
            ESP_BT.flush();     
            #ifdef VERBOSE_BT_JOY
            Serial.println("Unrecognized: ");   
            for (int bucle=0;bucle<loop_var;bucle++)
            {
                Serial.printf("%x",msg_rcv[bucle]);
            }
            Serial.println("");
            #endif
        }

        // si agarro comandos "por partes" habrá bugs! Hacerlo sufrir y ver qué onda


        }
        loop_var = 0;
    if(CLEAN_ARRAY)
    {
        CLEAN_ARRAY = false;
        #ifdef VERBOSE_BT_JOY
            Serial.println("Clean old data");
        #endif
        for (int clean=0;clean<sizeof(msg_rcv);clean++)
        {
            msg_rcv[clean] = 0;
        }
        // fLUSH remaining chars posibly received
        while(ESP_BT.available() > 0)
        {
            ESP_BT.read();
        }        
    }

}

#endif  //end of BT_JOY_C