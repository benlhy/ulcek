#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Set this to the number of pixels you have
#define PIN D6
#define INPUT_PIN A0 // config for ESP8266
#define MAX_BRIGHTNESS 400.0

                
int r = 0;
int g = 0;
int b = 0;
float input_value;
                
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
    Serial.begin(9600); // config for ESP8266
    pixels.begin();
}


void loop()
{
    input_value = analogRead(INPUT_PIN);
    Serial.println(input_value);
    input_value = ((MAX_BRIGHTNESS-input_value)/MAX_BRIGHTNESS) * (3*(255));
    //Serial.println(input_value);
    if (input_value<255){
        r = input_value;
        g = 0;
        b = 0;
    }
    if (input_value<510 && input_value>255){
        r = 510 - input_value;
        g = input_value-255;
        b = 0;
    }
    if(input_value>510){
        r = 0;
        g = 765-input_value;
        b = input_value-510;
    }
    pixels.setPixelColor(1,pixels.Color(r,g,b));
    pixels.show();
    delay(10);
}
