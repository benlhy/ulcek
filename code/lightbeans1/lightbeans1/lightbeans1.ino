//#define BUILTIN_LED D4 //for the ESP8266
//#define BUILTIN_LED 13 //for the Nano
#define OFF_TIME 2000 // time which it is off
#define ON_TIME 2000 // time which it is on

void setup()  
{
    pinMode(BUILTIN_LED,OUTPUT);
}
void loop()  
{
    digitalWrite(BUILTIN_LED,HIGH);
    delay(ON_TIME);
    digitalWrite(BUILTIN_LED,LOW);
    delay(OFF_TIME);
}
