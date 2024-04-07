#include <WiFi.h>

// WiFi network details
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server details
const char* host = "192.168.0.16"; // Local IP address of the device

#define MOISTURE_SENSOR_PIN 34

//Right now, these use lights to test code. They eventually will control a relay that turns a solenoid valve.
#define LED_BLUE 25 // Define the GPIO pin for the green LED
#define LED_CLEAR 26 // Define the GPIO pin for the red LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_CLEAR, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN); // Reading moisture value
  Serial.println(sensorValue); // Reporting level

  // Determining moisture level and light the appropriate LED
  if(sensorValue < 1500) { // Example threshold for "very wet" condition
    digitalWrite(LED_BLUE, HIGH); 
    digitalWrite(LED_CLEAR, LOW);
    sendCommand("LED=ON"); // Send command to server to indicate very wet condition
  } else if(sensorValue > 2000) { 
    digitalWrite(LED_BLUE, LOW); 
    digitalWrite(LED_CLEAR, HIGH);
    sendCommand("LED=OFF"); // Send command to server to indicate dry condition
  } else {
    // For moisture levels in between "very wet" and "dry", turn both LEDs off
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_CLEAR, LOW);
    // Optionally, send a different command or no command to the server
  }

  delay(1000);
}

void sendCommand(String command) {
  WiFiClient client;

  if (!client.connect(host, 80)) {
    Serial.println("Connection to host failed");
    return;
  }

  client.println("GET /" + command + " HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println();

  while(client.connected()) {
    if(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
}