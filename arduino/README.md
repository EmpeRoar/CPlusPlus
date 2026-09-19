# Arduino Servo + LCD Project

This project moves a servo motor smoothly from 0 to 180 degrees and displays the current angle on a 16x2 LCD screen.

## Hardware
- Arduino Uno or similar
- Servo motor
- 16x2 LCD with I2C module
- Jumper wires

## Wiring
- Servo signal pin -> Arduino pin 9
- Servo power -> 5V
- Servo ground -> GND
- LCD SDA -> Arduino A4
- LCD SCL -> Arduino A5
- LCD VCC -> 5V
- LCD GND -> GND

## Libraries
Install these in the Arduino IDE:
- `Servo`
- `Wire`
- `LiquidCrystal_I2C`

## Run
1. Open the file `servo_lcd_demo.ino` in the Arduino IDE.
2. Select the correct board and port.
3. Upload the sketch.

The servo will sweep back and forth while the LCD displays the current angle.
