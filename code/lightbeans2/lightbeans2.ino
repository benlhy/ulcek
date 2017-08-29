// Lightbeans 2, Sensors

#define MAX_BRIGHTNESS 450 // You will need to calibrate this value by opening the Serial Monitor
 

float LED_value;
float light_level;
void setup() {
    Serial.begin(9600);
    pinMode(A0,INPUT);
    pinMode(BUILTIN_LED,OUTPUT);
}

void loop() {
    light_level = analogRead(A0);
    Serial.println(light_level);
    LED_value = ((450.0 - light_level)/1024.0)*255.0;
    Serial.println(LED_value);
    analogWrite(BUILTIN_LED,LED_value);
    delay(1000);
}
