/* Testing nRF24L01 Receive Joystick values to NRF24l01 Module
  
   1 - GND 
   2 - VCC 3.3V /* WARNING SHOULD BE 3.3v Not 5V 
   3 - CE - Arduino pin 9
   4 - CSN - Arduino pin 10
   5 - SCK - Arduino pin 13
   6 - MOSI - Arduino pin 11
   7 - MISO - Arduino pin 12
   8 - UNUSED 

/*----- Import all required Libraries -----*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


/*----- Declare all constant pin to be used ----*/

#define CE_PIN   9
#define CSN_PIN 10

Servo myservo;  // create servo object to control a servo

const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module

int val;

/*-----Object Declaration ----*/

RF24 radio(CE_PIN, CSN_PIN); // Activate the Radio

/*-----Declaration of Variables -----*/

int joystick[2];  //  Two element array holding the Joystick readings

int pinA = 7; //define I1 interface
int pinB = 6; //define I2 interface
int speedpinA = 5; //enable motor A
int fspeed = 0; //define the forward spead of motor
int bspeed = 0; //define the backward spead of motor

void setup()  
{  pinMode(pinA, OUTPUT);
   pinMode(pinB, OUTPUT);
   pinMode(speedpinA, OUTPUT);
  
  Serial.begin(9600); /* Opening the Serial Communication */
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();;

  myservo.attach(8);
}//--(end setup )---


void loop()   
{
  if ( radio.available() )
  {
    // Reading the data payload until the RX received everything
    bool done = false;
    while (!done)
    {
      // Fetching the data payload
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);
      
      val = (joystick[0]);
      val = map(val, 0, 1023, 20, 90);
      myservo.write(val);
      delay(15);

      if(joystick[1] <= 510){
      fspeed = map(joystick[1], 520, 0, 0, 255);
      digitalWrite(pinB, LOW); 
      digitalWrite(pinA, HIGH);
      analogWrite(speedpinA, fspeed); 
  
   }

else if(joystick[1] >= 590){
      bspeed = map(joystick[1], 518, 1023, 0, 255);
      digitalWrite(pinA, LOW); 
      digitalWrite(pinB, HIGH);
      analogWrite(speedpinA, bspeed); 
   }
else{
      digitalWrite(pinB, LOW); 
      digitalWrite(pinA, LOW);
      analogWrite(speedpinA, 0);
}


      
    }
  }
  else
  {    
      Serial.println("No radio available");
      myservo.write(55);
      digitalWrite(pinB, LOW); 
      digitalWrite(pinA, LOW);
      analogWrite(speedpinA, 0);
  }

  

}


