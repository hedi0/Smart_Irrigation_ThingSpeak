# 💧 Smart Irrigation with ThingSpeak: Simple Intelligent IoT Irrigation System

An intelligent irrigation system leveraging IoT and ThingSpeak for remote monitoring, data visualization, and automated control of plant watering based on environmental conditions.

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license/Smart_Irrigation_ThingSpeak-green)
![Stars](https://img.shields.io/github/stars/hedi0/Smart_Irrigation_ThingSpeak?style=social)
![Forks](https://img.shields.io/github/forks/hedi0/Smart_Irrigation_ThingSpeak?style=social)
[![ESP8266](https://img.shields.io/badge/MCU-ESP8266-orange.svg)](https://www.espressif.com/)
[![ThingSpeak](https://img.shields.io/badge/Cloud-ThingSpeak-blue.svg)](https://thingspeak.com/)

![example-preview-image](/images/Smart_Irrigation_Preview_Image.pn)

## 📋 Table of Contents
- [Overview](#-overview)
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Circuit Wiring](#-circuit-wiring)
- [Software Setup](#-software-setup)
- [ThingSpeak Configuration](#-thingspeak-configuration)
- [Code Explanation](#-code-explanation)
- [Installation Guide](#-installation-guide)
- [Operation & Calibration](#-operation--calibration)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)

## 🌟 Overview

This **Smart Irrigation System** is an IoT-based solution that automates plant watering based on real-time soil moisture readings. It monitors environmental conditions and uploads data to ThingSpeak cloud for remote monitoring and analytics.

### How It Works
1. **Soil Moisture Sensor** continuously measures ground humidity
2. **DHT22 Sensor** tracks ambient temperature and humidity  
3. **ESP8266** processes sensor data and controls the pump
4. **ThingSpeak Cloud** stores and visualizes all data
5. **Automatic Watering** activates when soil becomes too dry

## ✨ Features

| Feature | Description |
|---------|-------------|
| **🌊 Real-time Monitoring** | Continuous soil moisture, temperature & humidity tracking |
| **⚡ Automatic Pump Control** | Smart watering based on soil moisture thresholds |
| **☁️ Cloud Integration** | Data logging and visualization on ThingSpeak |
| **📱 Remote Access** | Monitor system from anywhere via web dashboard |
| **📊 Data Analytics** | Historical trends and watering patterns |
| **🔧 Customizable** | Easy threshold adjustment and sensor calibration |
| **🔄 Low Power** | Efficient code with optimal reading intervals |

## 🔧 Hardware Requirements

### Essential Components
| Component | Quantity | Specification | Estimated Cost |
|-----------|:--------:|---------------|:--------------:|
| **NodeMCU ESP8266** | 1 | CP2102 version recommended | $5-8 |
| **Soil Moisture Sensor** | 1 | Capacitive (preferred) or Resistive | $3-6 |
| **DHT22 Sensor** | 1 | Temperature & Humidity | $4-7 |
| **5V Relay Module** | 1 | 1-channel, opto-isolated | $2-4 |
| **Mini Water Pump** | 1 | 3-6V DC, 120L/H | $4-8 |
| **Power Supply** | 1 | 5V 2A DC adapter | $5-8 |
| **Jumper Wires** | 20+ | Female-Female, Male-Female | $3-5 |
| **Breadboard** | 1 | 400 points | $2-4 |
| **PVC Tubing** | 1m | 4mm inner diameter | $1-2 |

**Total Estimated Cost: $29-52**

## 🔌 Circuit Wiring

### Pin Configuration Table
| NodeMCU Pin | Connected To | Wire Color | Notes |
|:------------|:-------------|:-----------|:------|
| **A0** | Soil Moisture Sensor (AO) | Orange | Analog input |
| **D1** | Relay Module (IN) | Yellow | Digital control |
| **D4** | DHT22 (DATA) | Green | Digital with pull-up |
| **3.3V** | DHT22 (VCC) | Red | Power for DHT22 |
| **GND** | Common Ground | Black | All components |
| **VIN** | 5V Power Supply (+) | Red | External power |
| **5V** | Relay Module (VCC) | Red | Relay power |
| **GND** | Relay Module (GND) | Black | Relay ground |

### Wiring Diagram
```
                External 5V Supply
                ┌──────┴────────┐
                │       +       │
                │       -       │
                └────────┬──────┘
                         │
    NodeMCU ESP8266      │
┌───────────────────┐    │
│ VIN ──────────────┼────┘
│ GND ──────┐       │
│ 3.3V ─────┼─┐     │
│ D4 ───────┼─┼───┐ │   
│ D1 ─────┐ │ │   │ │
│ A0 ───┐ │ │ │   │ │
└───────┼─┼─┼─┼───┼─┘
        │ │ │ │   │
        │ │ │ │   │    DHT22
        │ │ │ │   │    ┌────────┐
        │ │ │ └───┼────┤ VCC    │
        │ │ │     └────┤ DATA   │
        │ │ └──────────┤ GND    │
        │ │            └────────┘
        │ │    Relay Module
        │ │    ┌────────────┐
        │ └────┤ IN         │
        │      │ VCC ───────┼────┐
        │      │ GND ───────┼──┐ │
        │      │ COM ───────┼─┐│ │
        │      │ NO  ───────┼─┼┼─┼────┐
        │      │ NC         │ ││ │    │
        │      └────────────┘ ││ │    │
        │                   ││ │    │
        │ Soil Moisture     ││ │    │
        │ ┌───────────┐     ││ │    │
        └─┤ AO        │     ││ │    │
          │ GND ──────┼─────┼┼─┘    │
          │ VCC ──────┼─────┼┘      │
          └───────────┘     │       │
                          ┌─▼─┐   ┌─▼─┐
                          │Pump│   │5V │
                          │(+)│   │(-)│
                          └─┬─┘   └─┬─┘
                            └───────┘
```

### ⚠️ IMPORTANT SAFETY NOTES
- **External Power Required**: Pump draws 200-500mA, don't power through NodeMCU
- **Common Ground**: Connect all GND pins together
- **Relay Configuration**: Most modules are active-LOW (LOW = pump ON)
- **Flyback Diode**: Add 1N4007 diode across pump terminals to protect circuit

## 💻 Software Setup

### Required Software
1. **Arduino IDE** [Download](https://www.arduino.cc/en/software)
2. **CP2102 USB Driver** [Download](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### Arduino IDE Configuration

#### Step 1: Add ESP8266 Board
1. Open Arduino IDE
2. Go to **File** → **Preferences**
3. In "Additional Boards Manager URLs", add:
```
    http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
4. Click **OK**

#### Step 2: Install ESP8266 Board Package
1. Go to **Tools** → **Board** → **Boards Manager**
2. Search for "**esp8266**"
3. Install **"esp8266 by ESP8266 Community"**

#### Step 3: Install Required Libraries
Open **Library Manager** (Sketch → Include Library → Manage Libraries) and install:

| Library | Search Query |
|---------|--------------|
| **ThingSpeak** | "ThingSpeak by MathWorks" |
| **DHT sensor library** | "DHT sensor library by Adafruit" |
| **Adafruit Unified Sensor** | "Adafruit Unified Sensor" |


<!--
## ✨ Features

*   **📊 Real-time Data Monitoring:** Continuously collects and transmits sensor data (e.g., soil moisture, temperature) to ThingSpeak for live visualization.
*   **⚙️ Automated Watering Control:** Intelligently activates irrigation based on predefined soil moisture thresholds, ensuring optimal plant hydration.
*   **☁️ Cloud-Based Analytics:** Utilizes ThingSpeak's powerful analytics to track environmental trends and optimize watering schedules over time.
*   **📱 Remote Accessibility:** Monitor and potentially control your irrigation system from anywhere with an internet connection via the ThingSpeak platform.
*   **🔌 Modular Sensor Integration:** Designed for easy integration with various sensors, allowing for customization and expansion of monitoring capabilities.

## 🛠️ Installation Guide

This project is primarily designed for embedded systems, likely using an ESP32 or ESP8266 microcontroller with the Arduino IDE.

### Prerequisites

*   Arduino IDE installed.
*   ESP32/ESP8266 board definitions installed in Arduino IDE.
*   Required libraries installed (see Step 3).
*   A ThingSpeak account with a new channel set up (note your Channel ID and Write API Key).
*   A WiFi network for the device to connect to.

### Step-by-step Installation

1.  **Clone the Repository:**
    Start by cloning the project repository to your local machine using Git:

    ```bash
    git clone https://github.com/hedi0/Smart_Irrigation_ThingSpeak.git
    cd Smart_Irrigation_ThingSpeak
    ```

2.  **Open in Arduino IDE:**
    Open the `Smart_Irrigation_ThingSpeak.ino` file (or the main project folder) in your Arduino IDE.

3.  **Install Libraries:**
    Ensure you have the necessary libraries installed. Go to `Sketch > Include Library > Manage Libraries...` and search for and install the following:

    *   `WiFiClient` (usually built-in for ESP boards)
    *   `ThingSpeak` by MathWorks
    *   `DHT sensor library` by Adafruit (if using DHT sensors)
    *   `Adafruit Unified Sensor` by Adafruit (dependency for DHT)
    *   `[Your Soil Moisture Sensor Library]` (if applicable, e.g., analogRead is often sufficient)

4.  **Configure Environment Variables:**
    Locate the `config.h` (or similar, e.g., directly in the .ino file) and update it with your specific network credentials and ThingSpeak API keys.

    ```cpp
    // config.h (example structure)
    #define SECRET_SSID "YourWiFiSSID"          // Your WiFi network SSID (name)
    #define SECRET_PASS "YourWiFiPassword"      // Your WiFi network password
    #define SECRET_CH_ID   0000000              // Your ThingSpeak channel ID
    #define SECRET_WRITE_APIKEY "YOUR_API_KEY"  // Your ThingSpeak Write API key
    ```
    Replace `YourWiFiSSID`, `YourWiFiPassword`, `0000000`, and `YOUR_API_KEY` with your actual values.

5.  **Select Board and Port:**
    In the Arduino IDE, go to `Tools > Board` and select your ESP32/ESP8266 board. Then, go to `Tools > Port` and select the serial port connected to your microcontroller.

6.  **Upload the Code:**
    Click the "Upload" button (right arrow icon) in the Arduino IDE to compile and upload the code to your device.

## Components Required

| Component | Quantity | Purpose |
|-----------|----------|---------|
| **NodeMCU ESP8266** | 1 | Main microcontroller with WiFi capability |
| Soil Moisture Sensor Module | 1 | Measures soil moisture percentage |
| Water Pump Module | 1 | Pumps water for irrigation |
| Relay Module | 1 | Controls pump operation safely |
| DHT22 Sensor | 1 | Measures temperature and humidity |
| Breadboard | 1 | For prototyping connections |
| Jumper Wires | Multiple | For circuit connections |
| Power Supply (5V) | 1 | Powers sensors and pump |

## Pin Configuration

```
NodeMCU ESP8266 Pin Connections:
├── A0  ← Soil Moisture Sensor (Analog Output)
├── D1  → Relay Module (Control Pin)
├── D4  ← DHT22 Sensor (Data Pin)
├── 3.3V → DHT22 VCC
├── GND → Common Ground
└── VIN → 5V Power Supply
```

## ThingSpeak Setup
```
1. Create a ThingSpeak account at [ThingSpeak](https://thingspeak.mathworks.com/)
2. Create a new channel with 3 fields:
   - Field 1: Soil Moisture (%)
   - Field 2: Temperature (°C)
   - Field 3: Humidity (%)
3. Get your 'ChannelID' and 'Write API Key' from the channel settings
```
## 🚀 Usage Examples

Once the code is uploaded and your Smart Irrigation system is powered on, it will automatically connect to your specified WiFi network and begin sending sensor data to your ThingSpeak channel.

### Monitoring Data on ThingSpeak

1.  **Access Your Channel:**
    Open your web browser and navigate to `https://thingspeak.com/channels/[YOUR_CHANNEL_ID]`. Log in to your ThingSpeak account if prompted.

2.  **View Live Feeds:**
    You will see real-time charts visualizing your sensor data (e.g., soil moisture, temperature, humidity) as it's updated.

    ![ThingSpeak Dashboard Placeholder](/images/Dashboard_thingspeak_smart_irrigaition.png)
    [placeholder for ThingSpeak dashboard screenshot]

### Adjusting Thresholds (Firmware Update)

To change the automated watering thresholds (e.g., the minimum soil moisture level before irrigation starts), you will need to modify the `Smart_Irrigation_ThingSpeak.ino` file and re-upload the code.

```cpp
// Example snippet from Smart_Irrigation_ThingSpeak.ino
const int MOISTURE_THRESHOLD = 500; // Adjust this value (0-1023 for analog sensors)
                                    // Lower value means drier soil, higher means wetter.

void loop() {
  // ... sensor reading logic ...

  if (soilMoistureValue < MOISTURE_THRESHOLD) {
    // Activate pum
  // ... ThingSpeak update logic ...
}
```
Adjust `MOISTURE_THRESHOLD` to your desired level, then compile and upload the updated code.

## 🗺️ Project Roadmap

Our vision for Smart_Irrigation_ThingSpeak includes continuous improvement and expansion of its capabilities:

*   **Version 1.1.0 (Planned):**
    *   **Remote Threshold Configuration:** Implement a way to remotely adjust watering thresholds via ThingSpeak (using ThingSpeak Write/Read API or MQTT) without re-flashing the device.
    *   **Multiple Sensor Support:** Enhance code to easily integrate and manage data from multiple soil moisture sensors across different plant zones.
    *   **Battery Level Monitoring:** Add functionality to monitor and report the device's battery level (for solar-powered or remote units).

*   **Future Enhancements:**
    *   **Weather API Integration:** Incorporate external weather data to predict rainfall and intelligently skip unnecessary watering cycles.
    *   **Machine Learning for Optimization:** Explore using historical data to predict optimal watering schedules, minimizing water waste.
    *   **Mobile App Integration:** Develop a simple mobile application for more user-friendly monitoring and control.
    *   **Fault Detection & Alerts:** Implement alerts for sensor failures, low water supply, or pump malfunctions.
-->
