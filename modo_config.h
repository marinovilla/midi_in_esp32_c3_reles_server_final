#ifndef MODO_CONFIG_H
#define MODO_CONFIG_H

#include <Arduino.h>

#define EEPROM_START 0
#define NUM_CONFIGURACIONES 5

void modo_config_ini();
int modo_config_CC(uint8_t cc);
int modo_config_PC(uint8_t pc);
void modo_config_guardar(uint8_t configIndex, uint8_t tipo, uint8_t estados, uint8_t valor);

#endif
