#include <Wire.h>
#include <Adafruit_BMP280.h>

#define LED_PIN 8       // LED
#define POT_PIN 0       // Potentiometer

Adafruit_BMP280 bmp;

float huidigeTemp = 0;
float gewensteTemp = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin(6, 7); // SDA, SCL

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 niet gevonden!");
    while (1);
  }
}


void loop() {
  huidigeTemp = bmp.readTemperature();


  // Potentiometer van 0-3260 --> 0-30
  int potValue = analogRead(POT_PIN);
  gewensteTemp = map(potValue, 0, 3200, 0, 30);


  if (huidigeTemp < gewensteTemp) {
    digitalWrite(LED_PIN, HIGH);  // Ketel aan
  } else {
    digitalWrite(LED_PIN, LOW);   // Ketel uit
  }


  Serial.print("Huidige Temp: "); Serial.print(huidigeTemp);
  Serial.print(" °C | Gewenste Temp: "); Serial.print(gewensteTemp);
  Serial.print(" °C | Ketel: "); Serial.println(digitalRead(LED_PIN) ? "AAN" : "UIT");

  delay(1000);
}