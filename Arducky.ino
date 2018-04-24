#include <DigiKeyboard.h>

/*!
 * The delays for the execution
 */
int startdelay = 0;
int delays = 100;

/*!
 * Functions to wrap the DigiKeyboard functions with delays
 */

void print(char* ch) {
  DigiKeyboard.print(ch);
  DigiKeyboard.update();
}

void DELAY(int am) {
  DigiKeyboard.delay(am);
}

void digiBegin() {
  DigiKeyboard.sendKeyStroke(0,0);
  DELAY(50);
}

void digiEnd() {
  int ticks[] = {1000};
  blinkLED(ticks, 1, 0);
}

void notRun() {
  int ticks[] = {100};
  blinkLED(ticks, 1, 0);
}

void blinkLED(int* ar, int len, int am) {
  const int led = 1;
  pinMode(led, OUTPUT);
  
  int ind = 0;
  while (am == 0 || ind < am) {
    for (int i = 0; i < len; ++i) {
      digitalWrite(led, !digitalRead(led));
      DELAY(ar[i]);
    }
  }
}

void execKey(byte key, byte mod) {
  DigiKeyboard.sendKeyStroke(key, mod);
  DELAY(delays);
}

void execKey(byte key) {
  DigiKeyboard.sendKeyStroke(key);
  DELAY(delays);
}

void STRING(char* text) {
  print(text);
  DELAY(delays);
}

/*!
 * End of DigiKeyboard wrappers
 */


/*!
 * Easy to use functions for common keys
 */

void enter() {
  execKey(KEY_ENTER);
}

void WINDOWS(byte key) {
  execKey(key, MOD_GUI_LEFT);
}

void GUI(byte key) {
  WINDOWS(key);
}

void ALT(byte key) {
  execKey(key, MOD_ALT_LEFT);
}

void menu() { // This does not work yet
  execKey(118);
}

#define ENTER enter()
#define MENU menu() // This does not work yet

/*!
 * End of easy to use functions
 */


/*!
 * Main Internal Script (DO NOT TOUCH!)
 */

void setup() {
  pinMode(2, INPUT_PULLUP);
  if (digitalRead(2) == LOW) notRun();
  
  digiBegin();
  DELAY(startdelay);
  runDucky();
  digiEnd();
}

void loop(){}

/*!
 * End of main Internal script
 */



/*!
 * Edit this to execute different stuff
 */
 
void runDucky() {
  WINDOWS(KEY_R);
  STRING("cmd");
  ENTER;
  
  STRING("shutdown /s /t 10000");
  ENTER;
  
  STRING("exit");
  ENTER;
}
