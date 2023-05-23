#include <MPU6050_tockn.h>
#include <Wire.h>
#include <MIDI.h>
#include <LiquidCrystal.h>

//accelerometer vars
MPU6050 mpu6050(Wire);
long timer = 0;
float avg_acc = 0;

//ultrasound vars
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance=0;
int d=50;

//Midi init
MIDI_CREATE_DEFAULT_INSTANCE();
int k = 12;
int vel = 127;

//button pin init
const int index = 2;
const int middle = 3;
const int ring = 4;
const int pinky = 5;

//LCD
const int rs = 13;
const int en = 12;
const int d4 = 11;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
 //MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);

  //ultra
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //accele
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  //butons pins
  pinMode(index, INPUT);
  pinMode(middle, INPUT);
  pinMode(ring, INPUT);
  pinMode(pinky, INPUT);

  //LCD
  lcd.begin(16, 2); 
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, 30000);
  // Calculating the distance
  distance = duration * 0.034;
 
  if (distance != 0){
     d = distance;
   }
  // Serial.print("Distance: ");
  // Serial.println(distance);

  mpu6050.update();

  if(millis() - timer > 100){ 
    avg_acc = sqrt(pow(mpu6050.getAccX(),2) + pow(mpu6050.getAccY(),2) +pow(mpu6050.getAccZ(), 2));
    
   // Serial.print("avacc");
    //Serial.println(avg_acc);

    timer = millis();
  }
  
  if (avg_acc >= 1.9){
    //vel = 52.2 * avg_acc;    
    if (digitalRead(index) == HIGH){
      if(d >= 45){
        // C
        MIDI.sendNoteOn(60-k, vel, 1);
        MIDI.sendNoteOn(64-k, vel, 1);
        MIDI.sendNoteOn(67-k, vel, 1);
        MIDI.sendNoteOn(76-k, vel, 1);
        MIDI.sendNoteOn(55-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("C chord");
      }
      else{
        // F
        MIDI.sendNoteOn(65-k, vel, 1);
        MIDI.sendNoteOn(69-k, vel, 1);
        MIDI.sendNoteOn(60-k, vel, 1);
        MIDI.sendNoteOn(53-k, vel, 1);
        MIDI.sendNoteOn(48-k, vel, 1);
        MIDI.sendNoteOn(77-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("F chord");   
      }
      delay(250);
    }
    else if (digitalRead(middle) == HIGH){
      if(d >= 45){
        // A
        MIDI.sendNoteOn(69-k, vel, 1);
        MIDI.sendNoteOn(61-k, vel, 1);
        MIDI.sendNoteOn(64-k, vel, 1);
        MIDI.sendNoteOn(57-k, vel, 1);
        MIDI.sendNoteOn(76-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("A chord");
      }
      else{
        // Am
        MIDI.sendNoteOn(64-k, vel, 1);
        MIDI.sendNoteOn(57-k, vel, 1);
        MIDI.sendNoteOn(76-k, vel, 1);
        MIDI.sendNoteOn(65-k, vel, 1);
        MIDI.sendNoteOn(81-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Am chord");
      }
      delay(250);
    }
    else if (digitalRead(ring) == HIGH){
      if (d >= 45){
        //E
        MIDI.sendNoteOn(64-k, vel, 1);
        MIDI.sendNoteOn(68-k, vel, 1);
        MIDI.sendNoteOn(71-k, vel, 1);
        MIDI.sendNoteOn(52-k, vel, 1);
        MIDI.sendNoteOn(76-k, vel, 1);
        MIDI.sendNoteOn(59-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("E chord");
      }
      else{
        //Em
        MIDI.sendNoteOn(64-k, vel, 1);
        MIDI.sendNoteOn(67-k, vel, 1);
        MIDI.sendNoteOn(71-k, vel, 1);
        MIDI.sendNoteOn(52-k, vel, 1);
        MIDI.sendNoteOn(76-k, vel, 1);
        MIDI.sendNoteOn(59-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Em chord");        
      }
      delay(250);
    }
    else if (digitalRead(pinky)  == HIGH){
      if (d >=45){
        //G
        MIDI.sendNoteOn(67-k, vel, 1);
        MIDI.sendNoteOn(71-k, vel, 1);
        MIDI.sendNoteOn(62-k, vel, 1);
        MIDI.sendNoteOn(55-k, vel, 1);
        MIDI.sendNoteOn(59-k, vel, 1);
        MIDI.sendNoteOn(79-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("G chord"); 
      }
      else{
        //D
        MIDI.sendNoteOn(62-k, vel, 1);
        MIDI.sendNoteOn(66-k, vel, 1);
        MIDI.sendNoteOn(69-k, vel, 1);
        MIDI.sendNoteOn(50-k, vel, 1);
        MIDI.read();

        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("D chord");
      }
      delay(250);
    }
  }
}