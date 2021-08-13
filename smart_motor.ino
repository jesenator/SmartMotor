/*

*/
#include <Servo.h>
//#include <ArduinoSTL.h>
//using namespace std;

// analog sensors
int lightPin = A0;
int resistorPin = A1;
int linePin = A2;
int distPin = A3;

int buttonPin = 7;
int servoPin = 3;

// Motor 1
int dir1PinA = 2;
int dir2PinA = 4;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// RGB LED
int redPin= 11;
int greenPin = 9;
int bluePin = 10;

int lightVal, resistorVal, buttonVal, lastButtonVal, lineVal, distVal, sensorVal, actuatorVal;
int buttonCounter = 0;
int trainingNum = 0;
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

    pinMode(dir1PinA,OUTPUT);
    pinMode(dir2PinA,OUTPUT);
    pinMode(speedPinA,OUTPUT);
    
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
    sensorVal = lightVal;
    actuatorVal = resistorVal;
  
//    print values
//    Serial.println(lightVal);
//    Serial.println(resistorVal);
//    Serial.println(buttonVal);
//      Serial.println(lineVal);
//      Serial.println(distVal);  
//    Serial.println(servoPos);

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
//        Serial.println(buttonCounter);
    }
    else
        buttonCounter = 0;
    
    if (trainingDone) {
        RGBcolor("green");
    
        int closestPos = 0;
        int minDiff = abs(sensorArray[0] - sensorVal);
        for (int i = 0; i < trainingNum; i++) {
            if (abs(sensorArray[i] - sensorVal) < minDiff) {
                minDiff = sensorArray[i] - sensorVal;
                closestPos = i;
            }
        }
        actuatorVal = actuatorArray[closestPos];
//        Serial ray, trainingNum);
        writeActuator(actuatorVal);

        if (buttonPressed) {
          Serial.println("==============================");
          Serial.println("actual sensor value: " + String(sensorVal));
          Serial.println("closest sensor value: " + String(sensorArray[closestPos]));
          Serial.println("actuator value: " + String(actuatorVal));
          Serial.print("sensor array: ");
          printArr(sensorArray, trainingNum);  
          Serial.print("actuator array: ");
          printArr(actuatorArray, trainingNum);
        }
          
    } else if (buttonPressed) {
        blinkColor("purple", 2);
        sensorArray[trainingNum] = sensorVal;
        actuatorArray[trainingNum] = actuatorVal;

        trainingNum++;
//      train(sensor, acutator);

        printArr(sensorArray, trainingNum);  
        printArr(actuatorArray, trainingNum);        
      
    } else {
        RGBcolor("blue");
        writeActuator(actuatorVal);
    }
    delay(30);
    lastButtonVal = buttonVal;
}

void printArr(int arr[], int limit) {
  for (int i =0; i < limit; i++)
      Serial.print(String(arr[i]) + ", ");
  Serial.println();
}

void writeActuator(int val) {
//      dc motor
//    val = map(val, 0, 1023, -255, 255);
//    analogWrite(speedPinA, abs(val));
//    if (val > 0) {
//        digitalWrite(dir1PinA, LOW);
//        digitalWrite(dir2PinA, HIGH);
//    }
//    else {
//        digitalWrite(dir1PinA, HIGH);
//        digitalWrite(dir2PinA, LOW);
//    }

//      servo
      val = map(val, 0, 1023, 0, 180);
      servo.write(val);
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
  
