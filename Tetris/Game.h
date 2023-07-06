#pragma once

#include "Board.h"
#include "Block.h"

class MainMenu;

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Update();
	bool IsNotGameOver() { return _gameOver; }

private:
	std::shared_ptr<Board>	_board;
	MainMenu*				_menu;
	Block*					_block;
	Block*					_nextBlock;
	bool					_gameOver = false;
};