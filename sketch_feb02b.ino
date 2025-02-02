#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Define pin connections (update these if you use different pins)
#define SS_PIN  D2    // Slave Select pin (SDA) on NodeMCU (GPIO4)
#define RST_PIN D1    // Reset pin on NodeMCU (GPIO5)

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial to be ready (for Leonardo/Micro)
  
  Serial.println("Initializing SPI RFID Reader...");

  // Initialize SPI bus
  SPI.begin();
  
  // Initialize the RFID module
  mfrc522.PCD_Init();
  Serial.println("RFID Reader Initialized.");
  Serial.println("Place an RFID tag near the reader.");
}

void loop() {
  // Look for new RFID cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID of the card in hexadecimal format
  Serial.print("RFID UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // Add a leading zero for bytes less than 0x10
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print(" 0");
    } else {
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Halt PICC (card) and stop encryption on PCD
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  // Add a small delay to avoid reading the same tag multiple times in rapid succession
  delay(500);
}
