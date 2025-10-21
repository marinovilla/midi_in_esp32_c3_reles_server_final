#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define NUM_CONFIGURACIONES 5
#define NUM_RELES 4
#define EEPROM_START 0
#define CONFIG_SIZE 2
#define EEPROM_SIZE (EEPROM_START + NUM_CONFIGURACIONES * CONFIG_SIZE)

#define PIN_MODO 0

constexpr uint8_t PINES_RELES[NUM_RELES] = {4, 5, 6, 7};
constexpr uint8_t PINES_LED[NUM_RELES] = {2,3,8,9};


#define AP_SSID "MAPO_MIDI_CONFIG"
#define AP_PASSWORD "12345678"
#define HOST_NAME "mapo-midi"
#define mdns "mapo-midi.local"

#endif
