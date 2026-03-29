Receiver Code:

#include <ArduinoBLE.h>

// Set up a unique UUID for the Service and the Characteristic
// You can generate custom UUIDs online if you ever need new ones
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); 

// Create a Byte characteristic that the Central can read and write to
BLEByteCharacteristic ledCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the BLE hardware
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  // Set the name that will appear when scanning
  BLE.setLocalName("NanoLED");
  
  // Attach the service and characteristic
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(ledCharacteristic);
  BLE.addService(ledService);

  // Set the initial value of the characteristic to 0 (LED off)
  ledCharacteristic.writeValue(0);

  // Start broadcasting!
  BLE.advertise();
  Serial.println("Peripheral advertising. Waiting for connections...");
}

void loop() {
  // Check if a Central device has connected
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to Central MAC: ");
    Serial.println(central.address());

    // Keep running this while the boards are connected
    while (central.connected()) {
      
      // If the Central wrote a new value to our characteristic
      if (ledCharacteristic.written()) {
        
        // Read the value and update the LED
        if (ledCharacteristic.value()) {
          Serial.println("LED ON");
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          Serial.println("LED OFF");
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }

    // If the loop breaks, the Central disconnected
    Serial.print("Disconnected from Central MAC: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, LOW); // Turn off LED on disconnect
  }
}
