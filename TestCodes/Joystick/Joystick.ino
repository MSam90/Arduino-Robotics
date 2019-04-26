/*This code is used to test the analogue joystick
  the function is to read both x and y axis and
  display them on the serial monitor*/


// Analogue pin 0 is used to read the X axis
const int xPin = A0;
// Analogue pin 1 is used to read the X axis
const int yPin = A1;

//Variables to store the analogue read values
int x;
int y;
void setup() {

  //Input declarations
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  //initializing the serial monitor at baud rate 19200
  //to display the x and y axis
  Serial.begin(19200);

}

void loop() {

  x = analogRead(xPin);
  y = analogRead(yPin);

  Serial.print(" X value : ");
  Serial.println(x);
  Serial.print("Y value : ");
  Serial.println(y);
  delay(100);
  
}
