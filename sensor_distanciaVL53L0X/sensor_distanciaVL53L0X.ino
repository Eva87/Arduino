#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int led_rojo = 12;
int led_amarillo1 = 13;
int led_amarillo2 = 11;

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  while (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 

  pinMode(led_rojo, OUTPUT);
  pinMode(led_amarillo1, OUTPUT);
  pinMode(led_amarillo2, OUTPUT);
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    int encender = measure.RangeMilliMeter;
    if(encender < 50) {
      digitalWrite(led_rojo, HIGH);
      digitalWrite(led_amarillo1, LOW);
      digitalWrite(led_amarillo2, LOW);
    } else if(encender > 50 && encender < 100) {
      digitalWrite(led_amarillo1, HIGH);
      digitalWrite(led_rojo, LOW);
      digitalWrite(led_amarillo2, LOW);
    } else {
      digitalWrite(led_amarillo2, HIGH);
      digitalWrite(led_rojo, LOW);
      digitalWrite(led_amarillo1, LOW);
    }
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);
}
