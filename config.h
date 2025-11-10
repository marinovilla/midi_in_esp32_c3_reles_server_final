#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define NUM_CONFIGURACIONES 2
#define NUM_RELES 2
#define NUM_REDIRECCIONES 2

#define EEPROM_START 0
#define CONFIG_SIZE 2
#define EEPROM_SIZE (EEPROM_START + NUM_CONFIGURACIONES * CONFIG_SIZE + NUM_REDIRECCIONES * 4)

#define PIN_MODO 1

#define MIDI_TX 17
#define MIDI_RX 18

constexpr uint8_t PINES_RELES[NUM_RELES] = {4,5};
constexpr uint8_t PINES_LED[NUM_RELES] = {2,3};


#define AP_SSID "MAPO_MIDI_CONFIG"
#define AP_PASSWORD "12345678"
#define HOST_NAME "mapo-midi"
#define mdns "mapo-midi.local"

#endif
