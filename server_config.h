#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <ESPmDNS.h>
#include "config.h"
#include "html.h"

void server_config_ini();

#endif
