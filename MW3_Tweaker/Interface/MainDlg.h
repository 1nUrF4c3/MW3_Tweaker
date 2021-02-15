//=====================================================================================

#pragma once

#include "../Resources/Resource.h"
#include "../Interface/WinAPI/Dialog.hpp"
#include "../Interface/WinAPI/Slider.hpp"
#include "../Interface/WinAPI/Static.hpp"
#include "../Helpers/Memory.hpp"

//=====================================================================================

#define CG_FOV 0x59E8EC4
#define COM_MAXFPS 0x59D1F88

//=====================================================================================

class cMainDlg : public cDialog
{
public:

	cMainDlg(HINSTANCE instance);
	~cMainDlg() {};

private:

	void RefreshGUI();

	DLG_HANDLER(OnInit);
	DLG_HANDLER(OnClose);
	DLG_HANDLER(OnSlider);
	DLG_HANDLER(OnTimer);

	ctrl::cSlider _fieldOfView;
	ctrl::cSlider _framesPerSecond;

	ctrl::cStatic _fovText;
	ctrl::cStatic _fpsText;

	HINSTANCE _instance;
};

//=====================================================================================