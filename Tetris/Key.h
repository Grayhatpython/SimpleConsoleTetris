#pragma once
#include <conio.h>

class Key
{
public:
	static bool KeyInputCheck()
	{
		int key;

		if (_kbhit())
		{
			key = _getch();

			if (key == 224) {
				key = _getch();

				if (key == 77 || key == 75 || key == 72)
				{
					if (key == 75)
						_leftKeyInput = true;
					else if (key == 77)
						_rightKeyInput = true;
					else
						_upKeyInput = true;

					return true;
				}
			}
			else
			{
				if (key == 32)
				{
					_spaceKeyInput = true;
					return true;
				}
			}
		}

		return false;
		/*if (::GetAsyncKeyState(VK_LEFT) & 0x8000)
			_leftKeyInput = true;
		else if (::GetAsyncKeyState(VK_RIGHT) & 0x8000)
			_rightKeyInput = true;

		if (_leftKeyInput == true || _rightKeyInput == true)
			return true;

		return false;*/
	}

	static void KeyInputInitialzation()
	{
		_leftKeyInput = false;
		_rightKeyInput = false;
		_upKeyInput = false;
		_spaceKeyInput = false;
	}

public:
	static bool _leftKeyInput;
	static bool _rightKeyInput;
	static bool _upKeyInput;
	static bool _spaceKeyInput;
};

