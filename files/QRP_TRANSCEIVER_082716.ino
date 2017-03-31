/**************************************************************************
   DIRECT CONVERSION CW TRANSCEIVER CONTROLLER WITH IAMBIC KEYER FOR ARDUINO
   Uses SI5351 clock generator shild from Adafruit for VFO
   Uses NT7S SI5351 library for Arduino on github:
   https://github.com/etherkit/Si5351Arduino
   2 x 16 LCD display for frequency, offset, and tuning rate
   Has an iambic keyer with dot/dash memories
   Arduino Pro Mini pin assignments:
   2) Iambic paddle DSH input
   3) Iambic paddle DIT input
   4) Pushbutton on rotary encoder input
   5) Encoder A input
   6) 
   7) Encoder B input
   8) Transmit/mute output
   9) Sidetone output
   10) LCD RS output
   11) LCD E output
   12) LCD D4 output
   13) LCD D5 output
   A0) LCD D6 output
   A1) LCD D7 output
   A2)
   A3)
   A4) si5351 SDA
   A5) si5351 SCL
   A6) Offset voltage input
   A7) Keyer speed voltage input
 ***************************************************************************/
#include <si5351.h>
#include "Wire.h"
Si5351 si5351;
#include <LiquidCrystal.h> // use Arduino LCD library.
LiquidCrystal lcd(10, 11, 12, 13, A0, A1); //Set up LCD pin assignments

////////////////////////ENCODER SETUP///////////////////////////////////////
#define encoder_a 7
#define encoder_b 5
#define pbswitch 4
int enca = 0;
int encb = 0;
int oldenc = 0;
int newenc = 0;
int encdir = 0;
int pbutton = 1;
int zero = 1;
int option = 0;
float frequency = 7030000; //Start up frequency
long bandbottom = 7000000;
long bandtop = 7300000;
long readout;
long tunerate = 10;
int rateindicator = 5;
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////RIT SETUP//////////////////////////////////////
int rit = A6;
int ritvoltage = 0;
int oldritvoltage = 0;
int modulo = 0;
int ritcenter = 512;
int rittune = 0;
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////IAMBIC KEYER////////////////////////////////////
int count = 0;
int dit = 1;
int dah = 1;
int sidetone = 700;
int ditmem = 0;
int dahmem = 0;
int sspeed = 50;
int speedinput = A7;
/////////////////////////////////////////////////////////////////////////////

void setup()  {

  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0);
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
  lcd.begin(16, 2);
  pinMode(encoder_a, INPUT);
  digitalWrite(7, HIGH);
  pinMode(encoder_b, INPUT);
  digitalWrite(5, HIGH);
  pinMode(pbswitch, INPUT);
  digitalWrite(4, HIGH);
  pinMode(A2, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  encdir = 0;
  encoder_a == 0;
  encoder_b == 0;
  digitalWrite(A2, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("TR 10   ");
  lcd.print(" KHz    ");
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
}

void encoder()  {
  encdir = bitRead(oldenc, 1) ^ bitRead(newenc, 0);
  oldenc = (enca + (2 * encb));
  if (encdir == 0) {
    frequency = frequency + tunerate;
  }
  else {
    frequency = frequency - tunerate;
  }

  //set upper tuning limit of the band
  if (frequency <= bandbottom) {  //highest frequency limit
    frequency = bandbottom;
  }

  //set lower tuning limit of the band
  if (frequency >= bandtop) {
    frequency = bandtop;
  }

  setclock0(); //put the frequency into the clock generator
}

void setclock0() {  //function to set the SI5351 clock frequency
  lcd.setCursor(0, 0);
  lcd.print(frequency / 1000);
  lcd.print(" KHz    ");
  si5351.set_freq((frequency + rittune) * 100, SI5351_PLL_FIXED, SI5351_CLK0);
}

void rateselect() {
  {
    while (pbutton == 0) {
      pbutton = digitalRead(pbswitch);
      if (pbutton == 1) setclock0();
      enca = digitalRead(encoder_a);
      encb = digitalRead(encoder_b);
      newenc = (enca + (2 * encb));
      if (newenc != oldenc) {
        encdir = bitRead(oldenc, 1) ^ bitRead(newenc, 0);
        oldenc = (enca + (2 * encb));
        if (encdir == 0) {
          option = option + 1;
        }
        else {
          option = option - 1;
        }
      }
      if (option < 0) option = 0;
      if (option > 2) option = 2;
      lcd.setCursor(0, 1);

      if (option == 0) {
        tunerate = 10;
        lcd.print("TR 10 ");
      }
      if (option == 1) {
        tunerate = 100;
        lcd.print("TR 100 ");
      }
      if (option == 2) {
        tunerate = 1000;
        lcd.print("TR 1000");
      }
    }
  }
}

void ritune() {  //function to determine RIT offset frequency
  modulo = 0;
  oldritvoltage = ritvoltage;
  rittune = ritvoltage - ritcenter;
  rittune = rittune * 5;  //RIT steps in 5 Hz increments
  if (rittune > 30) {  //Keep a dead zone near 0 offset
    rittune = rittune;
  }
  else if (rittune < -30)  {
    rittune = rittune;  //Keep a dead zone near 0 offset
  }
  else {
    rittune = 0;
  }
  lcd.setCursor(8, 1);
  lcd.print("        ");
  lcd.setCursor(8, 1);
  lcd.print("OS ");
  if (rittune > 0) {
    lcd.print("+");
  }
  lcd.print(rittune);
  setclock0();
}

void checkpaddle() { //function for checking iambic paddle status
  dit = digitalRead(3);
  dah = digitalRead(2);
  if (!dit) makedit();
  if (!dah) makedah();
}

void makedit() { //function to make dits
  count = 0;
  ditmem = 0;
  si5351.set_freq(frequency * 100, SI5351_PLL_FIXED, SI5351_CLK0);
  digitalWrite(8, 0);
  tone(9, sidetone);
  while (count < sspeed) {
    dah = digitalRead(2);
    if (!dah) dahmem = 1;
    delay(1);
    ++count;
  }
  count = 0;
  noTone(9);
  digitalWrite(8, 1);
  si5351.set_freq((frequency + rittune) * 100, SI5351_PLL_FIXED, SI5351_CLK0);
    while (count < sspeed) {
    dah = digitalRead(2);
    delay(1);
    ++count;
  }
}

void makedah() { //function to make dahs
  count = 0;
  dahmem = 0;
  si5351.set_freq(frequency * 100, SI5351_PLL_FIXED, SI5351_CLK0);
  digitalWrite(8, 0);
  tone(9, sidetone);
  while (count < (sspeed * 3)) {
    dit = digitalRead(3);
    if (!dit) ditmem = 1;
    delay(1);
    ++count;
  }
  count = 0;
  noTone(9);
  digitalWrite(8, 1);
  si5351.set_freq((frequency + rittune) * 100, SI5351_PLL_FIXED, SI5351_CLK0);
    while (count < sspeed) {
    dit = digitalRead(3);
    if (!dit) ditmem = 1;
    delay(1);
    ++count;
  }
}
void loop() {
  pbutton = digitalRead(pbswitch);
  if (pbutton == 0) rateselect();
  enca = digitalRead(encoder_a);
  encb = digitalRead(encoder_b);
  newenc = (enca + (2 * encb));
  if (newenc != oldenc) encoder();
  ritvoltage = analogRead(A6);
  rittune = ritvoltage - ritcenter;
  rittune = rittune * 5;
  if (ritvoltage != oldritvoltage){
    ritune(); 
  }  
  if (ditmem == 1) makedit();
  if (dahmem == 1) makedah();
  sspeed = analogRead(speedinput);
  sspeed = sspeed / 6.5;
  if (sspeed < 24) sspeed = 24; 
  count = 0;
  checkpaddle();
}












