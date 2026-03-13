#define BLYNK_TEMPLATE_ID        "TMPL5FwuhzHsa"
#define BLYNK_TEMPLATE_NAME      "Thermostaat"
#define BLYNK_DEVICE_NAME        "ESP32"

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define LED_PIN 8
#define POT_PIN 0

char auth[] = "AoN5Xq5F7_iVq0uZdJ9dQiSDg2y1bZVd";
char ssid[] = "embed";
char pass[] = "weareincontrol";

Adafruit_BMP280 bmp;

float currentTemp;
float desiredTemp;

BlynkTimer timer;

BLYNK_WRITE(V1)
{
  desiredTemp = param.asFloat();
}


void sendData()
{
  currentTemp = bmp.readTemperature();

  Blynk.virtualWrite(V0, currentTemp);
  Blynk.virtualWrite(V2, digitalRead(LED_PIN));

  Serial.print("Temp: ");
  Serial.print(currentTemp);
  Serial.print(" | Gewenst: ");
  Serial.print(desiredTemp);
  Serial.print(" | Ketel: ");
  Serial.println(digitalRead(LED_PIN));
}


void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin(6,7);

  if (!bmp.begin(0x76))
  {
    Serial.println("BMP280 niet gevonden");
    while (1);
  }

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, sendData);
}


void loop()
{
  Blynk.run();
  timer.run();

  if (currentTemp < desiredTemp)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}