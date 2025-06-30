#ifndef APSERVER_C 
#define APSERVER_C

#include "../include/APServer.h"
#include "../include/MatrixFunctions.h"
#include "../include/FileHandling.h"
#include <string.h>


/*------------------------------------------------------------
                      server handles
  -----------------------------------------------------------*/
void WiFiAPConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Activity bit set!");
    ACTIVITY_BIT = true;
}
void register_events()
{
  WiFi.onEvent(WiFiAPConnected, ARDUINO_EVENT_WIFI_AP_STACONNECTED);
}

void handleRoot() 
{     
  // // ========== SD ========== Working and tested  
  // server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
  //   Serial.println("Mother");
  //   // voy a ver si cerrando y abriendo fs todo el tiempo libera "algo"
  //   // y ahace cooperar
  //   SD.end();
  //   bool SD_ERROR =init_spi_sd(1);
  //     if(!SD_ERROR)
  //     {
  //     request->send(SD, "/data/favicon.ico", "image/png");
  //     }
  //     // do not answer anything
  // });  
  // server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
  //     Serial.println("Foca");
  //     // voy a ver si cerrando y abriendo fs todo el tiempo libera "algo"
  //     // y la hace cooperar: SI! si lo hace!
  //     SD.end();
  //     bool SD_ERROR = init_spi_sd(1);
  //     if(!SD_ERROR)
  //       {
  //         request->send(SD, "/data/index.html");
  //       }
  //       else
  //       {
  //         request->send(404,"text/html","File not found");
  //       }       
  // }); 
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  //   Serial.println("Foca");
  //   // voy a ver si cerrando y abriendo fs todo el tiempo libera "algo"
  //   // y la hace cooperar: SI! si lo hace!
  //   SD.end();
  //   bool SD_ERROR = init_spi_sd(1);
  //   if(!SD_ERROR)
  //     {
  //       request->send(SD, "/data/index.html");
  //     }
  //     else
  //     {
  //       request->send(404,"text/html","File not found");
  //     }       
  // }); 
  // server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
  //     Serial.println("Foca2");
  //     request->send(SD, "/data/index.html");
  // });
  // Hice link derecho en index; ya no hay método openConverter!
  server.on("/pixart1-1-0.html", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("Foca");
      // voy a ver si cerrando y abriendo fs todo el tiempo libera "algo"
      // y ahace cooperar
      // SD.end();
      // bool SD_ERROR = init_spi_sd(1);
      bool SD_ERROR = false;
        if(!SD_ERROR)
        {
          ACTIVITY_BIT = true;
          request->send(SD, "/data/pixart1-1-0.html");
        }
        else
        {
          request->send(404,"text/html","File not found");
        }  
  }); 

// With "manual" chunked (same as server.on) but slower
// y no manda a pedir favicon.ico; pero puedo ver cuanto tardan los chunks
// y cuanto buffer hay; que con server.on no lo veo
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // voy a ver si cerrando y abriendo fs todo el tiempo libera "algo"
    // y ahace cooperar
    ACTIVITY_BIT = true;
    // SD.end();
    // bool SD_ERROR = init_spi_sd(1);
    bool SD_ERROR = false;
    if(!SD_ERROR)
      {
        const File SDfile = SD.open("/data/index.html", FILE_READ);
        if (SDfile){
          Serial.printf("SD File exists [%d]\r\n", SDfile);
        } else {
          Serial.printf("SD File DOESN'T exists [%d] <<< ERROR !!!\r\n", SDfile);
        }
        request->send(SD, "/data/index.html");      //ver si puede servir todo el archivo de una o en chunks automáticamente
      }
      else
      {
        request->send(404,"text/html","File not found");
      }        
    }
  );
}



void handleNotFound() 
{
  String message = "File Not Found\n\n";
  server.onNotFound( [](AsyncWebServerRequest *request){
    // request->send(404, "text/plain", message);
    request->send(404);
  });
}


// Comandos Clear matrix, draw pixel (color) y paint area (base color)
void handlePlain() 
{                                               //handles the post requests for clearing the canvas and drawing a pixel
  server.on("/live", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST method!");
    //request->send(LittleFS, "/index.html", String(), false);
    if(request->hasArg("cl"))
    {
      Serial.println("Clear Matrix");
      clearMatrix();
    }
    else if(request->hasArg("pt"))
    {
      FILL_DEFERRED = true;
      fill_color_current_color = strtoul(request->arg("cc").c_str(), NULL, 16);
      fill_color_reference_color = strtoul(request->arg("rc").c_str(), NULL, 16);
      fill_x = request->arg("x").toInt();
      fill_y = request->arg("y").toInt();
      Serial.println("Fill color - deferred on x:"+String(fill_x) +"y:"+String(fill_y)+"Currcolor:"+String(fill_color_current_color)+"RefColor"+String(fill_color_reference_color) );
    }
    else
    {
      //Serial.println("Draw pixel:" + String (request->arg("i").toInt()) );
      //i for the index, c for the color
      draw(request->arg("i").toInt(), strtoul(request->arg("c").c_str(), NULL, 16));
      // El ghost es la copia local en el ESP de lo que hacen en el canvas web
      // Lo uso para despues volcar a memoria si quieren guardar.
      large_canvas_ghost[request->arg("i").toInt()] = strtoul(request->arg("c").c_str(), NULL, 16);
      //color_to_deposit = strtoul(request->arg("c").c_str(), NULL, 16); //Me agarro el color 
    }
    request->send(200);
  });  
}

// Cuando me piden names; permito que pueda ser chunkeado(entregado por partes)
void handleGetNames() 
{                                                //handles the request for getting the names of the stored patterns
 server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("Get names from SD card (hopefully)");
      print_heap(111);
      listDir(SD,"/img",0);
      request->send(SD, "/names.txt", "text/html");
      print_heap(112);
      //Verificar si names llega al punto de ser chunkeable! igual creo
      //estar seguro que el método request->send sabe manejarlo
  });
}

///////////////////////////////////////////////
// Métodos para leer patrones guardados en la SD del ESP
// e imprimirlos en el canvas web: pueden ir chunkeados
// (y lo harán los de 32 y 64 SIEMPRE)
// #define VERBOSE_HANDLE_LOAD_CHUNK
// #define VERBOSE_HANDLE_LOAD
void handleLoad() 
{                                               //handles loading of a pattern
  server.on("/load", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("Load File on pattern!");
    Serial.println(request->args());
    if(request->hasArg("id"))
    {
      //int arg_int;
      //arg_int = request->arg("id").toInt();
      ruta = "/img/";
      name_to_load.clear();
      name_to_load = v[request->arg("id").toInt()]; 
      ruta += name_to_load;
      //name_to_load = v[request->arg("id").toInt()];
      Serial.println(ruta.c_str());
      //String id_requested = "/" + request->arg("id") + ".txt";
      // SD.end();
      // init_spi_sd(1);
      File loadPattern = SD.open(ruta.c_str(), FILE_READ, false);
      if (loadPattern ) 
      {
        Serial.println("Get size of file.16 by default!");
        size_t estimated_size_canvas = loadPattern.size();
        loadPattern.close();  
        // SD.end();
        Serial.println("Of size:"+String(estimated_size_canvas));
        int bucle_read_file = 255;
        canvas_size = 16;                 //default, 
        if(estimated_size_canvas > 2304) //if 32x32 canvas: file size will be greater than..
        {
          Serial.println("or 32");
          bucle_read_file = 1023;    
          canvas_size = 32; 
        }
        if(estimated_size_canvas > 20000) //if 64x64
        {
          Serial.println("or 64");
          bucle_read_file = 4096;    
          canvas_size = 64;   
        }
                                                //close the file      
        PRINT_SCREEN_DIFERIDO = true;
        // los método se me cuelgan cuando el programa crece mucho
        // los hago en el main!
        //file_to_print_deferred = request->arg("id").toInt();
        estimated_size_for_deferred_print = estimated_size_canvas;
        //contesto
        request->send(SD, ruta, "text/html");
      } 
      else 
      {                                                        
        // debería ser medio imposible que llegue aquí, pero dejo por las dudas
        // si alguien borra de la SD el file nro (solicitado) fallará!
        Serial.println("Cant open names file"); 
        request->send(404, "text/plain", "Error. File does not exist");
      }
    }
    else
    {
      // acá tampoco podría llegar, porque no pueden hacer click en un nombre de archivo
      // que NO existe (no hay botón generado) dejo igual por claridad
      // (y por si la tarjeta se saca sobre la marcha!)
      #ifdef VERBOSE_HANDLE_LOAD
      Serial.println("NO arg ID");
      #endif
      request->send(200, "text/plain","No id to read");
    }
  });  
}

#define VERBOSE_HANDLE_SAVE
// método save. Crea archivo con el nombre pasado como argumento-diferido al callback
// Lo hace en entorno de main loop, por falta de descriptores y heap y mierdas
void handleSave() 
{
  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request)
  {
      print_heap(15);
      SKIP_NAMES_CREATION = false;  //allow re-listing of names, to include newly created image
      name_to_deferred.clear();
      name_to_deferred = request->arg("name");

      #ifdef VERBOSE_HANDLE_SAVE
        Serial.println("Save to SD card-deferred from callback");
        Serial.println("pt" + String(request->arg("pt")));
        Serial.println("Name:" + name_to_deferred);
      #endif

      if(canvas_size == 64)
      {
        SAVE_LARGE_FILE = true; 
      }
      if(canvas_size == 32)
      {
        SAVE_32_FILE = true; 
      }
      if(canvas_size == 16)
      {
       SAVE_16_FILE  = true; 
      }
      request->send(200, "text/plain", "done");
      print_heap(16);
  });
}

// Borra desde el archivo escogido PARA ABAJO!
// Y luego cuando grabo otro queda como el OJETE!
// Y si pongo el nombre de archivo en el nombre de archivo?
// arreglar función cuando pongamos el explorador de archivos
// o luego de leer un file, poder mandar a borrarlo!
// simplemente hacer delete del archivo y permitir listdir
void handleDelete()
 {                                             //response to the client
  server.on("/delete", HTTP_POST, [](AsyncWebServerRequest *request){
    long pos = findPos(request->arg("name").c_str());                 //find the position of the name to delete in the name file
    File names = SD.open("/names.txt", FILE_WRITE);
    Serial.println("Position:"+ String(pos) );
    names.seek(pos);    
    Serial.println("Position1:"+ String(names.position()) );  //add by guga 
                                               //open the file with the cursor at the pos
    names.write('^');                                               //^ is the character for deleted names
    for (int i = 0; i < request->arg("name").length(); i++) {
      names.write(' ');                                             //there is no easy way to really delete something from a file so we just ust spaces
    }
    names.close();
    request->redirect("/"); 
  });
}

// Toggle mode Live interact or portrait display mode
void handleMode() 
{                                               //displaying saved patterns in a loop or draw live 
  server.on("/mode", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("MODE selection");
      if(request->hasArg("mode"))
      {
        if(request->arg("mode") == "true")
        {
          live = true;
          Serial.println("MODE TRUE");
          FIND_CURSOR = true;
        }
        else
        {
          live = false;
          Serial.println("MODE FALSE");
          FIND_CURSOR = false;
        }
      }
      request->send(200);
  });   
}

// Limpiar el canvas en el ESP!
void handleChangeCanvas()
{
  server.on("/changecanvas", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("Change Canvas size");
      //request->send(LittleFS, "/index.html", String(), false);
      if(request->hasArg("canvas"))
      {
        if(request->arg("canvas") == "16")
        {
          Serial.println("Canvas 16x16");
          canvas_size = 16;
        }
        else if(request->arg("canvas") == "32")
        {
          Serial.println("Canvas 32x32");
          canvas_size = 32;
        }
        else if(request->arg("canvas") == "64")
        {
          Serial.println("Canvas 64x64");
          canvas_size = 64;
        }

        clearMatrix();
      }
      request->send(200);
  });     
}

void handleChangeColor()
{
  server.on("/changeColor", HTTP_POST, [](AsyncWebServerRequest *request){
  Serial.println("POST NEW color:");
  Serial.printf(request->arg("color").c_str());
  if(request->hasArg("color"))
    {
      color_to_deposit = strtoul(request->arg("color").c_str(), NULL, 16); //Me agarro el color             
      Serial.printf("Color %lu\r\n",color_to_deposit);
    }
    request->send(200);
  });  
}

void hadleGetPixelColor()
{
  server.on("/getPixelColor", HTTP_GET, [](AsyncWebServerRequest *request){
    String message;
    // message = "PixColor=";
    message += String(pattern[actualIndex]);    //el color en string sin el #!!
    //message += pattern[actualIndex];  //seguramente rompo todo! mandar stringssss
    request->send(200, "text/plain", message);
    color_to_deposit = pattern[actualIndex]; //y lo tomo como para usar por la aplicación
  });  
}

// Serving apk for Android Bluetooth Joystick
// Must disable Play Protect, allow not signed apps and give near devices permission (BT access)
// check when 0 is returned!!!!!
void handleAPKDownload()
{
  server.on("/downloadAPK", HTTP_GET,[](AsyncWebServerRequest *request){
    Serial.printf("Request to download apk file");
    const File SDfile = SD.open("/apk/BT_Joy.apk", FILE_READ);
    if(SDfile)
    {
      request->send(SDfile, "/apk/BT_Joy.apk","application/octet-stream" , true, NULL);
    }
    else
    {
      request->send(404,"text/html","File not found on SD");
    }
  });
}

// Me llegarán Jsons de (max 256 pixeles)
// Ver de recibirlos; desparsearlos e imprimirlos en canvas!
// para retraer los params!
// https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/
// Leer este!!!!
// https://raphaelpralat.medium.com/example-of-json-rest-api-for-esp32-4a5f64774a05
// https://techtutorialsx.com/2018/10/12/esp32-http-web-server-handling-body-data/

//#define VERBOSE_DEBUG_JSON
//#define VERBOSE_SLIM_JSON
void handleJsonFromConverter()
{
  server.on("/json/state",HTTP_POST,[](AsyncWebServerRequest * request){},NULL,[](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {

    #ifdef VERBOSE_DEBUG_JSON
    Serial.print("Index:");
    Serial.println(String(index));   
    Serial.print("Total:");
    Serial.println(String(total));
    #endif
    // char pixelartconverter_json_string[2500]; //era global, lo traigo aca a ver si arregla la puta SD
    int auto_size;
    if(index == 0)  //En el "primer chunk" veo el tamaño total. Veo de recogerlo y DESPUES deserializarlo
    {
      ANALIZAR_JSON = false;
      #ifdef VERBOSE_DEBUG_JSON
      Serial.println("First Chunk");
      #endif
      total_size_of_portion = total;  //
      total_bytes_received = 0;

      for (size_t i = 0; i < len; i++) 
      {
        pixelartconverter_json_string[i]  = data[i];
        total_bytes_received++;
        if((total_bytes_received) >= total_size_of_portion)
        {
          #ifdef VERBOSE_DEBUG_JSON
          Serial.println("End of. All bytes collected in one chunk!");
          #endif

          ANALIZAR_JSON = true;
          break;
        }        
      }
    }
    else
    {
      #ifdef VERBOSE_DEBUG_JSON
      Serial.println("Another Chunk");
      #endif
      for (size_t i = 0; i < len; i++) 
      {
        pixelartconverter_json_string[i+index]  = data[i];
        total_bytes_received++;
        if((total_bytes_received) >= total_size_of_portion)
        {
          #ifdef VERBOSE_DEBUG_JSON
          Serial.println("End of. All bytes collected");
          #endif
          ANALIZAR_JSON = true;
          break;
        }
      }      
    }

    if(ANALIZAR_JSON == true)
    {
      int iterar_n_veces = 256;
      String pixel_str;
      //print_heap(200);
  //      Serial.print("Free heap: ");
  //      Serial.println(ESP.getFreeHeap());
      // Serial.print("Free heap: ");
      // Serial.println(ESP.getMinFreeHeap());
      // Tuve unos quilombos de la madre con el Json que decía NoMemory
      // y el Dynamic y el static y la concha de su hermana!
      // Con static mucho muy grande logre que el deserialize coopere
      // así que así quedará
      // DynamicJsonDocument doc(5000);
     // StaticJsonDocument<3000> doc;
      DynamicJsonDocument doc(5000);
      
      err = deserializeJson(doc, pixelartconverter_json_string);
      // err = deserializeJson(doc, pntr_json);
      #ifdef VERBOSE_SLIM_JSON
       Serial.println("Deserialization returns:");
       Serial.println(err.c_str());
      #endif
      if(!err)
      {
        canvas_size = doc["on"];
        #ifdef VERBOSE_DEBUG_JSON
        Serial.println("Received size " +String(canvas_size));
        #endif
        // compatibilidad hacia atrás con lo que ya tengo escrito
        if(canvas_size == 16)
        {
          auto_size = 0;
        }
        else if (canvas_size == 32)
        {
          auto_size = 2304;
        }
        else
        {
          auto_size = 20000;
        }

        offset_of_pixel = doc["seg"]["i"][0];
        //hacerlo en funcion del size del array
        #ifdef VERBOSE_SLIM_JSON
          Serial.println("Offset: " + String(offset_of_pixel));
        #endif
        #ifdef VERBOSE_DEBUG_JSON
        Serial.println("Offset: " + String(offset_of_pixel));
        #endif
        for(int j=1;j<=iterar_n_veces;j++)
        {
        // int nPixels = doc["seg"]["i"].size() - 1; // el primero es el offset
        // char buf[7];
        // for (int j = 1; j <= nPixels; j++)        
        // {
        //   const char* hex = doc["seg"]["i"][j];
        //   strncpy(buf, hex, 6);
        //   buf[6] = '\0'; // null terminator
        //   long color_for_canvas = strtoul(buf, NULL, 16);   
          
          // Chat GPT sugerencia-usar char buf . siquiero volver a la veisón anterior
          //dejo acá comentado
          pixel_str = doc["seg"]["i"][j].as<String>();  //Esto esta ok!
          #ifdef VERBOSE_DEBUG_JSON
          // Serial.print(pixel_str);
          // Serial.print("---");
          #endif
          String red,green,blue;
          long RedC,GreenC,BlueC;
          red = pixel_str.substring(0,2);
          green = pixel_str.substring(2,4);
          blue = pixel_str.substring(4,6);
          long color_for_canvas = strtoul(pixel_str.c_str(), NULL, 16);

          //El array del Json tiene el primer pixel (pixel 0 de MI array)
          // en la posición 1; por eso resto uno acá
          pattern[offset_of_pixel+j-1] = color_for_canvas;
          #ifdef VERBOSE_DEBUG_JSON
          // Serial.print("-");
          // Serial.printf("%lu",color_for_canvas);
          // Serial.print("-");
          // long suma = offset_of_pixel+j;
          // Serial.printf("%lu",suma);
          // Serial.print("-");
          // Serial.printf("%lu",large_canvas_ghost[offset_of_pixel+j]);
          // Serial.println("");
          #endif
        }
      }
      else
      {
        ANALIZAR_JSON = false;  //hubo error, no tengo bien nada para plantar en el canvas!
        #ifdef VERBOSE_SLIM_JSON
          Serial.println("Json error! Check what to do!");

        #endif
      }
      //print_heap(201);
    } //end of if ANALIZAR_JSON
      
    if(ANALIZAR_JSON == true)
    {
      ANALIZAR_JSON = false;
      if(!err)    //solo si no hubo error
      {
        //print_heap(300); siempre va y vuelve con lo mismo 300-400
        showPattern(auto_size);
        //print_heap(400);
      }
    }
  
    // Respondo siempre esta mierda para que me siga mandando chunks (si los hay)
    if(!err)
      {
        request->send(200, "application/json", "{\"id\":0}");
      }
    else
      {
        request->send(400); //ver si hace que reenvíe el chunk actual
      }

  });  
}

// Cuando pinten con fill flood, mando todo el canvas una vez que 
// termine la iteración- en chunks
void handleUploadPattern()
{
  server.on("/uploadPatternChunk", HTTP_POST, [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      Serial.println("UploadPatternChunk callback");
      Serial.flush();
      StaticJsonDocument<2048> doc;  // Ajusta el tamaño según el chunk
      DeserializationError error = deserializeJson(doc, data);
      
      if (error) {
        Serial.println("NOT JSON");
        Serial.flush();
        request->send(400, "text/plain", "Invalid JSON");
        return;
      }

      //int CANVAS_WIDTH = canvas_size;

      JsonArray chunk = doc["pattern"];
      int chunkIndex = doc["chunkIndex"];
      int totalChunks = doc["totalChunks"];
      Serial.println("chunkIndex:"+String(chunkIndex)+"total:"+String(totalChunks));

      if (expectedTotalChunks == -1) {
        Serial.println("First!");
        expectedTotalChunks = totalChunks;
        receivedPatternChunks.resize(totalChunks);
      }

      // Guarda el chunk en su índice correspondiente
      String chunkData = "";
      for (JsonVariant color : chunk) {
        chunkData += color.as<String>() + ",";  // Separador para unir luego
      }

      receivedPatternChunks[chunkIndex] = chunkData;
      receivedChunks++;

      if (receivedChunks >= expectedTotalChunks) {
        // Ya llegaron todos los chunks
        Serial.println("Todos los chunks recibidos, reconstruyendo patrón...");

        // Reconstruir el arreglo completo
        String fullPatternString = "";
        for (int i = 0; i < receivedPatternChunks.size(); i++) {
          fullPatternString += receivedPatternChunks[i];
        }

        // Separar colores
        std::vector<String> fullPattern;
        int start = 0;
        while (start < fullPatternString.length()) {
          int comma = fullPatternString.indexOf(',', start);
          if (comma == -1) break;
          fullPattern.push_back(fullPatternString.substring(start, comma));
          start = comma + 1;
        }

        // Aquí puedes procesar fullPattern para actualizar tu matriz LED
        // Por ejemplo:
        for (int i = 0; i < fullPattern.size(); i++) {
          String color = fullPattern[i];
          long numeric_color = strtoul(color.c_str(), NULL, 16);
 //         int x = i % CANVAS_WIDTH;
 //         int y = i / CANVAS_WIDTH;
          // setPixel(x, y, color);
          draw(i, numeric_color);
          Serial.printf("Pixel (%d): #%d\n",i,numeric_color);
        }

        // Limpiar para siguiente uso
        receivedPatternChunks.clear();
        expectedTotalChunks = -1;
        receivedChunks = 0;

        request->send(200, "text/plain", "Pattern completo recibido");
      } else {
        // Chunk recibido, esperando más
        request->send(200, "text/plain", "Chunk recibido");
      }
  });

}
// Quizá debiera re-razonar el proyecto con WS pero creo que ya es tarde
// la elección debió ocurrir antes que se convierta en el mostruo que es
// Quizá para montar un file manager o un web serial para debug. 
/*
// Jugando con web sockets!
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data,
               size_t len)
{
  if (type == WS_EVT_CONNECT)
  {
    // Serial.printf("ws[Server: %s][ClientID: %u] WSClient connected\n", server->url(), client->id());
    WS_CLIENT_CONNECTED = true;
    // Serial.println("Must send canvas to web app");
    // client->text("Hello Client");
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.printf("ws[Server: %s][ClientID: %u] WSClient disconnected\n", server->url(), client->id());
    WS_CLIENT_CONNECTED = false;
  }
  else if (type == WS_EVT_ERROR)
  {
    //error was received from the other end
    Serial.printf("ws[Server: %s][ClientID: %u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg),
                  (char*)data);
  }
  else if (type == WS_EVT_PONG)
  {
    //pong message was received (in response to a ping request maybe)
    Serial.printf("ws[Server: %s][ClientID: %u] pong[%u]: %s\n", server->url(), client->id(), len,
                  (len) ? (char*)data : "");
  }
  else if (type == WS_EVT_DATA)
  {
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;

    if (info->final && info->index == 0 && info->len == len)
    {
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[Server: %s][ClientID: %u] %s-message[len: %llu]: ", server->url(), client->id(),
                    (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

      if (info->opcode == WS_TEXT)
      {
        data[len] = 0;
        Serial.printf("%s\n", (char*)data);
      }
      else
      {
        for (size_t i = 0; i < info->len; i++)
        {
          Serial.printf("%02x ", data[i]);
        }

        Serial.printf("\n");
      }

      if (info->opcode == WS_TEXT)
        client->text("Got your text message");
      else
        client->binary("Got your binary message");
    }
    else
    {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if (info->index == 0)
      {
        if (info->num == 0)
        {
          Serial.printf("ws[Server: %s][ClientID: %u] %s-message start\n", server->url(), client->id(),
                        (info->message_opcode == WS_TEXT) ? "text" : "binary");
        }

        Serial.printf("ws[Server: %s][ClientID: %u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num,
                      info->len);
      }

      Serial.printf("ws[Server: %s][ClientID: %u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(),
                    info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);

      if (info->message_opcode == WS_TEXT)
      {
        data[len] = 0;
        Serial.printf("%s\n", (char*)data);
      }
      else
      {
        for (size_t i = 0; i < len; i++)
        {
          Serial.printf("%02x ", data[i]);
        }

        Serial.printf("\n");
      }

      if ((info->index + len) == info->len)
      {
        Serial.printf("ws[Server: %s][ClientID: %u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);

        if (info->final)
        {
          Serial.printf("ws[Server: %s][ClientID: %u] %s-message end\n", server->url(), client->id(),
                        (info->message_opcode == WS_TEXT) ? "text" : "binary");

          if (info->message_opcode == WS_TEXT)
            client->text("I got your text message");
          else
            client->binary("I got your binary message");
        }
      }
    }
  }
}
*/

#endif