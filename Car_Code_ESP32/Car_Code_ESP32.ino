#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4 // DHT11 Sensor Pin
#define DHTTYPE DHT11 // DHT Sensor Type
#define SOIL_PIN 34 // Soil Moisture Analog Pin

#define throttlePin 33 // FS-iA10B Channel 2 (Throttle)
#define steeringPin 32 // FS-iA10B Channel 1 (Steering)

#define leftFwd 13 // Grey - Left Wheels Forward (L298N IN1)
#define rightBwd 12 // Purple - Right Wheels Backward (L298N IN2)
#define leftBwd 14 // Blue - Left Wheels Backward (L298N IN3)
#define rightFwd 27 // White - Right Wheels Forward (L298N IN4)

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);
const char* ssid = "Your_SSID";
const char* password = "Your_Password"; //Removed due to senstive data

void setup() {
    Serial.begin(115200);
    dht.begin();
    pinMode(throttlePin, INPUT);
    pinMode(steeringPin, INPUT);
    pinMode(leftFwd, OUTPUT);
    pinMode(rightBwd, OUTPUT);
    pinMode(leftBwd, OUTPUT);
    pinMode(rightFwd, OUTPUT);
    pinMode(SOIL_PIN, INPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected!");
    Serial.print("ESP32 Web Server IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    int throttlePWM = pulseIn(throttlePin, HIGH);
    int steeringPWM = pulseIn(steeringPin, HIGH);
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soilMoisture = analogRead(SOIL_PIN);
    int soilMoisturePercentage = map(soilMoisture, 0, 4095, 0, 100);

    Serial.printf("Throttle: %d | Steering: %d | Temp: %.2f | Humidity: %.2f | Soil: %d\n", 
                  throttlePWM, steeringPWM, temperature, humidity, soilMoisturePercentage);

    digitalWrite(leftFwd, LOW);
    digitalWrite(rightBwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);

    if (throttlePWM > 1500) {
        digitalWrite(leftFwd, HIGH);
        digitalWrite(rightFwd, HIGH);
    } else if (throttlePWM < 1300) {
        digitalWrite(leftBwd, HIGH);
        digitalWrite(rightBwd, HIGH);
    }
    if (steeringPWM < 1300) {
        digitalWrite(leftBwd, HIGH);
        digitalWrite(rightFwd, HIGH);
    } else if (steeringPWM > 1500) {
        digitalWrite(leftFwd, HIGH);
        digitalWrite(rightBwd, HIGH);
    }

    server.handleClient();
    delay(100);
}

void handleRoot() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soilMoisture = analogRead(SOIL_PIN);
    int soilMoisturePercentage = map(soilMoisture, 0, 4095, 0, 100);

    String html = "<html>";
    html += "<head>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>Smart Farm Monitoring</title>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; background: #f1f8e9; padding: 20px; }";
    html += "h1 { color: #2e7d32; font-size: 36px; }";
    html += ".container { display: flex; flex-wrap: wrap; justify-content: center; gap: 20px; }";
    html += ".data-box { background: #ffffff; padding: 20px; width: 300px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); text-align: center; }";
    html += ".data-box p { font-size: 24px; font-weight: bold; margin: 10px 0; }";
    html += ".icon { font-size: 50px; }";
    html += ".temperature { color: #e53935; }";
    html += ".humidity { color: #1e88e5; }";
    html += ".soil-moisture { color: #8e24aa; }";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Smart Farm Monitoring</h1>";
    html += "<div class='container'>";
    html += "<div class='data-box temperature'><div class='icon'>&#x1F321;</div><p>Temperature: " + String(temperature) + " °C (Ideal: 20-30°C)</p></div>";
    html += "<div class='data-box humidity'><div class='icon'>&#x1F4A7;</div><p>Humidity: " + String(humidity) + " % (Ideal: 40-60%)</p></div>";
    html += "<div class='data-box soil-moisture'><div class='icon'>&#x1F33F;</div><p>Soil Moisture: " + String(soilMoisturePercentage) + " % (Ideal: 30-50%)</p></div>";
    html += "</div><div class='footer'><p>Data updates every 5 seconds.</p></div></body></html>";

    server.send(200, "text/html", html);
}