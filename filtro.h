#ifndef FILTRO_H
#define FILTRO_H

#include <Arduino.h>

void filtro_CC(byte channel, byte control, byte value);
void filtro_PC(byte channel, byte program);
void filtro_setDebug(bool enable);
//bool filtro_getDebug();

#endif
