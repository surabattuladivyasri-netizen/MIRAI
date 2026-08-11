#include <DFRobotDFPlayerMini.h>
#include <TinyGPS++.h>

// Serial1: DFPlayer | Serial2: GPS | Serial3: GSM
DFRobotDFPlayerMini dfPlayer;
TinyGPSPlus gps;

// -------- PINS --------
const int trigF = 2, echoF = 3;
const int trigL = 4, echoL = 5;
const int trigR = 6, echoR = 7;
const int waterPin = A0;
const int buzzer = A1;
const int sosButton = A2;

unsigned long lastVoice = 0;
const String PHONE_NUMBER = "+917013551883"; 

// --- SENSITIVITY CONTROL ---
const int SENSE_FRONT = 45; 
const int SENSE_SIDE  = 30; 
const int WATER_THRESHOLD = 600;

long lastDF = 400, lastDL = 400, lastDR = 400;

// -------- DISTANCE FUNCTION --------
long getDist(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 20000); 
  if (duration == 0) return 400; 
  return duration * 0.034 / 2;
}

// -------- UPDATED SMS FUNCTION --------
void sendEmergencySMS() {
  Serial.println(F("Sending SOS SMS..."));
  
  Serial3.println("AT+CMGF=1"); 
  delay(500);
  Serial3.print("AT+CMGS=\"");
  Serial3.print(PHONE_NUMBER);
  Serial3.println("\"");
  delay(500);
  
  Serial3.print("EMERGENCY! I need help.");
  
  // CHECK GPS STATUS
  if (gps.location.isValid()) {
    Serial3.print("\nLocation: https://www.google.com/maps?q=");
    Serial3.print(gps.location.lat(), 6);
    Serial3.print(",");
    Serial3.print(gps.location.lng(), 6);
  } else {
    // SEND PLACEHOLDER IF GPS NOT FOUND
    Serial3.print("\nGPS Searching... Last Known/Default: https://www.google.com/maps?q=0.000000,0.000000");
  }
  
  delay(100);
  Serial3.write(26); // Ctrl+Z
  delay(3000);
  Serial.println(F("SMS Sent."));
}

void setup() {
  Serial.begin(9600);   
  Serial1.begin(9600);  // Pins 18, 19
  Serial2.begin(9600);  // Pins 16, 17
  Serial3.begin(9600);  // Pins 14, 15
  
  pinMode(trigF, OUTPUT); pinMode(echoF, INPUT);
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sosButton, INPUT_PULLUP);

  delay(3000); 
  if (dfPlayer.begin(Serial1, true, false)) {
    dfPlayer.volume(30); 
    dfPlayer.playMp3Folder(6); 
  }
}

void loop() {
  // Constant GPS stream
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }

  long dF = getDist(trigF, echoF);
  long dL = getDist(trigL, echoL);
  long dR = getDist(trigR, echoR);
  int waterVal = analogRead(waterPin);

  bool frontTrigger = (dF < SENSE_FRONT && lastDF < SENSE_FRONT);
  bool leftTrigger  = (dL < SENSE_SIDE  && lastDL < SENSE_SIDE);
  bool rightTrigger = (dR < SENSE_SIDE  && lastDR < SENSE_SIDE);

  // SOS PRIORITY
  if (digitalRead(sosButton) == LOW) {
    digitalWrite(buzzer, HIGH);
    dfPlayer.playMp3Folder(5); 
    sendEmergencySMS();        
    digitalWrite(buzzer, LOW);
    lastVoice = millis();
  }

  // VOICE ALERTS
  else if (millis() - lastVoice > 4000) {
    if (waterVal > WATER_THRESHOLD) {
      dfPlayer.playMp3Folder(4);
      lastVoice = millis();
    } 
    else if (frontTrigger) {
      dfPlayer.playMp3Folder(1);
      lastVoice = millis();
    } 
    else if (leftTrigger) {
      dfPlayer.playMp3Folder(2);
      lastVoice = millis();
    } 
    else if (rightTrigger) {
      dfPlayer.playMp3Folder(3);
      lastVoice = millis();
    }
  }

  lastDF = dF; lastDL = dL; lastDR = dR;
  delay(100);
}