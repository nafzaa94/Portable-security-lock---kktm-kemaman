#include <SPI.h>
#include <MFRC522.h>
constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
int unlockdoor1 = 6;
int unlockdoor2 = 7;
char data;

int ledred = 4;
int ledgreen = 5;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(unlockdoor1, OUTPUT);
  pinMode(unlockdoor2, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);

  digitalWrite(ledred, HIGH);
  digitalWrite(ledgreen, LOW);
}

void loop() {

  if(mySerial.available()>0) 
   {     
      data = mySerial.read();
      switch(data)
      {
        case 'a': 
        digitalWrite(unlockdoor1, HIGH);
        data = "z";
        break;
        
        case 'b': 
        digitalWrite(unlockdoor1, LOW);
        data = "z";
        break;

        case 'c': 
        digitalWrite(unlockdoor2, HIGH);
        data = "z";
        break;
        
        case 'd': 
        digitalWrite(unlockdoor2, LOW);
        data = "z";
        break;
      }
      Serial.println(data);
   }

  unlockdoor();

  if (tag == ""){
    digitalWrite(unlockdoor1, HIGH);
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, HIGH);
    delay(5000);
    digitalWrite(unlockdoor1, LOW);
    digitalWrite(ledred, HIGH);
    digitalWrite(ledgreen, LOW);
    }

  else if (tag == ""){
    digitalWrite(unlockdoor2, HIGH);
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, HIGH);
    delay(5000);
    digitalWrite(unlockdoor2, LOW);
    digitalWrite(ledred, HIGH);
    digitalWrite(ledgreen, LOW);
    }

   
}

void unlockdoor(){
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
    if (rfid.PICC_ReadCardSerial()) {
      for (byte i = 0; i < 4; i++) {
        tag += rfid.uid.uidByte[i];
      }
      Serial.println(tag);
    }
  }
