#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Set this to the number of pixels you have
#define PIN D6 // Set this to the pin that the data of the pixel is connected to
#define INPUT_PIN A0 // Input pin
#define MAX_BRIGHTNESS 400.0 // Maximum brightness detected
#define UPDATE_TIME 10 // time between updates in ms

int r = 0;
int g = 0;
int b = 0;

float input_value;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600); // setup the serial
    pixels.begin(); // initialise the neopixel
    pinMode(INPUT_PIN,INPUT);
}


void loop()
{
    input_value = analogRead(INPUT_PIN); // get the value read
    Serial.println(input_value); // print the value
    input_value = ((MAX_BRIGHTNESS-input_value)/MAX_BRIGHTNESS) * (3*(255)); // Scale input to 765 so we can use it for our rgb value
    //Serial.println(input_value);
    if (input_value<255){ // if less than 1/3, light only red
        r = input_value;
        g = 0;
        b = 0;
    }
    if (input_value<510 && input_value>255){ // if more than 1/3 and less than 2/3, then mix red and green
        r = 510 - input_value; // no red at 510
        g = input_value-255; // maximum value 510
        b = 0;
    }
    if(input_value>510){
        r = 0; // no red
        g = 765-input_value; // no green
        b = input_value-510; // max blue at 755
    }
    pixels.setPixelColor(1,pixels.Color(r,g,b)); // set the first pixel to the color we want
    pixels.show(); // display the color
    delay(UPDATE_TIME); // wait
}
