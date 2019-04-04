#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//motor pins
#define RIGHT_SPEED 5
#define RIGHT_DIRECTION 6
#define LEFT_SPEED 9
#define LEFT_DIRECTION 10

//arduino pins
#define ECHO_PIN 12
#define TRIG_PIN 1

//speeds
#define ZERO_SPEED 0
#define HALF_SPEED 127
#define FULL_SPEED 255

//motor states
#define FORWARD 1
#define REVERSE 0

#define DIR_DELAY 1000
#define SAFETY_THRESHOLD 5

//commands
#define CMD_RIGHT 1//add more commands for different speeds if u want to
#define CMD_LEFT  2
#define CMD_FORWARD 3
#define CMD_REVERSE 4
#define CMD_CDONUT  5
#define CMD_CCDONUT 6
#define CMD_STOP 7


int command;
RH_ASK rf_driver;
uint8_t buf[24];
uint8_t buflen;

void setup() {
  // setting pins to output and writing 0 to all
  Serial.begin( 9600 );
  if (!rf_driver.init()) Serial.println(" ASK Driver init failed");
  initMotors();
  initUltrasonics();
  stopMotors();
  command = CMD_STOP

}

void loop() {
  //wait for input (needs to be tested)
  if (Serial.available()){
    command = Serial.read();
    delay(DIR_DELAY); //always delay when changing direction
  }
  
  //receive command
  
  
  //checks ultrasonics twice for reliability
  command = (checkUltraSonics()&&checkUltrasonics())? CMD_STOP: receiveCommand();
  
  
  //execute received command
  executeCommand(command);
  
  
}


//Do something based on the command received
void executeCommand(int command){
  switch (command){
    case CMD_RIGHT:
      turnRight(HALF_SPEED);
      break; 
      
    case CMD_LEFT:
      turnLeft(HALF_SPEED);
      break; 
      
    case CMD_REVERSE:
      moveBackwards(HALF_SPEED);
      break; 
      
    case CMD_FORWARD:
      moveForward(HALF_SPEED);
      break; 
      
    case CMD_CDONUT:
      clockwiseDonut(HALF_SPEED);
      break; 
      
    case CMD_CCDONUT:
      counterClockwiseDonut(HALF_SPEED);
      break; 
      
    case CMD_STOP:
      stopMotors();
      break; 
      
    default:
      stopMotors();
      break;
    }
}

//initializes the pins connected to the motors
void initMotors(){
  pinMode( RIGHT_SPEED, OUTPUT );
  pinMode( RIGHT_DIRECTION, OUTPUT );
  pinMode( LEFT_SPEED, OUTPUT );
  pinMode( LEFT_DIRECTION, OUTPUT );
}

void initUltrasonics(){
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 
}

//Stops the motors
void stopMotors(){
  digitalWrite( RIGHT_SPEED, LOW );
  digitalWrite( RIGHT_DIRECTION, LOW );
  digitalWrite( LEFT_SPEED, LOW );
  digitalWrite( LEFT_DIRECTION, LOW );
  
}

//Does a clockwise donut
void clockwiseDonut(int speed){
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, speed);

}
//Does a counter-clockwise donut
void counterClockwiseDonut(int speed){
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, speed);

}

//moves left
void turnLeft(int speed){
 digitalWrite(RIGHT_DIRECTION, FORWARD);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, ZERO_SPEED);

}

//moves right
void turnRight(int speed){
 digitalWrite(RIGHT_DIRECTION, FORWARD);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, ZERO_SPEED);
 analogWrite(LEFT_SPEED, speed);

}

//moves forward
void moveForward(int speed){
 digitalWrite(RIGHT_DIRECTION, FORWARD);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, speed);

}

//moves backwards
void moveBackwards(int speed){
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, REVERSE);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, speed);

}

boolean checkUltraSonics(){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    return (distance < SAFETY_THRESHOLD) //if unsafe returns true
    
}

int receiveCommand(){
  buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)){
    command = figureOutWhatItIs(buff); 
  }
}


  
