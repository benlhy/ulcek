#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// =================== Code from Lightbeans 3 =======================

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

// ===================== Code from Lightbeans 3 ========================


const char* ssid = "MyNetwork";
const char* password = "Password";


// ===================== Interrupt Code =======================

int interruptPin = 14; //Defined as D5 on the WeMos
volatile bool state = false;

// ===================== Interrupt Code =======================



void setup () {

  pixels.begin();
  pinMode(INPUT_PIN, INPUT);

  // ===================== Interrupt Code =======================

  pinMode(interruptPin,INPUT); //interruptPin was defined earlier in the code
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonPress, FALLING);

  // ===================== Interrupt Code =======================

  WiFi.mode(WIFI_STA); //we are going to be a client!
  WiFi.begin(ssid,password); //Start the wifi, with this ssid and password

  Serial.begin(9600);

  // Wait for connection

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
      Serial.println("Connection Failed. Rebooting ... ");
      delay(5000);
      ESP.restart();
  }

  // Debug

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  // Start process

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();

  input_value = analogRead(INPUT_PIN);
  if (input_value < BRIGHTNESS and state==true) { // if larger than our threshold value, turn on.
    turn_on(r,g,b);
  }
  if (input_value > BRIGHTNESS or state==false) {
    turn_off();
  }
  delay(UPDATE_TIME);

}

void buttonPress(){
  state != state;
}

// Functions we wrote
// This function takes in a red, green, blue and displays the colors
void turn_on(int r, int g, int b){
  for(int i=0; i < NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(r,g,b));
  }
  pixels.show();
}


// This function turns off all pixels
void turn_off(){
  for(int i=0; i < NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0)); // set the color to (0,0,0), off!
  }
  pixels.show();
}
