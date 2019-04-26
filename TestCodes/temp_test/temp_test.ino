/*This code test the LM35 temperature sensor
  the code reads an analogue value and is displayed
  on the serial monitor
*/

const int tmpPin = A0;
int temp;
int deg;

void setup() {
Serial.begin(19200);

}

void loop() {
  
  temp = analogRead(tmpPin);
  
  /*Since the LM35 outputs a voltage up to 1V a calculation must
  be made to downsize the value read hence perform a conversion
  into celcius degrees*/
  
  float x = (temp/1024)*5000;
  x = x/10;
  Serial.println("Temp: ");
  Serial.print(x);
  Serial.println (" Celcius");
  delay(10000);
  
  
  

}
