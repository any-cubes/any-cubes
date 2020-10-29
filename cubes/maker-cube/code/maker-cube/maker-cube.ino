/*
 * Firmware for Any-Cubes Maker-Cube
 * ---------------------------------
 * The Maker-Cube is an output device from the Any-Cubes family.
 * Via its relays, it can be used to control up to four external (low-power) circuits
 * by switching the relays on or off individually.
 * It listens to control signals via MQTT from the Vision-Cube.
 * 
 * Author: The Any-Cubes authors
 * License: MIT
 * 
 * Hardware:
 * - NodeMCU V2:
 *     - We use a similar version to this one: https://joy-it.net/de/products/SBC-NodeMCU
 * - 4x Logic Level Converter:
 *     - We use a 4-channel I2C-safe Bi-directional Logic Level Converter - BSS138: https://www.adafruit.com/product/757
 * - 4x Relay
 *     - We use a Velleman VMA400: https://www.velleman.eu/products/view/?id=435558
 * - USB Powerbank:
 *     - Make sure it delivers enough Ampere
 *     - We use Ansmann USB Powerbank 5.4: 5V, 2.4 Ampera max: https://www.ansmann.de/consumer/powerbanks/powerbank-54
 * 
 * Libraries:
 * - PubSubClient (install via Arduino Library Manager)
 * - EspMQTTClient (install via Arduino Library Manager)
 * 
 * If you don’t find the specific version of the NodeMCU you are using in the Arduino menu,
 * try using NodeMCU 1.0 (works with the joy-it.net NodeMCU board).
 */

#include "EspMQTTClient.h"

/**
 * For the import below to work, duplicate the file "credentials_example.h",
 * rename it to "credentials.h" and specify your credentials.
 */
#include "credentials.h"

const int RELAY_PIN_1 = D0;
const int RELAY_PIN_2 = D1;
const int RELAY_PIN_3 = D2;
const int RELAY_PIN_4 = D3;

unsigned long PING_INTERVAL = 5000;

unsigned long lastPingMillis = 0;
int previousActiveRelay = 0;
int activeRelay = 0;

EspMQTTClient client(
  ssid,
  password,
  mqttServer,
  mqttUsername,
  mqttPassword,
  "maker-cube", // MQTT client name
  1883 // MQTT port
);

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);

  digitalWrite(RELAY_PIN_1, LOW); 
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  digitalWrite(RELAY_PIN_4, LOW);

  client.enableDebuggingMessages(); // Enable debug log via serial
  // Once the device is disconnected / loses power, send a "0" as
  // status to let other cubes know that it is offline.
  client.enableLastWillMessage("/any-cubes/maker-cube/status", "0");
}

// Called once Wifi and MQTT are connected
void onConnectionEstablished() {
  // Subscribe to class changes from the Vision-Cube
  client.subscribe("/any-cubes/visio-cube/active-class", [](const String & payload) {
    Serial.print("Vison-Cube: class changed: "); Serial.println(payload);
    // The payload is expected to be a number that represents the currently active class,
    // either 1, 2, 3 or 4.
    // This variable stands for one of the four relays and means that this relay will be closed,
    // while the other 3 relays will be open.
    activeRelay = payload.toInt();
  });
  // Send a message to let other Cubes know that this device is online
  client.publish("/any-cubes/maker-cube/status", "1");
}

void loop() {
  unsigned long curMillis = millis();
  client.loop();

  // Check if the activeRelay variable changed since last loop,
  // if it did, update the relays, so that only the one with the
  // active class is closed.
  if (activeRelay != previousActiveRelay) {
    digitalWrite(RELAY_PIN_1, activeRelay == 1 ? HIGH: LOW);
    digitalWrite(RELAY_PIN_2, activeRelay == 2 ? HIGH: LOW);
    digitalWrite(RELAY_PIN_3, activeRelay == 3 ? HIGH: LOW);
    digitalWrite(RELAY_PIN_4, activeRelay == 4 ? HIGH: LOW);
    previousActiveRelay = activeRelay;
  }

  // Every now and then send a message to the MQTT server to
  // let other cubes know this device is still working
  if (curMillis > lastPingMillis + PING_INTERVAL) {
    client.publish("/any-cubes/maker-cube/status/ping", "alive");
    lastPingMillis = curMillis;
  }
}
