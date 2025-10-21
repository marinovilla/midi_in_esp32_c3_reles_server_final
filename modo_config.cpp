#include "modo_config.h"
#include <EEPROM.h>

void modo_config_ini() {
  EEPROM.begin(512);
}

int modo_config_CC(uint8_t cc) {
  for (int i = 0; i < NUM_CONFIGURACIONES; i++) {
    uint8_t byteConfig = EEPROM.read(EEPROM_START + i * 2);
    uint8_t valor = EEPROM.read(EEPROM_START + i * 2 + 1);
    if ((byteConfig >> 7) == 1 && valor == cc) return i;
  }
  return -1;
}

int modo_config_PC(uint8_t pc) {
  for (int i = 0; i < NUM_CONFIGURACIONES; i++) {
    uint8_t byteConfig = EEPROM.read(EEPROM_START + i * 2);
    uint8_t valor = EEPROM.read(EEPROM_START + i * 2 + 1);
    if ((byteConfig >> 7) == 0 && valor == pc) return i;
  }
  return -1;
}

void modo_config_guardar(uint8_t configIndex, uint8_t tipo, uint8_t estados, uint8_t valor) {
  uint8_t val = (tipo << 7) | (estados & 0x7F);
  EEPROM.write(EEPROM_START + configIndex * 2, val);
  EEPROM.write(EEPROM_START + configIndex * 2 + 1, valor);
  EEPROM.commit();
}
