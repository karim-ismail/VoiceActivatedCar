#define RIGHT_SPEED 6
#define RIGHT_DIRECTION 7
#define LEFT_SPEED 10
#define LEFT_DIRECTION 9

#define ZERO_SPEED 0
#define HALF_SPEED 127
#define FULL_SPEED 255

#define FORWARD 1
#define REVERSE 0

#define DIR_DELAY 1000

void setup() {
  // setting pins to output and writing 0 to all
  Serial.begin( 9600 );
  pinMode( RIGHT_SPEED, OUTPUT );
  pinMode( RIGHT_DIRECTION, OUTPUT );
  pinMode( LEFT_SPEED, OUTPUT );
  pinMode( LEFT_DIRECTION, OUTPUT );
  stopMotors();

}

void loop() {
  
  
 delay(DIR_DELAY);
 digitalWrite(RIGHT_DIRECTION, FORWARD);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, HALF_SPEED);
 analogWrite(LEFT_SPEED, HALF_SPEED);

 delay(5000);
 
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, FORWARD);
 analogWrite(RIGHT_SPEED, FULL_SPEED);
 analogWrite(LEFT_SPEED, FULL_SPEED);

}

void stopMotors(){
  digitalWrite( RIGHT_SPEED, LOW );
  digitalWrite( RIGHT_DIRECTION, LOW );
  digitalWrite( LEFT_SPEED, LOW );
  digitalWrite( LEFT_DIRECTION, LOW );
  
}

  
