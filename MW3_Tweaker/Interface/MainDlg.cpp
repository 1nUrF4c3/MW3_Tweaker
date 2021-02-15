//=====================================================================================

#include "MainDlg.h"

//=====================================================================================

cMainDlg::cMainDlg(HINSTANCE instance) : cDialog(IDD_MAIN), _instance(instance)
{
	_messages[WM_INITDIALOG] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnInit);
	_messages[WM_COMMAND] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnCommand);
	_messages[WM_CLOSE] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnClose);
	_messages[WM_HSCROLL] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnSlider);
	_messages[WM_TIMER] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnTimer);
}

//=====================================================================================

INT_PTR cMainDlg::OnInit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	cDialog::OnInit(hDlg, message, wParam, lParam);

	HICON hIcon = LoadIcon(_instance, MAKEINTRESOURCE(IDI_ICON));

	SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	DeleteObject(hIcon);

	_fieldOfView.Attach(_hwnd, IDC_FIELDOFVIEW);
	_framesPerSecond.Attach(_hwnd, IDC_FRAMESPERSECOND);

	_fovText.Attach(_hwnd, IDC_FOVTEXT);
	_fpsText.Attach(_hwnd, IDC_FPSTEXT);

	_fieldOfView.SetRange(65, 120);
	_fieldOfView.Position(65);

	_framesPerSecond.SetRange(0, 240);
	_framesPerSecond.Position(85);

	SetTimer(_hwnd, IDT_TIMER, 1, (TIMERPROC)NULL);

	RefreshGUI();

	return TRUE;
}

//=====================================================================================

INT_PTR cMainDlg::OnClose(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return cDialog::OnClose(hDlg, message, wParam, lParam);
}

//=====================================================================================

INT_PTR cMainDlg::OnSlider(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if ((HWND)lParam == _fieldOfView.GetHwnd() || (HWND)lParam == _framesPerSecond.GetHwnd())
		RefreshGUI();

	return TRUE;
}

//=====================================================================================

INT_PTR cMainDlg::OnTimer(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (wParam == IDT_TIMER)
	{
		cMemory::MemWrite("iw5mp.exe", CG_FOV, (float)_fieldOfView.Position());
		cMemory::MemWrite("iw5mp.exe", COM_MAXFPS, (int)_framesPerSecond.Position());
	}

	return TRUE;
}

//=====================================================================================