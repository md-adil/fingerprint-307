#include <Arduino.h>
#include <SoftwareSerial.h>
#define FINGERPRINT_DEBUG



#include <Adafruit_Fingerprint.h>
#include "status.h"

SoftwareSerial * fserial = new SoftwareSerial(2, 3);

Adafruit_Fingerprint * fp = new Adafruit_Fingerprint(fserial);


uint8_t * downloadFingerprintTemplate(uint16_t id)
{
  Serial.println("------------------------------------");
  Serial.print("Attempting to load #"); Serial.println(id);
  uint8_t p = fp->loadModel(id);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return;
  }

  // OK success!

  Serial.print("Attempting to get #"); Serial.println(id);
  p = fp->getModel();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" transferring:");
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return;
  }
  
  // one data packet is 267 bytes. in one data packet, 11 bytes are 'usesless' :D
  uint8_t bytesReceived[534]; // 2 data packets
  memset(bytesReceived, 0xff, 534);

  uint32_t starttime = millis();
  int i = 0;
  while (i < 534 && (millis() - starttime) < 20000) {
      if (fserial->available()) {
          bytesReceived[i++] = fserial->read();
      }
  }
  Serial.print(i); Serial.println(" bytes read.");
  Serial.println("Decoding packet...");

  uint8_t fingerTemplate[512]; // the real template
  memset(fingerTemplate, 0xff, 512);

  // filtering only the data packets
  int uindx = 9, index = 0;
  while (index < 534) {
      while (index < uindx) ++index;
      uindx += 256;
      while (index < uindx) {
          fingerTemplate[index++] = bytesReceived[index];
      }
      uindx += 2;
      while (index < uindx) ++index;
      uindx = index + 9;
  }
    return fingerTemplate;
  Serial.println("\ndone.");
}


const char * sendInstruction() {
    byte data[] = { 0x1D };
    // Serial.println(sizeof(data));
    Adafruit_Fingerprint_Packet packet(FINGERPRINT_COMMANDPACKET, sizeof(data), data);
    fp->writeStructuredPacket(packet);
    byte p = fp->getStructuredPacket(&packet);

    uint16_t counts;
    if(p == FINGERPRINT_OK ) {
        counts = ( packet.data[1] << 8);
        counts |= packet.data[2];

        Serial.print("TEmplate count"); Serial.println(counts);
    }

    return parseStatus(p);


    if (packet.type != FINGERPRINT_ACKPACKET) return "FINGERPRINT_PACKETRECIEVEERR";
    return parseStatus(packet.data[0]);
}

const char * downImage() {
    byte data[] = { 0x09, 1 };
    // Serial.println(sizeof(data));
    Adafruit_Fingerprint_Packet packet(FINGERPRINT_COMMANDPACKET, sizeof(data), data);
    fp->writeStructuredPacket(packet);
    byte p = fp->getStructuredPacket(&packet);
    return parseStatus(p);
}

void doCopy() {

    const byte * data = downloadFingerprintTemplate(1);
    if(!data) {
        return;
    }
    


    Serial.println("Fingerprint downloaded");
    
    // return;
    const char * status = downImage();
    if(status != "FINGERPRINT_OK") {
        return;
    }

    Serial.println("Ready to be sent");
    return;

    for(int i = 0; i < 512; i++) {
        fserial->write(data[i]);
    }

    fp->storeModel(2);

    Serial.println(status);
}


void setup() {
    Serial.begin(9600);
    fp->begin(57600);
    if (fp->verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
    } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }

    if( FINGERPRINT_OK ==  fp->getTemplateCount() ) {
        Serial.printf("Template Count %d\n", fp->templateCount);
    }

    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}