#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// ---------------- Pins ----------------
#define TRIG_PIN 9
#define ECHO_PIN 10
#define GREEN_PIN 2
#define RED_PIN 3
#define BLUE_PIN 4
#define BUZZER_PIN 5
#define SERVO_PIN 6

Servo scanner;

// ---------------- Variables ----------------
long duration;
int distance;

int angle = 90;
bool increasing = true;

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  scanner.attach(SERVO_PIN);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SecurSight AI");
  delay(1000);
  lcd.clear();
}

// ---------------- Get Distance ----------------
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Added a timeout (20000 µs) so the code doesn't freeze if it misses an echo
  duration = pulseIn(ECHO_PIN, HIGH, 20000); 

  if (duration == 0) return 40; // If timeout, assume clear/safe distance
  return duration * 0.034 / 2;
}

// ---------------- Loop ----------------
void loop() {

  // WIDENED BOUNDARIES: Increments by 8 instead of 5, spans 10° to 170° for maximum coverage
  if (increasing) {
    angle += 2;
    if (angle >= 170) increasing = false;
  } else {
    angle -= 2;
    if (angle <= 10) increasing = true;
  }

  scanner.write(angle);
  
  // Reduced delay to 35ms. This gives the servo just enough physical time 
  // to move without creating massive lags in your data.
  delay(35); 

  int dist = getDistance();

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" Distance: ");
  Serial.println(dist);

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(dist);
  lcd.print(" cm    ");

  lcd.setCursor(0, 1);

  // ---------------- LOGIC ----------------
  if (dist > 0 && dist < 15) {
    lcd.print("Status: ALERT! ");
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    tone(BUZZER_PIN, 2000);
  } 
  else if (dist >= 15 && dist < 30) {
    lcd.print("Status: WARNING   ");
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    noTone(BUZZER_PIN);
  } 
  else {
    lcd.print("Status: SAFE   ");
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    noTone(BUZZER_PIN);
  }
}