int analogPin = A3;
int val = 0;  
const int valMax = 1023;

int outPin = 2;
int freqUs   = 5000; // 5000us = 200Hz
int dutyOffUs = 5000;

int loopCount = 0;
const int loopCountCheck = 100;


int measure()
{
    val = analogRead(analogPin); 

    float v = val;
    float vm = valMax;

    float r = v / vm;
    float ff = freqUs;

    float ndc = ff * r;

    int wemm = ndc;
    
    Serial.println(wemm);  

    return wemm;
}


void doLights(int dtc)
{
  digitalWrite(outPin, HIGH);
  delayMicroseconds(freqUs - dtc);
  digitalWrite(outPin, LOW);
  delayMicroseconds(dtc);
}


void startup()
{
  delay(5000); // allow capacitors to charge up fully.

  dutyOffUs = measure();
  int tempDuty = 0;
  
  while(tempDuty < dutyOffUs);
  {
    doLights(tempDuty);
    tempDuty++;
  }
}


void setup() {
  pinMode(outPin, OUTPUT);   
  Serial.begin(9600);       
  startup();
}

void loop() {
  doLights(dutyOffUs);
  if (loopCount > loopCountCheck)
  {
    dutyOffUs = measure();
    loopCount = 0;
  }
  loopCount++;
}
