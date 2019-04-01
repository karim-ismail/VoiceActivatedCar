//Import the Bitvoice library. 
#include <BitVoicer11.h>

//import the Tx
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

//Initiate the Tx
RH_ASK driver;

//Initiate the BitVoicer Serial Class. 
BitVoicerSerial bvSerial = BitVoicerSerial();
byte dataType;

void setup() {
  // put your setup code here, to run once:
  // start serial communication at 9600kbs
    driver.init();
  Serial.begin(9600);
}

void loop() {
}

// this function runs every time serial data is available in the serial buffer after a loop.
void serialEvent()
{
    //Reads the serial bugger and stores the received data type. 
    dataType = bvSerial.getData();
    
    //check if the data type is the same as the one in coming from bitvoicer.
    if (dataType == BV_INT)
    {
//          digitalWrite(32,HIGH);
//          delay(50);  

      if(bvSerial.intData == 1){
        char *command1 = "1";
        driver.send((uint8_t *)command1, strlen(command1));
        driver.waitPacketSent();
        
      }else if(bvSerial.intData == 2){
        char *command2 = "2";
        driver.send((uint8_t *)command2, strlen(command2));
        driver.waitPacketSent();
        
          }else if(bvSerial.intData == 3){
        char *command3 = "3";
        driver.send((uint8_t *)command3, strlen(command3));
        driver.waitPacketSent();
        
          }else if(bvSerial.intData == 4){
        char *command4 = "4";
        driver.send((uint8_t *)command4, strlen(command4));
        driver.waitPacketSent();
        
          }else if(bvSerial.intData == 5){
        char *command5 = "5";
        driver.send((uint8_t *)command5, strlen(command5));
        driver.waitPacketSent();
        
          }else if(bvSerial.intData == 6){
        char *command6 = "6";
        driver.send((uint8_t *)command6, strlen(command6));
        driver.waitPacketSent();

          }else if(bvSerial.intData == 7){
        char *command7 = "7";
        driver.send((uint8_t *)command7, strlen(command7));
        driver.waitPacketSent();
          }

    }   
}
