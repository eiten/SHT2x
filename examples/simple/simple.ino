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
     // On the following line, \260 is the octal code for the degree sign. If
     // you would just write °, this would not work, as the Arduino IDE would
     // save it as an UTF8 character, resulting in two characters in the serial
     // transmission.
     Serial.print("\260C, Humidity: ");
     Serial.print(SHT2x.readRH());
     Serial.println("%RH");
     delay(1000);
}

