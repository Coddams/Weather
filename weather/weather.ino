// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <ArduinoJson.h>

// const char *ssid = "PC";
// const char *password = "myDevice";
// const char *apiKey = "012a555aa4564a9891de49ec2efd9f91";

// void setup() {
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   Serial.println("Connected to WiFi");
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     // Your city and country code
//     String city = "abuja";
//     String country = "NG";

//     // Build the URL for the Weatherbit API
//     String url = "http://api.weatherbit.io/v2.0/current?key=" + String(apiKey) + "&city=" + String(city) + "&country=" + String(country);

//     // Make the HTTP request
//     HTTPClient http;
//     http.begin(url);

//     int httpResponseCode = http.GET();

//     if (httpResponseCode == HTTP_CODE_OK) {
//       // Parse JSON data
//       String payload = http.getString();
//       const size_t capacity = JSON_OBJECT_SIZE(3) + 150;
//       DynamicJsonDocument doc(capacity);

//       deserializeJson(doc, payload);

//       // Extract relevant information
//       const char* weatherDescription = doc["data"][0]["weather"]["description"];
//       float temperature = doc["data"][0]["temp"];
//       float windSpeed = doc["data"][0]["wind_spd"];
//       float windDirection = doc["data"][0]["wind_dir"];

//       // Print the extracted information
//       Serial.print("Weather Description: ");
//       Serial.println(weatherDescription);
//       Serial.print("Temperature: ");
//       Serial.println(temperature);
//       Serial.print("Wind Speed: ");
//       Serial.println(windSpeed);
//       Serial.print("Wind Direction: ");
//       Serial.println(payload);
//     } else {
//       Serial.print("Error in HTTP request. HTTP response code: ");
//       Serial.println(httpResponseCode);
//     }

//     http.end();
//   }

//   delay(60000); // Delay for 1 minute before making the next request
// }









// =====================================================================================================================================================================================


// #include <ArduinoJson.h>
// #include <HTTPClient.h>

// const char* apiKey = "82cce4c6e0083d3c6b425aef6fa4c735";

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   WiFi.begin("PC", "myDevice"); // Replace with your WiFi credentials
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     String city = "abuja";
//     String country = "NG";

//     String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&appid=" + apiKey;

//     HTTPClient http;
//     http.begin(url);
//     Serial.println(url);

//     int httpResponseCode = http.GET();

//     if (httpResponseCode == HTTP_CODE_OK) {
//       String payload = http.getString();
//       char jsonArray[payload.length() + 1];
//       payload.toCharArray(jsonArray, sizeof(jsonArray));
//       jsonArray[payload.length() + 1] = '\0';

//       StaticJsonDocument<1024> doc;
//       DeserializationError error = deserializeJson(doc, jsonArray);

//       if (error) {
//         Serial.print(F("deserializeJson() failed with code "));
//         Serial.println(error.c_str());
//         return;
//       }

//       const char* weatherDescription = doc["weather"][0]["description"];
//       float temperature = doc["main"]["temp"].as<float>();
//       float windSpeed = doc["wind"]["speed"].as<float>();
//       float windDirection = doc["wind"]["deg"].as<float>();

//       Serial.print("Weather Description: ");
//       Serial.println(weatherDescription);
//       Serial.print("Temperature: ");
//       Serial.println(temperature);
//       Serial.print("Wind Speed: ");
//       Serial.println(windSpeed);
//       Serial.print("Wind Direction: ");
//       Serial.println(windDirection);
//     } else {
//       Serial.print("Error in HTTP request. HTTP response code: ");
//       Serial.println(httpResponseCode);
//     }

//     http.end();
//   }

//   delay(60000); // Delay for 1 minute before making the next request
// }






// ==================================================================================================================

// #include <WiFi.h>
// #include <ArduinoJson.h>
// #include <ESP32Servo.h>

// const char* ssid     = "PC";                 // SSID of the local network
// const char* password = "myDevice";            // Password on the network
// String APIKEY = "82cce4c6e0083d3c6b425aef6fa4c735";
// String CityID = "2352778";                    // Your City ID
// WiFiClient client;
// char servername[] = "api.openweathermap.org"; // Remote server we will connect to
// String result;

// int servoPin = 4;  // Connect the servo signal wire to pin 4 on the Arduino
// Servo myServo;      // Create a servo object to control a servo motor

// void setup() {
//   Serial.begin(115200);
//   Serial.print("Connecting to ");
//   WiFi.mode(WIFI_STA);   // Create WiFi station
//   Serial.println(ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
//   myServo.attach(servoPin);  // Attach the servo to the specified pin
// }

// void loop() {
//   if (client.connect(servername, 80)) {
//     // Starts client connection, checks for connection
//     client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID=" + APIKEY);
//     client.println("Host: api.openweathermap.org");
//     client.println("User-Agent: ArduinoWiFi/1.1");
//     client.println("Connection: close");
//     client.println();
//   } else {
//     Serial.println("Connection failed"); // Error message if no client connection
//     Serial.println();
//   }

//   while (client.connected() && !client.available())
//     delay(1);  // Waits for data

//   while (client.connected() || client.available()) {
//     // Connected or data available
//     char c = client.read(); // Gets byte from the Ethernet buffer
//     result = result + c;
//   }

//   client.stop();             // Stop client
//   result.replace('[', ' ');
//   result.replace(']', ' ');
//   // Serial.println(result);
//   char jsonArray[result.length() + 1];
//   result.toCharArray(jsonArray, sizeof(jsonArray));
//   jsonArray[result.length() + 1] = '\0';
//   StaticJsonDocument<1024> doc;
//   DeserializationError error = deserializeJson(doc, jsonArray);

//   if (error) {
//     Serial.print(F("deserializeJson() failed with code "));
//     Serial.println(error.c_str());
//     return;
//   }

//   String location = doc["name"];
//   String country = doc["sys"]["country"];
//   int temperature = doc["main"]["temp"];
//   int humidity = doc["main"]["humidity"];
//   float pressure = doc["main"]["pressure"];
//   int cityId = doc["id"];
//   float windSpeed = doc["wind"]["speed"];
//   int windDegree = doc["wind"]["deg"];
//   float longitude = doc["coord"]["lon"];
//   float latitude = doc["coord"]["lat"];

//   Serial.println();
//   Serial.print("Country: ");
//   Serial.println(country);
//   Serial.print("Location: ");
//   Serial.println(location);
//   Serial.print("Location ID: ");
//   Serial.println(cityId);
//   Serial.printf("Temperature: %d°C\r\n", temperature);
//   Serial.printf("Humidity: %d %%\r\n", humidity);
//   Serial.printf("Pressure: %.2f hpa\r\n", pressure);
//   Serial.printf("Wind speed: %.1f m/s\r\n", windSpeed);
//   Serial.printf("Wind degree: %d°\r\n", windDegree);
//   Serial.printf("Longitude: %.2f\r\n", longitude);
//   Serial.printf("Latitude: %.2f\r\n", latitude);

//   myServo.write(windDegree); // Corrected servo control
//   delay(20000);               // Wait for 1 second
// }



// ===============================================================================================================================

#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid     = "PC";                 // SSID of the local network
const char* password = "myDevice";            // Password on the network
String APIKEY = "82cce4c6e0083d3c6b425aef6fa4c735";
String CityID = "2352778";                    // Your City ID
WiFiClient client;
char servername[] = "api.openweathermap.org"; // Remote server we will connect to
String result;

int servoPin = 4;  // Connect the servo signal wire to pin 4 on the Arduino
Servo myServo;      // Create a servo object to control a servo motor

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  WiFi.mode(WIFI_STA);   // Create WiFi station
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  myServo.attach(servoPin);  // Attach the servo to the specified pin
}

void loop() {
  if (client.connect(servername, 80)) {
    // Starts client connection, checks for connection
    client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed"); // Error message if no client connection
    Serial.println();
  }

  while (client.connected() && !client.available())
    delay(1);  // Waits for data

  while (client.connected() || client.available()) {
    // Connected or data available
    char c = client.read(); // Gets byte from the Ethernet buffer
    result = result + c;
  }

  client.stop();             // Stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  // Serial.println(result);
  char jsonArray[result.length() + 1];
  result.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, jsonArray);

  if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return;
  }

  int windDegree = doc["wind"]["deg"];  // Extract wind degree

  Serial.println();
  Serial.printf("Wind degree: %d°\r\n", windDegree);

  myServo.write(map(windDegree, 0, 360, 0, 180)); // Map wind degree to servo range
  delay(20000);               // Wait for 20 seconds
}

