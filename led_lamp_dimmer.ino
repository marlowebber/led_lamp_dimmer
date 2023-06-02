int analogPin = A3;
int val = 0;  
const int valMax = 1023;

int outPin = 2;
int freqUs   = 5000; // 5000us = 200Hz
int dutyOffUs = 5000;

int loopCount = 0;
const int loopCountCheck = 100;


void setup() {
  pinMode(outPin, OUTPUT);   
  Serial.begin(9600);       
}

void loop() {
  digitalWrite(outPin, HIGH);
  delayMicroseconds(freqUs - dutyOffUs);
  digitalWrite(outPin, LOW);
  delayMicroseconds(dutyOffUs);
  if (loopCount > loopCountCheck)
  {
    val = analogRead(analogPin); 

    float v = val;
    float vm = valMax;

    float r = v / vm;
    float ff = freqUs;

    float ndc = ff * r;

    dutyOffUs = ndc;
    
    Serial.println(dutyOffUs);  
    loopCount = 0;
  }
  loopCount++;
}
