//Import the Bitvoice library. 

//import the Tx
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

//Initiate the Tx
RH_ASK driver;


// Store the data type retreived by getData()
int port = 7;
byte dataType = 4;
char t[3];
String incomingByte = "";

String show = " Type: \n 1 to stop \n 2 to Forward \n 3 to Turn Left \n 4 to Turn Right \n 5 to Reverse  \n 6 to Donuts  \n ";
int i = 1;
void setup() {
  Serial.begin(9600);
  driver.init();
}

void loop() {
  if(i==1){
    Serial.println("");
    Serial.println(show);
    i=0;
  }
  if (Serial.available() > 0) {
        incomingByte = Serial.readString(); // read the incoming byte:
        Serial.println();
        Serial.print(" I received: ");
        Serial.println(incomingByte);
        const char *command = incomingByte.c_str();
        driver.send((uint8_t *)command, strlen(command));
        driver.waitPacketSent();
        Serial.print(" transmitter sent command");
        Serial.println("");
        Serial.println("");
        i=1;
}
}

// this function runs every time serial data is available. 
// in the serial buffer after a loop.
void serialEvent()
{  
          const char *stopp = "000";
          driver.send((uint8_t *)stopp, strlen(stopp));
          driver.waitPacketSent();

          digitalWrite(6,HIGH);
   
          const char *forward = "001";
          driver.send((uint8_t *)forward, strlen(forward));
          driver.waitPacketSent();
          
          const char *turnleft = "010";
          driver.send((uint8_t *)turnleft, strlen(turnleft));
          driver.waitPacketSent();
          
 
         const char *turnright = "011";
          driver.send((uint8_t *)turnright, strlen(turnright));
          driver.waitPacketSent();

         const char *reverse = "100";
          driver.send((uint8_t *)reverse, strlen(reverse));
          driver.waitPacketSent();
          
     
         const char *donuts = "101";
          driver.send((uint8_t *)donuts, strlen(donuts));
          driver.waitPacketSent();
          
         const char *test = "111";
          driver.send((uint8_t *)test, strlen(test));
          driver.waitPacketSent();
               
    
}
