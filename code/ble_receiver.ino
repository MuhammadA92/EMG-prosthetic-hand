#include <ArduinoBLE.h>
#include <Servo.h>

BLEService myService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEByteCharacteristic myChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

Servo myServo;

void setup() {
  Serial.begin(9600);
  
  myServo.attach(3); // servo connected to pin 3
  myServo.write(0);  // start open

  if (!BLE.begin()) {
    Serial.println("BLE failed");
    while (1);
  }

  BLE.setLocalName("NanoLED");
  BLE.setAdvertisedService(myService);

  myService.addCharacteristic(myChar);
  BLE.addService(myService);

  myChar.writeValue(0);

  BLE.advertise();
  Serial.println("Waiting...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Connected");

    while (central.connected()) {

      if (myChar.written()) {
        byte val = myChar.value();

        // 1 = close hand, 0 = open hand
        if (val == 1) {
          myServo.write(180);
          Serial.println("Close");
        } else {
          myServo.write(0);
          Serial.println("Open");
        }
      }
    }

    Serial.println("Disconnected");
    myServo.write(0); // open hand on disconnect
  }
}
