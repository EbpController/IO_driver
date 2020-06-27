// this project is part of the 'EBP controller' solution
//
// the interface has 6 digital inputs with pullup and 6 digital push-pull outputs
// the 6 inputs are connected to port D bit 2 to bit 7 (input 0 to 5)
// the 6 outputs are connected to port B bit 0 to bit 5 (output 0 to 5)
// for communication, to control the IO pins, we use the EBP serial bus
//
// written by: Jan van Hooydonk
//
// version: 1.0   date: 27/06/2020    comment: creation
//

// included libraries
//
#include "EbpSerial.h"

#define ADDRESS_HIGH 0b0011
byte inputValuesPortD;
byte oldInputValuesPortD;

// EbpSerial
int myAddress;
EbpSerial EbpSerial;

void setup()
{
  // set bits 0 to 5 of port B as push-pull output, without changing the state of bits 6 and 7
  DDRB |= 0b00111111;

  // set bits 0 to 5 of port C as inputs with pullup, without changing the state of bits 6 and 7
  DDRC &= 0b11000000;
  PORTC |= 0b00111111;

  // set bits 2 to 7 of port D as inputs with pullup, without changing the state of bits 0 and 1
  DDRD &= 0b00000011;
  PORTD |= 0b11111100;

  // read input value from port B
  oldInputValuesPortD = PINB & 0b00111111;

  // setup serial port
  myAddress = (ADDRESS_HIGH << 6) + ((PINC ^ 0b11111111) & 0b00111111);
  EbpSerial.init(myAddress);
}

void loop()
{
  // poll EBP serial bus
  byte receivedData = EbpSerial.poll();

  if (receivedData != 0xff) {
    // drive output (from output pin 8 to pin 13 = port D bit 2 to bit 7) 
    byte outputPin = 8 + ((receivedData >> 1) & 0b111) ;
    if ((receivedData & 1) == 1) {
      digitalWrite(outputPin, HIGH);
    }
    else {
      digitalWrite(outputPin, LOW);
    }
  }

  // poll inputs
  inputValuesPortD = (PIND >> 2) & 0b00111111;
  // if input(s) state changed then analyse the input(s)
  if (inputValuesPortD != oldInputValuesPortD) {
    analyzeInputValues(inputValuesPortD, oldInputValuesPortD);
    oldInputValuesPortD = inputValuesPortD;
  }
}

void analyzeInputValues(byte inputValuesPortD, byte oldInputValuesPortD)
{
  byte changedInputValuesPortD = inputValuesPortD ^ oldInputValuesPortD;

  for (int i = 0; i < 6; i++) {
    // look only to the values(s) of the changed input(s)
    if ((changedInputValuesPortD & (1 << i)) != 0) {
      if ((inputValuesPortD & (1 << i)) == 0) {
        EbpSerial.sendData((i << 1) & 0b00001110);
      }
      else {
        EbpSerial.sendData(((i << 1) & 0b00001110) | 1);
      }
    }
  }
}
