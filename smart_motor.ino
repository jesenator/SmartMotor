/*

*/
#include <Servo.h>

int lightPin = A0;
int resistorPin = A1;
int buttonPin = 7;
int servoPin = 3;
int lightVal, resistorVal, buttonVal;
long servoPos;
Servo servo;

void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, INPUT);
    Serial.write("running");
    
    servo.attach(servoPin);
}

void loop() {
//  read values
    lightVal = analogRead(lightPin);
    resistorVal = analogRead(resistorPin);
    buttonVal = digitalRead(buttonPin);
//    servoPos = map(resistorVal, 0, 1023, 0, 180);
    servoPos = map(lightVal, 10, 800, 0, 180);

//    servoPos = resistorVal;

//    print values
//    Serial.println(lightVal);
//    Serial.println(resistorVal);
//    Serial.println(buttonVal);
    Serial.println(servoPos);
    servo.write(servoPos);

    delay(30);
}
  
