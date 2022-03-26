#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SD.h>                           //include SD module library
#include <TMRpcm.h>                       //include speaker control library

#define SD_ChipSelectPin 4                //define CS pin

TMRpcm tmrpcm;                            //crete an object for speaker library

#define codeLength 5

char Code[codeLength];
// Change keypad password to a 3 digit number only
char password[codeLength] = "AD59";

const byte ROWS = 4;
const byte COLS = 4;
  
char keypadKeys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte keyCount = 0;

byte rowPins[ROWS] = {A5, 1, 10, A4};
byte colPins[COLS] = {A3, A2, A1, A0};
int LCDRow = 0;

Keypad customKey = Keypad(makeKeymap(keypadKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(2, 3, 8, 5, 6, 7);



void setup(){  
  tmrpcm.speakerPin = 9;                  //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
  
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    
    return;                               //don't do anything more if not
    }
  tmrpcm.setVolume(6);                    //0 to 7. Set volume level
  
  lcd.begin(16, 2);
  lcd.setCursor(LCDRow, 0);
  lcd.print("PHOENIX");
  lcd.setCursor(LCDRow, 1);
  lcd.print("WELCOMES YOU");
  delay(5000) ;
  lcd.setCursor(LCDRow, 0);
  lcd.print("DECODE AND ENTER");
  lcd.setCursor(LCDRow, 1);
  lcd.print("THE PASSWORD");
  }
  
void loop(){
  
  char key = customKey.getKey();
  
  if (key){
    lcd.clear();
    lcd.print(key);
    Code[keyCount] = key;
    keyCount++;
  }
  if(keyCount == codeLength - 1){
    
    if(!strcmp(Code,password)){
      delay(300);
      lcd.clear();
      lcd.print("HAPPY FOUNDER'S");
      lcd.setCursor(LCDRow, 1);
      lcd.print("DAY!");
      tmrpcm.play("1.wav");         //the sound file "1" will play saying "HAPPY FOUNDER'S DAY"
      delay(5000); 
      lcd.clear();
    }
       else{
         delay(300);
         lcd.clear();
         lcd.print("INCORRECT PASS-");
         lcd.setCursor(LCDRow, 1);
         lcd.print("KEY! TRY AGAIN");
         tmrpcm.play("2.wav");         //the sound file "2" will play saying "INCORRECT PASS-KEY! TRY AGAIN"
         delay(1500);
         lcd.clear();
       }
    
    deleteCount();
  }
}

void deleteCount(){
  while(keyCount != 0){
    Code[keyCount--] = 0;
  }
  return;
}
