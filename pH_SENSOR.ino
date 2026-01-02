#include "DFRobot_PH.h"
#include <EEPROM.h>

#define PH_PIN A2
float voltage,phValue,temperature = 25;
DFRobot_PH ph;

const int relayPinpH  = 9;    // Relay control pin (digital pin 9) in2 for pH motor

void setup()
{
    Serial.begin(9600);  
    ph.begin();

    pinMode(relayPinpH, OUTPUT);
  digitalWrite(relayPinpH, LOW);  // Make sure relay is off at start


}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
        voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
        //phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
        //Serial.print("temperature:");
        //Serial.print(temperature,1);
        Serial.print("pH: ");
        Serial.println(phValue,2);
    }
    ph.calibration(voltage,temperature);           // calibration process by Serail CMD
     // Relay control logic
  if (phValue >= 6.5) {
    digitalWrite(relayPinpH, LOW);   // Turn ON relay (activate motor/fan/heater)
    Serial.println("pH Motor ON");
  } 
  else if (phValue <= 5.5) {
    digitalWrite(relayPinpH, LOW);   // Turn ON relay (activate motor/fan/heater)
    Serial.println("pH Motor ON");
  } else {
    digitalWrite(relayPinpH, HIGH);    // Turn OFF relay
    Serial.println("pH Motor OFF");
  }
  Serial.println("----------------------");
   delay(5000);
}

//float readTemperature()
//{
  //add your code here to get the temperature from your temperature sensor
//}
