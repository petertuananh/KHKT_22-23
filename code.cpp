#include <Servo.h>
#include <Arduino.h>
#include <rdm6300.h>
#include <Adafruit_Fingerprint.h>
#define rfid 0
Rdm6300 rdm6300;
Servo myservo;
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
int tien = A0;
int the = A1;
int bt = A2;
int coi = 4;
int xl1=12;
int xl2=13;
int dc=6;
int a=0;
int b=0;
bool c=0;
bool k=0;
bool cc=0;
bool kk=0;
int d=0;
bool tuong=0;
int thai=0;
bool lananh=0;
const int ID1 = 5559260;
const int ID2 = 5559208;
int UID;
int tuongyeuhan=0;
bool tuananh=0;
void setup() {
Serial.begin(115200);
//rdm6300.begin(rfid);
myservo.attach(5);
pinMode(tien,INPUT);
pinMode(the,INPUT);
pinMode(bt,INPUT_PULLUP);
pinMode(coi,OUTPUT);
pinMode(xl1,OUTPUT);
pinMode(xl2,OUTPUT);
pinMode(dc,OUTPUT);
digitalWrite(xl1,1);
digitalWrite(xl2,1); 
//finger.begin(57600);
//  if (finger.verifyPassword()) {
//  } 
//    finger.getTemplateCount();
//}
}
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop() {
  tunghap:
  Serial.println(d);
cac();
if(d==0&&tuananh==0){
int x=digitalRead(tien);
int y=digitalRead(the);
  digitalWrite(coi,0);
if(x==0&&a==0&&c==0&&cc==0){
  a=1;
  c=1;
  cc=1;
  }
if(c==1){
  digitalWrite(dc,1);
  delay(2000);
  digitalWrite(dc,0);
  c=0;
  }
if(a==1){
  xl_mo();
  a=1;
  }
if(cc==1){
  myservo.write(0);
  delay(2000);
  myservo.write(90);
  delay(5000);
  cc=0;
  }

//if (b == 0){
//  UID=0;
//}
if(y==0&&a==1&&k==0&&kk==0&&b==0){
    UID=0;
    b=1;
    k=1;
    kk=1;
    }
if(k==1){
//  Serial.println(k);
    rdm6300.begin(rfid);
  myservo.write(180);
  delay(2000);
  myservo.write(90);
    }
if(b==1){
   if (rdm6300.get_new_tag_id()){
//    Serial.println("cc");
    UID = rdm6300.get_tag_id();
//    Serial.println(UID);
      if(UID == ID1 || UID == ID2){
//      Serial.println("THẺ ĐÚNG");
    xl_dong();
    a=0;
b=0;
c=0;
cc=0;
k=0;
kk=0;
rdm6300.end();
}else if (UID != ID1 && UID != ID2){
//    Serial.println("the sai");
    UID=0;
  myservo.write(0);
  delay(2000);
  myservo.write(90);
  delay(1000);
  digitalWrite(coi,0);
  delay(2000);
b=0;
k=0;
kk=0;
   }
  }
  }
}
  if(d==1&&a==0&&b==0){
    finger.begin(57600);
  if (finger.verifyPassword()) {
  }else{}
    finger.getTemplateCount();
  id = 1;
  if (id == 0) {
     return;
  }
  if (tuong == 0 && id == 1) {
     getFingerprintEnroll();
  }else if (tuong==1 && id==1){
    }
  if(thai==1&&tuong==1){
  getFingerprintIDez();
  delay(50);
    }
    }
    }



//////////////////////////////////////////////////////////////////////////////////////////////////////

void cac(){
    int lanh=digitalRead(bt);
    
if(lanh==0&&lananh==0){
  lananh=1;
  }
if(lanh==1&&lananh==1){
  d=d+1;
  lananh=0;
  tuongyeuhan = 0;
  }
if(d==2){
  d=0;
  tuongyeuhan = 2;
 Serial.println("cccccccccccccccc");
  }
  }
void xl_dong(){
  digitalWrite(xl1,1);
  digitalWrite(xl2,1);  
  }
void xl_mo(){
  digitalWrite(xl1,0);
  digitalWrite(xl2,0);  
  }
uint8_t getFingerprintEnroll() {

  int p = -1;
  
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK&&tuongyeuhan!=2) {
    
    cac();
    if(tuongyeuhan == 2){
      break;
      }
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error1");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
     
    }
  }

  // OK success!
cac();
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error2");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER&&tuongyeuhan!=2) {
    cac();
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK&&tuongyeuhan!=2) {
    cac();
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error3");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
      
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  cac();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error4");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
      
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error5");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    cac();
    tuong=1;
    thai=1;
    xl_mo();
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error6");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
    
  }   
}
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  cac();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error7");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  cac();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error8");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
      
  }
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error9");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  delay(1500);
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  xl_dong();
  tuong=0;
}
