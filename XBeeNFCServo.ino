
int led = 13;

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>
//#include <SoftwareSerial.h>

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

uint8_t wirereadstatus(void);

#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

int inByte; // Stores incoming command
int memoryByte=4;
int mem;

void setup()  {
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
   Serial.begin(19200);
   Serial.println( "Arduino started sending bytes via XBee" );
  
  // initialize the digital pin as an output.
pinMode(led, OUTPUT);
Serial3.begin(9600);
Serial3.println("Looking for PN532...");

 // set the data rate for the SoftwareSerial port
   Serial.begin( 19200 );
   
nfc.begin();

uint32_t versiondata = nfc.getFirmwareVersion();
if (! versiondata) 
{
	//Serial3.print("Didn't find PN53x board");
    while (1); // halt  
}

Serial3.print("Found chip PN5"); Serial3.println((versiondata>>24) & 0xFF, HEX);
Serial3.print("Firmware ver. "); Serial3.print((versiondata>>16) & 0xFF, DEC);
Serial3.print('.'); Serial3.println((versiondata>>8) & 0xFF, DEC);

nfc.setPassiveActivationRetries(2);
// configure board to read RFID tags
nfc.SAMConfig();

}

void loop()  {
  // send character via XBee to other XBee connected to Mac
  // via USB cable

  uint8_t success;                          // Flag to check if there was an error with the PN532
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool authenticated = false;               // Flag to indicate if the sector is authenticated
  uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  int counter=0;  
 //   inByte = Serial.read();
 //   memoryByte=Serial.read();
 //  if(memoryByte=='1' || memoryByte=='2')
 //  inByte = memoryByte;
    
while(Serial.available() == 0) {

  int count = 0;
  int flag = 2;
success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

if (counter==0)
{
  Serial.println(" "); 
  Serial.println("Please select a mode: "); 
  Serial.println("Mode 1: Lock Door ");
  Serial.println("Mode 2: Unlock Door ");
  inByte=Serial.read();
  mem=inByte;
  counter++;
} 

  // A byte is ready to receive
while ((success && count==0) || mem==49)
  {
      int i=0;
      mem=-1;
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      flag=0;
      Serial3.print("1   ");
      myservo.write(180);
      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
      if (inByte==50) {mem=50;}
  }
while (digitalRead(IRQ)==1 && flag==0)
  {   
    count=1;
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)             // wait for a second
    Serial3.print("2   ");
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {break;}
    inByte = Serial.read();
    if (inByte!=-1) {Serial.print(inByte);}
    if (inByte==50) {mem=50; break;}
  }
while ((success && count==1) || mem==50)
  {
      int j=0;
      mem=-1;
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      flag=1;
      myservo.write(0);
      Serial3.print(myservo.read());
      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
      if (inByte==49) {mem=49;}
  }

while (digitalRead(IRQ)==1 && flag==1)
  {   
    count=0;
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    Serial3.print("4   ");
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {break;}
    inByte = Serial.read();
    if (inByte!=-1) {Serial.print(inByte);}
    if (inByte==49) {mem=49; break;}
  }

}
}
uint8_t wirereadstatus(void) {
  uint8_t x = digitalRead(IRQ);
  
  if (x == 1)
    return PN532_I2C_BUSY;
  else
    return PN532_I2C_READY;
}
