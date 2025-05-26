#ifndef BOOTSPLASH_C
#define  BOOTSPLASH_C
    
    // #include <main.h>
    #include <../include/bootsplash.h>

//Robando scrolling text de por ahí
void getMesge()
{ 
  text1 = Message; 
  display = 0;
}


void scroll_text(String text,int ypos) 
{
  text_length = 64 + (text.length() * 12);
  dma_display->fillRect(0, ypos, 64, 12, myBLACK);
  int y = r;
  //dma_display->setFont(&atawi12b);
  dma_display->setCursor(xpos, ypos);
  for (int x = 0; x < text.length(); x++) 
  {
    //dma_display->setTextColor(myCOLORS[y]);
    dma_display->print(text[x]);
    y++;
  if (y > 9) { y = 0; }
  }
  dma_display->setFont();
  xpos--;
  if (xpos < 64-text_length) {xpos = 64, getMesge();}
}

void scroll_tex(String text)
{
  text_length = 64 + (text.length() * 12);
  dma_display->fillRect(0, 0, 64, 6, myBLACK);
  int yy = r;
  //dma_display->setFont(&atawi8b);
  dma_display->setCursor(xpo, 0);
  for (int x = 0; x < text.length(); x++)
  {
      //dma_display->setTextColor(myCOLORS[yy]);
      dma_display->print(text[x]);
      yy++;
      if (yy > 9) 
      {
         yy = 0; 
      }
  }
}

void scroll_texto()
{
  t = time(NULL);
  if (millis() - lastTim >= xp) 
  {
    scroll_text(Message, 56);
    lastTim = millis();
  }

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From: https://gist.github.com/davidegironi/31sSySho9yxbVpnF7UxSXgWib6eGG8Prc8
uint16_t colorWheel(uint8_t pos) {
  if(pos < 85) {
    return dma_display->color565(pos * 3, 255 - pos * 3, 0);
  } else if(pos < 170) {
    pos -= 85;
    return dma_display->color565(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return dma_display->color565(0, pos * 3, 255 - pos * 3);
  }
}

void SplashScreenWeb(int colorWheelOffset)
{
  // draw text with a rotating colour
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(true); // Don't wrap at end of line - will do ourselves

  dma_display->setCursor(4, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  const char *str = "- LYLArt -Pixel Art";
  // const char *str = "- LYLArt -Pixel Art";
  // const char *str2 = "Toile de Peinture";
  
  for (w=0; w<=9; w++) {
    dma_display->setTextColor(colorWheel((w*32)+colorWheelOffset));
    dma_display->print(str[w]);
  }
  dma_display->setCursor(4, 8);    // next line
  for (w=10; w<=18; w++) {
    dma_display->setTextColor(colorWheel((w*32)+colorWheelOffset));
    dma_display->print(str[w]);
  }
  
  dma_display->setCursor(8, 24);
  dma_display->setTextColor(dma_display->color444(15,64,15));
  //15,64,15 un buen lila
  dma_display->println("toile de");
  dma_display->setCursor(8, 32);
  dma_display->println("peinture");
 
  dma_display->setCursor(0, 48);
  dma_display->setTextColor(dma_display->color444(30,70,45));
  dma_display->print("LylaArtToy");

  dma_display->setTextWrap(false);
  dma_display->setCursor(0, 56);
  dma_display->println("192.168.2.1");  
}

void SplashScreenBT(int colorWheelOffset)
{
  // draw text with a rotating colour
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(true); // Don't wrap at end of line - will do ourselves
  dma_display->setCursor(4, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  const char *str = "- LYLArt -Pixel Art";
  // const char *str = "- LYLArt -Pixel Art";
  // const char *str2 = "Toile de Peinture";
  
  for (w=0; w<=9; w++) {
    dma_display->setTextColor(colorWheel((w*32)+colorWheelOffset));
    dma_display->print(str[w]);
  }
  dma_display->setCursor(4, 8);    // next line
  for (w=10; w<=18; w++) {
    dma_display->setTextColor(colorWheel((w*32)+colorWheelOffset));
    dma_display->print(str[w]);
  }
  
  dma_display->setCursor(8, 24);
  dma_display->setTextColor(dma_display->color444(15,64,15));
  //15,64,15 un buen lila
  dma_display->println("toile de");
  dma_display->setCursor(8, 32);
  dma_display->println("peinture");
 
  dma_display->setCursor(0, 40);
  dma_display->setTextColor(dma_display->color444(30,70,45));
  dma_display->print("Please use");

  dma_display->setCursor(0, 48);
  dma_display->setTextColor(dma_display->color444(30,70,45));
  dma_display->print("LylaArt BT");

  dma_display->setTextWrap(false);
  dma_display->setCursor(0, 56);
  dma_display->println("Joy app");  
}


#endif