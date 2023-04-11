//
//  "Led Animations for Lenswork Rentals"
//  April 2023, Paolo Cavagnolo.
//

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN 3
#define NUM_LEDS 60
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

//////////////////////////////////////////////////////////////////////////

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);  // 3 second delay for boot recovery, and a moment of silence
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);
  FastLED.clear();
  FastLED.show();
}

uint8_t r, g, b, x, y, z;

void loop() {
  EVERY_N_MILLISECONDS(20) {
    pulse();
    FastLED.show();
  }
}

static float pulse_speed = 0.5;  // Larger value gives faster pulse.

uint8_t satA = 230;      // Start saturation at valueMin.
float valueMin = 120.0;  // Pulse minimum value (Should be less then valueMax).

uint8_t satB = 255;      // End saturation at valueMax.
float valueMax = 255.0;  // Pulse maximum value (Should be larger then valueMin).

uint8_t sat = satA;                                       // Do Not Edit
float val = valueMin;                                     // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238;  // Do Not Edit

void pulse() {

  // A consistent timed pulse of light intensity. This will pulse the entire frame.
  // Use of the rotary encoders will allow changing of the R,G,B value of the pulse.
  // The other 3 encoders will allow changing of the Pulse Rate, Min intensity, & Max Intensity.
  // r,g,b
  // x = pulse speed
  // y = min intensity
  // z = max intensity

  pulse_speed = 0.5;  //x
  valueMin = 120.0;   //y
  valueMax = 255.0;   //z

  float dV = ((exp(sin(pulse_speed * millis() / 2000.0 * PI)) - 0.36787944) * delta);
  val = valueMin + dV;
  sat = map(val, valueMin, valueMax, satA, satB);  // Map sat based on current val

  fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
  FastLED.setBrightness(sat);
}

uint16_t start_point;
uint16_t end_point;
uint16_t num_leds_segment;

uint8_t max_intensity = 255;

uint32_t time_flicker = 0;
uint16_t duration_between_flashes = 1000;

bool flicker_state = false;

void flicker() {

  // A randomly timed pulse, at random location and intensity.
  // Use of the rotary encoders will allow changing of the R,G,B value of thempulse.
  // The other 3 encoders will allow changing of the Maximum intensity, # LEDs in the segment flashed,
  // and a variable to control duration between flashes (quicker/slower).
  // r,g,b
  // x = max intensity
  // y = # LEDs in the segment flashed
  // z = quicker / slower

  max_intensity = 255;              //x
  num_leds_segment = 10;            //y
  duration_between_flashes = 1000;  //z

  start_point = random(NUM_LEDS);
  end_point = start_point + num_leds_segment;

  if (end_point > NUM_LEDS) {
    end_point = end_point - NUM_LEDS;
  }

  if (!flicker_state) {
    if ((millis() - time_flicker) > 100) {
      time_flicker = millis();
      FastLED.clear();
      led_fill(start_point,end_point);
      flicker_state = true;
    }
  }
  else {
    
  }
}

void led_fill(uint16_t sP, uint16_t eP) {
  if (eP >= sP) {
    for (uint16_t i = sP; i < eP; i++) {
      leds[i] = CRGB(r, g, b);
    }
  } else {
    for (uint16_t i = sP; i < NUM_LEDS; i++) {
      leds[i] = CRGB(r, g, b);
    }
    for (uint16_t i = 0; i < eP; i++) {
      leds[i] = CRGB(r, g, b);
    }
  }
}
