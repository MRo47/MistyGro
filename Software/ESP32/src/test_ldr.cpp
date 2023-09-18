#include "ldr.h"
#include "utility.h"

ADC adc;
LDR ldr(10, &adc);

void setup()
{
  Serial.begin(115200);
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  Serial.println("LDR test, enter commands as below");
  Serial.println("r - to read LDR");
}

void loop()
{
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'r') {
      Serial.print("Reading LDR voltage: ");
      Serial.println(ldr.read_voltage());
    } else {
      Serial.println("invalid command");
    }
  }
}