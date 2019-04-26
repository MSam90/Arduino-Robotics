 #include <SoftwareSerial.h>
#include <avr/power.h>
#include <avr/sleep.h>
SoftwareSerial BTSlave(13,12);

const int EN_1 = 11;
const int EN_2 = 3;
const int INPUT_1 = 10;
const int INPUT_2 = 9;
const int INPUT_3 = 6;
const int INPUT_4 = 7;
byte rec;
char Direction;
int y;
int x;
int xpos;
int ypos;
char dataType;
//Functions Parameters
boolean led_state = true;
boolean prev_led = false;
const int led = 2;
const int led1 = 4;
const int tempPin = A0;

void setup() {
pinMode(EN_1,OUTPUT);
pinMode(EN_2,OUTPUT);
pinMode(INPUT_1,OUTPUT);
pinMode(INPUT_2,OUTPUT);
pinMode(INPUT_3,OUTPUT);
pinMode(INPUT_4,OUTPUT);
pinMode(led,OUTPUT);
pinMode(led1,OUTPUT);
BTSlave.begin(57600);
Serial.begin(19200);
}

void loop() {
    if(BTSlave.available() > 0){
      rec = BTSlave.read();
      Serial.println(rec);
      if(rec == '0' || rec == '1' || rec == '2'){
        Direction= rec;
        driveMode();  
      }else if(rec == '3'){
        lightMode();
        }else if(rec == '4'){
          tempMode();
          }else if(rec == '5'){
            sleepMode();}
            else if (rec =='6'){
              wakeUp();}
  }
  }

void driveMode(){
   if(Direction == '1'){     
             y = BTSlave.read();
             y = int(y);
             Serial.println(y);
             ypos = map(y,10,255,0,1023);
             delay(3);
             
    if(ypos > 550){

             Serial.println(ypos);
             MOVE('B');
             
  }
    else if(ypos < 470){
            Serial.println(ypos);
            MOVE('F');     
    }
       
 }else if(Direction == '0'){
            x = BTSlave.read();
            x = int(x);
            xpos = map(x,10,255,0,1023);
            delay(3);
            
    if(xpos > 550){
            Serial.println(xpos);
             MOVE('R');
             
             }
    else if(xpos < 470){
            Serial.println(xpos);
            MOVE('L');
            
            }
   }
    else if(Direction == '2' || xpos == 512 || ypos == 512){
      MOVE('S');}

   
   } 
  
  

void MOVE (char d){
   switch(d)
      {
         case 'L':
      digitalWrite(EN_1,HIGH);
      digitalWrite(EN_2,HIGH);
      digitalWrite(INPUT_1,HIGH);
      digitalWrite(INPUT_2,LOW);
      digitalWrite(INPUT_3,LOW);
      digitalWrite(INPUT_4,HIGH);
      delay(20);
      
      Direction = '2';
      break;
         case 'R':
      digitalWrite(EN_1,HIGH);
      digitalWrite(EN_2,HIGH);
      digitalWrite(INPUT_1,LOW);
      digitalWrite(INPUT_2,HIGH);
      digitalWrite(INPUT_3,HIGH);
      digitalWrite(INPUT_4,LOW);
      delay(20);
      
      Direction = '2';
      break;
         case 'S':
      digitalWrite(EN_1,HIGH);
      digitalWrite(EN_2,HIGH);
      digitalWrite(INPUT_1,LOW);
      digitalWrite(INPUT_2,LOW);
      digitalWrite(INPUT_3,LOW);
      digitalWrite(INPUT_4,LOW);
      break;
        case 'B':
      digitalWrite(EN_1,HIGH);
      digitalWrite(EN_2,HIGH);
      digitalWrite(INPUT_1,LOW);
      digitalWrite(INPUT_2,HIGH);
      digitalWrite(INPUT_3,LOW);
      digitalWrite(INPUT_4,HIGH);
      delay(20);
      
      Direction = '2';
      break;
        case 'F':
      digitalWrite(EN_1,HIGH);
      digitalWrite(EN_2,HIGH);
      digitalWrite(INPUT_1,HIGH);
      digitalWrite(INPUT_2,LOW);
      digitalWrite(INPUT_3,HIGH);
      digitalWrite(INPUT_4,LOW);
      delay(20);
      
      Direction = '2';
      break;
    }
  }
void tempMode(){
  Serial.println("In tempMode"); 
  int x = analogRead(tempPin);
  byte y = map(x,0,1023,0,255);
  Serial.print("ADC Value: ");
  Serial.println(x);
  Serial.print("ADC Value mapped: ");
  Serial.println(y);
  BTSlave.write(y);
  delay(10);
  }

void lightMode(){
  Serial.println("In lightMode");
  delay(5);
  int check = digitalRead(led);
  delay(20);
  if(check == HIGH){
  digitalWrite(led,LOW);
  digitalWrite(led1,LOW);

    }else if(check != HIGH){

      digitalWrite(led,HIGH);
      digitalWrite(led1,HIGH);
}
  }

void sleepMode(){

  set_sleep_mode(SLEEP_MODE_IDLE);
  power_adc_disable();
  power_spi_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_twi_disable();

  sleep_mode();
  delay(100);
  }

void wakeUp(){

  sleep_disable();
  power_all_enable();
  delay(100);
  }
