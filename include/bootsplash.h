// Robando scrolling text para cadenas "largas"
uint16_t text_length;
static time_t last_t;
uint32_t lastTime = 0, lastTim = 0; // millis() memory
String Message = "Connectez-vous au réseau LylaArtToy. Sur le site www.LylArt.com (ou à l'adresse 192.168.2.1) vous trouverez votre plaisir";
char crap[80];
int      FPS = 20;       // Maximum frames-per-second
uint32_t prevTime = 0; // For frame-to-frame interval timing
int h, m, s, d, yr, ft=20, tp=3000, xpos, xpo, xp=30;
uint8_t r = 0, g = 0, b = 0;
String text0, text1;
uint8_t  display = 0;
time_t t;

void scroll_text(String text,int ypos);
void scroll_tex(String text);
void getMesge();
void scroll_texto();