#define waterFlowIn_PIN 
#define waterFlowOut_PIN 
volatile double waterFlowIn;
volatile double waterFlowOut;

void setup()
{
  Serial.begin(9600);  //baudrate
  waterFlowOut = 0;
   waterFlowOut = 0;
   attachInterrupt(0, pulse, RISING);//DIGITAL Pin 2: Interrupt 0
  attachInterrupt(1, pulse, RISING);  //DIGITAL Pin 3: Interrupt 1
}

void loop()
{
  Serial.print("waterFlowIn: ");
  Serial.print(waterFlowIn);
  Serial.println("   L");
    Serial.print("waterFlowOut: ");
  Serial.print(waterFlowOut);
  Serial.println("   L");
   Serial.println("----------------------");
  delay(5000);
}

void pulse()   //measure the quantity of square wave
{
  waterFlowIn += 1.0 / 450.0; // 450 pulses for 1 liter (see product parameters)

  waterFlowOut += 1.0 / 450.0; // 450 pulses for 1 liter (see product parameters)
}

