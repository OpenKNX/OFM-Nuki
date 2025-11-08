### Nacht

Über diese Option wird festgelegt auf welche Art die Nachterkennung erfolgen soll:

- Deaktiviert
- Zeitfenster
  Die Beginnzeit und Endzeit für die Nacht kann festgelegt werden.
- Objekt
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegram die Nacht vorgegeben wird.
- Objekt UND Zeitfenster" Value="4" Id="%ENID%" />
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegram die Nacht vorgegeben wird.
  Der Nachtmodus wird aber nur aktiviert, wenn das Nachsignal innerhalb des konfigurierten Zeitfensters emfpangen wird.
- Objekt ODER Zeitfenster" Value="5" Id="%ENID%" />
  Blendet ein Gruppenobjekt ein, über das ein Nacht (1), Tag (0) Telegram die Nacht vorgegeben wird.
  Zusätzlich kann ein Zeitfenster für die Nacht festgelegt werden. Das Gerät schaltet im Zeitfenster oder beim Empfang des Nachtelegrams auf den Nachtmodus.

Hinweis: Wird die eine Einstellung mit Zeitfenster verwendet, muss die OpenKNX Steuerung über Zeit-Telegramme mit der aktuellen Uhrzeit versorgt werden.

