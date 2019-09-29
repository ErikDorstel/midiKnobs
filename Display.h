#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13
XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

char const *knobText[64]={"Attack","Hold","Decay","Sustain","Release","Arpeggiator Mode","Arpeggiator Speed","Glissando Speed",\
  "VCO 1 Waveform","VCO 2 Waveform","VCO 1/2 Ratio","VCO 2 Shift","Filter Bypass","Filter Lowpass","Filter Bandpass","Filter Highpass",\
  "LFO VCO Waveform","LFO VCO Phase Start","LFO VCO Level","LFO VCO Frequency","","","","",\
  "LFO Filter Waveform","LFO Filter Phase Start","LFO Filter Level","LFO Filter Frequency","Filter Frequency","Filter Resonance","","VCO 1+2 Level" };
int currScreen=0, maxScreen=3;

void initScreen() {
  tft.begin(); tft.setRotation(3); ts.begin(); ts.setRotation(1); delay(1000);
  tft.fillScreen(ILI9341_BLACK); tft.fillRect(319-50,0,50,50,ILI9341_RED); tft.fillRect(319-50,239-50,50,50,ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE); tft.setFont(Arial_12);
  tft.setCursor(285,17); tft.print("Up"); tft.setCursor(275,209); tft.print("Down"); }

void setGauge(byte g) {
  if (g-(g%8) == currScreen*8) { int y=2+((g%8)*30); int x=knobValues[g]*2;
    tft.fillRect(0,y,x,26,ILI9341_BLUE); tft.fillRect(x+1,y,255-x,26,ILI9341_BLACK);
    tft.setCursor(2,y+7); tft.print(knobText[g]); } }

void setScreen() {
  if (currScreen < 0) { currScreen=maxScreen; } if (currScreen > maxScreen) { currScreen=0; }
  tft.setFont(Arial_12); tft.fillRect(290,112,12,12,ILI9341_BLACK); tft.setCursor(290,112); tft.print(currScreen+1); tft.setFont(Arial_10);
  for (byte z=0;z<=7;z++) { setGauge(z+(currScreen*8)); } }

void getTouch() {
  if (ts.touched()) { TS_Point p=ts.getPoint();
    if (p.y < 2000) { currScreen--; setScreen(); } else { currScreen++; setScreen(); } } }
