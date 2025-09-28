// OFM-FunctionBlocks --
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

// -- OFM-FunctionBlocks //
