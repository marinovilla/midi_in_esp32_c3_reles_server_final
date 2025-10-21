#include "filtro.h"
#include "modo_config.h"
#include "reles.h"
#include <EEPROM.h>
#include "config.h"

void filtro_CC(byte channel, byte number, byte value) {
  int index = modo_config_CC(number);
  if (index >= 0) {
    uint8_t tipo_reles = EEPROM.read(EEPROM_START + index * CONFIG_SIZE);
    uint8_t relays = tipo_reles & 0x0F;
    reles_aplicar(relays);
    Serial.printf("[CC %d] Config %d => Relés: %02X\n", number, index + 1, relays);
  }
}

void filtro_PC (byte channel, byte program) {
  int index = modo_config_PC(program);
  if (index >= 0) {
    uint8_t tipo_reles = EEPROM.read(EEPROM_START + index * CONFIG_SIZE);
    uint8_t relays = tipo_reles & 0x0F;
    reles_aplicar(relays);
    Serial.printf("[PC %d] Config %d => Relés: %02X\n", program, index + 1, relays);
  }
}

static bool debugEnabled = false;

void filtro_setDebug(bool enable) {
    debugEnabled = enable;
}

/*bool filtro_getDebug() {
    return debugEnabled;
}*/
