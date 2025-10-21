#ifndef RELES_H
#define RELES_H

#include <Arduino.h>
#include "config.h"

void reles_ini();
void reles_activar(int index, bool estado);
void reles_aplicar(uint8_t estados);
void reles_debug(int configIndex);

#endif
