/*
1 Add your project libraries properly.
2 This example will give you how to send data of DHT11 sensor to server.
3 Before running this code, create your account on 000webhost and add the code for data handling on server side.
4 Add the URL properly 

Code By Pratik Bingewar.
*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Replace with your network credentials
const char* ssid     = "Username";
const char* password = "Password";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "URL";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");


    //those who have temp and humidity sensor in their code
    int val = DHT.read11(DHT11_PIN);
    String tempString = String(DHT.temperature);
    String humidityString = String(DHT.humidity);

    // Prepare your HTTP POST request data
    String httpRequestData = "&sensorTemperatureVal=" + tempString
                             + "&sensorHumidityVal=" + humidityString;

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 5 seconds
  delay(5000);
}
