/*Library inclusions*/

// Adafruit graphical functions library
#include <Adafruit_GFX.h> 

// ST7735 LCD display hardware library
#include <Adafruit_ST7735.h> 

//Arduino Serial peripheral interface library
#include <SPI.h> 

// Serial communication library
#include <SoftwareSerial.h>

// AVR sleep functions library
#include <avr/sleep.h>

/*Port Input/Output Declaration*/

//Bluetooth serial communication
SoftwareSerial BTMaster(0,1);

// LCD SPI Port declarations
#define TFT_CS 10
#define TFT_RST -1
#define TFT_DC 8

//LCD Initialization
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// LCD Power control for energy saving mode
const int lcdVcc = A0;

// Bluetooth enable pin
const int btEN = 5;

// Joystick input Ports
const int xpin = A4;
const int ypin = A5;

// Buttons declaration buttonPin0 is interrupt enabled
const int buttonPin = 4;
const int buttonPin0 = 3;
const int lcdLight = 9;

// Menu Variable Declaration
int menu;

//Joystick axis declaration
int xPos;
int yPos;

//Bluetooth transmission variables
char Direction;
byte BluetoothData;

//Buttons interaction variables
volatile boolean selected;
int pinRead;
int prevRead;

//Last temperature reading global variable
float l_temp;

// TFT LCD custom string display variables
String menuTxt;
int midPoint;

// Sleep Mode variable
boolean slept = false;
boolean vehicleSlept = false;

void setup(void) {
  
  // Serial Initialization
  BTMaster.begin(57600);
  
  // I/O initialization
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin0,LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin0), ISR_button, RISING);
  pinMode(lcdLight,OUTPUT);
  pinMode(lcdVcc,OUTPUT);
  pinMode(btEN,OUTPUT);

  
  //LCD Initalization
  analogWrite(lcdVcc,255);
  analogWrite(lcdLight,255);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);

  //BT initialization
  digitalWrite(btEN,LOW);
  
  //Selection variable initialization
  selected = false;
  // Menu integer initialization
  menu = 0;
}

/*The main loop takes readings from the joystick and the button
  while based on the axis movement(left or right) moves between
  the menu functions and the chooser function directs the program
  to the function to display text and enter into the functionalities
  once the button is pressed.
*/

void loop() {

  xPos = analogRead(xpin);
  yPos = analogRead(ypin);
  pinRead = digitalRead(buttonPin);
  delay(20);
 chooser(menu);
 
  if (xPos < 400 && menu != 0) {
    menu--;
    tft.fillScreen(ST7735_BLACK);
     delay(200);
     
  }

  else if (xPos > 600 && menu != 3) {
    menu++;
    tft.fillScreen(ST7735_BLACK);
    delay(200);
    
  }
 
}

void chooser (int menu){
  if (menu == 0){ 
    nav('0');
    }else if (menu == 1){
      nav('1');
      }else if (menu == 2){
        nav('2');}
        else if (menu == 3){
          nav('3');}
}

void nav (int n) {
  switch (n)
  {
    case '0':
    menuTxt = "Drive Mode";
    displaytext(menuTxt, ST7735_WHITE);
    driveMode();
    break;
    
    case '1':
      menuTxt = "Lights Mode";
      displaytext(menuTxt, ST7735_WHITE);
      light();
      break;
      
    case '2':
      menuTxt = "Sensor Mode";
      displaytext(menuTxt, ST7735_WHITE);
      tempRead();
      break;

    case '3':
      menuTxt = "Sleep Mode";
      displaytext(menuTxt, ST7735_WHITE);
      sleepMode();
      break;

  }
}


/*This fucntion is used to display the menu functions, a loop
  is used to center the text in the middle and rather avoid
  any overlapping or missing text, the text size used is 2 which
  which is 8 pixels
*/
void displaytext(String text, int color) {
  midPoint = 80;
  int x = (menuTxt.length()/2);
  for(int z = 0; z < x; z++){
    midPoint = midPoint - 12;
    }
  tft.setCursor(midPoint, 10);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(2);
  tft.print(text);
}
/*This function is used to display the temperature data
The reason of using a single function to do so was the text size
and the placement of the text which avoid overlapping with the menu
text
*/
void displayTemp(String text, int color){
  tft.setCursor(0,64);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.print(text);
}

/*This function transmits the joystick data to the vehicle based on a single axis
which ever is moved below or above the threshold levels which is received by the
vehicle and used to direct the driving.
*/
void driveMode(){
 
  if(pinRead == HIGH && selected == false){
    selected = true;
    delay(10);
  }
  else if(pinRead == HIGH && selected == true){
      selected = false;
      delay(10);
  }
      
  while(selected == true){ 
    int x = analogRead(xpin);
    int y = analogRead(ypin);
    delay(10);
  
    if(y < 450 || y > 570){
              Direction = '0';
              BTMaster.write(Direction);
              BluetoothData = map(y,0,1023,10,255);
              BTMaster.write(BluetoothData);
              delay(10);
     }else if(x < 450 || x > 570){
      
              Direction = '1';
              BTMaster.write(Direction);
              BluetoothData = map(x,0,1023,10,255);
              BTMaster.write(BluetoothData);
              delay(10);
              
     }else if((x > 450 || x < 570) && (y > 450 || y < 570) && Direction != '2') {
        Direction = '2';
        BTMaster.write(Direction);
        delay(10);
                    
    }
  }
}

void light(){
  if(pinRead == HIGH && prevRead != pinRead){
    Direction = '3';
    BTMaster.write(Direction);
    prevRead == pinRead;
    delay(10);
    BTMaster.write('2');
    delay(200);
  }
}

/*This function signals the vehicle to start transmitting the temperature data
while the conversion is applied on the remote aspect of the system.
*/
void tempRead(){
  if(pinRead == HIGH && selected == false){
    selected = true;
    delay(10);
  }
  else if(pinRead == HIGH && selected == true){
      selected = false;
      delay(10);}
      
      while(selected == true){ 
      Direction = '4';
      int temp;
      BTMaster.write(Direction);
      temp = BTMaster.read();
      temp = int(temp);
      temp = map(temp,0,255,0,1023);
      float mv = ( temp/1024.0)*5000; // convert analog input
      float cel = mv/10;    
      String sTemp = String(cel);
      delay(10);
      if(temp != l_temp){
        tft.fillScreen(ST7735_BLACK);
        displaytext("Sensor Mode", ST7735_WHITE);
        }
      displayTemp("Temperature: " +sTemp + " Celcius",ST7735_YELLOW);
      l_temp = temp;
      delay(1000);
  }
}
/*This function puts the device to sleep and can only be woken
by the interrupt button*/
  void sleepMode(){
  if(pinRead == HIGH && selected == false){
    selected = true;
    delay(10);
  }
    else if(pinRead == HIGH && selected == true){
      selected = false;
      delay(10);
    }
    
  while(selected == true){
  slept = true;
  analogWrite(lcdLight,0);
  analogWrite(lcdVcc,0);
  digitalWrite(btEN,LOW);  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  sleep_enable();
  }
  if(slept == true){
  wakeUp();
  }  
}
/*This function is enabled by interrupt and wakes
and reinitializes all the componenets put to sleep on the device*/
void wakeUp(){
  
  sleep_disable();
  digitalWrite(btEN,HIGH);
  analogWrite(lcdLight,255);
  analogWrite(lcdVcc,255);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  delay(100);
  slept = false;
  
  }
/*This function inverts the selected variable which is used to access
functions, the function is enabled by an interrupt*/
void ISR_button(){
  
  selected = false;

}

