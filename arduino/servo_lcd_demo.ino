#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Create an LCD object with I2C address 0x27 and 16x2 screen size.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create a servo object to control the motor.
Servo myServo;

// Pin used for the servo signal wire.
const int servoPin = 9;

// Current servo angle and direction step.
int angle = 0;
int step = 5;

void setup() {
  // Attach the servo to the chosen Arduino pin.
  myServo.attach(servoPin);

  // Initialize the LCD and turn on the backlight.
  lcd.init();
  lcd.backlight();

  // Show a startup message.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Servo + LCD");
  lcd.setCursor(0, 1);
  lcd.print("Angle: 0 deg");

  // Set the servo to the starting angle.
  myServo.write(angle);
}

void loop() {
  // Move the servo by the current step value.
  angle += step;

  // Reverse direction when the servo reaches the limits.
  if (angle >= 180 || angle <= 0) {
    step = -step;
  }

  // Update the servo position.
  myServo.write(angle);

  // Display the current angle on the LCD.
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");

  // Add a leading space for numbers less than 100 so the display stays aligned.
  if (angle < 100) {
    lcd.print(" ");
  }

  lcd.print(angle);
  lcd.print(" deg");

  // Small delay to make the movement smooth.
  delay(30);
}
