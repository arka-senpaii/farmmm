# Smart Farm Monitoring and RC Car Control

This project integrates an ESP32 with sensors, a web server, and a mobile app to monitor environmental conditions and control an RC car wirelessly.

## Features

- **Real-time Sensor Monitoring:** Reads temperature, humidity, and soil moisture.
- **Web Server Dashboard:** Displays live data updates every 5 seconds.
- **RC Car Control:** Uses PWM signals from an FS-iA10B receiver to control movement.
- **WiFi Connectivity:** ESP32 connects to a WiFi network to serve data via a web interface.
- **Automated Data Logging:** Sensor values can be logged for future analysis.
- **Failsafe Mechanism:** Stops the RC car in case of lost signal or error.
- **Customizable Thresholds:** User-defined values for ideal temperature, humidity, and soil moisture.
- **Remote Monitoring:** Access sensor data from anywhere within the WiFi range.
- **Mobile App Integration:** A dedicated app allows users to monitor sensor data and control the RC car remotely.
- **Low Power Consumption:** Optimized for energy-efficient performance.

## Components Used

- **ESP32** - Microcontroller with WiFi capabilities.
- **DHT11 Sensor** - Measures temperature and humidity.
- **Soil Moisture Sensor** - Reads soil moisture levels.
- **FS-iA10B Receiver** - Used for RC car control.
- **L298N Motor Driver** - Controls the wheels of the RC car.
- **Relay Module (Optional)** - Can be used for automation like irrigation control.
- **Water Pump (Optional)** - To water plants when soil moisture is low.

## Pin Configuration

| Component               | Pin              |
| ----------------------- | ---------------- |
| DHT11 Sensor            | GPIO 4           |
| Soil Moisture Sensor    | GPIO 34 (Analog) |
| Throttle Input          | GPIO 33          |
| Steering Input          | GPIO 32          |
| Left Wheels Forward     | GPIO 13          |
| Right Wheels Backward   | GPIO 12          |
| Left Wheels Backward    | GPIO 14          |
| Right Wheels Forward    | GPIO 27          |
| Relay Module (Optional) | GPIO 26          |

## Setup Instructions

1. **Connect the Components** as per the pin configuration above.
2. **Upload the Code** to ESP32 using Arduino IDE.
3. **Update WiFi Credentials** in the `ssid` and `password` variables.
4. **Power the ESP32** and monitor the Serial output.
5. **Access the Web Server** using the ESP32's IP address displayed in the Serial Monitor.
6. **Test RC Car Movement** by controlling it with an FS-iA10B remote.
7. **Verify Sensor Readings** in the Serial Monitor, web interface, and mobile app.

## Code Overview

- **`setup()`**
  - Initializes sensors, pins, and WiFi.
  - Starts the web server.
- **`loop()`**
  - Reads sensor values and PWM inputs.
  - Controls the RC car based on PWM signals.
  - Updates the web page and mobile app with sensor data.
  - Activates relay module if necessary.

## Web Interface & Mobile App

- Displays:
  - Temperature (°C)
  - Humidity (%)
  - Soil Moisture (%)
- Refreshes every 5 seconds for real-time updates.
- Provides a simple and clean UI for ease of monitoring.
- The mobile app allows users to:
  - View live sensor data.
  - Set alerts for critical conditions.

## Future Improvements

- Add a water pump automation feature based on soil moisture level.
- Implement a mobile app interface for better control.
- Use an OLED display for local sensor data visualization.
- Implement MQTT for cloud-based remote monitoring.
- Add battery level monitoring for wireless operation.
- Integrate AI-based predictive analytics for smart farming suggestions.
- Improve motor control precision using PID algorithms.
- Adding a ML dataset with all different types of crops so that farmer. 

## License

This project is open-source and free to use under the MIT License.

