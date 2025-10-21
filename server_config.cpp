#include "server_config.h"

AsyncWebServer server(80);

String generarConfiguraciones() {
    String html = "";

    for (int i = 0; i < NUM_CONFIGURACIONES; i++) {
        uint8_t byteConfig = EEPROM.read(EEPROM_START + i*2);
        uint8_t valor = EEPROM.read(EEPROM_START + i*2 + 1);

        String modoActual = (byteConfig >> 7) ? "CC" : "PC";
        bool r1Estado = byteConfig & 0x01;
        bool r2Estado = byteConfig & 0x02;
        bool r3Estado = byteConfig & 0x04;
        bool r4Estado = byteConfig & 0x08;

        html += "<div class='config'>";
        html += "<label>Config " + String(i+1) + "</label>";

        html += "<select name='modo_" + String(i) + "'>";
        html += "<option value='PC'" + String(modoActual == "PC" ? " selected" : "") + ">PC</option>";
        html += "<option value='CC'" + String(modoActual == "CC" ? " selected" : "") + ">CC</option>";
        html += "</select>";

        html += "<input type='number' name='valor_" + String(i) + "' min='0' max='127' value='" + String(valor) + "'>";

        html += "<label><input type='checkbox' name='r1_" + String(i) + "' " + (r1Estado ? "checked" : "") + "> R1</label>";
        html += "<label><input type='checkbox' name='r2_" + String(i) + "' " + (r2Estado ? "checked" : "") + "> R2</label>";
        html += "<label><input type='checkbox' name='r3_" + String(i) + "' " + (r3Estado ? "checked" : "") + "> R3</label>";
        html += "<label><input type='checkbox' name='r4_" + String(i) + "' " + (r4Estado ? "checked" : "") + "> R4</label>";

        html += "</div>";
    }

    return html;
}

void guardarConfiguraciones(AsyncWebServerRequest *request) {
    for (int i = 0; i < NUM_CONFIGURACIONES; i++) {
        String paramModo = "modo_" + String(i);
        String paramValor = "valor_" + String(i);

        uint8_t byteConfig = 0;

        if (request->hasParam(paramModo) && request->hasParam(paramValor)) {
            String modo = request->getParam(paramModo)->value();
            int valor = request->getParam(paramValor)->value().toInt();
            if (valor < 0) valor = 0;
            if (valor > 127) valor = 127;

            if (modo == "CC") byteConfig |= 0x80;

            EEPROM.write(EEPROM_START + i*2 + 1, (uint8_t)valor);
        }

        if (request->hasParam("r1_" + String(i))) byteConfig |= 0x01;
        if (request->hasParam("r2_" + String(i))) byteConfig |= 0x02;
        if (request->hasParam("r3_" + String(i))) byteConfig |= 0x04;
        if (request->hasParam("r4_" + String(i))) byteConfig |= 0x08;

        EEPROM.write(EEPROM_START + i*2, byteConfig);
    }

    EEPROM.commit();
}

void server_config_ini() {
    EEPROM.begin(512);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    WiFi.setHostname(HOST_NAME);
    Serial.println("Punto de acceso WiFi iniciado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.softAPIP());
    MDNS.begin(mdns);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = paginaHTML;
        html.replace("%CONFIGURACIONES%", generarConfiguraciones());
        request->send(200, "text/html; charset=UTF-8", html);
    });

    server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request) {
        guardarConfiguraciones(request);
        request->send(200, "text/html; charset=UTF-8", "<script>alert('¡Configuración guardada!'); window.location.href = '/';</script>");
    });

    server.begin();
    Serial.println("Servidor web iniciado");
}
