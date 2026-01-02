#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;

void setup() {
  Serial.begin(9600);
}

void loop() {

  float tempValue = readtemp();   // get temperature in float
  float humidity =  readHumidity() ;

}

float readtemp() {

  DHT11.read(DHT11PIN);  // read sensor

  float temp = (float)DHT11.temperature;  // save temp in float

  Serial.print("Temperature (C): ");
  Serial.println(temp, 2);

  delay(2000);

  return temp;   // return the float value
}


float readHumidity() {

  DHT11.read(DHT11PIN);  // read sensor

  float humidity = (float)DHT11.temperature;  // save temp in float

  Serial.print("humidity (%): ");
  Serial.println(humidity, 2);

  delay(2000);

  return humidity;   // return the float value
}
