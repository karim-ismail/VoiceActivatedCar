#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

int command;
RH_ASK rf_driver;
//
void setup() {
  // put your setup code here, to run once:
   Serial.begin( 9600 );
  rf_driver.init();

}

void loop() {
  // put your main code here, to run repeatedly:

 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN] = {0};
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)){
    //command = figureOutWhatItIs(buff); 
     Serial.println((char*)buf);
  }

}
