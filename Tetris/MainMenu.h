#pragma once

enum
{
	GAME_START	= 1,
	EXIT		= 2,
};

class MainMenu
{
public:
	void MenuOutput();
	bool DoYouWantPlayGame();

private:
	int16 _userInput;
};

