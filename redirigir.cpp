#include "redirigir.h"
#include "config.h"
#include <EEPROM.h>

void redirigir_CC(byte canal, byte numero, byte valor) {
  for (int i = 0; i < NUM_REDIRECCIONES; i++) {
    int addr = EEPROM_START + NUM_CONFIGURACIONES * CONFIG_SIZE + i * 4;
    bool activo = EEPROM.read(addr) || EEPROM.read(addr + 1) || EEPROM.read(addr + 2) || EEPROM.read(addr + 3);
    if (!activo) continue;
    bool tipoIn = EEPROM.read(addr) != 0;
    uint8_t valIn = EEPROM.read(addr + 1);
    bool tipoOut = EEPROM.read(addr + 2) != 0;
    uint8_t valOut = EEPROM.read(addr + 3);
    if (tipoIn && valIn == numero) {
      if (tipoOut) MIDI.sendControlChange(valOut, valor, canal);
      else MIDI.sendProgramChange(valOut, canal);
    }
  }
}

void redirigir_PC(byte canal, byte programa) {
  for (int i = 0; i < NUM_REDIRECCIONES; i++) {
    int addr = EEPROM_START + NUM_CONFIGURACIONES * CONFIG_SIZE + i * 4;
    bool activo = EEPROM.read(addr) || EEPROM.read(addr + 1) || EEPROM.read(addr + 2) || EEPROM.read(addr + 3);
    if (!activo) continue;
    bool tipoIn = EEPROM.read(addr) != 0;
    uint8_t valIn = EEPROM.read(addr + 1);
    bool tipoOut = EEPROM.read(addr + 2) != 0;
    uint8_t valOut = EEPROM.read(addr + 3);
    if (!tipoIn && valIn == programa) {
      if (tipoOut) MIDI.sendControlChange(valOut, 127, canal);
      else MIDI.sendProgramChange(valOut, canal);
    }
  }
}
