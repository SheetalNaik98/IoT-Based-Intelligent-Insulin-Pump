#include <LiquidCrystal.h>

// LCD pin configuration: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin assignments
const int sensorPin = A0;       // IR sensor connected to analog pin A0
const int motorPin = 9;         // Motor control pin
const int buzzerPin = 8;        // Optional: buzzer for alert (if available)
const int thresholdLow = 70;    // Hypoglycemia threshold
const int thresholdHigh = 130;  // Hyperglycemia threshold

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Simulated glucose value (0–1023)
  float glucoseLevel = map(sensorValue, 0, 1023, 50, 200); // Rough mapping

  lcd.setCursor(0, 0);
  lcd.print("Glucose: ");
  lcd.print(glucoseLevel, 0); // Print without decimals
  lcd.print(" mg/dL");

  if (glucoseLevel < thresholdLow) {
    lcd.setCursor(0, 1);
    lcd.print("Low! Alert Care.");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorPin, LOW);  // No insulin
  }
  else if (glucoseLevel > thresholdHigh) {
    lcd.setCursor(0, 1);
    lcd.print("Injecting Insulin");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, HIGH);
    delay(2000); // Injection duration
    digitalWrite(motorPin, LOW);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Level Normal    ");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
  }

  delay(5000); // Wait before next read
}
