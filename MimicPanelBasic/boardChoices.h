// Board choices available

#define ESP32_BOARD
//#define ATOM_BOARD

#ifdef defined(ATOM_BOARD)
  #pragma message ("ATOM_BOARD")
  #ifndef ARDUINO_M5STACK_ATOM
    #error message("USE_ATOM was selected, so must use a M5Stack Atom processor.")
  #endif
  #define BOARD "Atom"
  #define NUM_NATIVE_IO 3
  #define IOPINS        39,22,19  // 39 is the top button, the led is a smart RGB
  #define CAN_TX_PIN    (gpio_num_t)26
  #define CAN_RX_PIN    (gpio_num_t)32
  #ifndef USEGCSERIAL
    #include "ACAN_ESP32Can.h"
  #endif // USEGCSERIAL
  #define EEPROMSIZE 4096
  #define EEPROMbegin { EEPROM.begin(EEPROMSIZE); dP("\nEEPROM begin "); dP(EEPROMSIZE)
  #define EEPROMcommit { EEPROM.commit(); dP("EEPROM COMMIT"); }
  #define WIRE_begin Wire.begin(26, 32, 100000)  // choose pins for I2C // SDA, SCL
//


#elif defined(ESP32_BOARD)
  #pragma message ("ESP32_BOARD")
  #ifndef ARDUINO_ARCH_ESP32
    #error message("USE_ESP32_BOARD was selected, so must use an ESP32 processor")
  #endif
  #define BOARD "ESP32"
  #define CAN_TX_PIN (gpio_num_t) 2
  #define CAN_RX_PIN (gpio_num_t) 15
  #ifndef USEGCSERIAL
    #include "ACAN_ESP32Can.h"
  #endif // USEGCSERIAL
  #define EEPROMSIZE 4096
  #define EEPROMbegin EEPROM.begin(EEPROMSIZE); // this sets the size of the emulated eeprom. 
  #define EEPROMcommit EEPROM.commit();
  #define WIRE_begin Wire.begin(21, 22, 100000)

#else
#pragma error("No board selected");
#endif
