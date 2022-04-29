/* nanunauta */

#include "pitches.h"

bool WORKING = false;

byte BUZZER = 5;
byte BUTTON = 4;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

float calibrationFactor = 7.5;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

const unsigned long FALTA_POCO = 60000L;
const unsigned long LIMIT_BUZZER = 60800L;

const unsigned long TANQUE_LLENO = 69200L;

void setup()
{

  playOn();
   
  // Set up the status LED line as an output
  pinMode(LED_BUILTIN, OUTPUT);
    
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pinMode(BUTTON, INPUT_PULLUP);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}


void loop() {

   int buttonState = digitalRead(BUTTON);
   
   if(buttonState == LOW) { 
      WORKING = true;   
      playOn();

      pulseCount        = 0;
      flowRate          = 0.0;
      flowMilliLitres   = 0;
      totalMilliLitres  = 0;
      oldTime           = 0;
    }
  
   if(WORKING) {

     digitalWrite(LED_BUILTIN,  HIGH); 
     
     if((millis() - oldTime) > 1000) {  
     
      detachInterrupt(sensorInterrupt);
          
      flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
      
      oldTime = millis();
      
      flowMilliLitres = (flowRate / 60) * 1000;
      
      totalMilliLitres += flowMilliLitres;
        
      unsigned int frac;

      if(totalMilliLitres >= FALTA_POCO && totalMilliLitres <= LIMIT_BUZZER ){
        
        playAlmost();
            
      };
  
      if(totalMilliLitres >= TANQUE_LLENO){
        
        playMelody();
        delay(1000);
        playMelody();
        delay(1000);
        playMelody();
        delay(1000);
        playMelody();
        delay(1000);
        playMelody();

        pulseCount        = 0;
        flowRate          = 0.0;
        flowMilliLitres   = 0;
        totalMilliLitres  = 0;
        oldTime           = 0;
        digitalWrite(BUTTON, HIGH);
        digitalWrite(LED_BUILTIN, LOW); 
        
        WORKING = !WORKING;
            
      };
      
      pulseCount = 0;
      
      attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
  }        
}

void pulseCounter()
{
  pulseCount++;
}

void playMelody() {

  int melody[] = {
    NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5
  };
  
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  for (int thisNote = 0; thisNote < 8; thisNote++) {  
  
      int noteDuration = 1000 / noteDurations[thisNote];
  
      tone(BUZZER, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
  
      delay(pauseBetweenNotes);
  
      noTone(BUZZER);
  };
  
}

void playOn() {

  int melody[] = {
    NOTE_G4, 0, NOTE_G4, NOTE_D5
  };
  
  int noteDurations[] = {
    8, 8, 8, 4
  };

  for (int thisNote = 0; thisNote < 4; thisNote++) {  
  
      int noteDuration = 1000 / noteDurations[thisNote];
  
      tone(BUZZER, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
  
      delay(pauseBetweenNotes);
  
      noTone(BUZZER);
  };
  
}

void playAlmost() {

  int melody[] = {
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5
  };
  
  int noteDurations[] = {
    8, 8, 8, 4
  };

  for (int thisNote = 0; thisNote < 4; thisNote++) {  
  
      int noteDuration = 1000 / noteDurations[thisNote];
  
      tone(BUZZER, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
  
      delay(pauseBetweenNotes);
  
      noTone(BUZZER);
  };
  
}

void playWrong() {

  int melody[] = {
    NOTE_F5, 0, NOTE_F5, NOTE_C3
  };
  
  int noteDurations[] = {
    8, 8, 8, 4
  };

  for (int thisNote = 0; thisNote < 4; thisNote++) {  
  
      int noteDuration = 1000 / noteDurations[thisNote];
  
      tone(BUZZER, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
  
      delay(pauseBetweenNotes);
  
      noTone(BUZZER);
  };
  
}
