#include <EEPROM.h>
#include "GravityTDS.h"
#define TdsSensorPin A1
GravityTDS gravityTds;



const int relayPinTDS  = 8;    // Relay control pin (digital pin 8) in1 for TDS motor

float temperatureTDS = 25,tdsValue = 0;



volatile double waterFlowIn;


void setup() {
   Serial.begin(9600);  //baudrate
  waterFlowIn = 0;
  attachInterrupt(0, pulse, RISING);  //DIGITAL Pin 2: Interrupt 0
   pinMode(relayPinTDS, OUTPUT);
  digitalWrite(relayPinTDS, LOW);  // Make sure relay is off at start


    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization

}

void loop() {
   Serial.print("waterFlowIn: ");
  Serial.print(waterFlowIn);
  Serial.println("   L");
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperatureTDS);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print("tdsValue: ");
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    // Relay control logic
  if (tdsValue >= 450) {
    digitalWrite(relayPinTDS, LOW);   // Turn ON relay (activate motor/fan/heater)
    Serial.println("TDS Motor ON");
  } 
  else if (tdsValue <= 250) {
    digitalWrite(relayPinTDS, LOW);   // Turn ON relay (activate motor/fan/heater)
    Serial.println("TDS Motor ON");
  } else {
    digitalWrite(relayPinTDS, HIGH);    // Turn OFF relay
    Serial.println("TDS Motor OFF");
  }
  Serial.println("----------------------");

    delay(5000);

}
void pulse()   //measure the quantity of square wave
{
  waterFlowIn += 1.0 / 450.0; // 450 pulses for 1 liter (see product parameters)
}
