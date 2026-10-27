//----------------------------------------------
// MORI-ICHI-SHIKI Sample Sketch
// Target Board : MORI-ICHI-SHIKI
// Target MCU   : ESP32-S3 WROOM-1
//
//    by Forest Design  2026/10/26
//----------------------------------------------

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

//----------------------------------------------
// NeoPixel
//----------------------------------------------
#define LED_PIN       38
#define LED_COUNT     15    // onboard 1 + external 7 x 2
// Maximum number of NeoPixels used by this demo.
// Fewer LEDs can also be connected.
#define BRIGHTNESS    64

#define SHORT_WT       2
#define CHANGE_WT    300
#define LOW_WAIT       8

//----------------------------------------------
// OLED
//----------------------------------------------
#define OLED_SDA       9
#define OLED_SCL      10
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

Adafruit_NeoPixel pixel(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800
);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

//----------------------------------------------
// OLED text display
//----------------------------------------------
void showOLED(const char* colorName)
{
  Serial.println(colorName);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Forest Design");

  display.setCursor(0, 10);
  display.println("MORI-ICHISHIKI");

  display.setCursor(0, 22);
  display.print("LED : ");
  display.println(colorName);

  display.display();
}

//----------------------------------------------
// All NeoPixels same color
//----------------------------------------------
void allColor(uint8_t r, uint8_t g, uint8_t b)
{
  for (int i = 0; i < LED_COUNT; i++) {
    pixel.setPixelColor(i, pixel.Color(r, g, b));
  }

  pixel.show();
}

//----------------------------------------------
// Color Wheel
// 0 - 255 -> rainbow color
//----------------------------------------------
uint32_t Wheel(uint8_t pos)
{
  pos = 255 - pos;

  if (pos < 85) {
    return pixel.Color(
      255 - pos * 3,
      0,
      pos * 3
    );
  }

  if (pos < 170) {
    pos -= 85;

    return pixel.Color(
      0,
      pos * 3,
      255 - pos * 3
    );
  }

  pos -= 170;

  return pixel.Color(
    pos * 3,
    255 - pos * 3,
    0
  );
}

//----------------------------------------------
// Rainbow
//
// The 256-value color wheel is distributed
// evenly across all connected NeoPixels.
//----------------------------------------------
void rainbow()
{
  showOLED("RAINBOW");

  // 3 rotations
  for (int step = 0; step < 256 * 3; step++) {

    for (int i = 0; i < LED_COUNT; i++) {

      uint8_t pos =
        ((i * 256 / LED_COUNT) + step) & 255;

      pixel.setPixelColor(i, Wheel(pos));
    }

    pixel.show();
    delay(20);
  }
}

//----------------------------------------------
void setup()
{
  Serial.begin(115200);

  // NeoPixel
  pixel.begin();
  pixel.setBrightness(BRIGHTNESS);
  pixel.clear();
  pixel.show();

  // I2C
  Wire.begin(OLED_SDA, OLED_SCL);

  // OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS))
  {
    Serial.println("SSD1306 ERROR");

    while (1) {
      delay(100);
    }
  }

  showOLED("START");
  delay(500);
}

//----------------------------------------------
void loop()
{
  //--------------------------------------------
  // RED
  //--------------------------------------------
  showOLED("-> RED");

  for (int x = 0; x < 255; x++) {

    allColor(x, 0, 0);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // GREEN
  //--------------------------------------------
  showOLED("-> GREEN");

  for (int x = 0; x < 255; x++) {

    allColor(255 - x, x, 0);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // YELLOW
  //--------------------------------------------
  showOLED("-> YELLOW");

  for (int x = 0; x < 255; x++) {

    allColor(x, 255, 0);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // BLUE
  //--------------------------------------------
  showOLED("-> BLUE");

  for (int x = 0; x < 255; x++) {

    allColor(255 - x, 255 - x, x);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // MAGENTA
  //--------------------------------------------
  showOLED("-> MAGENTA");

  for (int x = 0; x < 255; x++) {

    allColor(x, 0, 255);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // CYAN
  //--------------------------------------------
  showOLED("-> CYAN");

  for (int x = 0; x < 255; x++) {

    allColor(255 - x, x, 255);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // WHITE
  //--------------------------------------------
  showOLED("-> WHITE");

  for (int x = 0; x < 255; x++) {

    allColor(x, 255, 255);

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  delay(CHANGE_WT);

  //--------------------------------------------
  // Fade to OFF
  //--------------------------------------------
  showOLED("-> OFF");

  for (int x = 0; x < 255; x++) {

    allColor(
      255 - x,
      255 - x,
      255 - x
    );

    if (x < 30) {
      delay(SHORT_WT + LOW_WAIT);
    }
    else {
      delay(SHORT_WT);
    }
  }

  pixel.clear();
  pixel.show();

  delay(500);

  //--------------------------------------------
  // Rainbow wave
  //--------------------------------------------
  rainbow();

  //--------------------------------------------
  // OFF
  //--------------------------------------------
  showOLED("OFF");

  pixel.clear();
  pixel.show();

  delay(1000);
}