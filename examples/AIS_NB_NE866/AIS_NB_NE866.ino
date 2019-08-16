#include "AIS_NB_NE866.h"
#include "ESPSoftwareSerial.h"

String serverIP = ""; // Your Server IP
String serverPort = ""; // Your Server Port
unsigned char sendMode = MODE_STRING_HEX; // Can be MODE_STRING or MODE_STRING_HEX
String payload = "HelloWorld";

ESPSoftwareSerial swSer;
AIS_NB_NE866 AISnb;

const long interval = 20000;  //millisecond

long msgID = 0;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  swSer.begin(9600, 15, 2, SWSERIAL_8N1, false, 95, 11);

  AISnb.debug = true;
  AISnb.send_mode = sendMode;

  AISnb.setupDevice(&swSer,serverPort,serverIP);

  AISnb.getDeviceIP();  
  pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
      AISnb.clearBuffer();
      
      msgID++;
      String data = "";
      if (sendMode == MODE_STRING) {
        data = payload+String(msgID);
      } else {
        data = AISnb.str2HexStr(payload+String(msgID));
      }
      UDPSend udp = AISnb.sendUDPmsg(data);
      previousMillis = currentMillis;
  }
  UDPReceive resp = AISnb.waitResponse();
}