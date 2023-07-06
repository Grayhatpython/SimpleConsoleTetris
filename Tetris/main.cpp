#include "pch.h"
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Game game;

	//	초기화
	game.Init();

	Time::CurrentTickCheck();

	while (true)
	{
		//	로직
		game.Update();

		if (game.IsNotGameOver() == true)
			break;
	}
	
	return 0;
}