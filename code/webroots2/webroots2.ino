#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 1 // change if you have more pixels
#define PIN D6 // config for ESP8266
#define INPUT_PIN A0 // config for ESP8266
#define BRIGHTNESS 4 //set this as the threshold value for darkness

#define IO_USERNAME    "your_username" //Your Adafruit username
#define IO_KEY         "your_key" //AIO key from earlier
#define WIFI_SSID       "your_ssid"
#define WIFI_PASS       "your_pass"

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // create Adafruit io object.

// Set the volatile keyword if you want to retain the RGB values

int volatile r = 0;  
int volatile g = 0;  
int volatile b = 0;  
int input_value = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 

AdafruitIO_Feed *color = io.feed("Nightlight_color");  

// setup and loop functions

void setup() {
  Serial.begin(115200); // begin serial communications for debugging

  io.connect(); // This is a method under AdafruitWifi.h that helps to set up the wireless connection and contacts the IO server.

  color->onMessage(handleMessage); //we will need to handle messages on the "Nightlight_color" stream that we have set up earlier

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText()); 
  

  // Init RGB led
 
  pixels.begin();
  pixels.show();
  
  pinMode(INPUT_PIN, INPUT);
}

void loop() {  
  // put your main code here, to run repeatedly:
  io.run(); 
  input_value = analogRead(INPUT_PIN);
  if (input_value < BRIGHTNESS) {
    turn_on();
  }
  if (input_value > BRIGHTNESS) {
    turn_off();
  }
  delay(100);
}


// Functions we wrote

void turn_on(){  
  r=100; // set RGB values
  g=30;
  b=70;
  for(int i=0; i <NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(r,g,b));
  }
  pixels.show();
}

void turn_off(){  
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0)); // set the color to (0,0,0), off!
  }
  pixels.show();
}

// New functions

void handleMessage(AdafruitIO_Data *data) { //New AdafruitIO_Data object!

  // print RGB values and hex value
  Serial.println("Received HEX: ");
  Serial.println(data->value()); // displays data as hex

  //Calls hex2dec function and updates global volatile rgb values.
  hex2dec(data->value());

  long color = data->toNeoPixel(); // converts hex to a value the neopixel can use!

  for(int i=0; i<NUMPIXELS; ++i) {
    pixels.setPixelColor(i, color); // sets the color.
  }
  pixels.show();

}

void hex2dec(String hexstring){
  int number = strtol( &hexstring[1], NULL, 16);

  // Split them up into r, g, b values
  r = number >> 16;
  g = number >> 8 & 0xFF;
  b = number & 0xFF;
}
