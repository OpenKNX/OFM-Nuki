# OFM-Nuki

Dies ist ein Modul zur Steuerung eines Nuki Smart Lock oder eines Nuki Opener.

Kompatibilität:
- Nuki Smart Lock 1.0
- Nuki Smart Lock 2.0
- Nuki Smart Lock 3.0
- Nuki Smart Lock 3.0 Pro
- Nuki Smart Lock 4.0
- Nuki Smart Lock 4.0 Pro
- Nuki Opener

Achtung: Nuki Smart Lock 5.0 ist derzeit nicht unterstützt, da dieses keine Statusänderungen über Bluetooth zur Verfügung stellt.

## Features

- Aufsperren
- Zusperren
- Lasche ziehen
- Lock 'n' go

## Hardware-Unterstützung

| Prozessor | Status      | Anmerkung |
|-----------|-------------|-----------|
| ESP32     | Beta        |           |


## Einbindung in die Anwendung

In das Anwendungs-XML müssen OFM-Network (oder OFM-WLAN) und das OFM-InternetWeatherModule aufgenommen werden:

```xml
  

  <op:define prefix="NUK" ModuleType="23"
    share=   "../lib/OFM-Nuki/src/NukiModule.share.xml"
    template="../lib/OFM-Nuki/src/NukiModule.templ.xml"
    NumChannels="5"
    KoSingleOffset="400"
    KoOffset="410">
    <op:verify File="../lib/OFM-Nuk/library.json" ModuleVersion="0.1" /> 
  </op:define>
```

**Hinweis:** Pro Kanal werden 20 KOs benötigt. Dies muss bei nachfolgenden Modulen bei KoOffset und KoSingleOffset entsprechend berücksichtigt werden.

```
[...]
#include "NukiModule.h"
[...]

void setup()
{
    [...]
    openknx.addModule(1, openknxNukiModule);
    [...]
}
```

Im platformio.ini müssen folgende build flags für das OFM-Nuki benötigt:

```
build_flags =
  -D BLESCANNER_USE_LATEST_NIMBLE
  -D NUKI_USE_LATEST_NIMBLE
  -D DEBUG_NUKI_COMMUNICATION
  -D NUKI_NO_WDT_RESET
  -D NUKI_ALT_CONNECT
  -D NUKI_MUTEX_RECURSIVE
  -D NUKI_64BIT_TIME
  -D OPENKNX_DUALCORE
```

### Applikationsbeschreibung

Die Applikationsbeschreibung ist [hier](doc/Applikationsbeschreibung-Nuki.md) zu finden. 

## Lizenz

[GNU GPL v3](LICENSE)