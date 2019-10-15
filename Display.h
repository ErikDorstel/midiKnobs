#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define Touch_CS  8
#define Touch_IRQ  2
#define TFT_DC  9
#define TFT_CS 10
XPT2046_Touchscreen ts(Touch_CS); // XPT2046_Touchscreen ts(Touch_CS,Touch_IRQ); for interrupt enabled polling
ILI9341_t3 tft=ILI9341_t3(TFT_CS,TFT_DC);

char const *knobText[10][64]={ {"Attack","Hold","Decay","Sustain","Release","Arpeggiator Mode","Arpeggiator Speed","Glissando Speed",\
  "VCO 1 Waveform","VCO 2 Waveform","VCO 1/2 Ratio","VCO 1/2 Add/Multiply","VCO 2 Shift","VCO 1+2 Level","","",\
  "LFO VCO Waveform","LFO VCO Phase Start","LFO VCO Level","LFO VCO Frequency","VCF Bypass","VCF Lowpass","VCF Bandpass","VCF Highpass",\
  "LFO VCF Waveform","LFO VCF Phase Start","LFO VCF Level","LFO VCF Frequency","VCF Frequency","VCF Resonance","",""},\
  {"Modulator Bottom Frequency","Modulator Top Frequency","Carrier Bottom Frequency","Carrier Top Frequency",\
  "Envelope Speed","Envelope Limiter","Filter Resonance","Output Amplifier",\
  "LFO 1 Waveform","LFO 2 Waveform","VCO 1 Waveform","VCO 2 Waveform","VCO 3 Waveform","VCO 4 Waveform","Modulator Source","Carrier Source",\
  "LFO 1 Level","LFO 2 Level","VCO 1 Level","VCO 2 Level","VCO 3 Level","VCO 4 Level","VCO 1-2 Modulation Depth","VCO 3-4 Modulation Depth",\
  "LFO 1 Frequency","LFO 2 Frequency","VCO 1 Frequency","VCO 2 Frequency","VCO 3 Frequency","VCO 4 Frequency","",""} };

int currApp=0, maxApp=1, currPage[10]={0,0}, maxPage[10]={3,3};

void initDisplay() {
  tft.begin(); tft.setRotation(3); ts.begin(); ts.setRotation(1); delay(1000);
  tft.fillScreen(ILI9341_BLACK); tft.fillRect(319-50,0,50,50,ILI9341_RED); tft.fillRect(319-50,239-50,50,50,ILI9341_RED);
  tft.fillRect(31*2,0,2,319,ILI9341_YELLOW); tft.fillRect(63*2,0,2,319,ILI9341_YELLOW); tft.fillRect(95*2,0,2,319,ILI9341_YELLOW);
  tft.setTextColor(ILI9341_WHITE); tft.setFont(Arial_12); tft.setCursor(275,17); tft.print("Down"); tft.setCursor(285,209); tft.print("Up");
  tft.setCursor(280,119-36); tft.print("App"); tft.setCursor(275,119+4); tft.print("Page"); }

void setGauge(byte g) {
  if (g-(g%8) == currPage[currApp]*8) { int y=2+((g%8)*30); int x=knobValues[g]*2;
    tft.fillRect(0,y,x,26,ILI9341_BLUE); tft.fillRect(x+1,y,255-x,26,ILI9341_BLACK);
    tft.setCursor(4,y+7); tft.print(knobText[currApp][g]); } }

void setPage() {
  if (currPage[currApp] < 0) { currPage[currApp]=maxPage[currApp]; } if (currPage[currApp] > maxPage[currApp]) { currPage[currApp]=0; }
  tft.setFont(Arial_12); tft.fillRect(290,119-16,12,12,ILI9341_BLACK); tft.setCursor(290,119-16); tft.print(currApp+1);
  tft.fillRect(290,119+24,12,12,ILI9341_BLACK); tft.setCursor(290,119+24); tft.print(currPage[currApp]+1); tft.setFont(Arial_10);
  for (byte z=0;z<=7;z++) { setGauge(z+(currPage[currApp]*8)); } }

void getTouch() {
  if (ts.touched()) { TS_Point p=ts.getPoint();
    if ((p.y < 2000) and (p.x > 2000)) { currPage[currApp]--; setPage(); }
    if ((p.y > 2000) and (p.x > 2000)) { currPage[currApp]++; setPage(); }
    if ((p.y < 2000) and (p.x < 2000)) { currApp--; if (currApp<0) { currApp=maxApp; } currPage[currApp]=0; setPage(); }
    if ((p.y > 2000) and (p.x < 2000)) { currApp++; if (currApp>maxApp) { currApp=0; } currPage[currApp]=0; setPage(); } } }
