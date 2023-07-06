#include "pch.h"
#include "Game.h"
#include "Key.h"
#include "Information.h"
#include "MainMenu.h"

Game::Game() : _board(std::make_shared<Board>()), _block(new Block()), _nextBlock(new Block()), _menu(new MainMenu())
{

}

Game::~Game()
{
	if (_block)
		delete _block;

	if (_nextBlock)
		delete _nextBlock;

	if (_menu)
		delete _menu;
}

void Game::Init()
{
	_board->Init();
}

void Game::Update()
{
	if (_menu->DoYouWantPlayGame() == false)
		_gameOver = true;

	if (_gameOver == false)
	{
		while (true)
		{
			if (Time::DeltaTickCheck() == true)
			{
				// Logic
				_board->Logic(_block);

				//	Render
				_board->Render();

				if (_board->GetblockMoveability() == false)
				{
					if (_block)
					{
						delete _block;
						_block = nullptr;
					}

					_block = _nextBlock;
					_nextBlock = new Block();

					_board->SetBlockMoveability();
					_board->SetBlockEnterPosition();

					if (_board->GameAvailability(_block) == false)
					{
						_gameOver = true;
						break;
					}
				}

				Information::InformationOutput(_nextBlock);
			}

			if (Time::KeyInputTickCheck() == true)
			{
				if (Key::KeyInputCheck())
				{
					// Logic
					_board->Logic(_block);

					//	Render
					_board->Render();
				}
			}
		}
	}
}
