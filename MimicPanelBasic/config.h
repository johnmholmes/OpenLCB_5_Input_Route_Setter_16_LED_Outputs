/*
 Node ID --- this must come from a range controlled by the user.
 See: http://registry.openlcb.org/uniqueidranges
 To choose a new NODEID edit this address
*/
#define NODE_ADDRESS 0x05,0x01,0x01,0x01,0x8E,0x05  // DIY range example, not for global use.

/* Set to 1 to Force Reset to Factory Defaults, else 0.
 This needs to be done at least once for each new board.
*/
#define RESET_TO_FACTORY_DEFAULTS 0

// ================================================================

//#define EEPROMSIZE 4096
#define GROUP_SIZE 5
#define NUM_GROUPS 1
#define NUM_INPUTS 5   // CALC BY HAND number of input buttons + Number routes required, requires to match the "pin definition"
#define NUM_TURNOUTS 8  // number of turnouts in a route changing this requires to the CDI & Memstruct 
#define NUM_OUTPUTS 12
const uint8_t outputPins[NUM_OUTPUTS] = {19,21, 22, 23, 13, 12, 14, 27, 26, 25, 33, 32};

#define NUM_EVENT (NUM_INPUTS + NUM_INPUTS * NUM_TURNOUTS + 3619) 


// check the above is right:
static_assert(NUM_INPUTS == (GROUP_SIZE * NUM_GROUPS), "NUM_INPUTS must equal GROUP_SIZE * NUM_GROUPS!");

// Pin definitions, if there is no pin assigned use 255
uint8_t pin[NUM_INPUTS] = { 4,16,17,5,18};            // for ESP32 
//uint8_t pin[NUM_INPUTS] = {39,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 }; // for Atom



/* Send GC to Serial
 To allow direct to JMRI via USB, without CAN controller,
 note: disable debugging if this option is chosen
*/
//#include "GCSerial.h"
//#define NOCAN    
//#define DEBUG Serial 

/*
 If using Can you can use the serial monitor for debugging during development
 uncomment the #define DEBUG Serial above
*/

/*
 Board definitions Keep short text within the " " if making alterations.
*/

#define MANU "J Holmes"         // The manufacturer of node
#define MODEL "ESP32"           // The model of the board
#define HWVERSION "ESP32 Dev1"  // Hardware version
#define SWVERSION "1.0.0"         // Software version

/*
  ************** End of USER DEFINTIONS *****************************
*/




