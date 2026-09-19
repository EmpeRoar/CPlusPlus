#include <Arduino.h>

enum DroneState
{
  DroneState_Idle,
  DroneState_Armed,
  DroneState_Active,
  DroneState_Stopped
};

struct DroneCommand
{
  String command;
  float strength;
  unsigned long durationMs;
  unsigned long issuedAtMs;
};

constexpr uint8_t MOTOR_PIN_FRONT = 9;
constexpr uint8_t MOTOR_PIN_BACK = 10;
constexpr uint8_t MOTOR_PIN_LEFT = 11;
constexpr uint8_t MOTOR_PIN_RIGHT = 12;
constexpr uint8_t EMERGENCY_PIN = 2;

DroneState state = DroneState_Idle;
DroneCommand activeCommand = { "", 0.0f, 0UL, 0UL };
bool emergencyStopActive = false;
unsigned long lastCommandAtMs = 0;
float batteryPercent = 100.0f;

void stopAllMotors();
void runSingleMotor(uint8_t pin, float strength);
void runMotorPair(uint8_t positivePin, uint8_t negativePin, float modifier, float strength);
int mapDutyCycle(float strength);
void parseCommand(const String& message);

void setup()
{
  Serial.begin(115200);
  pinMode(MOTOR_PIN_FRONT, OUTPUT);
  pinMode(MOTOR_PIN_BACK, OUTPUT);
  pinMode(MOTOR_PIN_LEFT, OUTPUT);
  pinMode(MOTOR_PIN_RIGHT, OUTPUT);
  pinMode(EMERGENCY_PIN, INPUT_PULLUP);

  stopAllMotors();
  state = DroneState_Idle;
  Serial.println(F("DRONE_READY"));
}

void loop()
{
  if (digitalRead(EMERGENCY_PIN) == LOW)
  {
    emergencyStopActive = true;
    state = DroneState_Stopped;
    stopAllMotors();
    Serial.println(F("EMERGENCY_STOP"));
    delay(100);
    return;
  }

  if (emergencyStopActive && (millis() - lastCommandAtMs) > 500UL)
  {
    emergencyStopActive = false;
    state = DroneState_Idle;
  }

  if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    if (message.length() > 0)
    {
      parseCommand(message);
    }
  }

  if (activeCommand.command.length() > 0 && (millis() - activeCommand.issuedAtMs) >= activeCommand.durationMs)
  {
    stopAllMotors();
    state = DroneState_Idle;
    activeCommand = { "", 0.0f, 0UL, 0UL };
  }

  batteryPercent = max(0.0f, batteryPercent - 0.0025f);
  delay(20);
}

void parseCommand(const String& message)
{
  String trimmed = message;
  trimmed.trim();

  if (trimmed.length() == 0)
  {
    return;
  }

  if (trimmed.equalsIgnoreCase("emergencyStop"))
  {
    emergencyStopActive = true;
    state = DroneState_Stopped;
    stopAllMotors();
    Serial.println(F("DRONE_STOPPED"));
    return;
  }

  String payload = trimmed.startsWith("CMD:") ? trimmed.substring(4) : trimmed;
  payload.trim();

  if (payload.length() == 0)
  {
    Serial.println(F("INVALID_COMMAND"));
    return;
  }

  int firstComma = payload.indexOf(',');
  int secondComma = (firstComma >= 0) ? payload.indexOf(',', firstComma + 1) : -1;
  int thirdComma = (secondComma >= 0) ? payload.indexOf(',', secondComma + 1) : -1;

  if (firstComma < 0 || secondComma < 0)
  {
    Serial.println(F("INVALID_COMMAND"));
    return;
  }

  String command = payload.substring(0, firstComma);
  command.trim();
  command.toLowerCase();

  String strengthText = payload.substring(firstComma + 1, secondComma);
  strengthText.trim();

  String durationText = (thirdComma > 0)
    ? payload.substring(secondComma + 1, thirdComma)
    : payload.substring(secondComma + 1);
  durationText.trim();

  float strength = strengthText.toFloat();
  unsigned long durationMs = static_cast<unsigned long>(durationText.toInt());

  if (command.length() == 0 || strength <= 0.0f || strength > 2.0f || durationMs == 0UL || durationMs > 5000UL)
  {
    Serial.println(F("INVALID_COMMAND"));
    return;
  }

  activeCommand = { command, strength, durationMs, millis() };
  lastCommandAtMs = millis();
  state = DroneState_Armed;

  if (command == "moveForward")
  {
    state = DroneState_Active;
    runMotorPair(MOTOR_PIN_FRONT, MOTOR_PIN_BACK, 1.0f, strength);
  }
  else if (command == "moveBackward")
  {
    state = DroneState_Active;
    runMotorPair(MOTOR_PIN_BACK, MOTOR_PIN_FRONT, 1.0f, strength);
  }
  else if (command == "moveUp")
  {
    state = DroneState_Active;
    runSingleMotor(MOTOR_PIN_FRONT, strength);
  }
  else if (command == "moveDown")
  {
    state = DroneState_Active;
    runSingleMotor(MOTOR_PIN_BACK, strength);
  }
  else if (command == "moveSidewardLeft")
  {
    state = DroneState_Active;
    runSingleMotor(MOTOR_PIN_LEFT, strength);
  }
  else if (command == "moveSidewardRight")
  {
    state = DroneState_Active;
    runSingleMotor(MOTOR_PIN_RIGHT, strength);
  }
  else if (command == "rotateHorizontal")
  {
    state = DroneState_Active;
    runMotorPair(MOTOR_PIN_LEFT, MOTOR_PIN_RIGHT, 0.75f, strength);
  }
  else
  {
    Serial.println(F("INVALID_COMMAND"));
    state = DroneState_Stopped;
    stopAllMotors();
    activeCommand = { "", 0.0f, 0UL, 0UL };
    return;
  }

  Serial.print(F("EXECUTED:"));
  Serial.println(command);
}

void runSingleMotor(uint8_t pin, float strength)
{
  analogWrite(pin, mapDutyCycle(strength));
}

void runMotorPair(uint8_t positivePin, uint8_t negativePin, float modifier, float strength)
{
  analogWrite(positivePin, mapDutyCycle(strength * modifier));
  analogWrite(negativePin, 0);
}

int mapDutyCycle(float strength)
{
  return constrain(static_cast<int>(strength * 255.0f), 0, 255);
}

void stopAllMotors()
{
  analogWrite(MOTOR_PIN_FRONT, 0);
  analogWrite(MOTOR_PIN_BACK, 0);
  analogWrite(MOTOR_PIN_LEFT, 0);
  analogWrite(MOTOR_PIN_RIGHT, 0);
}
