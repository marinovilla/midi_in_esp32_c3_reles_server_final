#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "server_config.h"
#include "config.h"
#include "modo_config.h"
#include "filtro.h"
#include "reles.h"
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

bool modo = false;

void setup() {

  Serial.begin(115200);
  Serial.println("MAPO MIDI RELE CONTROL");

  pinMode(PIN_MODO, INPUT_PULLUP);

  Serial1.begin(31250, SERIAL_8N1, 10, -1);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleControlChange(filtro_CC);
  MIDI.setHandleProgramChange(filtro_PC);

  EEPROM.begin(EEPROM_SIZE);

  reles_ini();
  modo_config_ini();

  filtro_debug(true);
  reles_debug(0);

  unsigned long Tiempo = millis();
  while (millis() - Tiempo < 5000) {
    if (digitalRead(PIN_MODO) == LOW) {
      modo = true;
      break;
    }
  }

  if (modo) {
    Serial.println("*** Modo Configuración ***");
    server_config_ini();
  } else {
    Serial.println("*** Modo Funcionamiento ***");
  }
}

void loop() {
  if (!modo) {
    MIDI.read();
  }
}
