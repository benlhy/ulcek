// Lightbeans 2, Sensors

#define MAX_BRIGHTNESS 450.0 // You will need to calibrate this value by opening the Serial Monitor, and add a decimal point
#define RESPONSE_TIME 1000 // in ms, reduce this if a faster response is wanted

float LED_value; // we use floats because we are using division and decimal points
float light_level;

void setup() {
    Serial.begin(9600);
    pinMode(A0,INPUT);
    pinMode(BUILTIN_LED,OUTPUT);
}

void loop() {
    light_level = analogRead(A0); // read the light level
    Serial.println(light_level); // see the value that we are reading
    LED_value = ((MAX_BRIGHTNESS - light_level)/1024.0)*255.0; // Take the difference, A0 can read from 0~1024 but we want it to be 0-255 and then scale it to the brightness that we want to represent (0-255)
    Serial.println(LED_value); // see what is the value we want to output
    analogWrite(BUILTIN_LED,LED_value); // now light the LED
    delay(RESPONSE_TIME); // wait for a time before updating the light
}
