#include "pch.h"
#include "Information.h"
#include "Block.h"
#include "Board.h"

int32 Information::_gameScore = 0;

void Information::InformationOutput(Block* nextBlock)
{
	Block::BlockModel nextBlockModel = nextBlock->GetBlockModel();

	ConsoleHelper::SetCursorPosition(32, 2);
	ConsoleHelper::SetCursorColor(ConsoleColor::WHITE);
	std::cout << "GameScore : " << _gameScore;

	for (int32 y = 0; y < 4; y++)
	{
		ConsoleHelper::SetCursorPosition(36, 6 + y);

		for (int32 x = 0; x < 4; x++)
		{
			if (nextBlockModel[y][x] == BlockType::WALL)
				std::cout << "бс";
			else
				std::cout << "  ";
		}
	}
}