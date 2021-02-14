//=====================================================================================

#pragma once

#include "Control.hpp"

//=====================================================================================

namespace ctrl
{
	class cSlider : public cControl
	{
	public:

		cSlider(HWND hwnd = NULL)
			: cControl(hwnd) {  }

		LRESULT SetRange(int minimum, int maximum) 
		{
			return SendMessage(_hwnd, TBM_SETRANGE, 1, MAKELONG(minimum, maximum)); 
		}

		LRESULT Position()
		{ 
			return SendMessage(_hwnd, TBM_GETPOS, 0, 0);
		}

		LRESULT Position(int pos) 
		{ 
			return SendMessage(_hwnd, TBM_SETPOS, 1, pos);
		}
	};
}

//=====================================================================================