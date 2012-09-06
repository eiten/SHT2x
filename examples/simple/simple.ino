#include <Wire.h>
#include <SHT2x.h>

void setup()
{
     Serial.begin(9600);
     Wire.begin();
}

void loop()
{
     Serial.print("Temperature: ");
     Serial.print(SHT2x.readT());
     Serial.print("°C, Humidity: ");
     Serial.print(SHT2x.readRH());
     Serial.println("%RH");
     delay(1000);
}

