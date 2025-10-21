#include <Arduino.h>
#include "html.h"

const char paginaHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>MAPO MIDI CONTROL RELÉS</title>
<style>
body {
    font-family: Arial;
    background-color: #121212;
    color: #fff;
    margin: 0;
    padding: 0;
}
form {
    width: 100%;
    max-width: 430px;
    padding: 15px;
    background: #1e1e1e;
    border-radius: 8px;
    display: flex;
    flex-direction: column;
    align-items: center;
    margin: 20px auto;
}
h1 {
    font-size: 26px;
    font-weight: bold;
    background: linear-gradient(90deg, #9b59b6, #8e44ad);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    text-shadow: 1px 1px 2px rgba(0,0,0,0.3);
    margin-bottom: 15px;
}
.config {
    display: flex;
    align-items: center;
    margin-bottom: 10px;
    gap: 8px;
}
.config label {
    font-size: 12px;
    font-weight: bold;
    color: #8e44ad;
    margin-right: 5px;
    white-space: nowrap;
}
.config select, 
.config input[type="number"] {
    border-radius: 4px;
    border: 1px solid #8e44ad;
    background-color: #1e1e1e;
    color: #fff;
    padding: 2px 5px;
}
.config select:focus,
.config input[type="number"]:focus {
    outline: none;
    background-color: #8e44ad;
    color: #fff;
}
.config input[type="number"] {
    width: 40px;
}
.config input[type="checkbox"] {
    accent-color: #8e44ad;
    margin-right: 3px;
}
.config select {
    transition: background-color 0.2s;
}
.config select:active {
    background-color: #8e44ad;
    color: #fff;
}
input[type="submit"] {
    background: #8e44ad;
    color: white;
    border: none;
    padding: 6px 15px;
    border-radius: 6px;
    cursor: pointer;
    margin-top: 10px;
    width: auto;
    align-self: center;
}
input[type="submit"]:hover {
    background: #9b59b6;
}
</style>
</head>
<body>
<div class='container'>
<form action='/set' method='GET'>
<h1>MAPO MIDI CONTROL RELÉS</h1>

%CONFIGURACIONES%

<input type="submit" value="Guardar">
</form>
</div>
</body>
</html>
)rawliteral";
