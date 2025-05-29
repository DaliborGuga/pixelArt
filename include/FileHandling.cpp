#ifndef FILE_HAND_C
#define FILE_HAND_C

#include "../include/FileHandling.h"

// Returns 0 on success
bool init_spi_sd(int num_files)
{
  print_heap(10);
  //ver como definir HSPI (si es que es necesario)
  // sd_spi = new SPIClass(VSPI);
  // sd_spi->begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  //Serial.println("SD_SPI?");
  sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI,SD_CS);
  //Serial.println("UHM?");
  delay(50);


  // if( !SD.begin(SD_CS, sd_spi, 20000000,"",10,false)  )   
  if( !SD.begin(SD_CS, sd_spi,20000000,"",num_files) )
  {
      Serial.println("Card Mount Failed");
      return(1);
  }
  else
  {
      uint8_t cardType = SD.cardType();

      if(cardType == CARD_NONE)
      {
          Serial.println("No SD card attached");
          return(1);
      }
      else
      {
          Serial.print("SD Card Type: ");
          if(cardType == CARD_MMC){
              Serial.println("MMC");
          } else if(cardType == CARD_SD){
              Serial.println("SDSC");
          } else if(cardType == CARD_SDHC){
              Serial.println("SDHC");
          } else {
              Serial.println("UNKNOWN");
          }
      }
      print_heap(11);
      return(0);
  }
}
/*------------------------------------------------------------
                      file handling
  -----------------------------------------------------------*/

void parsePattern(long (&colorArray)[4096]) 
{
  char buf[9];                                      //array zum Speichern eines Hexwertes (temp)
  int i = 0;                                        //Index für das buf array
  int j = 0;                                        //index für das patternArray
  while (patterns.available()) 
  {
    char inChar = patterns.read();                  //ein neuen char einlesen
    byte inCharAscii = inChar;                      //asciiwert des chars speichern
    if (inCharAscii == 10) {                        //ASCII 10 = newline
      buf[i] = '\0';                                //Cstring terminieren
      colorArray[j] = strtoul(buf + 2, NULL, 16);   //cstring in unsigned long umwandeln
      j++;
      i = 0;
    }
    else if (inCharAscii == 13) {                   //ASCII 13 = character return
    }
    else {
      buf[i] = inChar;                              //add the inChar into a buffer
      i++;
    }
  }
}

// Devuelvo size of file para mis métodos
//size_t readFile(int index, long (&colorArray)[4096]) 
size_t readFile(String file_to_read, long (&colorArray)[4096]) 
{ 
  size_t sizeoffile;
  SD.end();
  init_spi_sd(1);
  patterns = SD.open(file_to_read);  //open the file with the given index
  if (patterns) 
  {                                   //opening successful
    Serial.println("Parse pattern");
    sizeoffile = patterns.size();
    parsePattern(colorArray);                       //read the file and write to pattern array
    // patterns.close();
  }
  else 
  {
    patterns.close();
    Serial.println("Error opening file");
    return(0);
  }
  patterns.close();
  return (sizeoffile);
}

// Dir de FS, con posibilidad de subniveles
// Armo un vector v
// y automáticamente vuelco a SD/names.txt
//#define VERBOSE_DIR   
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) 
{
  //DynamicJsonDocument doc(5000);

  #ifdef VERBOSE_DIR
    Serial.printf("Listing directory: %s\r\n", dirname);
  #endif
  files_found = 0;
  v.clear();    //limpio vector al momento de entrar   
  File root = fs.open(dirname);
  if (!root) 
  {
    #ifdef VERBOSE_DIR
      Serial.println("- failed to open directory");
    #endif
    return;
  }
  if (!root.isDirectory()) 
  {
    #ifdef VERBOSE_DIR
      Serial.println(" - not a directory");
    #endif
    return;
  }
  File file = root.openNextFile();
  while (file) 
  {
 
    if (file.isDirectory()) 
    {
      #ifdef VERBOSE_DIR
        Serial.print("  DIR : ");
        Serial.println(file.name());
      #endif
      if (levels) 
      {
        listDir(fs, file.path(), levels - 1);
      }
    } 
    else 
    {
      v.push_back(file.name());
      files_found++;
      #ifdef VERBOSE_DIR
        Serial.print("  FILE: ");
        Serial.print(file.name());
        Serial.print("\tSIZE: ");
        Serial.println(file.size());
      #endif
    }
    file = root.openNextFile();
  }
  file.close();
  root.close();

  File names = SD.open("/names.txt", FILE_WRITE);
  //Serial.println("files in vector:");
  if (names) 
  {
    for (int i=0;i<v.size();i++)
    {
      names.println(v[i].c_str());
      Serial.printf(v[i].c_str());
      Serial.println();
    }
    Serial.println("Archivo names.txt creado a partir de dir(ls) del sistema");
  }
  else 
  {
    Serial.println("No puedo abrir SD para (re)crear names.txt");
  }
  names.close();
  //Serial.println("end of filesin vector");
}

// Hacer un dir, devolver contador con cantidad de files y alojar en algún array conveniente
// si hace falta - poner lo recolectado en el vector v
String getNames() 
{                                 //get the names of the patterns
  Serial.println("GetNames method!");

  String jsonarray = "[\"";                         //names will be send in a JSON array
  File names = SD.open("/names.txt");
  if (names) {
    while (names.available()) {
      char inChar = names.read();                   //read a new char
      byte inCharAscii = inChar;                    //save the ASCII of the char
      if (inCharAscii == 10) {                      //ASCII 10 = newline
        jsonarray += "\",\"";
      }
      else if (inCharAscii == 13) {                 //ASCII 13 = character return
      }
      else {
        jsonarray += inChar;                        //write the char into the array
      }
    }
    jsonarray += "\"]";
    names.close();
    return jsonarray;
  } 
  else 
  {
    names.close();  //lo cierro igual¿?
    Serial.println("Cant open names file");
    jsonarray += "\"]"; //dont knoww if necessary
    return jsonarray;
  }
}

// 
long findPos(const char searchString[20]) 
{         //finds the position of a string in a file
  Serial.println("Find pos routine");
  File names = SD.open("/names.txt");
  bool found = true;
  // long pos = 0;
  long pos = -1;
  int i = 0;                                        //Index für das buf array

  while (names.available()) 
  {
    Serial.println("Name available");
    char inChar = names.read();                     
    byte inCharAscii = inChar; 
    if (inCharAscii == 10) 
    {                        //ASCII 10 = newline
    Serial.println("New line");
    //pos = names.position();
      if (found == true) 
      {                          //if the characters of one line match the search string
        Serial.println("string found");
        return pos;
      }
      i = 0;
      found = true;
      pos = names.position();                       //save the position of the beginning of the line
    }
    else if (inCharAscii == 13) 
    {                   //ASCII 13 = carriage return
    Serial.println("carr ret");
    }
    else 
    {
      Serial.println("non special char");
      if (found == true) 
      {
        if (inChar == searchString[i]) 
        {            
          Serial.println("True:");
          found = true;
          Serial.println(String(inChar));
        }
        else 
        {
          Serial.println("False:");
          found = false;
          Serial.println(String(inChar));
        }
        i++;
      }
    }
  }
  names.close();
  return pos;
}

#endif