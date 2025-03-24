#include <Arduino.h>
#include <ArduinoBLE.h>
#include <TrickTrack-HTW-BigDataAnalytics_inferencing.h> // Edge Impulse Modell
#include <Arduino_LSM9DS1.h> // IMU-Bibliothek für Nano 33 BLE Sense

// BLE Setup
BLEService aiService("180C");  
BLECharacteristic resultCharacteristic("2A56", BLERead | BLENotify, 32);  

void setup() {
    Serial.begin(115200);
    delay(100); // Kurze Wartezeit für Initialisierung
    bool serialActive = Serial; // Prüft, ob Serial aktiv ist

    if (serialActive) Serial.println("🔄 Starte...");

    // 🔹 IMU starten
    if (!IMU.begin()) {
        if (serialActive) Serial.println("❌ IMU konnte nicht gestartet werden!");
        while (1);
    }

    // 🔹 Modell initialisieren
    run_classifier_init();

    // 🔹 BLE starten
    if (!BLE.begin()) {
        if (serialActive) Serial.println("❌ BLE konnte nicht gestartet werden!");
        while (1);
    }

    BLE.setLocalName("Nano33BLE_AI");
    BLE.setAdvertisedService(aiService);
    aiService.addCharacteristic(resultCharacteristic);
    BLE.addService(aiService);
    resultCharacteristic.writeValue("Bereit...");
    BLE.advertise();

    if (serialActive) Serial.println("✅ BLE bereit, warte auf Verbindung...");
}

void loop() {
    ei_impulse_result_t result = { 0 };
    signal_t signal;
    float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

    // Prüfen, ob Serial verbunden ist (für Debugging)
    bool serialActive = Serial;

    // 🔹 IMU-Daten erfassen & in Buffer speichern
    for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE / 6; i++) {
        while (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable());

        float ax, ay, az, gx, gy, gz;
        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);

        features[i * 6] = ax;
        features[i * 6 + 1] = ay;
        features[i * 6 + 2] = az;
        features[i * 6 + 3] = gx;
        features[i * 6 + 4] = gy;
        features[i * 6 + 5] = gz;
    }

    // 🔹 Signal für Edge Impulse vorbereiten
    numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);

    // 🔹 Modell ausführen
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
    if (res != EI_IMPULSE_OK) {
        if (serialActive) Serial.println("❌ Fehler beim Klassifizieren!");
        return;
    }

    // 🔹 Beste Klasse ermitteln
    String bestLabel = "";
    float bestValue = 0.0;
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > bestValue) {
            bestValue = result.classification[ix].value;
            bestLabel = result.classification[ix].label;
        }
    }

    // 🔹 Ergebnis auf Serial Monitor ausgeben (falls aktiv)
    if (serialActive) {
        Serial.print("🏷️  Trick erkannt: ");
        Serial.print(bestLabel);
        Serial.print(" (");
        Serial.print(bestValue * 100, 2);
        Serial.println("%)");
    }

    // 🔹 BLE übertragen
    if (BLE.connected()) {
        resultCharacteristic.writeValue(bestLabel.c_str());
    }

    delay(1000); // 1 Inferenz pro Sekunde
}