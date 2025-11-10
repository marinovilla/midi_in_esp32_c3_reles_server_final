#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

extern const char paginaHTML[];

const char paginaHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MAPO MIDI R&R</title>
    <style>
        body { 
            font-family: Arial, sans-serif; 
            background-color: #121212; 
            color: #fff; 
            margin: 0; 
            padding: 0; 
        }
        h1 { 
            text-align: center; 
            color: #8e44ad; 
            font-size: 26px; 
            margin-top: 10px; 
            text-transform: uppercase; 
        }
        h2 { 
            text-align: center; 
            color: #8e44ad; 
            font-size: 20px; 
            margin: 10px 0; 
            text-transform: uppercase; 
        }
        form { 
            width: calc(100% - 40px); 
            max-width: 600px; 
            margin: 20px auto 20px auto;  
            padding: 20px; 
            background-color: #1e1e1e; 
            border-radius: 10px; 
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.5); 
            display: flex; 
            flex-direction: column; 
            align-items: center; 
            box-sizing: border-box; 
        }
        .config, .redir { 
            border: 2px solid #444; 
            padding: 18px; 
            margin: 12px 0; 
            border-radius: 8px; 
            background-color: #1e1e1e; 
            display: flex; 
            justify-content: center; 
            align-items: center; 
            gap: 15px; 
            width: 100%; 
            box-sizing: border-box; 
        }
        label { 
            font-size: 14px; 
            color: #fff; 
            display: flex; 
            align-items: center; 
            gap: 5px; 
        }
        input[type='number'], select { 
            padding: 8px; 
            border: 2px solid #444; 
            border-radius: 8px; 
            font-size: 14px; 
            background-color: #333; 
            color: #fff; 
            text-align: center; 
            transition: all 0.3s ease;
            width: 45px; 
        } 
        select { width: 70px; }
        input[type='submit'] { 
            background-color: #8e44ad; 
            color: white; 
            border: none; 
            padding: 12px 18px; 
            font-size: 16px; 
            border-radius: 6px; 
            cursor: pointer; 
            width: auto; 
            margin-top: 15px; 
            transition: background-color 0.3s; 
        }
        input[type='submit']:hover { 
            background-color: #9b59b6; 
        }
        .footer { 
            text-align: center; 
            padding: 5px; 
            font-size: 10px; 
            background-color: #333; 
            color: white; 
            position: fixed; 
            width: 100%; 
            bottom: 0; 
        }
        input[type='checkbox'] { 
            width: 20px; 
            height: 20px; 
            accent-color: #8e44ad; 
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>MAPO MIDI R&R</h1>
        <form action="/set" method="GET">
            <h2>RELÉS</h2>
            %CONFIGURACIONES%

            <h2>REDIRECCIONES</h2>
            %REDIRECCIONES%

            <input type="submit" value="Guardar">
        </form>
    </div>

    <div class="footer">
        <p>&copy; 2025 MAPO MIDI CONTROLLER</p>
    </div>
</body>
</html>
)rawliteral";

#endif
