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

#ifndef SHT2X_H
#define SHT2X_H

#include <inttypes.h>
#include <Wire.h>
#include "Arduino.h"

//  Address
const uint8_t SHT2xADDR = 0x40;

//  CRC
const uint16_t POLYNOMIAL = 0x131;  //P(x)=x^8+x^5+x^4+1 = 100110001

// sensor commands
typedef enum {
     MEASUREMENT_T_HM    = 0xE3, // Temperature measurement, hold master
     MEASUREMENT_RH_HM   = 0xE5, // Humidity measurement,  hold master
     MEASUREMENT_T_POLL  = 0xF3, // Temperature measurement, no hold master, currently not used
     MEASUREMENT_RH_POLL = 0xF5, // Humidity measurement, no hold master, currently not used
     USER_REG_W          = 0xE6, // write user register
     USER_REG_R          = 0xE7, // read user register
     SOFT_RESET          = 0xFE  // soft reset
} SHT2xCommand;

// sensor resolutions
typedef enum {
     SHT2x_RES_12_14BIT       = 0x00, // RH=12bit, T=14bit
     SHT2x_RES_8_12BIT        = 0x01, // RH= 8bit, T=12bit
     SHT2x_RES_10_13BIT       = 0x80, // RH=10bit, T=13bit
     SHT2x_RES_11_11BIT       = 0x81, // RH=11bit, T=11bit
     SHT2x_RES_MASK           = 0x81  // Mask for res. bits (7,0) in user reg.
} SHT2xResolution;

typedef enum {
     SHT2x_HEATER_ON          = 0x04, // heater on
     SHT2x_HEATER_OFF         = 0x00, // heater off
     SHT2x_HEATER_MASK        = 0x04, // Mask for Heater bit(2) in user reg.
} SHT2xHeater;

// measurement signal selection
typedef enum {
     HUMIDITY,
     TEMP
} SHT2xMeasureType;


class SHT2xClass {
public:
     void softReset();
     void setHeater(uint8_t on);
     float readRH();
     float readT();

private:
     uint8_t readUserRegister();
     void writeUserRegister(uint8_t userRegister);
     uint16_t readMeasurement(SHT2xMeasureType type);
};

extern SHT2xClass SHT2x;

#endif
