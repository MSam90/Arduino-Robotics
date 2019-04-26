/*This is a test code to interact with the push buttons,
the code outputs light when the button is pressed*/
//pin 2 of the controller is reserved for the push button
const int pushButton = 2;
//pin 13 which has an onboard LED on Arduino and the Pro Trinket
//is used to show the state of the push button
const int ledPin = 13;
//Variable to store the current state of the button
int state;
void setup() {
  //Declare inputs and outputs
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
  //Initialize led to 0V
  digitalWrite(ledPin,LOW);
}

void loop() {
  
state = digitalRead(pushButton);
delay(25);

if(state == HIGH){
  
  digitalWrite(ledPin,HIGH);
  delay(20);
  
  }else {
    digitalWrite(ledPin,LOW);}

}
