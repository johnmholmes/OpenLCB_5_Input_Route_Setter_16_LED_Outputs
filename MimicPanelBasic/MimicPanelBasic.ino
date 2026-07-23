/* Node 5 Mimic Panel ESP32 Devkit 1
==============================================================
  OpenLCB Hybrid Node:
    - 5 Route Input Buttons (Producers/Consumer)
    - 12 Mimic Panel Outputs (Consumers with HIGH, LOW, 300ms FLASH)

  Input Pins 4,16,17,5,18
  Output Pins: 19, 21, 22, 23, 13, 12, 14, 27, 26, 25, 33, 32

  Tested with the 
  ESP32 board manager 3.3.10 + 3.3.11
  OpenLCB_Single_Thread libaray 0.1.19


==============================================================
*/

#include "config.h"               // User defined options
#include "mdebugging.h"           // Debugging macros
#include "processor.h"            // Processor auto-selection
#include "OpenLCBHeader.h"        // System housekeeping
#include "boardChoices.h"         // Board selection
#include "memstruct.h"            // Memory definitions



// Indicator States
enum PinState {
  STATE_OFF = 0,
  STATE_ON  = 1,
  STATE_FLASH = 2
};

PinState pinStates[NUM_OUTPUTS];
bool flashToggle = false;
unsigned long lastFlashTime = 0;
const unsigned long FLASH_INTERVAL = 300; // 300ms flash speed

extern "C" {
#define N(x) xN(x)
#define xN(x) #x

// ===== CDI (Configuration Description Information) =====
const char configDefInfo[] PROGMEM =
  CDIheader R"(
    <group replication=')" N(NUM_GROUPS) R"('>
      <name>Route Setter (Inputs)</name>
      <repname>Group </repname>
      <description>Define route events triggered by input buttons</description>
      <group replication=')" N(GROUP_SIZE) R"('>
        <name>Routes controlled by input buttons</name>
        <repname>Route </repname>
        <string size='24'><name>Description</name></string>
        <eventid><name>Triggering Event</name></eventid>
        <group replication=')" N(NUM_TURNOUTS) R"('>
          <name>Turnout Events</name>
          <repname>Trigger Turnout </repname>
          <eventid></eventid>
        </group>
      </group>
    </group>

    <group>
            <name>Global Delay Between Triggers</name>
            <hints><visibility hideable='yes' hidden='yes' ></visibility></hints>     
            <description>Possible choices between 0-2000ms in 100ms steps</description>
            <int size='1'><name>Choose one value and click write to save the new value</name>
              <map>
                <relation><property>0</property><value>None</value></relation> 
                <relation><property>1</property><value>100ms</value></relation> 
                <relation><property>2</property><value>200ms</value></relation> 
                <relation><property>3</property><value>300ms</value></relation>
                <relation><property>4</property><value>400ms</value></relation>
                <relation><property>5</property><value>500ms</value></relation>
                <relation><property>6</property><value>600ms</value></relation>
                <relation><property>7</property><value>700ms</value></relation>
                <relation><property>8</property><value>800ms</value></relation>
                <relation><property>9</property><value>900ms</value></relation>
                <relation><property>10</property><value>1000ms</value></relation>
                <relation><property>11</property><value>1100ms</value></relation>
                <relation><property>12</property><value>1200ms</value></relation>
                <relation><property>13</property><value>1300ms</value></relation>
                <relation><property>14</property><value>1400ms</value></relation>
                <relation><property>15</property><value>1500ms</value></relation>
                <relation><property>16</property><value>1600ms</value></relation>
                <relation><property>17</property><value>1700ms</value></relation>
                <relation><property>18</property><value>1800ms</value></relation>
                <relation><property>19</property><value>1900ms</value></relation>
                <relation><property>20</property><value>2000ms</value></relation>
              </map>
            </int>
         </group>

<!-- ================= OUTPUT INDICATORS SECTION ================= -->
<group>
  <name>Mimic Indicators (Outputs)</name>
  <description>Events for controlling physical outputs (HIGH, LOW, FLASH)</description>

  <group replication="6">
    <name>Outputs Group 1 (Outputs 1 - 6)</name>
    <repname>Indicator </repname>
    <description>Outputs on Pins 19, 21, 22, 23, 13, 12, 14</description>

    <string size='24'><name>Description</name></string>
    <eventid><name>Event 1: Turn ON (HIGH)</name></eventid>
    <eventid><name>Event 2: Turn OFF (LOW)</name></eventid>
    <eventid><name>Event 3: Flash (300ms)</name></eventid>
  </group>

  <group replication="6">
    <name>Outputs Group 2 (Outputs 7 - 12)</name>
    <repname>Indicator </repname>
    <description>Outputs on Pins 14, 27, 26, 25, 33, 32</description>

    <string size='24'><name>Description</name></string>
    <eventid><name>Event 1: Turn ON (HIGH)</name></eventid>
    <eventid><name>Event 2: Turn OFF (LOW)</name></eventid>
    <eventid><name>Event 3: Flash (300ms)</name></eventid>
  </group>

</group>

    
  )" CDIfooter;
}

// ===== MemStruct =====
typedef struct {
  EVENT_SPACE_HEADER eventSpaceHeader; // MUST BE AT TOP
  char nodeName[20];
  char nodeDesc[24];
  
  // Input Route Definitions
  struct {
    char desc[24];
    EventID consumer;
    EventID to[NUM_TURNOUTS];
  } inputs[NUM_INPUTS];

  uint8_t turnoutDelay;

  // Output Indicator Definitions
  struct {
    char desc[24];
    EventID eventOn;    // HIGH
    EventID eventOff;   // LOW
    EventID eventFlash; // 300ms FLASH
  } indicators[NUM_OUTPUTS];

  
} MemStruct;

extern "C" {
  /* ===== Event Table =====
     ACTIONEID generates events for the 5 route input buttons.
     INDICATORS_11_EID generates events for the 11 output indicators.
  */
  const EIDTab eidtab[NUM_EVENT] PROGMEM = {
    ACTIONEID(NUM_INPUTS, NUM_TURNOUTS),
    INDICATORS_12_EID
  };

  extern const char SNII_const_data[] PROGMEM = "\001" MANU "\000" MODEL "\000" HWVERSION "\000" SWVERSION " " OlcbCommonVersion;
};

// Protocol Identification
uint8_t protocolIdentValue[6] = {
  pSimple | pDatagram | pMemConfig | pPCEvents | !pIdent | pTeach | !pStream | !pReservation,
  pACDI | pSNIP | pCDI | !pRemote | !pDisplay | !pTraction | !pFunction | !pDCC,
  0, 0, 0, 0
};

uint16_t turnoutDelay = 0;
uint8_t actionIndex[NUM_INPUTS] = {0};

// --- Input & Route Handling ---
void processInputs() {
  static long last = 0;
  if ((millis() - last) < 250) return;
  last = millis();
  for (int i = 0; i < NUM_INPUTS; i++) {
    if (pin[i] == 255) continue;
    if (digitalRead(pin[i]) == LOW && actionIndex[i] == 0) {
      dP("\nButton pushed "); dP(i); dP(" pin="); dP(pin[i]);
      actionIndex[i] = NUM_TURNOUTS;
    }
  }
}

void processTurnouts() {
  static long last = 0;
  static int i = 0;
  if ((millis() - last) < turnoutDelay) return;
  if (actionIndex[i] > 0) {
    OpenLcb.produce((i + 1) * (NUM_TURNOUTS + 1) - actionIndex[i]);
    dP("\n Produce turnout event "); dP((i + 1) * NUM_TURNOUTS - actionIndex[i]);
    actionIndex[i]--;
    last = millis();
  } else {
    if (++i >= NUM_INPUTS) i = 0;
  }
}

// --- Output Indicator Handling ---
void processOutputs() {
  unsigned long currentMillis = millis();

  // Toggle flash clock
  if (currentMillis - lastFlashTime >= FLASH_INTERVAL) {
    lastFlashTime = currentMillis;
    flashToggle = !flashToggle;
  }

  // Update physical pin state
  for (int i = 0; i < NUM_OUTPUTS; i++) {
    switch (pinStates[i]) {
      case STATE_ON:
        digitalWrite(outputPins[i], HIGH);
        break;

      case STATE_OFF:
        digitalWrite(outputPins[i], LOW);
        break;

      case STATE_FLASH:
        digitalWrite(outputPins[i], flashToggle ? HIGH : LOW);
        break;
    }
  }
}

// Callback for incoming consumed events
void pceCallback(uint16_t index) {
  uint16_t routeEventCount = NUM_INPUTS * (NUM_TURNOUTS + 1);

  // Check if event belongs to route input triggers
  if (index < routeEventCount) {
    dP("\n Route pceCallback index="); dP(index);
    uint8_t i = index / (NUM_TURNOUTS + 1);
    actionIndex[i] = NUM_TURNOUTS;
  } 
  // Otherwise event belongs to output indicators
  else {
    uint16_t outputIndex = index - routeEventCount;
    uint8_t pinIndex = outputIndex / 3;
    uint8_t eventType = outputIndex % 3;

    if (pinIndex < NUM_OUTPUTS) {
      if (eventType == 0) {
        pinStates[pinIndex] = STATE_ON;
        dP("\nIndicator "); dP(pinIndex); dP(" -> HIGH");
      } else if (eventType == 1) {
        pinStates[pinIndex] = STATE_OFF;
        dP("\nIndicator "); dP(pinIndex); dP(" -> LOW");
      } else if (eventType == 2) {
        pinStates[pinIndex] = STATE_FLASH;
        dP("\nIndicator "); dP(pinIndex); dP(" -> FLASH (300ms)");
      }
    }
  }
}

void userInitAll() {
  NODECONFIG.put(EEADDR(nodeName), ESTRING("Route/Mimic Node"));
  NODECONFIG.put(EEADDR(nodeDesc), ESTRING("5-In / 12-Out"));
  NODECONFIG.write(EEADDR(turnoutDelay), 4);

  for (int i = 0; i < NUM_INPUTS; i++) {
    if (pin[i] < 255) {
      String s = "Input Pin " + String(pin[i]);
      NODECONFIG.put(EEADDR(inputs[i].desc), s);
    } else {
      NODECONFIG.put(EEADDR(inputs[i].desc), ESTRING("No pin"));
    }
  }

  for (int i = 0; i < NUM_OUTPUTS; i++) {
    String s = "Output Pin " + String(outputPins[i]);
    NODECONFIG.put(EEADDR(indicators[i].desc), s);
  }
}

void userSoftReset() {
  dP("\n In userSoftReset()"); Serial.flush();
  REBOOT;
}

void userHardReset() {
  dP("\n In userHardReset()"); Serial.flush();
  REBOOT;
}

void userConfigWritten(uint32_t address, uint16_t length, uint16_t func) {
  dP("\nuserConfigWritten "); dPH((uint32_t)address);
  turnoutDelay = NODECONFIG.read(EEADDR(turnoutDelay)) * 100;
}

NodeID nodeid(NODE_ADDRESS);
#include "OpenLCBMid.h"

// ==== Setup =========================================================
void setup() {
  EEPROM.begin(EEPROMSIZE);
  Olcb_init(nodeid, RESET_TO_FACTORY_DEFAULTS);

  // Setup Input Pins
  for (int i = 0; i < NUM_INPUTS; i++) {
    if (pin[i] < 255) {
      pinMode(pin[i], INPUT_PULLUP);
    }
    actionIndex[i] = 0;
  }

  // Setup Output Pins
  for (int i = 0; i < NUM_OUTPUTS; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
    pinStates[i] = STATE_OFF;
  }

  turnoutDelay = NODECONFIG.read(EEADDR(turnoutDelay)) * 100;
  dP("\nSetup Complete. Turnout Delay: "); dP(turnoutDelay);
}

// ==== Main Loop =====================================================
void loop() {
  Olcb_process();      // Process CAN communications
  processInputs();     // Scan input buttons
  processTurnouts();   // Emit scheduled route events
  processOutputs();    // Refresh indicator LED states
}