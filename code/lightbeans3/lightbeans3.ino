#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Set this to the number of pixels you have
#define PIN D6 // Set this to the pin that the data of the pixel is connected to
#define INPUT_PIN A0 // Input pin
#define BRIGHTNESS 400.0 // Threshold value to turn on light
#define UPDATE_TIME 100 // time between updates in ms

// Color to switch on to
int r = 100;
int g = 30;
int b = 70;

float input_value = 0;

void turn_on(int r, int g, int b);
void turn_off();

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// setup and loop functions

void setup() {
  pixels.begin();
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  input_value = analogRead(INPUT_PIN);
  if (input_value < BRIGHTNESS) { // if larger than our threshold value, turn on.
    turn_on(r,g,b);
  }
  if (input_value > BRIGHTNESS) {
    turn_off();
  }
  delay(UPDATE_TIME);
}


// Functions we wrote
// This function takes in a red, green, blue and displays the colors
void turn_on(int r, int g, int b){
  for(int i=0; i <NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(r,g,b));
  }
  pixels.show();
}


// This function turns off all pixels
void turn_off(){
  for(int i=0; i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0)); // set the color to (0,0,0), off!
  }
  pixels.show();
}
