#include <Servo.h>                // include the servo library
#include "pitches.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const int SPEAKER=6;  //Speaker Pin

const int leftLDR = A1;                  // left LDR attached to analog pin 1

const int rightLDR = A0;                  //right LDR attached to analog pin 0

int leftValue;                            // this variable is used to store the analog value r

int rightValue;                            // this variable is used to store the analog value r

int difference;                         // this varaible is used to compare the difference i

Servo leftServo;                           //create a servo object for the left servo

Servo rightServo;                          //create a servo object for the right servo

const int Direction1 = 0;      //////these variable stores the value of the amount of degrees being changed on a servo//////

const int Direction2 = 180;
////////////////////////////Arrays to store notes and durations for sound when car moves forward/////
//Note Array
int notes[] = {
 NOTE_A4, NOTE_E3, NOTE_A4, 0, 
 NOTE_A4, NOTE_E3, NOTE_A4, 0,
 NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
 NOTE_E4, NOTE_E3, NOTE_A4, 0
};

//The Duration of each note (in ms)
int times[] = {
 62.5, 62.5, 62.5, 62.5, 
 62.5, 62.5, 62.5, 62.5,
 31.25, 31.25, 31.25, 31.25, 31.25, 31.25, 31.25, 31.25,
 62.5, 62.5, 62.5, 62.5, 
};

/////////////////Arrays to store notes and durations for sound when car moves right/////////
//melody Array
int melody[] = {
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_DS5,NOTE_D5,NOTE_B4,NOTE_A4,NOTE_B4,
  NOTE_E4,NOTE_G4,NOTE_DS5,NOTE_D5,NOTE_G4,NOTE_B4,
  NOTE_B4,NOTE_FS5,NOTE_F5,NOTE_B4,NOTE_D5,NOTE_AS5,
  NOTE_A5,NOTE_F5,NOTE_A5,NOTE_DS6,NOTE_D6,NO_SOUND
};

//The Duration of each note (in ms)
int noteDurations[] = {
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,2,8,8,1,
  8,4,8,4,8,8,
  8,8,4,8,4,8,
  4,8,4,8,3
};

int pace = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000; // change pace of music("speedy")

/////////////////Arrays to store notes and durations for sound when car moves left/////////
//Mario main theme melody
int mario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo (duration)
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};








void setup()

{
  
  leftServo.attach(9);                          //left servo is attached to digital pin 6
  
  rightServo.attach(8);                         //right servo is attached to digital pin 8
  
  leftServo.write(90);                          //stop left servo
  
  rightServo.write(90);                         //stop right servo
    


   lcd.begin(16,2);
   lcd.clear();
  

}




void loop()

{
  
    rightValue = analogRead(rightLDR);            //store value from A0 into the variable rightValue
  
    leftValue = analogRead(leftLDR);              //store value from AI into the variable leftValue
  
    difference = abs(rightValue - leftValue);     //calculate the difference between the two values
  
    if(difference < 50)                          //if the difference is less than 50 then...
  
      {
    
        moveForward();                            //the robot will move forward
        
        musicForward();
        
           
             
             
              lcd.setCursor(0,0);
              lcd.print("FORWARD!");
              lcd.print(" LETITGO");
              lcd.setCursor(0,1);
              lcd.print("LFT:");
              lcd.print(leftValue);
              lcd.print("RGT:");
              lcd.print(rightValue);
        }
  
     else                                        //if not then...
  
       {
     
     if(rightValue > leftValue)              //is it darker on the right hand side?

        {
    
          moveLeft();    //light follow                              //if so then turn left
          
          //moveRight();    //light avoid
          
         musicLeft();
             
           
           
              lcd.setCursor(0,0);
              lcd.print("RIGHT!");
              lcd.print(" SUPERMARIO");
              lcd.setCursor(0,1);
              lcd.print("LFT:");
              lcd.print(leftValue);
              lcd.print(" RGT:");
              lcd.print(rightValue);
              
        }
  
        else
  
        {
    
        moveRight();  //light follow                    ..if it isn't then turn right
        
        //moveLeft();    //light avoid
        
        musicRight();
            
             
              lcd.setCursor(0,0);
              lcd.print("LEFT!");
              lcd.print(" JAMESBOND");
              lcd.setCursor(0,1);
              lcd.print("LFT:");
              lcd.print(leftValue);
              lcd.print("RGT:");
              lcd.print(rightValue);
      
       }
     
     }



}


//below are the movement voids. A write angle of 0 means full speed in one direction and 180 means full speed in the other

void moveForward()

{
  
  leftServo.write(Direction2);
  
  rightServo.write(Direction1);                                                          
}


void moveLeft()

{
  
  leftServo.write(Direction2);
  
  rightServo.write(Direction2);
  
}


void moveRight()

{
  
    leftServo.write(Direction1);
    
    rightServo.write(Direction1);
    
}


////////////below are the music voids. Each void accesses an array of notes and times. This allows Ben to play 3 different tunes depending on the direction it is moving in///////////

void musicForward()

{

  //Play each note for the right duration - this sound plays when Ben moves forward
        for (int i = 0; i < 20; i++)
         {
          tone(SPEAKER, notes[i], times[i]);
          delay(times[i]);
         }
  
}


void musicLeft()

{
 
  //Play each note for the right duration - this sound plays when Ben moves left
          for (int h = 0; h < 78; h++)
           {
            tone(SPEAKER, mario[h], tempo[h]);
            delay(tempo[h]);
           } 
                                                           
}


void musicRight()

{
  
   for (int Note = 0; Note <54; Note++) {//counter of Notes (54 limit of the array)
           int duration = pace/noteDurations[Note];//Adjust duration with the pace of music
           tone(SPEAKER, melody[Note],duration); //Play note

            // to distinguish the notes, a minimum time is set between them.
            delay(duration*1.1);

  
}

}

