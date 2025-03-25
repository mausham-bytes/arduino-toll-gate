// Arduino Toll Gate System using Ultrasonic Sensor

#include <Servo.h>

#define TRIG_PIN 9   // Ultrasonic Sensor Trigger Pin
#define ECHO_PIN 10  // Ultrasonic Sensor Echo Pin
#define SERVO_PIN 6  // Servo Motor Pin
#define DIST_THRESHOLD 10  // Distance threshold in cm

Servo gateServo;

void setup() {
  Serial.begin(9600);
  gateServo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  gateServo.write(0);  // Set initial position (closed)
  Serial.println("Toll Gate System Initialized");
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // Convert to cm
  return distance;
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < DIST_THRESHOLD) {
    Serial.println("Car detected, opening gate...");
    gateServo.write(90);  // Open gate
    delay(5000);          // Keep gate open for 5 seconds
    gateServo.write(0);   // Close gate
    Serial.println("Gate closed");
  }
  delay(1000);  // Delay for next reading
}
