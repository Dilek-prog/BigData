#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>  // Bibliothek für den IMU-Sensor

// BLE-Service für den IMU-Sensor (eigene UUID)
BLEService imuService("19B10000-E8F2-537E-4F6C-D104768A1214");

// BLE-Charakteristiken für Beschleunigung (X, Y, Z)
// Wir verwenden BLEStringCharacteristic, um die Float-Werte als Strings zu senden
BLEStringCharacteristic accXChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen
BLEStringCharacteristic accYChar("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen
BLEStringCharacteristic accZChar("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen

// BLE-Charakteristiken für Gyroskop (X, Y, Z)
BLEStringCharacteristic gyroXChar("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen
BLEStringCharacteristic gyroYChar("19B10005-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen
BLEStringCharacteristic gyroZChar("19B10006-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 10);  // max. 10 Zeichen

void setup() {
    Serial.begin(115200);  // Serielle Kommunikation starten (für Debugging)
    delay(500);  // Kurze Verzögerung, um sicherzustellen, dass alles hochfährt

    // BLE starten
    if (!BLE.begin()) {
        Serial.println("❌ BLE konnte nicht gestartet werden!");
        while (1);
    }

    // IMU-Sensor starten
    if (!IMU.begin()) {
        Serial.println("❌ IMU Sensor konnte nicht gestartet werden!");
        while (1);
    }

    // BLE-Gerätenamen setzen
    BLE.setLocalName("Nano33BLE_IMU");

    // Werbefunkmodus aktivieren
    BLE.setAdvertisedService(imuService);

    // Charakteristiken zum BLE-Service hinzufügen
    imuService.addCharacteristic(accXChar);
    imuService.addCharacteristic(accYChar);
    imuService.addCharacteristic(accZChar);
    imuService.addCharacteristic(gyroXChar);
    imuService.addCharacteristic(gyroYChar);
    imuService.addCharacteristic(gyroZChar);

    // Service zum BLE hinzufügen
    BLE.addService(imuService);

    // BLE-Werbung starten (damit das Gerät von anderen Geräten gefunden werden kann)
    BLE.advertise();

    Serial.println("✅ BLE IMU Sensor bereit...");
}

void loop() {
    // Werbe kontinuierlich in einer Schleife
    BLE.advertise();

    // Wenn ein zentrales Gerät verbunden ist, beginne mit der Datenübertragung
    BLEDevice central = BLE.central();

    if (central) {
        Serial.print("✅ Verbunden mit: ");
        Serial.println(central.address());

        // Solange der zentrale Client verbunden ist, bleibe in dieser Schleife
        while (central.connected()) {
            float accX, accY, accZ;
            float gyroX, gyroY, gyroZ;

            // Beschleunigungssensor auslesen und Werte senden
            if (IMU.accelerationAvailable()) {
                IMU.readAcceleration(accX, accY, accZ);
                
                // Konvertiere die Werte in Strings und sende sie an die entsprechenden Charakteristiken
                accXChar.writeValue(String(accX, 4));  // 4 Dezimalstellen
                accYChar.writeValue(String(accY, 4));
                accZChar.writeValue(String(accZ, 4));
            }

            // Gyroskop auslesen und Werte senden
            if (IMU.gyroscopeAvailable()) {
                IMU.readGyroscope(gyroX, gyroY, gyroZ);
                
                // Konvertiere die Werte in Strings und sende sie an die entsprechenden Charakteristiken
                gyroXChar.writeValue(String(gyroX, 4));  // 4 Dezimalstellen
                gyroYChar.writeValue(String(gyroY, 4));
                gyroZChar.writeValue(String(gyroZ, 4));
            }

            // Sensordatenrate begrenzen (100ms Delay)
            delay(100);
        }

        Serial.println("❌ Verbindung getrennt.");
    }
}
