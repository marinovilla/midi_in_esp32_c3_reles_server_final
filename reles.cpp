#include "reles.h"
#include <EEPROM.h>
#include "config.h"

void reles_ini() {
  for (int i = 0; i < NUM_RELES; i++) {
    pinMode(PINES_RELES[i], OUTPUT);
    pinMode(PINES_LED[i], OUTPUT);  
  }
}

void reles_activar(int index, bool estado) {
  if (index >= 0 && index < NUM_RELES) {
    digitalWrite(PINES_RELES[index], estado ? HIGH : LOW);
    digitalWrite(PINES_LED[index], estado ? HIGH : LOW);  
  }
}

void reles_aplicar(uint8_t estados) {
  for (int i = 0; i < NUM_RELES; i++) {
    bool estado = (estados >> i) & 0x01;
    reles_activar(i, estado);
  }
}

void reles_debug(int configIndex) {
  int addr = EEPROM_START + configIndex * CONFIG_SIZE;
  uint8_t tipo_reles = EEPROM.read(addr);
  uint8_t valor = EEPROM.read(addr + 1);

  Serial.print("Config ");
  Serial.print(configIndex);
  Serial.print(": byte tipo+relés=");
  Serial.print(tipo_reles, BIN);
  Serial.print(" (modo=");
  Serial.print((tipo_reles & 0x80) ? "CC" : "PC");
  Serial.print("), valor=");
  Serial.println(valor);
}
