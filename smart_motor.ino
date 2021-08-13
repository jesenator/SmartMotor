/*

*/
#include <Servo.h>
//#include <ArduinoSTL.h>
//using namespace std;

int lightPin = A0;
int resistorPin = A1;
int linePin = A2;
int distPin = A3;

int buttonPin = 7;
int servoPin = 3;
int redPin= 11;
int greenPin = 9;
int bluePin = 10;

int lightVal, resistorVal, buttonVal, lastButtonVal, lineVal, distVal, sensorVal, actuatorVal;
int buttonCounter = 0;
int trainingNum = 0;
long servoPos;
bool buttonPressed, buttonHeld, trainingDone = false;
double scale = .7;

const int ELEMENT_COUNT_MAX = 50;
int sensorArray[ELEMENT_COUNT_MAX];
int actuatorArray[ELEMENT_COUNT_MAX];

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
//      Serial.println(distVal);  
//    Serial.println(servoPos);
    servo.write(servoPos);



    sensorVal = lightVal;
    actuatorVal = resistorVal;

    buttonHeld = (not buttonVal and lastButtonVal and buttonCounter > 15);
    buttonPressed = (not buttonVal and lastButtonVal and not buttonHeld);
    if (buttonHeld) {
      trainingDone = not trainingDone;
      Serial.println("button held");
      buttonCounter = 0;
    } 
    if (buttonVal) {
//        RGBcolor("white");
        buttonCounter++;
        Serial.println(buttonCounter);
    }
    if (trainingDone) {
        RGBcolor("green");

//        int closest;
//        minDiff = abs(sensorArray[0] - sensor)
//        int actuatorPos;
//        for (int i = 1; i < trainingNum; i++) {
//            
          
        }
    else if (buttonPressed) {
        blinkColor("purple", 2);
        sensorArray[trainingNum] = sensorVal;
        actuatorArray[trainingNum] = actuatorVal;

        trainingNum++;
//      train(sensor, acutator);

        printArr(sensorArray, trainingNum);  
        printArr(actuatorArray, trainingNum);        
      
    }
    else {
        RGBcolor("blue");
        buttonCounter = 0;
    }
      

    delay(30);
    lastButtonVal = buttonVal;
}

void printArr(int arr[], int limit) {
  for (int i =0; i < limit; i++)
      Serial.print(arr[i] + ", ");
  Serial.prinln()
}


void blinkColor(String color, int num) {
  int delayNum = 200;
  for (int i = 0; i < num; i++) {
      delay(delayNum);
      RGBcolor(color);
      delay(delayNum);
      RGBcolor("none");
  }
  delay(delayNum);
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
//  else if (color == "yellow")
//    RGBcolor(0, 255, 255);
//  else if (color == "white")
//    RGBcolor(255, 255, 255);
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
  
