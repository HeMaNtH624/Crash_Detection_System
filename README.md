# 🚗 Vehicle Crash Alert System

## 📌 Overview
The Vehicle Crash Alert System is an Arduino-based safety solution that detects sudden vehicle impacts using a 3-axis accelerometer and automatically sends an SMS alert with live GPS coordinates via a GSM module.

---

## 🎯 Features
- Real-time crash detection  
- GPS-based live location tracking  
- Automatic SMS alert system  
- Google Maps location link  
- Serial monitoring for debugging  

---

## 🛠️ Hardware Components
- Arduino Board  
- GSM Module (SIM800/SIM900)  
- GPS Module (NEO-6M)  
- 3-Axis Accelerometer  
- SIM Card (SMS enabled)  
- Power Supply  

---

## 🔌 Pin Configuration

| Component | Arduino Pin |
|-----------|------------|
| GSM TX    | 5 |
| GSM RX    | 7 |
| GPS TX    | 12 |
| GPS RX    | 11 |
| X-axis    | A0 |
| Y-axis    | A1 |
| Z-axis    | A2 |

---

## ⚙️ Working Principle
1. Accelerometer continuously monitors X, Y, Z values.  
2. If sudden deviation exceeds threshold → crash detected.  
3. GPS fetches current coordinates.  
4. GSM sends SMS with Google Maps link to emergency contact.  

---

## 📩 Sample SMS Alert
```
⚠️ Movement Detected!
Location: https://maps.google.com/?q=13.0827,80.2707
```

---

## 📚 Libraries Required
- SoftwareSerial  
- TinyGPS++  

Install TinyGPS++ from Arduino Library Manager before uploading the code.

---

## 🚀 Setup Instructions
1. Connect hardware as per pin configuration.  
2. Insert active SIM card into GSM module.  
3. Replace phone number inside the code:
```cpp
gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\"");
```
4. Upload the code.  
5. Open Serial Monitor at 9600 baud rate.  

---

## 🔮 Future Improvements
- IoT cloud monitoring  
- Emergency auto-call feature  
- Mobile app integration  
- Advanced crash detection algorithm  

---

## 📜 License
This project is open-source and available for educational and research purposes. Feel free to send pull request.
