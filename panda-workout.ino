/*
 * Panda Workout fitness machine remote control
 *
 * Author: Haff
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

int keyStates[KEY_COUNT] = { 0 };
int keyStableStates[KEY_COUNT] = { 0 };
unsigned long lastDebounces[KEY_COUNT] = { 0 };
unsigned long debounceDelay = 10;

void setup()
{
  for (int i = 0; i < KEY_COUNT; i++) {
    pinMode(i, INPUT_PULLUP);
    keyStates[i] = HIGH;
  }

  Keyboard.begin();
}

void pressKey(int pin)
{
  switch (pin) {
    case K_UP     : Keyboard.press(KEY_UP);               break;
    case K_DOWN   : Keyboard.press(KEY_DOWN);             break;
    case K_LEFT   : Keyboard.press(KEY_LEFT);             break;
    case K_RIGHT  : Keyboard.press(KEY_RIGHT);            break;
    case K_PLAY   : Keyboard.press(KEY_SPACE);            break;  // NOTE: Video players use space to start/stop playback
    case K_ESC    : Keyboard.press(KEY_ESC);              break;
    case K_RET    : Keyboard.press(KEY_ENTER);            break;
    case K_PG_DN  : Keyboard.press(KEY_PAGE_DOWN);        break;
    case K_PG_UP  : Keyboard.press(KEY_PAGE_UP);          break;
    case K_VOL_DN : Keyboard.press(KEY_MEDIA_VOLUME_DEC); break;
    case K_VOL_UP : Keyboard.press(KEY_MEDIA_VOLUME_INC); break;
    case K_PWR    : Keyboard.press(KEY_SYSTEM_WAKE_UP);   break;
  }
  keyStableStates[pin] = LOW;
}

void releaseKey(int pin)
{
  switch (pin) {
    case K_UP     : Keyboard.release(KEY_UP);               break;
    case K_DOWN   : Keyboard.release(KEY_DOWN);             break;
    case K_LEFT   : Keyboard.release(KEY_LEFT);             break;
    case K_RIGHT  : Keyboard.release(KEY_RIGHT);            break;
    case K_PLAY   : Keyboard.release(KEY_SPACE);            break;
    case K_ESC    : Keyboard.release(KEY_ESC);              break;
    case K_RET    : Keyboard.release(KEY_ENTER);            break;
    case K_PG_DN  : Keyboard.release(KEY_PAGE_DOWN);        break;
    case K_PG_UP  : Keyboard.release(KEY_PAGE_UP);          break;
    case K_VOL_DN : Keyboard.release(KEY_MEDIA_VOLUME_DEC); break;
    case K_VOL_UP : Keyboard.release(KEY_MEDIA_VOLUME_INC); break;
    case K_PWR    : Keyboard.release(KEY_SYSTEM_WAKE_UP);   break;
  }
  keyStableStates[pin] = HIGH;
}

void processKey(int pin)
{
  int state = digitalRead(pin);

  if (state != keyStates[pin])
    lastDebounces[pin] = millis();
  keyStates[pin] = state;

  if ((millis() - lastDebounces[pin]) <= debounceDelay)
    return;
  if (state == keyStableStates[pin])
    return;

  switch (state) {
    case LOW:  pressKey(pin);   break;
    case HIGH: releaseKey(pin); break;
  }
}

void loop()
{
  for (int i = 0; i < KEY_COUNT; i++)
    processKey(i);
}
