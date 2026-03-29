Sender code:

#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  Serial.println("Central starting scan...");
  
  // Scan specifically for the Service UUID we defined in the Peripheral
  BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
}

void loop() {
  // Check if we found a peripheral matching our scan
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found Peripheral: ");
    Serial.println(peripheral.localName());

    // Stop scanning since we found what we were looking for
    BLE.stopScan();

    // Try to connect and control the LED
    controlLed(peripheral);

    // If we disconnect, start scanning again
    BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
  }
}

void controlLed(BLEDevice peripheral) {
  // Connect to the peripheral
  Serial.println("Connecting...");
  if (!peripheral.connect()) {
    Serial.println("Failed to connect!");
    return;
  }

  // Discover peripheral attributes (services and characteristics)
  Serial.println("Discovering attributes...");
  if (!peripheral.discoverAttributes()) {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // Retrieve the specific LED characteristic
  BLECharacteristic ledCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");

  if (!ledCharacteristic) {
    Serial.println("Peripheral does not have the LED characteristic!");
    peripheral.disconnect();
    return;
  }

  Serial.println("Connected and ready to control LED!");

  // Loop to toggle the LED while we remain connected
  while (peripheral.connected()) {
    // Send a '1' to turn the LED on
    ledCharacteristic.writeValue((byte)0x01);
    delay(1000);

    // Send a '0' to turn the LED off
    ledCharacteristic.writeValue((byte)0x00);
    delay(1000);
  }

  Serial.println("Peripheral disconnected.");
}
