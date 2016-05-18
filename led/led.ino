#include <Brain.h>

// Arduino Brain Library - Brain Serial Test

// Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)
// More info: https://github.com/kitschpatrol/Arduino-Brain-Library
// Author: Eric Mika, 2010 revised in 2014

#include <Brain.h>
int att;
int theta;
int signalLed = 11;
int attentionLed = 10;
int okLed = 9;
int readSignalQuality;
int readAttention;
int readMeditation;
int readTheta;
// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

void setup() {
    // Start the hardware serial.
    Serial.begin(9600);
    pinMode(attentionLed, OUTPUT);
    pinMode(signalLed, OUTPUT);
    pinMode(okLed, OUTPUT);
    
}

void loop() {
    // Expect packets about once per second.
    // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
    // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"    

        //Serial.println(brain.readErrors());
     if( brain.update())
     {
      readSignalQuality = brain.readSignalQuality();
      if(readSignalQuality == 0)
      {
        digitalWrite(signalLed, HIGH);
        digitalWrite(okLed, LOW);
      }
      else if(readSignalQuality > 0 && readSignalQuality <= 27)
      {
        digitalWrite(okLed, HIGH);
        digitalWrite(signalLed, LOW);
      }
      else
      {
        digitalWrite(signalLed, LOW);
        digitalWrite(okLed, LOW);
      }
      readAttention = brain.readAttention();
        
        Serial.println(readSignalQuality);
        brain.readCSV();   
    
        att = (readAttention * 255) / 100;
 
        if(att > 225)
          att = 225;
        if(att < 0)
          att = 0;

        //att = att * 1.2;
        Serial.print("Attention: ");
        Serial.println(att);
        analogWrite(attentionLed, att);
        
        
     }
  
    
}
