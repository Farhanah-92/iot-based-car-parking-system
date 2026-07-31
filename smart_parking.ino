#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "Your_Blynk_Auth_Token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

LiquidCrystal_I2C lcd(0x27, 16, 2);

// IR sensor pins
#define IR1 D1
#define IR2 D2
#define IR3 D5
#define IR4 D6

void setup() {
  Serial.begin(9600);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Car Parking IoT");
  delay(2000);
  lcd.clear();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);

  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(s1 == LOW ? "Occ" : "Emp ");
  lcd.print(" S2:");
  lcd.print(s2 == LOW ? "Occ" : "Emp");

  lcd.setCursor(0, 1);
  lcd.print("S3:");
  lcd.print(s3 == LOW ? "Occ" : "Emp ");
  lcd.print(" S4:");
  lcd.print(s4 == LOW ? "Occ" : "Emp");

  Blynk.virtualWrite(V0, s1 == LOW ? 255 : 0);
  Blynk.virtualWrite(V1, s2 == LOW ? 255 : 0);
  Blynk.virtualWrite(V2, s3 == LOW ? 255 : 0);
  Blynk.virtualWrite(V3, s4 == LOW ? 255 : 0);

  delay(500);
}
