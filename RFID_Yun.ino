  // communication
  #include <Wire.h>
  // access EEPROM to store data
  #include <EEPROM.h>
  // communication bridge for Yun
  #include <Process.h>
/*
 * @cmoz
 * Listing 5 RFID codes and varous responses
 * StrongLink SL018/SL030 RFID reader demo
 * marc@marcboon.com
 *
 *  Arduino to SL018/SL030 wiring:
 *  A3/TAG     1      5
 *  A4/SDA     2      3
 *  A5/SCL     3      4 
 *  5V         4      -
 *  GND        5      6
 *  3V3        -      1
 */
 
 
 // ++++++++++++++++++++++++++++++++++++++++ TO DO 
 // Send values over WiFi on the Yun to data.sparkfun.com
 // to connect and list information about when the tag is 
 // scanned etc.
 
 // ++++++++++++++++++++++++++++++++++++++++ TO DO 
 // Amend EEPROM - send to an SD card and not to EEPROM
 
  #define TAG A3 // A3
  
  byte data;
  
   int value = 0; 
   
   int LED1 = 15; //A6
   int LED2 = 14; //A7
   int LED3 = 13; //A8
   int LED4 = 12; //A9
   int LED5 = A2; //A10

   int LEDWhite = A1; // 20
   
   // The 5 cards that will be listed in this example 
            boolean tag1Card;
            boolean tag2Card;
            boolean tag3Card;
            boolean tag4Card;
            boolean tag5Card;
  
  //constants used to identify EEPROM addresses
  const int MY_BOOL1 = 0; 
  const int MY_BOOL2 = 1;
  const int MY_BOOL3 = 2;
  const int MY_BOOL4 = 3;
  const int MY_BOOL5 = 4;  
   
  String inputString = "";         // a string to hold incoming data
  boolean stringComplete = false;  // whether the string is complete
  
  String driverName;
  int rfidNumber;
  int truckID = 54837;
   // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  void setup()
  {
  Wire.begin();
  // Init serial port to host and I2C interface to SL018/SL030
  Serial.begin(9600);

  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); 
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LEDWhite, OUTPUT);
  
 // pinMode(TAG, INPUT);
 /*
  digitalWrite(LEDWhite, HIGH); 
  delay(250);  
    digitalWrite(LEDWhite, LOW); 
  delay(50); 
  digitalWrite(LEDWhite, HIGH); 
  delay(250);  
    digitalWrite(LEDWhite, LOW); 
  delay(50);
    digitalWrite(LEDWhite, HIGH); 
  delay(250); 
  tone(piezo,800,50);
  digitalWrite(vibe, HIGH);
  delay(50);
  digitalWrite(vibe, LOW);
  digitalWrite(LEDWhite, LOW);
  */
           
       // read the values written to EEPROM which is the last boolean
       // value from the scanned tags     
       
      int card1 = EEPROM.read(MY_BOOL1);
      int card2 = EEPROM.read(MY_BOOL2);
      int card3 = EEPROM.read(MY_BOOL3);
      int card4 = EEPROM.read(MY_BOOL4);
      int card5 = EEPROM.read(MY_BOOL5);
      
      if (card1 == 0) {
        tag1Card = false;
      } else if (card1 == 1){
        tag1Card = true;
        driverName = "Mia Wallace";
        rfidNumber = 7546735624;
      }
      if (card2 == 0) {
        tag2Card = false;
      } else if (card2 == 1) {
        tag2Card = true;
        driverName = "Winston Wolfe";
        rfidNumber = 7546737648;
      }
      if (card3 == 0) {
        tag3Card = false;
      } else if (card3 == 1) {
        tag3Card = true;
        driverName = "Jules Winnfield";
        rfidNumber = 2494735624;
      }
      if (card4 == 0) {
        tag4Card = false;
      } else if (card4 == 1) {
        tag4Card = true;
        driverName = "Vincent Vega";
        rfidNumber = 894735624;
      } 
      if (card5 == 0) {
        tag5Card = false;
      } else if (card5 == 1) {
        tag5Card = true;
        driverName = "Marsellus Wallace";
        rfidNumber = 4673566;
      }
  
  Bridge.begin();	// Initialize the Bridge, for communication with linux chip.                          
  Serial.println("set up ready");  
  setLEDsToLow();
              
  }

  // **********************************************************************************************************************************
  // END OF SET UP 
  // **********************************************************************************************************************************

  void loop()
  {
  
  // Wait for tag
  while(digitalRead(TAG));

  // Read tag ID
  readID();

  // Wait until tag is gone
  while(!digitalRead(TAG)); 
  
                  // what to do when ALL tags are scanned
     if (tag1Card == true && tag2Card == true && tag3Card == true && tag4Card == true && tag5Card == true) {
                  Serial.println("all tags scanned");
                  int pinArray[] = {A2, 11, 10, 9, A4, A5};
                  int count = 0;
                  int timer = 10;
                  int timer2 = 30;
                  int timer3 = 90;
                  
            for (int i=0; i<5; i++){
                  for (count=0;count<6;count++) {
                  digitalWrite(pinArray[count], HIGH);
                  delay(timer);
                  digitalWrite(pinArray[count + 1], HIGH);
                  delay(timer);
                  digitalWrite(pinArray[count], LOW);
                  delay(timer*2);
                  }
                 for (count=5;count>0;count--) {
                 digitalWrite(pinArray[count], HIGH);
                 delay(timer);
                 digitalWrite(pinArray[count - 1], HIGH);
                 delay(timer);
                 digitalWrite(pinArray[count], LOW);
                 delay(timer*2);
                 }
          }
          
           for (int i=0; i<3; i++){
                  for (count=0;count<6;count++) {
                  digitalWrite(pinArray[count], HIGH);
                  delay(timer2);
                  digitalWrite(pinArray[count + 1], HIGH);
                  delay(timer2);
                  digitalWrite(pinArray[count], LOW);
                  delay(timer2*2);
                  }
                 for (count=5;count>0;count--) {
                 digitalWrite(pinArray[count], HIGH);
                 delay(timer2);
                 digitalWrite(pinArray[count - 1], HIGH);
                 delay(timer2);
                 digitalWrite(pinArray[count], LOW);
                 delay(timer2*2);
                 }
          }
          
           for (int i=0; i<1; i++){
                  for (count=0;count<6;count++) {
                  digitalWrite(pinArray[count], HIGH);
                  delay(timer3);
                  digitalWrite(pinArray[count + 1], HIGH);
                  delay(timer3);
                  digitalWrite(pinArray[count], LOW);
                  delay(timer3*2);
                  }
                 for (count=5;count>0;count--) {
                 digitalWrite(pinArray[count], HIGH);
                 delay(timer3);
                 digitalWrite(pinArray[count - 1], HIGH);
                 delay(timer3);
                 digitalWrite(pinArray[count], LOW);
                 delay(timer3*2);
                 }
          }
          
          for (count=0;count<6;count++) {
                  digitalWrite(pinArray[count], HIGH);
                  delay(timer);
                  digitalWrite(pinArray[count + 1], HIGH);
                  delay(350);
                  }
                  
                  for (count=0;count<6;count++) {
                  digitalWrite(pinArray[count], LOW);
                  digitalWrite(pinArray[count + 1], LOW);
                  }
          
      }
    
    
   setLEDsToLow(); // checks the state of the tagCards 
   
   // send recent tag scans to data.sparkfun
   sendRFIDataToSparkfun(driverName, String(rfidNumber), String(truckID));
  }
    
  // ************************************************************************************
  // END OF VOID LOOP 
  // ************************************************************************************
    
    
  void sendRFIDataToSparkfun(String driverName, String rfidNumber, String truckID) {
  sendStringToSpakfun( "\"name\": \"" + driverName + "\", \"RFIDnumber\": \"" + rfidNumber + "\", \"truck\": \"" + truckID + "\"" );
}


void sendStringToSpakfun(String str) {
  String strToSend = "curl -m 5 -k -X POST http://data.sparkfun.com/input/0lzWz1nqKaIqbYxlXn7l -H 'Phant-Private-Key: D6n7nDkMYlFY1Exby4Mb' -d '{" + str + "}'";
  Process p;
  p.runShellCommand(strToSend);
  p.close();
}

/*
curl -X POST 'http://data.sparkfun.com/input/0lzWz1nqKaIqbYxlXn7l' \
  -H 'Phant-Private-Key: D6n7nDkMYlFY1Exby4Mb' \
  -d 'temp=91.4&humidity=86%25'
*/

  int readID()
  {
  // Serial.println("readID");
  // Send SELECT command
  Wire.beginTransmission(0x50);
  Wire.write(1);
  Wire.write(1);
  Wire.endTransmission();
  
  // ***+++++++++++++++++++++++++
  // Wait for response
  while(!digitalRead(TAG))
  {   
    // Allow some time to respond
    delay(5);
    //Serial.println("wait for response, !digitalRead(TAG)");
    // Anticipate maximum packet size
    Wire.requestFrom(0x50, 11); // 11
    if(Wire.available())
    {     
      // Get length of packet
      byte len = Wire.read();
      
      // Wait until whole packet is received
      while(Wire.available() < len)
      {
        // Quit if no response before tag left
        if(digitalRead(TAG)) return 0; 
        Serial.print(TAG);  
      }

      // Read command code, should be same as request (1)
      byte command = Wire.read();
      if(command != 1) return -1;

      // Read status
      byte status = Wire.read();
      switch(status)
      {
        case 0: // Succes, read ID and tag type
        {
          len -= 2;
          // Get tag ID
          while(--len)
          {
            byte data = Wire.read();
            if(data < 0x10) Serial.print(0);
            
            if (data == 0xA2 && 0x8E && 0x1F && 0x58) tag1Card ^= true;             
            if (data == 0x52 && 0x74 && 0x1E && 0x58) tag2Card ^= true;
            if (data == 0xEB && 0xE8 && 0xDF && 0x03) tag3Card ^= true;
            if (data == 0xD2 && 0xB6 && 0x1E && 0x58) tag4Card ^= true; 
            if (data == 0x2A && 0xFF && 0xD7 && 0x09) tag5Card ^= true;
            Serial.print(data, HEX);      // changed to println not print    
            //Serial.println();
            setLEDsToLow();
            
            }
            Serial.println();
            
  // beep when tag placed over area
  //tone(piezo,800,100); 
  digitalWrite(LEDWhite, HIGH);
  delay(100);
  //tone(piezo,1300,100);
  
  // vibe when tag there, for haptic feedback
  //digitalWrite(vibe, HIGH);
  //delay(200);
  //digitalWrite(vibe, LOW);
  digitalWrite(LEDWhite, LOW);
           
        }     
      return 1;

      case 0x0A: // Collision
        Serial.println("Collision detected");
        break;

      case 1: // No tag
        Serial.println("No tag found");
        break;

      default: // Unexpected
        Serial.println("Unexpected result");
      }
      return -1;
    }
  }
  // No tag found or no response
  return 0;
  }
    
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void setLEDsToLow(){ 

                if (tag1Card == true) {
                digitalWrite(LED1, LOW);  
                EEPROM.write(MY_BOOL1, 1);
                delay(10);   
                } else {
                  analogWrite(LED1, 40);
                  EEPROM.write(MY_BOOL1, 0);
                }
                                          
                if (tag2Card == true) {
                digitalWrite(LED2, LOW);
                EEPROM.write(MY_BOOL2, 1);   
                delay(10);               
                } else {
                  analogWrite(LED2, 30);
                  EEPROM.write(MY_BOOL2, 0);
                }
            
                if (tag3Card == true) {
                digitalWrite(LED3, LOW); 
                EEPROM.write(MY_BOOL3, 1); 
                delay(10);               
                } else {
                  analogWrite(LED3, 200);
                  EEPROM.write(MY_BOOL3, 0);
                }
        
                if (tag4Card == true) {
                digitalWrite(LED4, LOW); 
                EEPROM.write(MY_BOOL4, 1);
                delay(10);                
                } else {
                  analogWrite(LED4, 30);
                  EEPROM.write(MY_BOOL4, 0);
                }
            
                if (tag5Card == true) {
                digitalWrite(LED5, LOW);  
                EEPROM.write(MY_BOOL5, 1);
                delay(10);               
                } else {
                  digitalWrite(LED5, HIGH);
                  EEPROM.write(MY_BOOL5, 0);
                }
  
}
