#include <SPI.h> 
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#define SS_PIN D2 // sda pin d2
#define RST_PIN D3 // reset pin d3
#define FIREBASE_HOST "HOST FIREBASE"
#define FIREBASE_AUTH "AUTH FIREBASE"
#define WIFI_SSID "NAMA_WIFI"
#define WIFI_PASSWORD "PASSWORD WIFI"
#define pinBuzz D4
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() 
{
  pinMode(pinBuzz, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();   
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() 
{
  int potMeasure = analogRead(A0);
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String idCard= "";
 
  for (int i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.println(mfrc522.uid.uidByte[i], HEX);
     idCard.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  idCard.toUpperCase();

  if(idCard == "809E831B")
  {
    if(potMeasure > 512)
    {
      Firebase.setString("nama", "Galih Wiyatno");
      Firebase.setInt("suhu", potMeasure);
      Firebase.setString("message", "Suhu kamu diatas 37 Derajat\nKamu tidak dapat masuk");
      Firebase.setString("absen", "Sakit");
      digitalWrite(pinBuzz, HIGH);
      delay(2000);
      digitalWrite(pinBuzz, LOW);
      // handle error
      if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());  
        return;
      }
    }
    else
    {
      Firebase.setString("nama", "Galih Wiyatno");
      Firebase.setFloat("suhu", potMeasure);
      Firebase.setString("message", "Suhu kamu Normal\nAbsen Berhasil");
      Firebase.setString("absen", "Hadir");
      digitalWrite(pinBuzz, HIGH);
      delay(100);
      digitalWrite(pinBuzz, LOW);
      // handle error
      if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());  
        return;
      }
    }
  }
  else if(idCard == "D1DF6826")
  {
    if(potMeasure > 512)
    {
      Firebase.setString("nama", "Ngarvan Dwi Bahtiar");
      Firebase.setInt("suhu", potMeasure);
      Firebase.setString("message", "Suhu kamu diatas 37 Derajat\nKamu tidak dapat masuk");
      Firebase.setString("absen", "Sakit");
      digitalWrite(pinBuzz, HIGH);
      delay(2000);
      digitalWrite(pinBuzz, LOW);
      // handle error
      if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());  
        return;
      }
    }
    else
    {
      Firebase.setString("nama", "Ngarvan Dwi Bahtiar");
      Firebase.setFloat("suhu", potMeasure);
      Firebase.setString("message", "Suhu kamu Normal\nAbsen Berhasil");
      Firebase.setString("absen", "Hadir");
      digitalWrite(pinBuzz, HIGH);
      delay(100);
      digitalWrite(pinBuzz, LOW);
      // handle error
      if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());  
        return;
      }
    }
  }
  delay(1000);
}
