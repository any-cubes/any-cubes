 /*
 * Firmware for Any-Cubes Light-Cube
 * ---------------------------------
 * The Light-Cube is an output device from the Any-Cubes family.
 * It lights up in one of three colors to visualise what the Vision-Cube (another
 * cube from the Any-Cubes family) sees.
 * It listens to control signals via MQTT from the Vision-Cube.
 * 
 * Author: The Any-Cubes team
 * 
 * Hardware:
 * - Arduino Nano 33 IoT
 * - Adafruit NeoPixel NeoMatrix 8x8 RGB LED Matrix
 * - SN74AHCT125N logic level converter
 * 
 * Libraries:
 * - WiFiNINA
 * - PubSubClient
 * - Adafruit NeoMatrix
 */ 

#include <Adafruit_NeoMatrix.h>
#include <WiFiNINA.h> 
#include <PubSubClient.h>

/**
 * For the import below to work, duplicate the file "credentials_example.h",
 * rename it to "credentials.h" and specify your credentials.
 */
#include "credentials.h"

#define LED_MATRIX_PIN 2

unsigned long PING_INTERVAL = 5000;

unsigned long lastPingMillis = 0;
int activeClass = 0;
int previousActiveClass = 0;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, LED_MATRIX_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 0),       // transparent (black)
  matrix.Color(0, 0, 255),     // blue
  matrix.Color(255, 114, 119), // pink
  matrix.Color(0, 255, 0)      // green
};

/*
 * Color - Vision-Cube active class mapping:
 * --------------------------------------------
 * Transparent:  0 (no class)
 * Blue:         class 1
 * Pink:         class 2
 * Green:        class 3
 */

char subTopic[] = "/any-cubes/visio-cube/active-class";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setupMatrix() {
  matrix.begin();
  matrix.setBrightness(100);
  matrix.fillScreen(colors[0]);
  matrix.show();  
}

void setupWifi()  {
  delay(10);

  Serial.println("");
  Serial.print("Trying to connect to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("Assigned IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT Message received [");
  Serial.print(topic);
  Serial.print("] ");
  String s = String((char*)payload);
  Serial.println(s);

  // We assume that the payload is a number (representing the class detected by the Vision-Cube)
  activeClass = s.toInt();
  Serial.print("Active class: "); Serial.println(activeClass);

  // If the active class is outside the expected range [0..3], we correct it:
  if (activeClass < 0) {
    activeClass = 0;
  }
  else if (activeClass > 3) {
    activeClass = 0;
  }
}

void reconnectMqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("light-cube", mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT server.");
      client.subscribe(subTopic);
    } else {
      Serial.print("MQTT connection failed! client state: ");
      Serial.print(client.state());
      Serial.println("See https://pubsubclient.knolleary.net/api#state for client state descriptions.");
      Serial.println("Will try again in 5 seconds ...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupMatrix();
  setupWifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMqtt();
  }
  client.loop();

  unsigned long curMillis = millis();

  if (previousActiveClass != activeClass) {
    matrix.fillScreen(colors[activeClass]);
    matrix.show();
    previousActiveClass = activeClass;
  }
  
  if (curMillis > lastPingMillis + PING_INTERVAL) {
    client.publish("/any-cubes/light-cube/status/ping", "alive");
    lastPingMillis = curMillis;
  }
}
