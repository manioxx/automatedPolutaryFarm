#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace these with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Firebase project credentials
#define FIREBASE_HOST "poultry-76eb0-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret-or-auth-key"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // Initialize Serial1 for communication with Arduino (using GPIO16 and GPIO17)

  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Serial1.available()) {
    String sensorValue = Serial1.readStringUntil('\n'); // Read data from Arduino
    Serial.println("Received sensor data: " + sensorValue);

    // Split the sensorValue string into individual values
    int commaIndex1 = sensorValue.indexOf(',');
    int commaIndex2 = sensorValue.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = sensorValue.indexOf(',', commaIndex2 + 1);
    int commaIndex4 = sensorValue.indexOf(',', commaIndex3 + 1);
    int commaIndex5 = sensorValue.indexOf(',', commaIndex4 + 1);
    int commaIndex6 = sensorValue.indexOf(',', commaIndex5 + 1);
    int commaIndex7 = sensorValue.indexOf(',', commaIndex6 + 1);
    int commaIndex8 = sensorValue.indexOf(',', commaIndex7 + 1);

    String temperature = sensorValue.substring(0, commaIndex1);
    String humidity = sensorValue.substring(commaIndex1 + 1, commaIndex2);
    String flame = sensorValue.substring(commaIndex2 + 1, commaIndex3);
    String ir = sensorValue.substring(commaIndex3 + 1, commaIndex4);
    String egg = sensorValue.substring(commaIndex4 + 1, commaIndex5);
    String fan = sensorValue.substring(commaIndex5 + 1, commaIndex6);
    String food = sensorValue.substring(commaIndex6 + 1, commaIndex7);
    String heater = sensorValue.substring(commaIndex7 + 1, commaIndex8);
    String light = sensorValue.substring(commaIndex8 + 1);

    Serial.println("Parsed values:");
    Serial.println("Temperature: " + temperature);
    Serial.println("Humidity: " + humidity);
    Serial.println("Flame: " + flame);
    Serial.println("IR: " + ir);
    Serial.println("Egg: " + egg);
    Serial.println("Fan: " + fan);
    Serial.println("Food: " + food);
    Serial.println("Heater: " + heater);
    Serial.println("Light: " + light);

    // Upload each value to Firebase
    if (Firebase.setString(firebaseData, "/realtime/temp", temperature)) {
      Serial.println("Temperature sent to Firebase successfully");
    } else {
      Serial.println("Failed to send temperature to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/humidity", humidity)) {
      Serial.println("Humidity sent to Firebase successfully");
    } else {
      Serial.println("Failed to send humidity to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/flame", flame)) {
      Serial.println("Flame sent to Firebase successfully");
    } else {
      Serial.println("Failed to send flame to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/ir", ir)) {
      Serial.println("IR sent to Firebase successfully");
    } else {
      Serial.println("Failed to send IR to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/switches/eggs", egg)) {
      Serial.println("Egg sent to Firebase successfully");
    } else {
      Serial.println("Failed to send egg to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/switches/fan", fan)) {
      Serial.println("Fan sent to Firebase successfully");
    } else {
      Serial.println("Failed to send fan to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/switches/food", food)) {
      Serial.println("Food sent to Firebase successfully");
    } else {
      Serial.println("Failed to send food to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/switches/heater", heater)) {
      Serial.println("Heater sent to Firebase successfully");
    } else {
      Serial.println("Failed to send heater to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, "/realtime/switches/light", light)) {
      Serial.println("Light sent to Firebase successfully");
    } else {
      Serial.println("Failed to send light to Firebase");
      Serial.println(firebaseData.errorReason());
    }
  }
}
