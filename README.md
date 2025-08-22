# Solari-Embedded 🌞

An intelligent solar panel monitoring and automatic cleaning system built for ESP32/ESP8266 microcontrollers. This project provides real-time monitoring of solar panel performance, environmental conditions, and automated cleaning capabilities with IoT connectivity.

## 🚀 Features

### Monitoring Capabilities
- **Current Sensing**: Real-time current measurement using ACS712 sensor (5A version)
- **Voltage Monitoring**: Dual voltage sensing with voltage dividers for comprehensive power analysis
- **Power Calculation**: Automatic power computation from current and voltage readings
- **Water Level Detection**: Ultrasonic sensor for monitoring cleaning water reservoir
- **Light Sensing**: 4-position LDR (Light Dependent Resistor) sensors for optimal solar tracking
- **Environmental Monitoring**: Comprehensive sensor data collection and analysis

### Control Systems
- **Servo Motor Control**: Horizontal and vertical servo motors for panel positioning and cleaning mechanism
- **Water Pump Management**: Automated pump control for cleaning operations
- **Remote Control**: MQTT-based remote command execution

### IoT Connectivity
- **WiFi Connection**: Seamless wireless connectivity
- **MQTT Communication**: Real-time data transmission using HiveMQ cloud broker
- **JSON Data Format**: Structured data transmission for easy integration
- **Remote Monitoring**: Access system status and data from anywhere

## 🛠️ Hardware Requirements

### Microcontroller
- ESP32 or ESP8266 development board

### Sensors
- **ACS712 Current Sensor** (5A version) - GPIO 13
- **Voltage Sensors** with voltage dividers:
  - Voltage Sensor 1: GPIO 14
  - Voltage Sensor 2: GPIO 27
- **HC-SR04 Ultrasonic Sensor**:
  - Trigger Pin: GPIO 5
  - Echo Pin: GPIO 18
- **LDR Sensors** (4 units):
  - Up Left: A0
  - Up Right: A2
  - Down Left: A1
  - Down Right: A3

### Actuators
- **Servo Motors**:
  - Horizontal Motor: GPIO 12
  - Vertical Motor 1: GPIO 13
  - Vertical Motor 2: GPIO 14
- **Water Pump**: GPIO 4

### Additional Components
- Voltage divider circuits (R1: 30kΩ, R2: 7.5kΩ)
- Power supply suitable for your ESP board
- Waterproof enclosure (recommended)

## 📚 Software Dependencies

### Arduino Libraries
```cpp
#include <ArduinoJson.h>        // JSON data handling
#include <PubSubClient.h>       // MQTT communication
#include <WiFiClientSecure.h>   // Secure WiFi client
#include <ESP32Servo.h>         // Servo motor control (ESP32)
```

### ESP8266 Specific
```cpp
#include <ESP8266WiFi.h>        // WiFi for ESP8266
```

### ESP32 Specific
```cpp
#include <WiFi.h>               // WiFi for ESP32
```

## ⚙️ Installation and Setup

### 1. Hardware Assembly
1. Connect all sensors and actuators according to the pin configuration above
2. Ensure proper power supply connections
3. Install the system on your solar panel setup

### 2. Software Configuration

#### WiFi Configuration
Update the WiFi credentials in `MQTT.h`:
```cpp
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"
```

#### MQTT Broker Configuration
The system is pre-configured for HiveMQ cloud broker. Update credentials in `MQTT.h` if needed:
```cpp
#define MQTT_SERVER "7ecb7163642946fe9098e05b57857ef6.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_USER "your_mqtt_username"
#define MQTT_PASSWORD "your_mqtt_password"
```

### 3. Upload Code
1. Open `Solari.ino` in Arduino IDE
2. Select your ESP32/ESP8266 board
3. Install required libraries
4. Upload the code to your microcontroller

## 🎯 Usage

### System Startup
1. Power on the system
2. Monitor serial output for connection status
3. System will automatically connect to WiFi and MQTT broker
4. Data transmission begins immediately

### Data Monitoring
The system publishes data to three main MQTT topics:

#### Sensor Readings Topic: `solari/readings`
```json
{
  "readings": [
    {
      "id": "Solari",
      "v1": 12.5,     // Voltage sensor 1 (V)
      "v2": 12.3,     // Voltage sensor 2 (V)  
      "i": 2.1,       // Current (A)
      "p": 26.25      // Power (W)
    }
    // ... 60 readings per transmission
  ]
}
```

#### Water Level Topic: `solari/water_level`
```json
{
  "percentage": 85,    // Water tank fill percentage
  "status": "good"     // "good" or "empty" (when ≤15%)
}
```

#### Faults Topic: `solari/faults`
System fault codes for maintenance alerts

#### Remote Control Topic: `solari/cleaning_time`
Subscribe to this topic to receive cleaning schedule commands

### Manual Control
Send commands via MQTT to control cleaning operations and system parameters.

## 📊 System Architecture

```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐
│   Solar Panel   │────│  Solari-Box  │────│  Cloud Service  │
│                 │    │              │    │                 │
│ ├─ Voltage      │    │ ├─ ESP32     │    │ ├─ HiveMQ       │
│ ├─ Current      │    │ ├─ Sensors   │    │ ├─ Data Logger  │
│ └─ Performance  │    │ └─ Actuators │    │ └─ Remote UI    │
└─────────────────┘    └──────────────┘    └─────────────────┘
```

## 🔧 Configuration Parameters

### Sensor Calibration
- **Current Sensor**: ACS712 5A version (185 mV/A sensitivity)
- **Voltage Reference**: 3.3V ADC reference
- **ADC Resolution**: 4096 steps (12-bit)

### MQTT Settings
- **QoS Level**: 0 (configurable)
- **Keep Alive**: 120 seconds
- **Retained Messages**: Configurable per topic
- **Max Packet Size**: 3072 bytes

### Timing Configuration
- **Reading Interval**: 60 readings per transmission (1 second apart)
- **Transmission Interval**: Configurable via delay
- **Connection Maintenance**: Continuous via MQTT loop

## 🐛 Troubleshooting

### Common Issues

#### WiFi Connection Problems
- Verify SSID and password in configuration
- Check WiFi signal strength
- Monitor serial output for connection status

#### MQTT Connection Issues
- Confirm broker credentials
- Check internet connectivity
- Verify firewall settings

#### Sensor Reading Errors
- Check wire connections
- Verify pin configurations
- Monitor serial output for sensor data

#### Power Issues
- Ensure adequate power supply
- Check voltage levels
- Verify ground connections

### Debug Mode
Enable detailed logging by monitoring the serial output at 115200 baud rate.

## 🚨 Safety Considerations

- Ensure proper electrical isolation when working with solar panels
- Use weatherproof enclosures for outdoor installations
- Implement proper grounding for all electrical connections
- Regular maintenance checks for water level and mechanical components

## 🤝 Contributing

We welcome contributions to improve the Solari-Embedded system!

### Development Guidelines
1. Follow existing code style and structure
2. Test all changes thoroughly
3. Update documentation for new features
4. Submit pull requests with clear descriptions

### Areas for Improvement
- Enhanced fault detection algorithms
- Additional sensor integrations
- Mobile app development
- Machine learning optimization
- Energy efficiency improvements

## 📝 License

This project is open source. Please check the repository for specific license information.

## 📞 Support

For technical support, feature requests, or bug reports, please open an issue in the GitHub repository.

---

**Made with ❤️ for sustainable energy monitoring**