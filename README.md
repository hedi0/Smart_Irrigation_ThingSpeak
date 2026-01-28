# 💧 Smart Irrigation with ThingSpeak: Simple Intelligent IoT Irrigation System

An intelligent irrigation system leveraging IoT and ThingSpeak for remote monitoring, data visualization, and automated control of plant watering based on environmental conditions.

<!-- Badges Row -->
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license/Smart_Irrigation_ThingSpeak-green)
![Stars](https://img.shields.io/github/stars/hedi0/Smart_Irrigation_ThingSpeak?style=social)
![Forks](https://img.shields.io/github/forks/hedi0/Smart_Irrigation_ThingSpeak?style=social)

<!-- Project Preview Image -->
![example-preview-image](/preview_example.png)

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

    ![ThingSpeak Dashboard Placeholder](/thingspeak_dashboard_example.png)
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
    // Activate pump
    digitalWrite(PUMP_PIN, HIGH);
    delay(PUMP_ON_DURATION_MS);
    digitalWrite(PUMP_PIN, LOW);
  }

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

## 🤝 Contribution Guidelines

We welcome contributions to make Smart_Irrigation_ThingSpeak even better! Please follow these guidelines:

### Code Style
*   Follow standard C++ best practices.
*   Use clear, descriptive variable and function names.
*   Comment your code where necessary, especially for complex logic.
*   Maintain consistent indentation (2 spaces or 4 spaces, as per existing code).

### Branch Naming Conventions
*   `main`: The stable, production-ready branch.
*   `develop`: For ongoing development and integration of new features.
*   `feature/[feature-name]`: For new features (e.g., `feature/remote-thresholds`).
*   `bugfix/[issue-number]`: For bug fixes (e.g., `bugfix/123-wifi-disconnect`).

### Pull Request (PR) Process
1.  **Fork the repository** and clone it to your local machine.
2.  **Create a new branch** from `develop` for your feature or bug fix.
3.  **Make your changes**, ensuring they adhere to the code style.
4.  **Test your changes** thoroughly.
5.  **Commit your changes** with a clear, concise message.
6.  **Push your branch** to your forked repository.
7.  **Open a Pull Request** against the `develop` branch of the main repository.
8.  **Provide a clear description** of your changes in the PR, including any relevant issue numbers.

### Testing Requirements
*   All new features should include basic unit tests or demonstrate successful functionality through manual testing.
*   Bug fixes should include a test case that reproduces the bug and verifies the fix.
*   Ensure the system continues to connect to WiFi and send data to Thin
