#include <Metro.h>

const bool logging=false;
const bool hc4067_0=true;
const bool hc4067_1=true;
const bool hc4067_2=false;
const bool hc4067_3=false;
const byte MIDIchannel=0;
Metro timer = Metro(10000);

void setup() {
  if (logging) { Serial.begin(9600); }
  Serial1.begin(31250,SERIAL_8N1);
  pinMode(2, OUTPUT); pinMode(3, OUTPUT); pinMode(4, OUTPUT); pinMode(5, OUTPUT); pinMode(13, OUTPUT);
  analogReadResolution(7);
  delay(1000); timer.interval(10); timer.reset(); }
  
void loop() {
  static byte knobValues[64], counter, curPort;
  byte mulPort, knobValue;
  if (timer.check() == 1) {
    digitalWrite(13, LOW);
    for (mulPort=0;mulPort<=15;mulPort++) {
      selectPort(mulPort); delayMicroseconds(200);
      if (hc4067_0) { knobValue=analogRead(A0); if (knobValue!=knobValues[mulPort]) {
        knobValues[mulPort]=knobValue; sendMidi(mulPort,knobValue); digitalWrite(13, HIGH); } }
      if (hc4067_1) { knobValue=analogRead(A1); if (knobValue!=knobValues[mulPort+16]) {
        knobValues[mulPort+16]=knobValue; sendMidi(mulPort+16,knobValue); digitalWrite(13, HIGH); } }
      if (hc4067_2) { knobValue=analogRead(A2); if (knobValue!=knobValues[mulPort+32]) {
        knobValues[mulPort+32]=knobValue; sendMidi(mulPort+32,knobValue); digitalWrite(13, HIGH); } }
      if (hc4067_3) { knobValue=analogRead(A3); if (knobValue!=knobValues[mulPort+48]) {
        knobValues[mulPort+48]=knobValue; sendMidi(mulPort+48,knobValue); digitalWrite(13, HIGH); } } }

  if (counter>100) { counter=0;
    if (curPort>15) { curPort=0; }
    selectPort(curPort); delayMicroseconds(200);
    if (hc4067_0) { sendMidi(curPort,analogRead(A0)); }
    if (hc4067_1) { sendMidi(curPort+16,analogRead(A1)); }
    if (hc4067_2) { sendMidi(curPort+32,analogRead(A2)); }
    if (hc4067_3) { sendMidi(curPort+48,analogRead(A3)); }
    curPort++; } counter++; } }

void selectPort(byte port) { digitalWrite(2, port&1); digitalWrite(3, port&2); digitalWrite(4, port&4); digitalWrite(5, port&8); }
  
void sendMidi(byte knobNumber, byte knobValue) {
  Serial1.write(0xb0+MIDIchannel); Serial1.write(knobNumber); Serial1.write(knobValue);
  if (logging) { Serial.print(knobNumber); Serial.print(" "); Serial.println(knobValue); } }
