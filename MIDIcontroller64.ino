const bool logging=false;
const bool hc4067_0=true;
const bool hc4067_1=true;
const bool hc4067_2=false;
const bool hc4067_3=false;
const int MIDIchannel=1;

void setup() {
  if (logging) { Serial.begin(9600); }
  Serial1.begin(31250);
  pinMode(2, OUTPUT); pinMode(3, OUTPUT); pinMode(4, OUTPUT); pinMode(5, OUTPUT);
  analogReadResolution(7); }
  
void loop() {
  static int knobs[64],counter,curPort;
  int mulPort,knob;
  
  for (mulPort=0;mulPort<=15;mulPort++) {
    selectPort(mulPort);
    if (hc4067_0) { knob=analogRead(A0); if (knob!=knobs[mulPort]) { knobs[mulPort]=knob; sendMidi(mulPort,knob); } }
    if (hc4067_1) { knob=analogRead(A1); if (knob!=knobs[mulPort+16]) { knobs[mulPort+16]=knob; sendMidi(mulPort+16,knob); } }
    if (hc4067_2) { knob=analogRead(A2); if (knob!=knobs[mulPort+32]) { knobs[mulPort+32]=knob; sendMidi(mulPort+32,knob); } }
    if (hc4067_3) { knob=analogRead(A3); if (knob!=knobs[mulPort+48]) { knobs[mulPort+48]=knob; sendMidi(mulPort+48,knob); } } }

  counter++;
  if (counter>100) { counter=0;
    if (curPort>15) { curPort=0; }
    selectPort(curPort);
    if (hc4067_0) { knob=analogRead(A0); sendMidi(curPort,knob); }
    if (hc4067_1) { knob=analogRead(A1); sendMidi(curPort+16,knob); }
    if (hc4067_2) { knob=analogRead(A2); sendMidi(curPort+32,knob); }
    if (hc4067_3) { knob=analogRead(A3); sendMidi(curPort+48,knob); }
    curPort++; }
    
  delay(10); }

  void selectPort(int port) { digitalWrite(2, port&1); digitalWrite(3, port&2); digitalWrite(4, port&4); digitalWrite(5, port&8); }
  
  void sendMidi(int knobNumber, int knob) {
    Serial1.write(0xb0+MIDIchannel); Serial1.write(knobNumber); Serial1.write(knob);
    if (logging) { Serial.print(knobNumber); Serial.print(" "); Serial.println(knob); } }
  
