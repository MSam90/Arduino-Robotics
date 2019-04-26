const int voltageRead = A7;
double ratio;
double idleCurrent;
double maxCurrent;
double idlePower;
double maxPower;
double voltage;
double resistance;
double batteryCapacity = 4000;
double onTime;
double idleTime;
void setup() {
pinMode(voltageRead,INPUT);

}

void loop() {

}

void calculateMaxPower(){
  voltage = analogRead(voltageRead);
  voltage = voltage * ratio;
  maxPower = (resistance) * (2*maxCurrent);
  }

void calculateIdlePower(){
  int voltage = analogRead(voltageRead);
  voltage = voltage * ratio;
  idlePower = (resistance) * (2*idleCurrent);
  }

void findIdleTime(){
  //IDLE time in minutes based on 4000mah battery capacity
  onTime = (batteryCapacity/1000)/(idleCurrent)*60;
  }
void findOnTime(){
  //ON time in minutes based on 4000mah battery capacity
  onTime = (batteryCapacity/1000)/(maxCurrent)*60;
  }
