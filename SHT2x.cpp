/*
SHT2x - Library for the SHT2x series of Sensirion sensors.

Copyright 2012 Eduard Iten

Supported devices:
SHT20*
SHT21
SHT25

*The SHT20 has not been tested so far, but should work according
the Sensirion datasheet. If anyone can confirm this, please report.

This library is free software, it is released under the GNU GPL v3.
Please find the terms and conditions in the attached gpl.txt or
in the world wide web: <http://www.gnu.org/licenses/>

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
or check in the web: <http://www.gnu.org/licenses/>
*/

#include "SHT2x.h"

uint32_t timeout=0;

void SHT2xClass::softReset ()
{
     Wire.beginTransmission(SHT2xADDR);
     Wire.write(SOFT_RESET);
     delay(15);
}

uint8_t SHT2xClass::readUserRegister()
{
     Wire.beginTransmission(SHT2xADDR);
     Wire.write(USER_REG_R);
     Wire.endTransmission();
     Wire.requestFrom(SHT2xADDR,(uint8_t)2);
     while(Wire.available()<2) {
          ;
     }
     return Wire.read();
}

void SHT2xClass::writeUserRegister(uint8_t userRegister)
{
     Wire.beginTransmission(SHT2xADDR);
     Wire.write(userRegister);
     Wire.endTransmission();
}


uint16_t SHT2xClass::readMeasurement(SHT2xMeasureType type)
{
     uint16_t value = 0;
     uint8_t low, high;

     Wire.beginTransmission(SHT2xADDR);
     switch (type) {
     case HUMIDITY:
          Wire.write(MEASUREMENT_RH_HM);
          break;
     case TEMP:
          Wire.write(MEASUREMENT_T_HM);
          break;
     }
     Wire.endTransmission();

     //wait for measurement to complete.
     timeout= millis()+300;
     while (!digitalRead(18)) {
          if (millis()>timeout) {
               return 0;
          }
     }

     Wire.requestFrom(SHT2xADDR,(uint8_t)3);
     timeout=millis()+300;
     while (Wire.available()<3) {
          if (millis()>timeout) {
               return 0;
          }
     }
     high=Wire.read();
     low=Wire.read();
     value=(uint16_t)high << 8 | low;
     value &= ~0x0003;
     return value;
}

float SHT2xClass::readT()
{
     return -46.85+175.72/65536.00*(float)readMeasurement(TEMP);
}

float SHT2xClass::readRH()
{
     return -6.0+125.0/65536.00*(float)readMeasurement(HUMIDITY);
}

void SHT2xClass::setHeater(uint8_t on)
{
     uint8_t userRegister;
     userRegister=readUserRegister();
     if (on) {
          userRegister=(userRegister&~SHT2x_HEATER_MASK) | SHT2x_HEATER_ON;
     } else {
          userRegister=(userRegister&~SHT2x_HEATER_MASK) | SHT2x_HEATER_OFF;
     }
}
SHT2xClass SHT2x;
