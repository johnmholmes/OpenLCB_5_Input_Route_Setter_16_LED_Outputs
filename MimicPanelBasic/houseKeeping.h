/* 
Do not delete any of these as it will brake the sketch
*/

  #ifdef DEBUG
    // set up serial comm; may not be space for this!
    Serial.begin(115200); while(!Serial); delay(250);
    dP("\nOlcbBasicNode\n");
    delay(1000);
  #endif

#ifdef DEBUG
  static unsigned long T = millis() + 5000;
  if (millis() > T) {
    T += 5000;
    //dP("\n.");
  }
#endif

//#ifndef OLCB_NO_BLUE_GOLD // Do not delete 

// ===== Blue/Gold =====
// Blue-gold refers to two standard buttons offering a rudimentary control ssystem for an node.
//   Features: teaching/learning of eventids; node identification; node reset.

// Board choices, each has differing i/o choices
    //#include "boardChoices.h"

// This section uses the ButtonLed lib to muliplex an input and output onto a single pin.
// It includes sampling the pin every 32 ms, and implements blink patterns.

// Patterns
// Each pattern is 32 bits, each bit is used sequencely to blink the LED on and off, at 64 ms per bit.
    #define ShortBlinkOn   0x00010001L
    #define ShortBlinkOff  0xFFFEFFFEL
    
    uint32_t patterns[] = { // two per channel, one per event
      ShortBlinkOff,ShortBlinkOn,
      ShortBlinkOff,ShortBlinkOn,
      ShortBlinkOff,ShortBlinkOn,
      ShortBlinkOff,ShortBlinkOn
    };

// An array of buttons/leds, pA etc are defined in boardChoices.h
    ButtonLed* buttons[] = {
      &pA,&pA,&pB,&pB,&pC,&pC,&pD,&pD // One for each event; each channel is a pair
    };

  #ifndef OLCB_NO_BLUE_GOLD
    if (activity) {
      // blink blue to show that the frame was received
      //P("\nrcv");
      blue.blink(0x1);
    }
    if (olcbcanTx.active) { // set when a frame sent
      gold.blink(0x1);
      //P("\nsnd");
      olcbcanTx.active = false;
    }
    // handle the status lights
    blue.process();
    gold.process();
  
  // process inputs
  if(produceFromInputs) produceFromInputs();
  #endif //OLCB_NO_BLUE_GOLD

