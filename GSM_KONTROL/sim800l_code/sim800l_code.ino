#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);  

//-------------------------------------------------------------------------------------------------
void setup() {
  pinMode(8, OUTPUT);  
  Serial.begin(9600);  
  mySerial.begin(9600);  
  
  Serial.println("Sistem baslatiliyor...");
  delay(5000);  

  // GSM modülüne başlangıç AT komutları gönder
  mySerial.println("AT+CSQ");  
  delay(1000);

  mySerial.println("AT+CMGF=1");  
  delay(500);
  mySerial.println("AT+CNMI=2,2,0,0,0");  
  delay(1000);

  Serial.println("Mesaj almaya hazir.");
}

//------------------------------------------------------------------------------------------------ 
void loop() {
  if (mySerial.available()) {
    String sms = "";
    while (mySerial.available()) {
      sms += (char)mySerial.read();  
    }

    // SMS mesajını yazdır
    Serial.println(sms);

    // SMS mesajını kontrol et ve uygun komutu al
    if (sms.indexOf("AC") >= 0) {  // "ac" komutunu kontrol et
      digitalWrite(8, HIGH); 
      Serial.println("--ON--.");
  delay(1000);
    }
    else if (sms.indexOf("KAPA") >= 0) {  // "kapa" komutunu kontrol et
     digitalWrite(8, LOW); 
      Serial.println("--OFF--.");
      delay(1000);
    }
    delay(500);  
  }
}
