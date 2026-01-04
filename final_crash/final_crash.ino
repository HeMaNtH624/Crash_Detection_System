#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// ------------------ Pin Definitions ------------------
#define GSM_TX 5
#define GSM_RX 7
#define GPS_TX 12
#define GPS_RX 11

#define X_PIN A0
#define Y_PIN A1
#define Z_PIN A2

// ------------------ Objects ------------------
SoftwareSerial gsmSerial(GSM_TX, GSM_RX);
SoftwareSerial gpsSerial(GPS_TX, GPS_RX);
TinyGPSPlus gps;

// ------------------ Variables ------------------
int baselineX = 733;  // Change these based on your steady readings
int baselineY = 705;
int baselineZ = 704;
const int threshold = 30;

String latitude = "";
String longitude = "";

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  gpsSerial.begin(9600);
  
  delay(1000);
  Serial.println("System Booting...");
  
  sendSMS("System is ready.");
}

void loop() {
  readGPS();

  if (detectMovement()) {
    String msg = "⚠️ Movement Detected!\n";
    if (latitude != "" && longitude != "") {
      msg += "Location: https://maps.google.com/?q=" + latitude + "," + longitude;
    } else {
      msg += "GPS not available yet.";
    }
    sendSMS(msg);
    delay(10000);  // avoid spamming
  }

  delay(500);
}

// ------------------ Read Accelerometer ------------------
bool detectMovement() {
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  int z = analogRead(Z_PIN);

  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" Z: "); Serial.println(z);

  if (abs(x - baselineX) > threshold || abs(y - baselineY) > threshold || abs(z - baselineZ) > threshold) {
    Serial.println("⚠️ Movement Detected!");
    baselineX = x; baselineY = y; baselineZ = z;
    return true;
  }
  return false;
}

// ------------------ Read GPS ------------------
void readGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
    Serial.print("Latitude: "); Serial.println(latitude);
    Serial.print("Longitude: "); Serial.println(longitude);
  }
}

// ------------------ Send SMS ------------------
void sendSMS(String text) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS to text mode
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+919390306225\""); // <-- Replace with your phone number
  delay(1000);
  gsmSerial.print(text);
  delay(1000);
  gsmSerial.write(26); // Ctrl+Z to send
  delay(5000);
  Serial.println("SMS Sent!");
}
