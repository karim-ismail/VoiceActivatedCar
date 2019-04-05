
//motor pins
#define RIGHT_SPEED 5
#define RIGHT_DIRECTION 4
#define LEFT_SPEED 8
#define LEFT_DIRECTION 9

//arduino pins
#define ECHO_PIN 12
#define TRIG_PIN 1

//speeds
#define ZERO_SPEED 255
#define HALF_SPEED 127
#define FULL_SPEED 0

//motor states
#define FORWARD 1
#define REVERSE 0

#define DIR_DELAY 1000
#define SAFETY_THRESHOLD 5

void setup() {
  // put your setup code here, to run once:
  pinMode( RIGHT_SPEED, OUTPUT );
  pinMode( RIGHT_DIRECTION, OUTPUT );
  pinMode( LEFT_SPEED, OUTPUT );
  pinMode( LEFT_DIRECTION, OUTPUT );

}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(RIGHT_DIRECTION, REVERSE);
 digitalWrite(LEFT_DIRECTION, REVERSE);
 analogWrite(RIGHT_SPEED, FULL_SPEED);
 analogWrite(LEFT_SPEED, FULL_SPEED);

}
