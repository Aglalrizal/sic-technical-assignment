#include <WiFi.h>
#include <HTTPClient.h>

#define MQ2_PIN 36

float sensorValue, voltage;

const char *ssid = "Redmi Note 8";
const char *password = "12345670";

const char *serverName = "127.0.0.1:5000/sensor-data"; // ini pake ngrok

void setup()
{
    Serial.begin(115200);

    pinMode(MQ2_PIN, INPUT);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop()
{
    sensorValue = analogRead(MQ2_PIN);
    voltage = sensorValue * (3.3 / 4095.0);

    Serial.print("sensor value: ");
    Serial.print(sensorValue);
    Serial.print(" - voltage: ");
    Serial.println(voltage);

    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        http.begin(serverName);

        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String httpRequestData = "sensorValue=" + String(sensorValue) + "&voltage=" + String(voltage);

        int httpResponseCode = http.POST(httpRequestData);

        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }

    delay(5000);
}
