#include <ArduinoBLE.h>

int emgPin = A0;     // EMG sensor input
int threshold = 500; // adjust this later

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("BLE failed");
    while (1);
  }

  Serial.println("Scanning...");
  BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found: ");
    Serial.println(peripheral.localName());

    BLE.stopScan();

    sendEMG(peripheral);

    BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
  }
}

void sendEMG(BLEDevice peripheral) {
  if (!peripheral.connect()) {
    Serial.println("Connect fail");
    return;
  }

  Serial.println("Connected");

  if (!peripheral.discoverAttributes()) {
    Serial.println("No attributes");
    peripheral.disconnect();
    return;
  }

  BLECharacteristic myChar = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");

  if (!myChar) {
    Serial.println("No characteristic");
    peripheral.disconnect();
    return;
  }

  while (peripheral.connected()) {

    int emgValue = analogRead(emgPin);
    Serial.println(emgValue); // see values in monitor

    // simple threshold check
    if (emgValue > threshold) {
      myChar.writeValue((byte)1);
      Serial.println("Send 1");
    } else {
      myChar.writeValue((byte)0);
      Serial.println("Send 0");
    }

    delay(100); // small delay to keep it stable
  }

  Serial.println("Disconnected");
}
