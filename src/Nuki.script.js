// OFM-Nuki --
// SPDX-License-Identifier: AGPL-3.0-only

function nukAddChannel(device, online, progress, context) {
    var numberOfChannelds = device.getParameterByName('NUK_VisibleChannels');
    var newNumberOfChannels = numberOfChannelds.value + 1;
    var channelType = device.getParameterByName('NUK_CH' + newNumberOfChannels + 'ChannelType');
    var notAllowed = device.getParameterByName('NUK_AddNotAllowed');
    if (channelType == 0)
    {
        notAllowed.value = 1;
    }
    else
    {
        notAllowed.value = 0;
        numberOfChannelds.value = newNumberOfChannels;
    }
}

function nukPairDevice(device, online, progress, context) {
    progress.setText("Starte Bluetooth Koppelung Kanal " + context.channel);
    online.connect();

    var data = [
        1, // pairing;
        context.channel - 1 // zero based channel index
        ]; 
   
    var resp = online.invokeFunctionProperty(0xA0, 9, data);
    if (resp.length < 1 || resp[0] == 1)
        throw new Error("Fehler: Das Gerät unterstützt diesen Befehl nicht.");
    var result = resp[0];
    if (result == 3) 
        throw new Error("Fehler: Pairing fehlgeschlagen. Bitte prüfen, ob das Nuki Gerät im Kopplungsmodus ist.");
    if (result == 4) 
        throw new Error("Fehler: Kanal ungültig. Bitte zuerst die Anwendung programmieren.");
    if (result == 5) 
        throw new Error("Fehler: Kanal ist deaktiviert. Bitte zuerst die Anwendung programmieren.");
    if (result != 2)
        throw new Error("Unbekannter Fehler: " + result);
    
    online.disconnect();
    progress.setText("Nuki Gerät erfolgreich gekoppelt.");
}

// -- OFM-Nuki //
