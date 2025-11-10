#include "filtro.h"
#include "modo_config.h"
#include "reles.h"
#include <EEPROM.h>
#include "config.h"

uint8_t estado_actual_reles = 0;

void filtro_CC(byte channel, byte number, byte value) {
  int index = modo_config_CC(number);
  if (index >= 0) {
    uint8_t tipo_reles = EEPROM.read(EEPROM_START + index * CONFIG_SIZE);
    uint8_t reles = tipo_reles & 0x0F;
    estado_actual_reles ^= reles;
    reles_aplicar(estado_actual_reles);
    Serial.printf("[CC %d] Config %d => Relés toggled => Nuevo estado: %02X\n",
                  number, index + 1, estado_actual_reles);
  }
}


void filtro_PC (byte channel, byte program) {
  int index = modo_config_PC(program);
  if (index >= 0) {
    uint8_t tipo_reles = EEPROM.read(EEPROM_START + index * CONFIG_SIZE);
    uint8_t reles = tipo_reles & 0x0F;
    reles_aplicar(reles);
    Serial.printf("[PC %d] Config %d => Relés: %02X\n", program, index + 1, reles);
  }
}

