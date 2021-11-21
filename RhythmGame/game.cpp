#include "game.h"

BOOL WaveOutSetVolume(DWORD wVolume);

void DrawGame() {
    char tempStr[255];
    memset(screenText, '\0', 32767);
    ScreenClear();
}

void GamePlay(const int musicIndex) {
    PlaySound(TEXT("music_0.wav"), NULL, SND_ASYNC);
    WaveOutSetVolume((int)(65535 * 0.7));
	while (true) {
		DrawGame();
		ScreenPrint(0, 0, screenText);
		ScreenFlipping();
		if (_kbhit()) {
			int key_code = _getch();

			if (key_code == 27)
				return;
		}
	}
}

BOOL WaveOutSetVolume(DWORD wVolume)
{
    DWORD j;
    HMIXER hmx;
    MIXERLINE mxl;
    MIXERCAPS caps;
    DWORD cChannels;
    DWORD cConnections;
    BOOL bUpdate = FALSE;
    MIXERLINECONTROLS mxlctrl;
    LPMIXERCONTROLDETAILS_UNSIGNED pUnsigned;
    MIXERCONTROL pmxctrl;
    MIXERCONTROLDETAILS mxcd;

    if (mixerOpen(&hmx, 0, 0, (DWORD)GetModuleHandle(NULL), MIXER_OBJECTF_WAVEIN) == MMSYSERR_NOERROR)
    {
        mxl.cbStruct = sizeof(MIXERLINE);

        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

        if (mixerGetLineInfo((HMIXEROBJ)hmx, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) == MMSYSERR_NOERROR)
        {
            mxlctrl.cbStruct = sizeof(MIXERLINECONTROLS);
            mxlctrl.dwLineID = mxl.dwLineID;
            mxlctrl.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
            mxlctrl.cControls = 1;
            mxlctrl.cbmxctrl = sizeof(MIXERCONTROL);
            mxlctrl.pamxctrl = &pmxctrl;

            pmxctrl.cbStruct = sizeof(MIXERCONTROL);

            if (mixerGetLineControls((HMIXEROBJ)hmx, &mxlctrl, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE) == MMSYSERR_NOERROR)
            {
                cChannels = mxl.cChannels;

                if (MIXERCONTROL_CONTROLF_UNIFORM & pmxctrl.fdwControl)
                    cChannels = 1;

                pUnsigned = (LPMIXERCONTROLDETAILS_UNSIGNED)malloc(cChannels * sizeof(MIXERCONTROLDETAILS_UNSIGNED));

                mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
                mxcd.dwControlID = pmxctrl.dwControlID;
                mxcd.cChannels = cChannels;
                mxcd.hwndOwner = (HWND)0;
                mxcd.cMultipleItems = pmxctrl.cMultipleItems;
                mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
                mxcd.paDetails = pUnsigned;

                mixerGetControlDetails((HMIXEROBJ)hmx, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);

                pUnsigned[0].dwValue = pUnsigned[cChannels - 1].dwValue = wVolume;

                if (mixerSetControlDetails((HMIXEROBJ)hmx, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
                    bUpdate = TRUE;

                free(pUnsigned);
            }
        }
    }
    mixerClose(hmx);

    return bUpdate;
}