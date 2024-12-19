#include <WiFi.h>
#include <WiFiUdp.h>
#include <MFVFormat.h>

#include "Definition.h"
#include "Motor.h"

WiFiUDP udp;
char packet[255];

MFVFormat mfvf;
int values[2];

Motor motor(0, 0, 0, 0, 0);

void setup() {
  Serial.begin(115200);

  // Start Access Point
  WiFi.softAP(WIFI_NAME, PASSWORD);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  udp.begin(UDP_PORT);
  Serial.printf("UDP server started on port %d\n", UDP_PORT);
}

void loop() {
  // Check for incoming packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d\n", packetSize);
    Serial.printf("From %s, port %d\n", udp.remoteIP().toString().c_str(), udp.remotePort());

    // Read the packet
    int len = udp.read(packet, sizeof(packet) - 1);
    if (len > 0) {
      // Null-terminate the string
      packet[len] = '\0';

      if (packet[len] == '\0') {
        Serial.printf("Packet: %s\n", packet);
        mfvf.parse(packet);
        parsePacket();
      }
    }

    // Send a reply
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print("Message received!");
    udp.endPacket();
  }
}

void parsePacket() {
  if (mfvf.message.module == "motor") {
    if (mfvf.message.feature == "fw")       { mfvf.parseValueToInt(values); motor.forward(values[0], values[1]); }
    else if (mfvf.message.feature == "bw")  { mfvf.parseValueToInt(values); motor.backward(values[0], values[1]); }
    else if (mfvf.message.feature == "tlw") { mfvf.parseValueToInt(values); motor.turn_left_w(0); }
    else if (mfvf.message.feature == "trw") { mfvf.parseValueToInt(values); motor.turn_right_w(0); }
    else if (mfvf.message.feature == "tlb") { mfvf.parseValueToInt(values); motor.turn_left_b(0); }
    else if (mfvf.message.feature == "trb") { mfvf.parseValueToInt(values); motor.turn_right_b(0); }
    else if (mfvf.message.feature == "sl")  { mfvf.parseValueToInt(values); motor.spin_left(values[0], values[1]); }
    else if (mfvf.message.feature == "sr")  { mfvf.parseValueToInt(values); motor.spin_right(values[0], values[1]); }
    else if (mfvf.message.feature == "st")    motor.stop();
  }
}
