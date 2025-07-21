/* major project
geusture-controlled car


MPu6050
vcc-3.3
gnd-gnd
sda-21
scl-22

a4988 driver1
dir-26
step-27
sleep-reset
vmot-external power
gnd- external gnd
1a-A+ motor
1b-A- motot
2a-B+ motor
2b-b- motor


a4988 driver2
dir-14
step-12
sleep-reset
vmot-external power
gnd- external gnd
1a-A+ motor
1b-A- motot
2a-B+ motor
2b-b- motor

 a4988 driver 3
dir-33
step-25
sleep-reset
vmot-external power
gnd- external gnd
1a-A+ motor
1b-A- motot
2a-B+ motor
2b-b- motor


a4988 driver 4
dir-35
step-32
sleep-reset
vmot-external power
gnd- external gnd
1a-A+ motor
1b-A- motot
2a-B+ motor
2b-b- motor
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define DIR_PIN1 26
#define STEP_PIN1 27

#define DIR_PIN2 14
#define STEP_PIN2 12

#define DIR_PIN3 33
#define STEP_PIN3 25

#define DIR_PIN4 18
#define STEP_PIN4 32


#define LED_FORWARD 4
#define LED_BACKWARD 16
#define LED_RIGHT 17
#define LED_LEFT 5


Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

 
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(STEP_PIN1, OUTPUT);

  pinMode(DIR_PIN2, OUTPUT);
  pinMode(STEP_PIN2, OUTPUT);

  pinMode(DIR_PIN3, OUTPUT);
  pinMode(STEP_PIN3, OUTPUT); 

  pinMode(DIR_PIN4, OUTPUT);
  pinMode(STEP_PIN4, OUTPUT);

  pinMode(LED_FORWARD, OUTPUT);//green
  pinMode(LED_BACKWARD, OUTPUT);//red
  pinMode(LED_RIGHT, OUTPUT);//blue
  pinMode(LED_LEFT, OUTPUT);//yellow

}

 
  void stepMotors(bool dir1, bool dir2, bool dir3, bool dir4, int steps, int delayMicros = 600) {
  digitalWrite(DIR_PIN1, dir1);
  digitalWrite(DIR_PIN2, dir2);
  digitalWrite(DIR_PIN3, dir3);
  digitalWrite(DIR_PIN4, dir4); 

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN1, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(STEP_PIN1, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(STEP_PIN2, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(STEP_PIN2, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(STEP_PIN3, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(STEP_PIN3, LOW);
    delayMicroseconds(delayMicros);

     digitalWrite(STEP_PIN4, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(STEP_PIN4, LOW);
    delayMicroseconds(delayMicros);
    }
  }
 

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (a.acceleration.y > 1.0) {
    moveForward();
  } else if (a.acceleration.y < -1.0) {
    moveBackward();
  } else if (a.acceleration.x > 1.0) {
    turnRight();
  } else if (a.acceleration.x < -1.0) {
    turnLeft();
  } else {
    stopMotors();
  }

  delay(100);
}

void moveForward() {
  stepMotors(false,false,true,true,200);
  indicateDirection(LED_FORWARD);
  Serial.println("moveing forward");
}

void moveBackward() {
  stepMotors(true,true,false,false,200);
  indicateDirection(LED_BACKWARD);
  Serial.println("moving backward");
}

void turnRight() {
  stepMotors(true,true,true,true,200);
  indicateDirection(LED_RIGHT);
  Serial.println("moving righ side");
}

void turnLeft() {
  stepMotors(false,false,false,false,200);
  indicateDirection(LED_LEFT);
  Serial.println("movieng left side");
}

void stopMotors() {
  indicateDirection(0);
}

void indicateDirection(int ledPin) {
  digitalWrite(LED_FORWARD, LOW);
  digitalWrite(LED_BACKWARD, LOW);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_LEFT, LOW);
  


  if (ledPin != 0) {
    digitalWrite(ledPin, HIGH);
  }
}
