#include <dht11.h>
#define DHT11PIN 6
#include <LiquidCrystal.h>
#include <IRremote.h>    
int RECV_PIN =10;     
int relay = 8;    
int value; 
int led1=9;
int led2=13;
int led3=7;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht11 DHT11;
int tempmax=24; 
int tempmin=20; 
int umdmax=60; 
int umdmin=50; 

void setup() {  
 Serial.begin(9600);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);
 pinMode(en, OUTPUT);
 pinMode(relay, OUTPUT); 
 digitalWrite(relay, HIGH);    
 Serial.begin(9600);     
 //irrecv.enableIRIn();  
 IrReceiver.begin(10); 
 
         
 
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  float umd=((float)DHT11.humidity);
  float temp=((float)DHT11.temperature);
  lcd.begin(16, 2);
  lcd.print("H(%):");
  lcd.print(umd);
  lcd.setCursor(0,1);
  lcd.print("Temp(C):");
  lcd.print(temp);
  if(temp>=tempmin&&temp<=tempmax){
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     ;}
     
  else {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    
    }
  
  if(umd>=umdmin&&umd<=umdmax)
  { digitalWrite(led3, LOW);
    }
  else{
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led3, LOW);
    //digitalWrite(relay, HIGH);
    }
    if (IrReceiver.decode()){  
     Serial.println(IrReceiver.decodedIRData.command);
     switch(IrReceiver.decodedIRData.command){     
        case 12: //Keypad button "1"        
         digitalWrite(relay, LOW); 
         break;   
        case 22: //Keypad button "0"     
          digitalWrite(relay, HIGH);  
          break;
        case 21: //keypad button "+" ->crestere temp maxima
          {
          tempmax++; 
          lcd.begin(16, 2);
          lcd.print("Temp max:");
          lcd.print(tempmax);
          delay(500);
          break;}
        case 7: //Keypad button "-" ->scadere temp maxima
          { 
           tempmax--;
           lcd.begin(16, 2);
           lcd.print("Temp. max:");
           lcd.print(tempmax);
           delay(500);
           break;}
        case 9: //Keypad button "EQ-afisare temperatura maxima si temperatura minima curenta"
          { 
           lcd.begin(16, 2);
           lcd.print("Temp. max:");
           lcd.print(tempmax);
           lcd.setCursor(0,1);
           lcd.print("Temp. min:");
           lcd.print(tempmin);
           delay(800);
           break;}
         case 69: //Keypad button "CH- scadere temp min"
          { 
            tempmin--;
           lcd.begin(16, 2);
           lcd.print("Temp. min:");
           lcd.print(tempmin);
           delay(500);
           break;}  
           case 71: //Keypad button "CH+ crestere temp min"
          { 
            tempmin++;
           lcd.begin(16, 2);
           lcd.print("Temp. min:");
           lcd.print(tempmin);
           delay(500);
           break;}
            case 64: //keypad button "NEXT" ->crestere umiditate maxima
          {
          umdmax++; 
          lcd.begin(16, 2);
          lcd.print("Umd.max:");
          lcd.print(umdmax);
          delay(500);
          break;}
        case 68: //Keypad button "PREV" ->scadere temp maxima
          { 
           umdmax--;
           lcd.begin(16, 2);
           lcd.print("Umd. max:");
           lcd.print(umdmax);
           delay(500);
           break;}
        case 67: //Keypad button "PLAY/PAUSE"-afisare umiditate maxima si umiditate minima curenta"
          { 
           lcd.begin(16, 2);
           lcd.print("Umd. max:");
           lcd.print(umdmax);
           lcd.setCursor(0,1);
           lcd.print("Umd. min:");
           lcd.print(umdmin);
           delay(800);
           break;}
         case 25: //Keypad button "100+" - scadere umiditate min"
          { 
            umdmin--;
           lcd.begin(16, 2);
           lcd.print("Umd. min:");
           lcd.print(umdmin);
           delay(500);
           break;}  
           case 13: //Keypad button "200+"- crestere umid min"
          { 
            umdmin++;
           lcd.begin(16, 2);
           lcd.print("Umd. min:");
           lcd.print(umdmin);
           delay(500);
           break;}        
        default:
          break; 
         }      
          IrReceiver.resume();  
   }   
  delay(400) ; 
  }
