#include "server_config.h"
#include "html.h"
#include <EEPROM.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server(80);

String generarConfiguraciones(){
    String html = "";
    for(int i=0;i<NUM_CONFIGURACIONES;i++){
        int addr = EEPROM_START + i*CONFIG_SIZE;
        uint8_t byteConfig = EEPROM.read(addr);
        uint8_t valor = EEPROM.read(addr+1);
        String modoActual = (byteConfig>>7)?"CC":"PC";

        html += "<div class='config'>";
        html += "<label>Config "+String(i+1)+"</label>";
        html += "<select name='modo_"+String(i)+"'><option value='PC'";
        if(modoActual=="PC") html += " selected";
        html += ">PC</option>";
        html += "<option value='CC'";
        if(modoActual=="CC") html += " selected";
        html += ">CC</option></select>";
        html += "<input type='number' name='valor_"+String(i)+"' min='0' max='127' value='"+String(valor)+"'>";
        for(int r=0;r<NUM_RELES;r++){
            bool estado = byteConfig & (1<<r);
            html += "<label><input type='checkbox' name='r"+String(r+1)+"_"+String(i)+"' ";
            if(estado) html += "checked";
            html += "> R"+String(r+1)+"</label>";
        }
        html += "</div>";
    }
    return html;
}

String generarRedirecciones(){
    String html = "";
    for(int i=0;i<NUM_REDIRECCIONES;i++){
        int addr = EEPROM_START + NUM_CONFIGURACIONES*CONFIG_SIZE + i*4;
        bool activo = EEPROM.read(addr) || EEPROM.read(addr+1) || EEPROM.read(addr+2) || EEPROM.read(addr+3);
        bool tipoIn = EEPROM.read(addr)!=0;
        uint8_t valIn = EEPROM.read(addr+1);
        bool tipoOut = EEPROM.read(addr+2)!=0;
        uint8_t valOut = EEPROM.read(addr+3);

        html += "<div class='redir redir"+String(i)+"'>";
        html += "<input type='checkbox' id='activo_"+String(i)+"' name='activo_"+String(i)+"' ";
        if(activo) html += "checked";
        html += " onchange='toggleRedir("+String(i)+")'>";
        html += "Entrada<select name='tipoIn_"+String(i)+"'>";
        html += "<option value='PC'";
        if(!tipoIn) html += " selected";
        html += ">PC</option>";
        html += "<option value='CC'";
        if(tipoIn) html += " selected";
        html += ">CC</option>";
        html += "</select>";
        html += "<input type='number' name='valIn_"+String(i)+"' min='0' max='127' value='"+String(valIn)+"'>";
        html += "Salida<select name='tipoOut_"+String(i)+"'>";
        html += "<option value='PC'";
        if(!tipoOut) html += " selected";
        html += ">PC</option>";
        html += "<option value='CC'";
        if(tipoOut) html += " selected";
        html += ">CC</option>";
        html += "</select>";
        html += "<input type='number' name='valOut_"+String(i)+"' min='0' max='127' value='"+String(valOut)+"'>";
        html += "</div>";
    }

    html += "<script>"
            "function toggleRedir(idx){"
            "var tick = document.getElementById('activo_'+idx);"
            "var container = document.querySelector('.redir'+idx);"
            "var selects = container.querySelectorAll('select');"
            "var nums = container.querySelectorAll('input[type=number]');"
            "if(!tick.checked){"
            "selects.forEach(s=>{s.disabled=true; s.classList.add('inactivo');});"
            "nums.forEach(n=>{n.disabled=true; n.classList.add('inactivo');});"
            "} else {"
            "selects.forEach(s=>{s.disabled=false; s.classList.remove('inactivo');});"
            "nums.forEach(n=>{n.disabled=false; n.classList.remove('inactivo');});"
            "}"
            "}"
            "document.addEventListener('DOMContentLoaded', function(){"
            "for(var i=0;i<" + String(NUM_REDIRECCIONES) + ";i++){"
            "var t=document.getElementById('activo_'+i); if(t) toggleRedir(i); }"
            "});"
            "</script>";

    return html;
}

void guardarConfiguraciones(AsyncWebServerRequest *request){
    for(int i=0;i<NUM_CONFIGURACIONES;i++){
        String modoParam = "modo_"+String(i);
        String valParam = "valor_"+String(i);
        uint8_t byteConfig = 0;

        if(request->hasParam(modoParam) && request->hasParam(valParam)){
            String modo = request->getParam(modoParam)->value();
            int val = request->getParam(valParam)->value().toInt();
            if(val<0) val=0; if(val>127) val=127;
            if(modo=="CC") byteConfig|=0x80;
            EEPROM.write(EEPROM_START + i*2 +1,(uint8_t)val);
        }

        for(int r=0;r<NUM_RELES;r++){
            if(request->hasParam("r"+String(r+1)+"_"+String(i))) byteConfig |= 1<<r;
        }
        EEPROM.write(EEPROM_START + i*2,byteConfig);
    }

    for(int i=0;i<NUM_REDIRECCIONES;i++){
        int addr = EEPROM_START + NUM_CONFIGURACIONES*CONFIG_SIZE + i*4;
        bool activo = request->hasParam("activo_"+String(i));
        if(!activo){
            EEPROM.write(addr,0);
            EEPROM.write(addr+1,0);
            EEPROM.write(addr+2,0);
            EEPROM.write(addr+3,0);
            continue;
        }
        bool tipoIn = request->getParam("tipoIn_"+String(i))->value()=="CC";
        uint8_t valIn = request->getParam("valIn_"+String(i))->value().toInt();
        bool tipoOut = request->getParam("tipoOut_"+String(i))->value()=="CC";
        uint8_t valOut = request->getParam("valOut_"+String(i))->value().toInt();

        EEPROM.write(addr, tipoIn?1:0);
        EEPROM.write(addr+1, valIn);
        EEPROM.write(addr+2, tipoOut?1:0);
        EEPROM.write(addr+3, valOut);
    }
    EEPROM.commit();
}

void server_config_ini(){
    EEPROM.begin(EEPROM_SIZE);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    WiFi.setHostname(HOST_NAME);
    MDNS.begin(mdns);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = FPSTR(paginaHTML);
        html.replace("%CONFIGURACIONES%", generarConfiguraciones());
        html.replace("%REDIRECCIONES%", generarRedirecciones());
        request->send(200,"text/html; charset=UTF-8",html);
    });

    server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
        guardarConfiguraciones(request);
        request->send(200,"text/html; charset=UTF-8","<script>alert('¡Configuración guardada!'); window.location.href = '/';</script>");
    });

    server.begin();
}
