/*
  Arduino Programs Blink

  This sketch demonstrates the Keyboard library.

  For Leonardo and Due boards only.

  When you connect pin 2 to ground, it creates a new window with a key
  combination (CTRL-N), then types in the Blink sketch, then auto-formats the
  text using another key combination (CTRL-T), then uploads the sketch to the
  currently selected Arduino using a final key combination (CTRL-U).

  Circuit:
  - Arduino Leonardo, Micro, Due, LilyPad USB, or Yún
  - wire to connect D2 to ground

  created 5 Mar 2012
  modified 29 Mar 2012
  by Tom Igoe
  modified 3 May 2014
  by Scott Fitzgerald

  This example is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardReprogram
*/

#include "Keyboard.h"


#define KEY_COUNT 12

/* NOTE: in the release PCB pins GND and UP are swapped */
#define K_DOWN   0
#define K_LEFT   1
#define K_RIGHT  2
#define K_PLAY   3
#define K_UP     4
#define K_RET    5
#define K_ESC    6
#define K_VOL_DN 7
#define K_VOL_UP 8
#define K_PG_DN  9
#define K_PG_UP  10
#define K_PWR    11

int pinStates[KEY_COUNT];


void setup()
{
  for (int i = 0; i < KEY_COUNT; i++) {
    pinMode(i, INPUT_PULLUP);
    pinStates[i] = digitalRead(i);
  }

  Keyboard.begin();
}

void pressKey(int key)
{
  switch (key) {
    case K_DOWN   : Keyboard.println("DOWN");   break;
    case K_LEFT   : Keyboard.println("LEFT");   break;
    case K_RIGHT  : Keyboard.println("RIGHT");  break;
    case K_PLAY   : Keyboard.println("PLAY");   break;
    case K_UP     : Keyboard.println("UP");     break;
    case K_ESC    : Keyboard.println("ESC");    break;
    case K_RET    : Keyboard.println("RET");    break;
    case K_PG_DN  : Keyboard.println("PG_DN");  break;
    case K_PG_UP  : Keyboard.println("PG_UP");  break;
    case K_VOL_DN : Keyboard.println("VOL_DN"); break;
    case K_VOL_UP : Keyboard.println("VOL_UP"); break;
    case K_PWR    : Keyboard.println("PWR");    break;
  }
}


void loop()
{
  for (int i = 0; i < KEY_COUNT; i++) {
    int state = digitalRead(i);
    if (state == LOW && pinStates[i] == HIGH) {
      pressKey(i);
    }
    pinStates[i] = state;
  }
  delay(50);
}
