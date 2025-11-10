#ifndef REDIRIGIR_H
#define REDIRIGIR_H

#include <Arduino.h>
#include <MIDI.h>
#include "config.h"

extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI;

void redirigir_CC(byte canal, byte numero, byte valor);
void redirigir_PC(byte canal, byte programa);

#endif
