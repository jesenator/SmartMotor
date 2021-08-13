/*

*/
#include <Servo.h>

int lightPin = A0;
int resistorPin = A1;
int linePin = A2;
int distPin = A3;

int buttonPin = 7;
int servoPin = 3;
int lightVal, resistorVal, buttonVal, lastButtonVal, lineVal, distVal;
int buttonCounter = 0;
long servoPos;
bool buttonPressed, buttonHeld, trainingDone = false;
int redPin= 11;
int greenPin = 9;
int bluePin = 10;
double scale = .7;

Servo servo;

void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.write("running");
    
    servo.attach(servoPin);
}

void loop() {
//  read values
    lightVal = analogRead(lightPin);
    resistorVal = analogRead(resistorPin);
    buttonVal = digitalRead(buttonPin);
    lineVal = analogRead(linePin);
    distVal = analogRead(distPin);
    servoPos = map(resistorVal, 0, 1023, 0, 180);
//    servoPos = map(lightVal, 10, 800, 0, 180);
//    servoPos = resistorVal;
  
//    print values
//    Serial.println(lightVal);
//    Serial.println(resistorVal);
//    Serial.println(buttonVal);
//      Serial.println(lineVal);
      Serial.println(distVal);
//    Serial.println(servoPos);
    servo.write(servoPos);

    buttonHeld = (not buttonVal and lastButtonVal and buttonCounter > 15);
    buttonPressed = (not buttonVal and lastButtonVal and not buttonHeld);
    if (buttonHeld)
      trainingDone = not trainingDone;
      
    if (buttonVal) {
        RGBcolor("white");
        buttonCounter++;
    }
    else if (not buttonHeld) {
        RGBcolor("none");
        buttonCounter = 0;
    }
      

    if (trainingDone and not buttonVal)
      RGBcolor("green");
    else if (buttonPressed) {
      blinkColor("purple", 2);
    }

    delay(30);
    lastButtonVal = buttonVal;
}

void blinkColor(String color, int num) {
  int delayNum = 200;
  for (int i = 0; i < num; i++) {
      delay(delayNum);
      RGBcolor(color);
      delay(delayNum);
      RGBcolor("none");
  }
}

void RGBcolor(String color) {
  if (color == "red")
    RGBcolor(255, 0, 0);
  else if (color == "green")
    RGBcolor(0, 255, 0);
  else if (color == "blue")
    RGBcolor(0, 0, 255);
  else if (color == "purple")
    RGBcolor(255, 0, 255);
  else if (color == "white")
    RGBcolor(255, 255, 255);
  else if (color == "none")
    RGBcolor(0, 0, 0);
}
void RGBcolor(int redVal, int greenVal, int blueVal) {
//    Serial.println(redVal);
//    Serial.println(greenVal);
//    Serial.println(blueVal);

    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);
}
  
