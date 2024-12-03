#include <Arduino.h>
#include <HCSR04.h>
#include "BTHome.h"

#define TRIG_PIN 4  // Pin for the Trigger
#define ECHO_PIN 5 // Pin for the Echo
#define DEVICE_NAME "Water-tank-sensor"  // The name of the sensor
#define ENABLE_ENCRYPT // Remove this line for no encryption
String BIND_KEY = "80d612dd69846e9c4e9d6db6d11c785e"; // Change this key with a string containing 32 of: a-f and 0-9 characters (hex) this will be asked in HA

BTHome bthome;
UltraSonicDistanceSensor hcSrSensor(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);
#ifdef ENABLE_ENCRYPT
  bthome.begin(DEVICE_NAME, true, BIND_KEY, false);
#else
  bthome.begin(DEVICE_NAME, false, "", false);
#endif
}

void loop() {
  uint64_t distance = hcSrSensor.measureDistanceCm() * 10;
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" mm");

  delay(500); // Delay for half a second
  //MEASUREMENT_MAX_LEN = 23, ENABLE_ENCRYPT will use extra 8 bytes, so each Measurement should smaller than 15

  // 1st method: just addMeasurement as much as you can, the code will split and send the adv packet automatically
  // each adv packet sending lasts for 1500ms
  bthome.resetMeasurement();
  // bthome.addMeasurement(sensorid, value) you can use the sensorids from the BTHome.h file
  // the Object ids of addMeasurement have to be applied in numerical order (from low to high) in your advertisement
  bthome.addMeasurement(ID_DISTANCE, distance);//3

  bthome.sendPacket();
  bthome.stop();

  delay(10000);
}

//Object ids by order
#if 0
#define ID_PACKET				0x00
#define ID_BATTERY				0x01
#define ID_TEMPERATURE_PRECISE 	0x02
#define ID_HUMIDITY_PRECISE 	0x03
#define ID_PRESSURE 			0x04
#define ID_ILLUMINANCE			0x05
#define ID_MASS					0x06
#define ID_MASSLB				0x07
#define ID_DEWPOINT				0x08
#define ID_COUNT				0x09
#define ID_ENERGY				0x0A
#define ID_POWER				0x0B
#define ID_VOLTAGE				0x0C
#define ID_PM25					0x0D
#define ID_PM10					0x0E
#define STATE_GENERIC_BOOLEAN	0x0F
#define STATE_POWER_ON			0x10
#define STATE_OPENING			0x11
#define ID_CO2					0x12
#define ID_TVOC					0x13
#define ID_MOISTURE_PRECISE		0x14
#define STATE_BATTERY_LOW		0x15
#define STATE_BATTERY_CHARHING	0x16
#define STATE_CO				0x17
#define STATE_COLD				0x18
#define STATE_CONNECTIVITY		0x19
#define STATE_DOOR				0x1A
#define STATE_GARAGE_DOOR		0x1B
#define STATE_GAS_DETECTED		0x1C
#define STATE_HEAT				0x1D
#define STATE_LIGHT				0x1E
#define STATE_LOCK				0x1F
#define STATE_MOISTURE			0x20
#define STATE_MOTION			0x21
#define STATE_MOVING			0x22
#define STATE_OCCUPANCY			0x23
#define STATE_PLUG				0x24
#define STATE_PRESENCE			0x25
#define STATE_PROBLEM			0x26
#define STATE_RUNNING			0x27
#define STATE_SAFETY			0x28
#define STATE_SMOKE				0x29
#define STATE_SOUND				0x2A
#define STATE_TAMPER			0x2B
#define STATE_VIBRATION			0x2C
#define STATE_WINDOW			0x2D
#define ID_HUMIDITY				0x2E
#define ID_MOISTURE				0x2F
#define EVENT_BUTTON			0x3A
#define EVENT_DIMMER			0x3C
#define ID_COUNT2				0x3D
#define ID_COUNT4				0x3E
#define ID_ROTATION				0x3F
#define ID_DISTANCE				0x40
#define ID_DISTANCEM			0x41
#define ID_DURATION				0x42
#define ID_CURRENT				0x43
#define ID_SPD					0x44
#define ID_TEMPERATURE			0x45
#define ID_UV					0x46
#define ID_VOLUME1				0x47
#define ID_VOLUME2				0x48
#define ID_VOLUMEFR				0x49
#define ID_VOLTAGE1				0x4A
#define ID_GAS					0x4B
#define ID_GAS4					0x4C
#define ID_ENERGY4				0x4D
#define ID_VOLUME				0x4E
#define ID_WATER				0x4F
#endif


///*
   //Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   //Ported to Arduino ESP32 by pcbreflux
   //Modified to work with NimBLE
   //Modified for V2 by Chreece
   //Modified by countrysideboy: Code cleanups, Chop Data, Encryption
   //BLE advertisement format from https://bthome.io/

//*/

//#include "BTHome.h"

//#define DEVICE_NAME "water-tank-sensor"  // The name of the sensor
////#define ENABLE_ENCRYPT // Remove this line for no encryption
//String BIND_KEY = "231d39c1d7cc1ab1aee224cd096db932"; // Change this key with a string containing 32 of: a-f and 0-9 characters (hex) this will be asked in HA

//BTHome bthome;

//#define TRIG_PIN 4  // Pin for the Trigger
//#define ECHO_PIN 5 // Pin for the Echo

//void setup() {
  //Serial.begin(115200);
//#ifdef ENABLE_ENCRYPT
  //bthome.begin(DEVICE_NAME, true, BIND_KEY, false);
//#else
  //bthome.begin(DEVICE_NAME, false, "", false);
//#endif
  //// Set TRIG_PIN as output and ECHO_PIN as input
  //pinMode(TRIG_PIN, OUTPUT);
  //pinMode(ECHO_PIN, INPUT);

  //Serial.println("HC-SR04 Distance Measurement Initialized");
//}

//void loop() {
    //// Trigger the sensor by sending a 10-microsecond HIGH pulse
  //digitalWrite(TRIG_PIN, LOW);
  //delayMicroseconds(2); // Ensure clean LOW pulse
  //digitalWrite(TRIG_PIN, HIGH);
  //delayMicroseconds(10); // 10-microsecond pulse
  //digitalWrite(TRIG_PIN, LOW);

  //// Read the echo pin and calculate the time in microseconds
  //long duration = pulseIn(ECHO_PIN, HIGH);

  //// Calculate the distance in centimeters
  //// Speed of sound = 343 m/s => 0.0343 cm/μs
  //float distance = duration * 0.0343 / 2;

  //// Print the distance to the serial monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  //delay(500); // Delay for half a second
  ////MEASUREMENT_MAX_LEN = 23, ENABLE_ENCRYPT will use extra 8 bytes, so each Measurement should smaller than 15

  //// 1st method: just addMeasurement as much as you can, the code will split and send the adv packet automatically
  //// each adv packet sending lasts for 1500ms
  //bthome.resetMeasurement();
  //// bthome.addMeasurement(sensorid, value) you can use the sensorids from the BTHome.h file
  //// the Object ids of addMeasurement have to be applied in numerical order (from low to high) in your advertisement
  //bthome.addMeasurement(ID_DISTANCE, (uint64_t)distance);//3

  //bthome.sendPacket();
  //bthome.stop();

  //bthome.resetMeasurement();
  //delay(10000);
//}

////Object ids by order
//#if 0
//#define ID_PACKET				0x00
//#define ID_BATTERY				0x01
//#define ID_TEMPERATURE_PRECISE 	0x02
//#define ID_HUMIDITY_PRECISE 	0x03
//#define ID_PRESSURE 			0x04
//#define ID_ILLUMINANCE			0x05
//#define ID_MASS					0x06
//#define ID_MASSLB				0x07
//#define ID_DEWPOINT				0x08
//#define ID_COUNT				0x09
//#define ID_ENERGY				0x0A
//#define ID_POWER				0x0B
//#define ID_VOLTAGE				0x0C
//#define ID_PM25					0x0D
//#define ID_PM10					0x0E
//#define STATE_GENERIC_BOOLEAN	0x0F
//#define STATE_POWER_ON			0x10
//#define STATE_OPENING			0x11
//#define ID_CO2					0x12
//#define ID_TVOC					0x13
//#define ID_MOISTURE_PRECISE		0x14
//#define STATE_BATTERY_LOW		0x15
//#define STATE_BATTERY_CHARHING	0x16
//#define STATE_CO				0x17
//#define STATE_COLD				0x18
//#define STATE_CONNECTIVITY		0x19
//#define STATE_DOOR				0x1A
//#define STATE_GARAGE_DOOR		0x1B
//#define STATE_GAS_DETECTED		0x1C
//#define STATE_HEAT				0x1D
//#define STATE_LIGHT				0x1E
//#define STATE_LOCK				0x1F
//#define STATE_MOISTURE			0x20
//#define STATE_MOTION			0x21
//#define STATE_MOVING			0x22
//#define STATE_OCCUPANCY			0x23
//#define STATE_PLUG				0x24
//#define STATE_PRESENCE			0x25
//#define STATE_PROBLEM			0x26
//#define STATE_RUNNING			0x27
//#define STATE_SAFETY			0x28
//#define STATE_SMOKE				0x29
//#define STATE_SOUND				0x2A
//#define STATE_TAMPER			0x2B
//#define STATE_VIBRATION			0x2C
//#define STATE_WINDOW			0x2D
//#define ID_HUMIDITY				0x2E
//#define ID_MOISTURE				0x2F
//#define EVENT_BUTTON			0x3A
//#define EVENT_DIMMER			0x3C
//#define ID_COUNT2				0x3D
//#define ID_COUNT4				0x3E
//#define ID_ROTATION				0x3F
//#define ID_DISTANCE				0x40
//#define ID_DISTANCEM			0x41
//#define ID_DURATION				0x42
//#define ID_CURRENT				0x43
//#define ID_SPD					0x44
//#define ID_TEMPERATURE			0x45
//#define ID_UV					0x46
//#define ID_VOLUME1				0x47
//#define ID_VOLUME2				0x48
//#define ID_VOLUMEFR				0x49
//#define ID_VOLTAGE1				0x4A
//#define ID_GAS					0x4B
//#define ID_GAS4					0x4C
//#define ID_ENERGY4				0x4D
//#define ID_VOLUME				0x4E
//#define ID_WATER				0x4F
//#endif