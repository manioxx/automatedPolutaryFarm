#include <Servo.h>
const int motorPin = 7;   // Digital pin connected to the motor control input
const int motorPin2 = 6;
const int motorPinena = 5 ; // Digital pin connected to the motor control input
Servo myServo;
int servoPin = 3;  // Use a PWM-capable pin



void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPinena, OUTPUT);   // Set motor control pin as an output
  analogWrite(motorPinena, 50);
  myServo.attach(servoPin);
  rotateServo(95);

}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();  // Read the incoming character from serial

    if (command == '1') {
      delay(1000);  // Enable time in milliseconds
      rotateServo(180);
      digitalWrite(motorPin, HIGH);
      digitalWrite(motorPin2, LOW);
      delay(3000);  
      digitalWrite(motorPin, LOW);
      rotateServo(95);
      delay(1000);
      //reverse
      digitalWrite(motorPin, LOW);
      digitalWrite(motorPin2, HIGH);
      delay(3000);  // Enable time in milliseconds
      digitalWrite(motorPin2, LOW);
      Serial.write("Done");
    }
  }
}
void rotateServo(int degrees) {
  // Ensure the specified angle is within valid range (0 to 180)
  degrees = constrain(degrees, 0, 180);
  
  // Rotate the servo to the specified angle
  myServo.write(degrees);
}



