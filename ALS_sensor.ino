#include "DFRobot_VEML7700.h" /* sensor library */
#include <Wire.h> /* arduino library used to communicate with i2c */
#include <stdint.h>

DFRobot_VEML7700 als; /* instance of als object */

void take_action(uint8_t state){
  digitalWrite(LED_BUILTIN, state);
}

void setup() {
  als.begin(); /* default initialization */
  Serial.begin(9600);
}

void loop() {
  float illuminance, w_illuminance,a_illuminance, aw_illuminance;
  als.getALSLux(illuminance); /* Illuminance measured */
  Serial.print("Lux measured: ");
  Serial.println(illuminance);
  /*als.getWhiteLux(w_illuminance);
  als.getAutoALSLux(a_illuminance);
  als.getAutoWhiteLux(aw_illuminance);
  Serial.print(" white illuminance lux measured: ");
  Serial.print(w_illuminance);
  Serial.print(" auto illuminance lux measured: ");
  Serial.print(a_illuminance);
  Serial.print(" auto white illuminance lux measured: ");
  Serial.println(aw_illuminance);*/
  if(illuminance < 100){
    take_action(HIGH);
  }
  else{
    take_action(LOW);
  }
  delay(500);

}
