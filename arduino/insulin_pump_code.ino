#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// LCD: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pins
const int sensorPin = A0;
const int motorPin = D5;      // Use appropriate GPIO if using NodeMCU or ESP8266 board
const int buzzerPin = D6;

// Thresholds (mg/dL)
const int thresholdLow = 70;
const int thresholdHigh = 130;

// Wi-Fi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Optional: your server endpoint to send glucose values
const char* endpoint = "http://your-server.com/api/glucose"; // Replace with your API endpoint

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  Serial.begin(115200);

  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin); // IR/NIR sensor simulation
  float glucoseLevel = map(sensorValue, 0, 1023, 50, 200); // Estimation

  Serial.print("Glucose: ");
  Serial.println(glucoseLevel);

  lcd.setCursor(0, 0);
  lcd.print("Glucose: ");
  lcd.print(glucoseLevel, 0);
  lcd.print(" mg/dL");

  // Buzzer & Insulin Logic
  if (glucoseLevel < thresholdLow) {
    lcd.setCursor(0, 1);
    lcd.print("Low! Call Doctor");
    tone(buzzerPin, 1000); // 1 kHz beep
    digitalWrite(motorPin, LOW);
  }
  else if (glucoseLevel > thresholdHigh) {
    lcd.setCursor(0, 1);
    lcd.print("Injecting Insulin");
    noTone(buzzerPin);
    digitalWrite(motorPin, HIGH);
    delay(2000);
    digitalWrite(motorPin, LOW);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Level Normal    ");
    noTone(buzzerPin);
    digitalWrite(motorPin, LOW);
  }

  // Optional: Send to cloud server or app
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"glucose\":" + String(glucoseLevel, 1) + "}";
    int httpCode = http.POST(payload);

    Serial.print("POST status: ");
    Serial.println(httpCode);
    http.end();
  }

  delay(5000);
}
