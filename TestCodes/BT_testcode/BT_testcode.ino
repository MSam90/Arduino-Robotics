/*This code allows a connection to a bluetooth enabled terminal
  the code can both send and receive values. once the controller
  received a 1 the LED on pin 13 are set to high and if 0 set to LOW
*/

#include<SoftwareSerial.h>
// the TX pin of the BT device is connected to pin 0 and RX to 1
SoftwareSerial btSerial(0,1);s
const int ledPin = 13;
int rec;

void setup() {
  
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  btSerial.begin(57600);

}

void loop() {
  if(btSerial.available()>0)
  rec = btSerial.read();

  if(rec == 1){
    digitalWrite(ledPin,HIGH);
    delay(20);
  }else if(rec == 0){
    digitalWrite(ledPin,LOW);
    delay(10);
    }
}
