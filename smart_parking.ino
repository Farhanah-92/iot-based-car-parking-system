#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "Your_Blynk_Auth_Token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

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

  Serial.println("Car Parking IoT System");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);

  Serial.print("S1: ");
  Serial.print(s1 == LOW ? "Occupied" : "Empty");
  Serial.print(" | S2: ");
  Serial.print(s2 == LOW ? "Occupied" : "Empty");
  Serial.print(" | S3: ");
  Serial.print(s3 == LOW ? "Occupied" : "Empty");
  Serial.print(" | S4: ");
  Serial.println(s4 == LOW ? "Occupied" : "Empty");

  // Send status to Blynk
  Blynk.virtualWrite(V0, s1 == LOW ? 255 : 0);
  Blynk.virtualWrite(V1, s2 == LOW ? 255 : 0);
  Blynk.virtualWrite(V2, s3 == LOW ? 255 : 0);
  Blynk.virtualWrite(V3, s4 == LOW ? 255 : 0);

  delay(500);
}
