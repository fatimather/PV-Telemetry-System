#include <Wire.h>
#include <Adafruit_INA219.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define GREEN_LED 8
#define RED_LED 9

Adafruit_INA219 ina219;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    digitalWrite(RED_LED, HIGH);
    while (1) { delay(10); }
  }
  dht.begin();
  digitalWrite(GREEN_LED, HIGH);
}

void loop() {
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW(); 
  float calculated_power = current_mA * busvoltage;
  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print CSV formatted output for easy logging/plotting
  Serial.print("Voltage(V): "); Serial.print(busvoltage);
  Serial.print(" | Current(mA): "); Serial.print(current_mA);
  Serial.print(" | Power(mW) by INA 219: "); Serial.print(power_mW);
  Serial.print(" | Power(mW) by Calculation: "); Serial.print(calculated_power);
  Serial.print(" | Temp(C): "); Serial.print(tempC);
  Serial.print(" | Humidity(%): "); Serial.println(humidity);

  delay(2000);
}
