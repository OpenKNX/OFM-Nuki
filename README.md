# OFM-Nuki

Dies ist ein Modul zur Steuerung eines Nuki Schlosses

## Features

- Aufsperren
- Zusperren
- Lasche Ziehen
- Lock 'n' go

## Hardware Unterstützung

|Prozessor | Status | Anmerkung                     |
|----------|--------|-------------------------------|
|ESP32     | Development |                               |


## Einbindung in die Anwendung

In das Anwendungs XML muss OFM-Network (oder OFM-WLAN) und das OFM-InternetWeatherModule aufgenommen werden:

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

**Hinweis:** Pro Kanal werden XX KO's benötigt. Dies muss bei nachfolgenden Modulen bei KoOffset und KoSingleOffset entsprechend berücksichtigt werden.

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

## Lizenz

[GNU GPL v3](LICENSE)