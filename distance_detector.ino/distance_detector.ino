/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
int ledGreenPin = 0;
int ledYellowPin = 1;
int ledRedPin = 2;
const int buzzer = 9; //buzzer to arduino pin 9

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(led2,LOW);
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  PaulinaDistanceFunction(distance);
  delay(500);
}


void PaulinaDistanceFunction (long distanceValue) {
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledYellowPin, LOW);
  digitalWrite(ledRedPin, LOW);
  noTone(buzzer);     // Stop sound...
  
  if (distanceValue >= 20){
    digitalWrite(ledGreenPin, HIGH);
  }
  else {
    if( (distanceValue >= 10) && (distanceValue < 20) ) {
      digitalWrite(ledYellowPin, HIGH);
     }
    else{
      digitalWrite(ledRedPin, HIGH);
      tone(buzzer, 1000); // Send 1KHz sound signal...
    }
    
  }
  
}

