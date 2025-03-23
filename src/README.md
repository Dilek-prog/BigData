# TrickTrack - Intelligente Skateboard Trick-Analyse 🛹

## Für Skateboarder, Profis, Coaches & Trainer

TrickTrack ist ein innovatives System zur Analyse und Verbesserung von Skateboard-Tricks. Mithilfe eines tragbaren Motion-Devices und intelligenter Sensordatenverarbeitung bietet es sofortiges Feedback und detaillierte Analysen.

## Agenda

1. Projektthema

2. Scope

3. Approach

4. Konzepte

## Projektthema: TrickTrack

- Intelligente Skateboard-Trick-Analyse mittels Sensortechnologie

- Automatische Erkennung und Verbesserung von Tricks

- Sofortige Benachrichtigung bei erfolgreicher oder fehlerhafter Ausführung

- Tragbares Motion-Device zur flexiblen Nutzung


**Vorteile:**

- Kein manuelles Starten der Analyse erforderlich

- System erkennt Tricks automatisch

- Hilft beim Erlernen und Perfektionieren von Tricks


## Scope: Projektscope

#### Muss-Have Features

- Erkennung von Skateboard-Tricks mit IMU-Sensoren (Beschleunigung & Gyroskop)

- Unterscheidung verschiedener Tricks (z. B. Ollie, Kickflip, Shove-it)

- Live-Datenanalyse & Speicherung zur späteren Auswertung

- Bluetooth-Übertragung der Daten an ein Smartphone oder PC


#### Nice to Have Features

- Echtzeit-Datenvisualisierung in einer App oder Web-Oberfläche

- Bewertung der Trick-Ausführung (z. B. Höhe, Drehgeschwindigkeit, Landung)

- Community-Feature: Teilen & Vergleichen von Tricks mit anderen Skatern


#### Won't Have Features

- Keine Videoanalyse oder Kamera-basierte Trick-Erkennung

- Kein vollständiges Coaching- oder Trainingssystem

- Keine Integration mit bestehenden Skate-Apps

- Keine 3D-Visualisierung des Skateboards (nur Sensordaten)

- Kein Echtzeit-Upload in eine Cloud-Datenbank (nur lokale Speicherung & Übertragung)

## Approach: Technischer Ansatz

#### Sensorbasierte Datenerfassung

- Nutzung des IMU-Sensors (Beschleunigung & Gyroskop) auf dem Arduino Nano 33 BLE Sense

- Live-Messung der Bewegung des Skateboards während eines Tricks

- Speicherung & Übertragung der Sensordaten via Bluetooth Low Energy (BLE) an ein Smartphone oder PC

#### Trick-Analyse & Erkennung

- Vergleich der Sensordaten mit bekannten Bewegungsmustern

- Unterscheidung zwischen normaler Fahrt, Sprünge & Drehungen

- Training eines Machine Learning Modells zur besseren Erkennung

#### Feedback & Benutzerinteraktion

- Anzeige des Tricks auf einer App oder einem Bildschirm

- Speicherung der Daten zur langfristigen Analyse

#### Validierung & Tests

- Tests mit verschiedenen Skatern und Tricks

- Verbesserung der Algorithmen durch kontinuierliches Lernen


## Konzepte: Hardware & Software

#### 1. Hardware-Komponenten

Unsere Lösung verwendet leicht zugängliche Hardware:

- Arduino Nano 33 BLE Sense als zentrale Verarbeitungseinheit

- IMU-Sensor zur Bewegungserkennung

- Klebeband zur flexiblen Befestigung am Skateboard

- Smartphone oder PC zur Datenauswertung

- Powerbank zur mobilen Stromversorgung

- USB-Kabel zur Verbindung und Datenübertragung

#### 2. Software & KI-Integration

- Wir setzen auf moderne Software-Tools:

- Arduino IDE zur Mikrocontroller-Programmierung

- GitHub & Git zur Versionskontrolle

- Edge Impulse zur KI-gestützten Datenauswertung


## Fazit & Nächste Schritte

- Verbesserung der Trick-Erkennung durch Machine Learning

- Entwicklung einer benutzerfreundlichen App

- Community-Features zur Vernetzung von Skatern

## Autoren

**Erstellt von: [Henrike Krista Pflüger: s0590917​, Dilek Ogur: s0578816, Susann Gesch: s0578525/ Gruppe 7]** 

