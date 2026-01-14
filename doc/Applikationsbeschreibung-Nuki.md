<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2025 Michael Geramb -->

# Applikationsbeschreibung Nuki

Über diese Anwendung können bis zu 10 Nuki Smart Lock oder Nuki Opener über Bluetooth von dem KNX System gesteuert werden.
Es müssen sich die Nuki Geräte in Bluetooth Reichweite befinden.

ACHTUNG: Die Anwendung kann nicht zusammen mit der Nuki Bridge verwendet werden.

Kompatibilität:
- Nuki Smart Lock 1.0
- Nuki Smart Lock 2.0
- Nuki Smart Lock 3.0
- Nuki Smart Lock 3.0 Pro
- Nuki Smart Lock 4.0
- Nuki Smart Lock 4.0 Pro
- Nuki Opener

Achtung: Nuki Smart Lock 5.0 ist derzeit nicht unterstützt, da dieses keine Statusänderungen über Bluetooth zur Verfügung stellt.

# Basiseinstellungen

Es wird die aktuelle Versionsnummer des Nuki OpenKNX Moduls angezeigt und die Kanäle werden auf dieser Seite konfiguriert.

<!-- DOC -->
## Kanalauswahl

In diesem Abschnitt wird die Anzahl, Verwendung und der Name der Kanäle festgelegt.

<!-- DOC -->
## Verfügbare Kanäle

Anzahl der Nuki Geräte, die gesteuert werden sollen.

<!-- DOC HelpContext="Bezeichnung" -->
### Bezeichnung 1-n

Name des Gerätes das über den Kanal gesteuert werden soll. 
Beispielsweise: Eingangstüre, Kellertüre

<!-- DOC -->
### Typ

Auswahl, welches Nuki Gerät gesteuert werden soll:

- Deaktiviert
- Nuki Lock
- Nuki Opener

<!-- DOCEND -->
# Smart Lock

Auf dieser Seite werden die Konfiguration für die Steuerung festgelegt und das Bluetooth Pairing durchgeführt.

### Bezeichnung

Hier kann die Bezeichnung des Gerätes die in der Übersicht vergeben wurde, ebenfalls angepasst werden.
Beispielsweise: Eingangstüre, Kellertüre

<!-- DOC -->
### Kanal deaktivieren zu Testzwecken

Mit dieser Option kann der Kanal deaktiviert werden, ohne dass die Konfiguration verloren geht.

<!-- DOCEND -->
## Bluetooth Kopplung (Pairing)

Die OpenKNX Steuerung muss einmalig mit dem Nuki Smart Lock gekoppelt werden.

<!-- DOC -->
### Abschnitt anzeigen

Über diese Option kann der Pairing Abschnitt ein- und ausgeblendet werden.
Da das Pairing normalerweise nur einmal erfolgt, wird nach dem Pairing dieser Abschnitt automatisch ausgeblendet.
Dieser Abschnitt kann hier aber erneut eingeblendet werden, um z.B. nach einem Tausch des Nuki Smart Lock das Pairing erneut durchzuführen.

<!-- DOCEND -->
### Bluetooth Kopplung durchführen

1) Gerät über die ETS programmieren
2) Knopf am Smart Lock für 10 Sekunden drücken, bis der Ring leuchtet
3) In der ETS mit 'Mit Smart Lock koppeln' betätigen. Ist die Taste trotz Programmierung deaktiviert, einmal die Seite wechseln.

<!-- DOCEND -->
## Versperren

In diesem Abschnitt werden die Optionen zum automatischen Versperren festgelegt.

<!-- DOC -->
### Automatisch versperren

Aktiviert / deaktiviert das automatische Versperren.

<!-- DOC HelpContext="LockAfterTime" -->
#### nach

Legt fest, nach welcher Zeit das Smart Lock automatisch versperrt wird.
Normalerweise wird diese Zeit deutlich länger konfiguriert, als die Zeit im Abschnitt OpenKNX Lock'n'Go, die nur zum unmittelbaren Verlassen des Raumes gedacht ist.

<!-- DOC -->
#### Automatisch versperren Zeit

Zeitangabe, nach der das Schloss versperrt werden soll.

<!-- DOC -->
#### Automatisch versperren Zeit Einheit

Legt die Einheit fest, in der die Zeitangabe für das automatische Versperren verwendet wird.

- Sekunden
- Minuten
- Stunden

LockAfterTime

<!-- DOC -->
### Verbleibend Count-Down verwenden

Gibt an, ob am 'Verbleibend Offen' Gruppenobjekt für das automatische Versperren ein Count-Down ausgegeben werden soll.

<!-- DOC -->
### In der Nacht andere Versperreinstellungen

Mit dieser Einstellung kann festgelegt werden, dass in der Nacht das automatische Versperren mit anderen Einstellungen erfolgt.

Die Verwendung getrennter Einstellungen ist nur möglich, wenn im Abschnitt Nacht eine Konfiguration für die Auswahl des Nachmodus vorgenommen wurde.

<!-- DOC -->
### Versperren

Legt fest, ob beim Versperren der Schlüssel einmal oder zweimal gedreht wird.
ACHTUNG: Manche Versicherungen verlangen ein doppeltes Versperren.

<!-- DOC -->
## OpenKNX Lock'n'Go

Das OpenKNX Lock'n'Go ist gedacht zum unmittelbaren Verlassen und anschließenden Versperren des Schlosses.
Im Unterschied zum Nuki Lock'n'Go gibt es aber eine Reihe an zusätzlichen Einstellungen.

Z.B. kann der Versperr-Count-Down gestoppt werden oder über einen KNX-Türkontakt unterbrochen werden.

<!-- DOC -->
### Modus

Gibt an, welche Aktion beim Starten von Lock'n'Go ausgelöst werden soll:

- entsperren
- Lasche ziehen

<!-- DOC HelpContext="LocknGo-Zeit"-->
### Wiederversperrzeit

Zeit die nach dem Aufsperren gewartet wird, bis das Schloss sich wieder automatisch versperrt.
Diese Zeit kann durch einen Türkontakt beim Öffnen der Tür unterbrochen werden.

<!-- DOC HelpContext="LocknGo-Zeit-Einheit"-->
### Wiederversperrzeit Eimheit

Legt die Einheit fest, in der die Zeitangabe für das Wiederversperren verwendet wird.

- Sekunden
- Minuten
- Stunden

<!-- DOC -->
### Manuell entsperren startet Lock'n'Go

Ist diese Option gesetzt, wird wenn das Schloss manuell durch drehen des Knopfes geöffnet wird, der Lock'n'Go Count-Down für das Wiederversperren gestartet.

<!-- DOC -->
### Entsperren über Nuki Taste startet Lock'n'Go

Ist diese Option gesetzt, wird wenn das Schloss über die Taste am Nuki Smart Lock geöffnet wird, der Lock'n'Go Count-Down für das Wiederversperren gestartet.
ACHTUNG: Das funktioniert nur, wenn die Taste über die Nuki App mit Aufsperren belegt ist. 
Beim Nuki eigenen Lock'n'Go funktioniert diese Option nicht.

<!-- DOC -->
### Entsperren über Nuki App oder Schlüssel startet Lock'n'Go

Ist diese Option gesetzt, wird wenn das Schloss über die Nuki App (auch bei Auto Unlock) oder mit Schlüssel geöffnet wird, der Lock'n'Go Count-Down für das Wiederversperren gestartet.


<!-- DOC -->
### Weiteres EIN Telegramm am 'OpenKNX Lock'n'Go' Eingang

Gibt an, was passieren soll, wenn über das 'OpenKNX Lock'n'Go' Gruppenobjekt bei geöffnetem Schloss ein Telegramm anliegt:

- Nichts
- Zeit neu starten
  Die Wartezeit für das Versperren wird neu gestartet.
- Versperren
  Das Schloss wird sofort ohne Wartezeit versperrt.
- Dauerhaft entsperren wenn aktiv, sonst versperren
  Wenn OpenKNX Lock'n'Gp Vorgang aktiv, wird der Vorgang abgebrochen und das Schloss bleibt entriegelt.
  Wenn automatisch Versperren eingeschalten ist, wird der Count Down für das automatisch versperren gestartet.
  Ist OpenKNX Lock'n'Go nicht aktiv, wird das Schloss versperrt.
- Dauerhaft entsperren wenn aktiv,
  Wenn OpenKNX Lock'n'Gp Vorgang aktiv, wird der Vorgang abgebrochen und das Schloss bleibt entriegelt.
  Wenn automatisch Versperren eingeschalten ist, wird der Count Down für das automatisch versperren gestartet.

<!-- DOC -->
### AUS Telegramm am OpenKNX Lock'n'Go Eingang

Gibt an, ob ein AUS Telegramm am Lock'n'Go Eingang zum sofortigen Versperren führt:

Auswahl:

- Nichts
  Das Telegramm wird ignoriert und das Schloss versperrt nach der eingestellten Wartezeit.
- Versperren
  Ein AUS (0) Telegramm beendet das Lock'n'Go und versperrt das Schloss
- Dauerhaft entsperren
  Ein AUS (0) Telegramm beendet das Lock'n'Go und lässt das Schloss entriegelt. 
  Wenn automatisch Versperren eingeschalten ist, wird der Count Down für das automatisch versperren gestartet.

<!-- DOCEND -->
## Versperr-Count-Down

Dieser Abschnitt dient zur Konfiguration des Count-Downs bis zum Versperren.

<!-- DOC -->
### Objekt für Versperr-Count-Down

Für folgende Aktionen kann ein Count-Down auf einem Gruppenobjekt ausgegeben werden

- Nuki Lock'n'Go
- OpenKNX Lock'n'Go
- automatischen Versperren, sofern 'Verbleibend Count-Down' im Abschnitt 'Versperren' konfiguriert ist

Als Option stehen folgende Werte bereit:

- Keines
  Es wird kein Gruppenobjekt erzeugt.
- Sekunden
  Die Ausgabe am Objekt erfolgt in Sekunden.
- Minuten
  Die Ausgabe am Objekt erfolgt in Minuten.

<!-- DOCEND -->
## Türkontakt

Über einen KNX-Türkontakt kann das automatische Versperren verhindert werden, solange die Türe geöffnet ist.

<!-- DOC -->
### KNX Türsensor 

Mit dieser Option wird ein Gruppenobjekt für den Türkontakt und die Einstellungen für das Verhalten eingeblendet.

<!-- DOC -->
### Nach Tür schließen

Legt die Aktion fest, die nach dem Schließen der Tür ausgeführt wird

- Versperrwartezeit fortsetzen
  Die unterbrochene Zeit wird fortgesetzt
- Versperrwartezeit neu starten
  Der ursprüngliche Versperr-Count-Down wird wieder gestartet 
- Versperren nach
  Es wird ein neuer Versperr-Count-Down mit der vorgegeben Wartezeit gestartet
- bei OpenKNX Lock'n'Go versperren nach
  Wenn OpenKNX Lock'n'Go aktiv ist, wird nach der konfigurierte Wartezeit versperrt, ansonsten wird eine eventuell aktive Versperrwartezeit fortgesetzt.

<!-- DOC HelpContext="WaitTime"-->
#### Wartezeit

Legt die neue Wartezeit fest, die nach dem Schließen der Tür angewendet wird, bevor das Schloss versperrt wird.

<!-- DOC -->
##### Wartezeit

Zeit, die gewartet wird, bis die Tür versperrt wird.

<!-- DOC -->
##### Wartezeit Einheit

Einheit für die Wartezeit:

- Sekunden
- Minuten
- Stunden

<!-- DOC -->
### Einbruchalarm

Ein unberechtigtes Öffnen der Tür kann ein Alarm Telegramm auslösen.

- nicht aktiv
- wenn Tür offen und Nuki versperrt
  blendet das Gruppenobjekt 'Einbruchsalarm Aktiv' ein und gibt einen Alarm aus, wenn die Tür geöffnet (aufgebrochen) wird, obwohl das Schloss im versperrten Zustand ist.

<!-- DOCEND -->
## Nacht

In diesem Abschnitt wird festgelegt, wie die Steuerung erkennt, ob es Nacht ist.

<!-- DOC -->
### Nacht

Über diese Option wird festgelegt, auf welche Art die Nachterkennung erfolgen soll:

- Deaktiviert
- Zeitfenster
  Die Beginnzeit und Endzeit für die Nacht kann festgelegt werden.
- Objekt
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegramm die Nacht vorgegeben wird.
- Objekt UND Zeitfenster
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegramm die Nacht vorgegeben wird.
  Der Nachtmodus wird aber nur aktiviert, wenn das Nachttelegramm innerhalb des konfigurierten Zeitfensters empfangen wird.
- Objekt ODER Zeitfenster
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegramm die Nacht vorgegeben wird.
  Zusätzlich kann ein Zeitfenster für die Nacht festgelegt werden. Das Gerät schaltet im Zeitfenster oder beim Empfang des Nachttelegrams auf den Nachtmodus.

Hinweis: Wird eine Einstellung mit Zeitfenster verwendet, muss die OpenKNX Steuerung über Zeit-Telegramme mit der aktuellen Uhrzeit versorgt werden.

<!-- DOC -->
### Nacht Auswahl

<!-- DOC -->
### Nacht Beginn

Diese Option ist nur sichtbar, wenn bei der Konfiguration 'Nacht' eine Option mit Zeitfenster gewählt wurde.
Die Einstellung legt die Uhrzeit für den Nacht Beginn fest.

Hinweis: die OpenKNX Steuerung muss über Zeit-Telegramme mit der aktuellen Uhrzeit versorgt werden.

<!-- DOC -->
### Nacht Ende

Diese Option ist nur sichtbar, wenn bei der Konfiguration 'Nacht' eine Option mit Zeitfenster gewählt wurde.
Die Einstellung legt die Uhrzeit für das Nacht Ende fest.

Hinweis: die OpenKNX Steuerung muss über Zeit-Telegramme mit der aktuellen Uhrzeit versorgt werden.

<!-- DOC -->
### Aktion bei Nachtanfang

Legt fest, welche Aktion beim Beginn der Nacht ausgeführt werden soll:

- keine Aktion
- einfach versperren
- 2-fach versperren
- entsperren

<!-- DOC -->
### Aktion bei Nachtende

Legt fest, welche Aktion beim Ende der Nacht ausgeführt werden soll:

- keine Aktion
- einfach versperren
- 2-fach versperren
- entsperren

<!-- DOCEND -->
# Opener

Auf dieser Seite werden die Konfiguration für die Steuerung festgelegt und das Bluetooth Pairing durchgeführt.

### Bezeichnung

Hier kann die Bezeichnung des Gerätes die in der Übersicht vergeben wurde, ebenfalls angepasst werden.
Beispielsweise: Eingangstüre, Kellertüre

### Kanal deaktivieren zu Testzwecken

Mit dieser Option kann der Kanal deaktiviert werden, ohne dass die Konfiguration verloren geht.

## Bluetooth Kopplung (Pairing)

Die OpenKNX Steuerung muss einmalig mit dem Nuki Opener gekoppelt werden.

<!-- DOC -->
### Abschnitt anzeigen

Über diese Option kann der Pairing Abschnitt ein- und ausgeblendet werden.
Da das Pairing normalerweise nur einmal erfolgt, wird nach dem Pairing dieser Abschnitt automatisch ausgeblendet.
Dieser Abschnitt kann hier aber erneut eingeblendet werden, um z.B. nach einem Tausch des Nuki Opener das Pairing erneut durchzuführen.

<!-- DOCEND -->
### Bluetooth Kopplung durchführen

1) Gerät über die ETS programmieren
2) Knopf am Opener für 10 Sekunden drücken
3) In der ETS mit 'Mit Opener koppeln' betätigen. Ist die Taste trotz Programmierung deaktiviert, einmal die Seite wechseln.
