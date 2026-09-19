// This sketch connects an ESP32 to AWS IoT Core over MQTT,
// controls a servo motor from incoming commands,
// and displays the current angle on an I2C LCD screen.
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

// -------------------------
// WiFi settings
// -------------------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// -------------------------
// AWS IoT settings
// -------------------------
const char* awsEndpoint = "YOUR-THING-ID-ats.iot.REGION.amazonaws.com";
const int awsPort = 8883;

const char* topicCommand = "servo/control";
const char* topicStatus = "servo/status";

// -------------------------
// AWS certs
// -------------------------
const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR AWS ROOT CA CERTIFICATE HERE
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR DEVICE CERTIFICATE HERE
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN PRIVATE KEY-----
YOUR PRIVATE KEY HERE
-----END PRIVATE KEY-----
)EOF";

// -------------------------
// LCD and servo
// -------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;
const int servoPin = 18;
int currentAngle = 90;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void showAngle(int angle) {
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  if (angle < 100) {
    lcd.print(" ");
  }
  lcd.print(angle);
  lcd.print(" deg");
}

void setServoAngle(int angle) {
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  currentAngle = angle;
  myServo.write(currentAngle);
  showAngle(currentAngle);

  Serial.print("Servo angle set to: ");
  Serial.println(currentAngle);
}

void publishStatus(int angle) {
  StaticJsonDocument<128> doc;
  doc["angle"] = angle;
  doc["status"] = "ok";

  char payload[128];
  serializeJson(doc, payload);

  client.publish(topicStatus, payload);
  Serial.println("Published status:");
  Serial.println(payload);
}

void handleCommand(String payload) {
  Serial.print("Received payload: ");
  Serial.println(payload);

  StaticJsonDocument<128> doc;
  DeserializationError err = deserializeJson(doc, payload);

  if (!err && doc.containsKey("angle")) {
    int angle = doc["angle"].as<int>();
    setServoAngle(angle);
    publishStatus(currentAngle);
    return;
  }

  int angle = payload.toInt();
  if (angle >= 0 && angle <= 180) {
    setServoAngle(angle);
    publishStatus(currentAngle);
    return;
  }

  Serial.println("Invalid angle command received");
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (String(topic) == String(topicCommand)) {
    handleCommand(message);
  }
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

void connectAWS() {
  while (!client.connected()) {
    Serial.println("Connecting to AWS IoT Core...");

    if (client.connect("esp32-servo-client")) {
      Serial.println("MQTT connected");
      client.subscribe(topicCommand);
      Serial.print("Subscribed to: ");
      Serial.println(topicCommand);
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AWS Servo");
  lcd.setCursor(0, 1);
  lcd.print("Booting...");

  myServo.attach(servoPin);
  myServo.write(currentAngle);

  connectWiFi();

  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(awsEndpoint, awsPort);
  client.setCallback(callback);

  connectAWS();
  publishStatus(currentAngle);
  showAngle(currentAngle);
}

void loop() {
  if (!client.connected()) {
    connectAWS();
  }

  client.loop();
  delay(100);
}
