#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5     // Slave Select (SDA)
#define RST_PIN 22   // Reset Pin

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
    Serial.begin(115200);
    SPI.begin();        // Initialize SPI bus
    rfid.PCD_Init();    // Initialize RFID module
    Serial.println("Place your RFID card near the reader...");
}

void loop() {
    // Check if a new card is present
    if (!rfid.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if (!rfid.PICC_ReadCardSerial()) {
        return;
    }

    Serial.print("RFID UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    rfid.PICC_HaltA(); // Halt PICC
    rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}
