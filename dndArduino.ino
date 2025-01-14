#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fsm.h>
#include <SoftwareSerial.h>
// #include <Wire.h>


/////////////////////////////////////////////////////////////////
// DISPLAY
/////////////////////////////////////////////////////////////////
#define SCREEN_I2C_ADDR 0x3C  // or 0x3C
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RST_PIN -1       // Reset pin (-1 if not available)
#define FRAME_WIDTH (64)
#define FRAME_HEIGHT (64)

////////////////////////////////////////////////////////////////
// MODE
////////////////////////////////////////////////////////////////
#define IS_REQUESTER_ONLY false  // set to false if this is a requester

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);
const byte PROGMEM bitmap_yes[512] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0, 0, 0, 0, 0, 224, 0, 0, 0, 0, 0, 0, 0, 224, 0, 0, 0, 0, 0, 0, 1, 192, 0, 0, 0, 0, 0, 0, 3, 128, 0, 0, 0, 0, 0, 0, 3, 128, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0, 0, 0, 0, 0, 224, 0, 0, 0, 0, 0, 0, 1, 192, 0, 0, 0, 0, 0, 0, 1, 192, 0, 0, 0, 192, 0, 0, 3, 128, 0, 0, 0, 224, 0, 0, 7, 0, 0, 0, 0, 112, 0, 0, 7, 0, 0, 0, 0, 56, 0, 0, 14, 0, 0, 0, 0, 30, 0, 0, 12, 0, 0, 0, 0, 15, 0, 0, 28, 0, 0, 0, 0, 7, 128, 0, 56, 0, 0, 0, 0, 3, 192, 0, 48, 0, 0, 0, 0, 0, 224, 0, 112, 0, 0, 0, 0, 0, 112, 0, 224, 0, 0, 0, 0, 0, 56, 0, 192, 0, 0, 0, 0, 0, 28, 1, 192, 0, 0, 0, 0, 0, 14, 3, 128, 0, 0, 0, 0, 0, 7, 131, 128, 0, 0, 0, 0, 0, 3, 199, 0, 0, 0, 0, 0, 0, 1, 238, 0, 0, 0, 0, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const byte PROGMEM bitmap_no[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 2, 0, 0, 224, 0, 0, 0, 0, 7, 0, 0, 112, 0, 0, 0, 0, 14, 0, 0, 56, 0, 0, 0, 0, 28, 0, 0, 28, 0, 0, 0, 0, 56, 0, 0, 14, 0, 0, 0, 0, 112, 0, 0, 7, 0, 0, 0, 0, 224, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 0, 224, 0, 0, 7, 0, 0, 0, 0, 112, 0, 0, 14, 0, 0, 0, 0, 56, 0, 0, 28, 0, 0, 0, 0, 28, 0, 0, 56, 0, 0, 0, 0, 14, 0, 0, 112, 0, 0, 0, 0, 7, 0, 0, 224, 0, 0, 0, 0, 3, 128, 1, 192, 0, 0, 0, 0, 1, 192, 3, 128, 0, 0, 0, 0, 0, 224, 7, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 0, 0, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 28, 56, 0, 0, 0, 0, 0, 0, 14, 112, 0, 0, 0, 0, 0, 0, 7, 224, 0, 0, 0, 0, 0, 0, 3, 192, 0, 0, 0, 0, 0, 0, 3, 192, 0, 0, 0, 0, 0, 0, 7, 224, 0, 0, 0, 0, 0, 0, 14, 112, 0, 0, 0, 0, 0, 0, 28, 56, 0, 0, 0, 0, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 0, 0, 0, 0, 224, 7, 0, 0, 0, 0, 0, 1, 192, 3, 128, 0, 0, 0, 0, 3, 128, 1, 192, 0, 0, 0, 0, 7, 0, 0, 224, 0, 0, 0, 0, 14, 0, 0, 112, 0, 0, 0, 0, 28, 0, 0, 56, 0, 0, 0, 0, 56, 0, 0, 28, 0, 0, 0, 0, 112, 0, 0, 14, 0, 0, 0, 0, 224, 0, 0, 7, 0, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 7, 0, 0, 0, 0, 224, 0, 0, 14, 0, 0, 0, 0, 112, 0, 0, 28, 0, 0, 0, 0, 56, 0, 0, 56, 0, 0, 0, 0, 28, 0, 0, 112, 0, 0, 0, 0, 14, 0, 0, 224, 0, 0, 0, 0, 7, 0, 0, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const byte PROGMEM bitmap_bell[512] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 128, 0, 0, 0, 0, 0, 0, 7, 224, 0, 0, 0, 0, 0, 0, 15, 240, 0, 0, 0, 0, 0, 0, 28, 56, 0, 0, 0, 0, 0, 0, 28, 56, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 28, 56, 0, 0, 0, 0, 0, 0, 30, 120, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 3, 255, 255, 192, 0, 0, 0, 0, 7, 192, 3, 224, 0, 0, 0, 0, 15, 0, 0, 240, 0, 0, 0, 0, 28, 0, 0, 56, 0, 0, 0, 0, 56, 0, 0, 28, 0, 0, 0, 0, 48, 0, 0, 12, 0, 0, 0, 0, 112, 0, 0, 14, 0, 0, 0, 0, 96, 0, 0, 6, 0, 0, 0, 0, 224, 0, 0, 7, 0, 0, 0, 0, 192, 0, 0, 7, 0, 0, 0, 0, 192, 0, 0, 3, 0, 0, 0, 0, 192, 0, 0, 3, 0, 0, 0, 0, 192, 0, 0, 3, 0, 0, 0, 0, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 128, 0, 0, 3, 128, 0, 0, 1, 128, 0, 0, 1, 128, 0, 0, 1, 128, 0, 0, 1, 128, 0, 0, 1, 128, 0, 0, 1, 192, 0, 0, 3, 128, 0, 0, 1, 192, 0, 0, 3, 0, 0, 0, 1, 192, 0, 0, 3, 0, 0, 0, 0, 192, 0, 0, 7, 0, 0, 0, 0, 224, 0, 0, 6, 0, 0, 0, 0, 96, 0, 0, 14, 0, 0, 0, 0, 112, 0, 0, 12, 0, 0, 0, 0, 48, 0, 0, 28, 0, 0, 0, 0, 56, 0, 0, 56, 0, 0, 0, 0, 28, 0, 0, 112, 0, 0, 0, 0, 14, 0, 0, 224, 0, 0, 0, 0, 7, 0, 0, 224, 0, 0, 0, 0, 3, 0, 0, 192, 0, 0, 0, 0, 3, 0, 0, 224, 0, 0, 0, 0, 7, 0, 0, 112, 0, 0, 0, 0, 14, 0, 0, 124, 0, 0, 0, 0, 126, 0, 0, 31, 192, 0, 0, 7, 248, 0, 0, 7, 255, 255, 255, 255, 224, 0, 0, 0, 127, 255, 255, 255, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 224, 7, 0, 0, 0, 0, 0, 0, 224, 7, 0, 0, 0, 0, 0, 0, 96, 6, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 0, 0, 0, 0, 60, 60, 0, 0, 0, 0, 0, 0, 31, 248, 0, 0, 0, 0, 0, 0, 15, 240, 0, 0, 0, 0, 0, 0, 1, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const byte PROGMEM bitmap_sleeper[512] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 254, 0, 0, 0, 0, 0, 3, 255, 255, 192, 0, 0, 0, 0, 15, 224, 15, 248, 0, 0, 0, 0, 62, 0, 0, 124, 0, 0, 0, 0, 248, 0, 0, 31, 0, 0, 0, 3, 224, 0, 0, 7, 128, 0, 0, 7, 128, 0, 0, 1, 224, 0, 0, 15, 0, 0, 0, 0, 240, 0, 0, 30, 0, 0, 0, 0, 56, 0, 0, 60, 0, 0, 0, 0, 28, 0, 0, 112, 0, 0, 0, 0, 14, 0, 0, 240, 0, 0, 0, 0, 15, 0, 0, 224, 0, 0, 0, 0, 7, 0, 1, 192, 0, 0, 0, 0, 3, 128, 3, 128, 0, 0, 0, 0, 1, 192, 3, 128, 0, 0, 0, 0, 1, 192, 7, 0, 0, 0, 0, 0, 0, 224, 7, 0, 0, 0, 0, 0, 0, 224, 14, 0, 0, 0, 0, 0, 0, 96, 14, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 0, 0, 0, 0, 48, 12, 0, 0, 0, 0, 0, 0, 48, 28, 0, 0, 0, 0, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 56, 24, 0, 0, 0, 0, 0, 0, 24, 24, 2, 0, 32, 4, 0, 96, 24, 24, 7, 0, 112, 14, 0, 224, 24, 24, 3, 227, 224, 7, 199, 192, 24, 24, 1, 255, 192, 3, 255, 128, 24, 24, 0, 127, 0, 0, 254, 0, 24, 24, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 24, 28, 0, 0, 0, 0, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 56, 12, 0, 0, 0, 0, 0, 0, 48, 12, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 63, 252, 0, 0, 112, 6, 0, 7, 255, 255, 224, 0, 112, 7, 0, 7, 254, 255, 224, 0, 224, 7, 0, 6, 0, 0, 96, 0, 224, 3, 128, 0, 0, 0, 0, 1, 192, 3, 128, 0, 0, 0, 0, 1, 192, 1, 192, 0, 0, 0, 0, 3, 128, 0, 224, 0, 0, 0, 0, 7, 0, 0, 112, 0, 0, 0, 0, 15, 0, 0, 112, 0, 0, 0, 0, 30, 0, 0, 56, 0, 0, 0, 0, 28, 0, 0, 30, 0, 0, 0, 0, 120, 0, 0, 15, 0, 0, 0, 0, 240, 0, 0, 7, 128, 0, 0, 1, 224, 0, 0, 1, 224, 0, 0, 7, 192, 0, 0, 0, 248, 0, 0, 31, 0, 0, 0, 0, 63, 0, 0, 124, 0, 0, 0, 0, 15, 240, 7, 240, 0, 0, 0, 0, 3, 255, 255, 192, 0, 0, 0, 0, 0, 127, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const byte PROGMEM timer[512] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 254, 0, 0, 0, 0, 0, 3, 255, 255, 192, 0, 0, 0, 0, 31, 240, 15, 248, 0, 0, 0, 0, 63, 0, 0, 252, 0, 0, 0, 0, 248, 0, 0, 31, 0, 0, 0, 3, 224, 0, 0, 7, 192, 0, 0, 7, 128, 0, 0, 1, 224, 0, 0, 15, 0, 0, 0, 0, 240, 0, 0, 30, 0, 0, 0, 0, 120, 0, 0, 60, 0, 0, 0, 0, 60, 0, 0, 120, 0, 0, 0, 0, 30, 0, 0, 240, 0, 0, 0, 0, 15, 0, 0, 224, 0, 0, 0, 0, 7, 0, 1, 192, 0, 0, 0, 0, 3, 128, 1, 128, 0, 0, 0, 0, 1, 128, 3, 128, 0, 3, 192, 0, 1, 192, 7, 0, 0, 3, 192, 0, 0, 224, 7, 0, 0, 3, 192, 0, 0, 224, 6, 0, 0, 3, 192, 0, 0, 96, 14, 0, 0, 3, 192, 0, 0, 112, 14, 0, 0, 3, 192, 0, 0, 112, 12, 0, 0, 3, 192, 0, 0, 48, 28, 0, 0, 3, 192, 0, 0, 56, 28, 0, 0, 3, 192, 0, 0, 56, 28, 0, 0, 3, 192, 0, 0, 56, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 24, 0, 0, 3, 192, 0, 0, 24, 28, 0, 0, 1, 192, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 56, 28, 0, 0, 0, 0, 0, 0, 56, 12, 0, 0, 0, 0, 0, 0, 48, 14, 0, 0, 0, 0, 0, 0, 112, 14, 0, 0, 3, 192, 0, 0, 112, 6, 0, 0, 3, 192, 0, 0, 96, 7, 0, 0, 3, 192, 0, 0, 224, 7, 0, 0, 3, 192, 0, 0, 224, 3, 128, 0, 3, 192, 0, 1, 192, 1, 128, 0, 0, 0, 0, 1, 128, 1, 192, 0, 0, 0, 0, 3, 128, 0, 224, 0, 0, 0, 0, 7, 0, 0, 240, 0, 0, 0, 0, 15, 0, 0, 120, 0, 0, 0, 0, 30, 0, 0, 60, 0, 0, 0, 0, 60, 0, 0, 30, 0, 0, 0, 0, 120, 0, 0, 15, 0, 0, 0, 0, 240, 0, 0, 7, 128, 0, 0, 1, 224, 0, 0, 3, 224, 0, 0, 7, 192, 0, 0, 0, 248, 0, 0, 31, 0, 0, 0, 0, 63, 0, 0, 252, 0, 0, 0, 0, 31, 240, 15, 248, 0, 0, 0, 0, 3, 255, 255, 192, 0, 0, 0, 0, 0, 127, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/////////////////////////////////////////////////////////////////
// HC12
/////////////////////////////////////////////////////////////////
SoftwareSerial hc12(10, 11);

/////////////////////////////////////////////////////////////////
// buttons and leds
/////////////////////////////////////////////////////////////////
#define BUTTON_A_PIN 3
#define BUTTON_B_PIN 4

#define LED_R_PIN 7
#define LED_G_PIN 8
#define LED_B_PIN 9

/////////////////////////////////////////////////////////////////
// State machine setup
/////////////////////////////////////////////////////////////////
enum STATUS { IDLE,
              WAITING,
              CANCELLED,
              TIMEDOUT,
              ACCEPTED,
              DENIED };

// define events
#define WAIT_EVENT 1

#define REQUEST_BUTTON_PRESSED_EVENT 2
#define REQUEST_ACCEPTED_EVENT 3
#define REQUEST_DENIED_EVENT 4
#define REQUEST_TIMED_OUT 5

#define REQUEST_MESSAGE_RECEIVED_EVENT 6
#define RESPONDED_WITH_YES 7
#define RESPONDED_WITH_NO 8
#define RESPONSE_TIMED_OUT 9


// create states
State state_start(&on_state_start_enter, &on_state_start, NULL);
State state_wait(&on_state_wait_enter, &on_state_wait, NULL);

State state_request_sent(&on_state_request_sent_enter, &on_state_request_sent, NULL);
State state_request_accepted(&on_state_request_accepted_enter, &on_state_request_accepted, NULL);
State state_request_denied(&on_state_request_denied_enter, &on_state_request_denied, NULL);
State state_request_timed_out(&on_state_request_timed_out_enter, &on_state_request_timed_out, NULL);

State state_request_received(&on_state_request_received_enter, &on_state_request_received, NULL);
State state_responded_with_yes(&on_state_responded_with_yes_enter, &on_state_responded_with_yes, NULL);
State state_responded_with_no(&on_state_responded_with_no_enter, &on_state_responded_with_no, NULL);
State state_response_timed_out(&on_state_response_timed_out_enter, &on_state_response_timed_out, NULL);

Fsm fsm(&state_start);

// state handlers
// start
void on_state_start_enter() {
  Serial.println("Entering start");
  Serial.flush();

  // flush hc12's buffer
  hc12.flush();
  fsm.trigger(WAIT_EVENT);
}

void on_state_start() {}

// wait
void on_state_wait_enter() {
  Serial.println("Entering wait");

  updateStatus(IDLE, 6000, 0x888888, bitmap_sleeper);
}
void on_state_wait() {
  if (IS_REQUESTER_ONLY) {
    // if button pressed
    if (digitalRead(BUTTON_B_PIN) == LOW) {
      hc12.print("REQUEST");
      hc12.flush();
      fsm.trigger(REQUEST_BUTTON_PRESSED_EVENT);
    }
  }

  else {
    // check hc12. if message available
    if (hc12.available()) {
      String msg = hc12.readString();
      if (msg.equals("REQUEST")) {
        fsm.trigger(REQUEST_MESSAGE_RECEIVED_EVENT);
      }
    }
  }
}

// request sent
void on_state_request_sent_enter() {
  Serial.println("Entering request_sent");

  updateStatus(WAITING, 15000, 0xFF00FF, bitmap_bell);
  // flush hc12's buffer
  hc12.flush();
}
void on_state_request_sent() {
  // check hc12. if message available, move to accepted/denied
  if (hc12.available()) {
    String msg = hc12.readString();
    if (msg.equals("YES")) {
      fsm.trigger(REQUEST_ACCEPTED_EVENT);
    }
    if (msg.equals("NO")) {
      fsm.trigger(REQUEST_DENIED_EVENT);
    }
  }
}

// request accepted
void on_state_request_accepted_enter() {
  Serial.println("Entering request_accepted");

  updateStatus(ACCEPTED, 5000, 0x00FF00, bitmap_yes);
}
void on_state_request_accepted() {}

// request denied
void on_state_request_denied_enter() {
  Serial.println("Entering request_denied");

  updateStatus(DENIED, 5000, 0xFF0000, bitmap_no);
}
void on_state_request_denied() {}

// request timed out
void on_state_request_timed_out_enter() {
  Serial.println("Entering request_timed_out");

  updateStatus(TIMEDOUT, 2000, 0xFFFF00, timer);
}
void on_state_request_timed_out() {}

// request received
void on_state_request_received_enter() {
  Serial.println("Entering request_received");

  updateStatus(WAITING, 15000, 0xFF00FF, bitmap_bell);
}
void on_state_request_received() {
  // if A button pressed, then cancel
  if (digitalRead(BUTTON_A_PIN) == LOW) {
    fsm.trigger(RESPONDED_WITH_NO);

    // send the hc12 message
    hc12.print("NO");
    hc12.flush();
  }

  // if B button pressed, then accept
  if (digitalRead(BUTTON_B_PIN) == LOW) {
    fsm.trigger(RESPONDED_WITH_YES);
    // send the hc12 message
    hc12.print("YES");
    hc12.flush();
  }
}

// responded with yes
void on_state_responded_with_yes_enter() {
  Serial.println("Entering responded_with_yes");

  updateStatus(ACCEPTED, 5000, 0x00FF00, bitmap_yes);
}
void on_state_responded_with_yes() {}

// responded with no
void on_state_responded_with_no_enter() {
  Serial.println("Entering responded_with_no");

  updateStatus(DENIED, 5000, 0xFF0000, bitmap_no);
}
void on_state_responded_with_no() {}

// response timed out
void on_state_response_timed_out_enter() {
  Serial.println("Entering response_timed_out");

  updateStatus(TIMEDOUT, 2000, 0xFF00FF, timer);
}
void on_state_response_timed_out() {}

void setRGBLED(long color) {
  int redColor = color >> 16;
  int greeColor = color >> 8 & 0xFF;
  int blueColor = color & 0xFF;

  Serial.println(redColor);
  Serial.println(greeColor);
  Serial.println(blueColor);
  Serial.flush();

  analogWrite(LED_R_PIN, redColor);
  analogWrite(LED_G_PIN, greeColor);
  analogWrite(LED_B_PIN, blueColor);
}

void updateStatus(STATUS status, unsigned long timer_duration, long led_color, const byte* bmp) {
  // Serial.println(led_color);

  // set LED to led_color
  setRGBLED(led_color);

  // // start timer
  // start_millis = millis();
  // end_millis = start_millis + timer_duration;
  // is_display_timer_enabled = true;

  // update display
  display.clearDisplay();
  display.drawBitmap(32, 0, bitmap_yes, FRAME_WIDTH, FRAME_HEIGHT, 1);  // hardcoding it to bitmap_yes works
  display.drawBitmap(32, 0, bmp, FRAME_WIDTH, FRAME_HEIGHT, 1);         // using the parameter crashes the program
  display.display();

}

void setup() {
  // // display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);


  // transitions
  fsm.add_transition(&state_start, &state_wait, WAIT_EVENT, NULL);

  // fsm.add_timed_transition( &state_wait,                &state_back_to_idle,        5000,                           NULL);
  // fsm.add_transition(       &state_back_to_idle,        &state_wait,                WAIT_EVENT,                     NULL);

  fsm.add_transition(&state_wait, &state_request_sent, REQUEST_BUTTON_PRESSED_EVENT, NULL);
  fsm.add_transition(&state_request_sent, &state_request_accepted, REQUEST_ACCEPTED_EVENT, NULL);
  fsm.add_transition(&state_request_sent, &state_request_denied, REQUEST_DENIED_EVENT, NULL);
  fsm.add_timed_transition(&state_request_sent, &state_request_timed_out, 15000, NULL);
  fsm.add_timed_transition(&state_request_accepted, &state_wait, 5000, NULL);
  fsm.add_timed_transition(&state_request_denied, &state_wait, 5000, NULL);
  fsm.add_timed_transition(&state_request_timed_out, &state_wait, 5000, NULL);

  fsm.add_transition(&state_wait, &state_request_received, REQUEST_MESSAGE_RECEIVED_EVENT, NULL);
  fsm.add_transition(&state_request_received, &state_responded_with_yes, RESPONDED_WITH_YES, NULL);
  fsm.add_transition(&state_request_received, &state_responded_with_no, RESPONDED_WITH_NO, NULL);
  fsm.add_timed_transition(&state_request_received, &state_response_timed_out, 15000, NULL);
  fsm.add_timed_transition(&state_responded_with_yes, &state_wait, 5000, NULL);
  fsm.add_timed_transition(&state_responded_with_no, &state_wait, 5000, NULL);
  fsm.add_timed_transition(&state_response_timed_out, &state_wait, 5000, NULL);

  // buttons
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);

  // LED
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  // HC12
  hc12.begin(9600);  // Serial port to HC12

  Serial.begin(9600);
}

void loop() {
  fsm.run_machine();
}
