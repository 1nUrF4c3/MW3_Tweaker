//=====================================================================================

#include "MainDlg.h"

//=====================================================================================

void cMainDlg::RefreshGUI()
{
	_fieldOfView.Position() == 65 ?
		_fovText.Text("FOV (Default)") :
		_fovText.Text("FOV (" + std::to_string(_fieldOfView.Position()) + ")");

	_framesPerSecond.Position() == 85 ?
		_fpsText.Text("FPS (Default)") :
		_framesPerSecond.Position() == 0 ?
		_fpsText.Text("FPS (Unlimited)") :
		_fpsText.Text("FPS (" + std::to_string(_framesPerSecond.Position()) + ")");
}

//=====================================================================================