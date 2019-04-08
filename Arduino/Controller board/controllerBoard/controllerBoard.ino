#include <RH_ASK.h>
#include <SPI.h> 

//motor pins
#define RIGHT_SPEED 4
#define RIGHT_DIRECTION 5
#define LEFT_SPEED 8
#define LEFT_DIRECTION 9

//arduino pins
#define ECHO_PIN 13
#define TRIG_PIN 2

//speeds
#define ZERO_SPEED 255
#define HALF_SPEED 127
#define FULL_SPEED 0

//motor states
#define FORWARD 1
#define REVERSE 0

#define DIR_DELAY 1000
#define SAFETY_THRESHOLD 8

//commands
#define CMD_RIGHT 6
#define CMD_LEFT  5
#define CMD_FORWARD 1
#define CMD_REVERSE 3
#define CMD_CDONUT  7
#define CMD_CCDONUT 4
#define CMD_STOP 2

//global variables
int command;
RH_ASK rf_driver;


void setup() {
  // initializing components and global variables
  Serial.begin( 9600 );
  if (!rf_driver.init()) Serial.println(" ASK Driver init failed");
  initMotors();
  initUltrasonics();
  stopMotors();
  command = CMD_STOP;

}

void loop() {
  //checks ultrasonics twice for reliability
  command = (checkUltraSonics()&&checkUltraSonics())? CMD_STOP: receiveCommand(command);
  delay(100);
  
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

//initializes the ultrasonics pins
void initUltrasonics(){
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 
}

//Stops the motors
void stopMotors(){
  digitalWrite( RIGHT_SPEED, LOW );
  digitalWrite( RIGHT_DIRECTION, LOW );
  digitalWrite( LEFT_SPEED, ZERO_SPEED );
  digitalWrite( LEFT_DIRECTION, ZERO_SPEED );
  
}

//Does a clockwise donut
void clockwiseDonut(int speed){
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, ZERO_SPEED);
 analogWrite(LEFT_SPEED, speed);

}
//Does a counter-clockwise donut
void counterClockwiseDonut(int speed){
 digitalWrite(RIGHT_DIRECTION, FORWARD);
 digitalWrite(LEFT_DIRECTION, REVERSE);
 analogWrite(RIGHT_SPEED, speed);
 analogWrite(LEFT_SPEED, ZERO_SPEED);

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
 analogWrite(RIGHT_SPEED, ZERO_SPEED);
 analogWrite(LEFT_SPEED, ZERO_SPEED);

}

//checks the ultrasonic sensor and returns true if we're closer than the safety threshold
boolean checkUltraSonics(){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    int duration = pulseIn(ECHO_PIN, HIGH);
   
    // Calculating the distance
    duration= duration*0.034/2;
    return (duration < SAFETY_THRESHOLD); //if unsafe returns true
   
    
}

//Receive a command from the 433 MHz receiver and do some maths to change it to an int
int receiveCommand(int command){
 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN] = {0};
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)){
    Serial.print("received: ");
    Serial.println((buf[0]-48));
  return ( (buf[0]-48));

  }
  return command;
 
  
}


  
