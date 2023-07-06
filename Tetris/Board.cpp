#include "pch.h"
#include "Board.h"
#include "Block.h"
#include "Information.h"

Board::Board()
{
}

Board::~Board()
{

}

void Board::Init()
{
	GenerateBoard();
}

void Board::Logic(Block* block)
{
	BlockMoveability(block);
}

void Board::BlockMoveability(Block* block)
{
	int index = 0;

	if (Key::_leftKeyInput == true || Key::_rightKeyInput == true)
		LeftRightMoveBlockCheck(block);
	else if (Key::_upKeyInput == true)
		BlockRotation(block);
	else if (Key::_spaceKeyInput == true)
		ContinuesBlockDownToBottom(block);
	else
	{
		if (DownMoveBlockCheck(block) == false)
			RemoveBlockLines();
	}

	Key::KeyInputInitialzation();
}

bool Board::DownMoveBlockCheck(Block* block)
{
	int index = 0;

	Block::BlockModel blockModel = block->GetBlockModel();
	Position blockPreviewPositon[4] = { _blockPreviewPosition[0],_blockPreviewPosition[1],
	_blockPreviewPosition[2] ,_blockPreviewPosition[3] };

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[y][x] == BlockType::WALL && _board[_blockEnterPosition.y + y][_blockEnterPosition.x + x] == BlockType::WALL)
			{
				for (int i = 0; i < 4; i++)
				{
					_blockPreviewPosition[i] = {};
					_board[blockPreviewPositon[i].y][blockPreviewPositon[i].x] = BlockType::WALL;
				}

				_blockMoveability = false;
				return false;
			}

			if (blockModel[y][x] == BlockType::WALL)
			{
				_blockPreviewPosition[index] = Position{ _blockEnterPosition.y + y, _blockEnterPosition.x + x };
				index++;
			}
		}
	}

	return true;
}

bool Board::LeftRightMoveBlockCheck(Block* block)
{
	_blockEnterPosition.y -= 1;

	int index = 0;

	Block::BlockModel blockModel = block->GetBlockModel();
	Position blockPreviewPositon[4] = { _blockPreviewPosition[0],_blockPreviewPosition[1],
	_blockPreviewPosition[2] ,_blockPreviewPosition[3] };

	Position blockEnterPosition = _blockEnterPosition;

	if (Key::_leftKeyInput == true)
		blockEnterPosition.x -= 1;
	if (Key::_rightKeyInput == true)
		blockEnterPosition.x += 1;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[y][x] == BlockType::WALL && _board[blockEnterPosition.y + y][blockEnterPosition.x + x] == BlockType::WALL)
			{
				for (int i = 0; i < 4; i++)
					_blockPreviewPosition[i] = blockPreviewPositon[i];

				return false;
			}

			if (blockModel[y][x] == BlockType::WALL)
			{
				_blockPreviewPosition[index] = Position{ blockEnterPosition.y + y, blockEnterPosition.x + x };
				index++;
			}
		}
	}

	_blockEnterPosition = blockEnterPosition;

	return true;
}

bool Board::BlockRotation(Block* block)
{
	_blockEnterPosition.y -= 1;

	int index = 0;

	Block::BlockModel beforeBlockModel = block->GetBlockModel();
	Block::BlockModel rotationBlockModel = block->BlockModelChange();

	Position blockPreviewPositon[4] = { _blockPreviewPosition[0],_blockPreviewPosition[1],
	_blockPreviewPosition[2] ,_blockPreviewPosition[3] };

	Position blockEnterPosition = _blockEnterPosition;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (rotationBlockModel[y][x] == BlockType::WALL && _board[blockEnterPosition.y + y][blockEnterPosition.x + x] == BlockType::WALL)
			{
				for (int i = 0; i < 4; i++)
					_blockPreviewPosition[i] = blockPreviewPositon[i];

				block->SetBlockModel(beforeBlockModel);

				return false;
			}

			if (rotationBlockModel[y][x] == BlockType::WALL)
			{
				_blockPreviewPosition[index] = Position{ blockEnterPosition.y + y, blockEnterPosition.x + x };
				index++;
			}
		}
	}

	_blockEnterPosition = blockEnterPosition;

	return true;
}

bool Board::ContinuesBlockDownToBottom(Block* block)
{
	while (DownMoveBlockCheck(block) == true)
		_blockEnterPosition.y += 1;

	RemoveBlockLines();

	return true;
}

bool Board::GameAvailability(Block* block)
{
	Block::BlockModel blockModel = block->GetBlockModel();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[y][x] == BlockType::WALL && _board[_blockEnterPosition.y + y][_blockEnterPosition.x + x] == BlockType::WALL)
				return false;
		}
	}
	
	return true;
}

void Board::RemoveBlockLines()
{
	int line = 0;

	for (int32 y = BOARD_COLUMN_SIZE - 2 ; y > 0 ; y--)
	{
		for (int32 x = 1; x < BOARD_ROW_SIZE - 1; x++)
		{
			if (_board[y][x] == BlockType::WALL)
				line++;
		}
		if (line == BOARD_ROW_SIZE - 2)
		{
			for (int l = 0; l < y - 1; l++)
				::memcpy(&_board[y - l][1], &_board[y - l - 1][1], sizeof(BlockType) * line);
			
			y += 1;

			Information::_gameScore += 10;
		}

		line = 0;
	}
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	bool blockCheck = false;
	int boolCheckCount = 0;

	for (int32 y = 0; y < BOARD_COLUMN_SIZE; y++)
	{
		for (int32 x = 0; x < BOARD_ROW_SIZE; x++)
		{
			if (boolCheckCount < 4)
			{
				for (int32 i = 0; i < 4; i++)
				{
					if (y == _blockPreviewPosition[i].y && x == _blockPreviewPosition[i].x)
					{
						ConsoleHelper::SetCursorColor(ConsoleColor::GREEN);
						std::cout << _blockOutput;
						blockCheck = true;
						boolCheckCount++;
						break;
					}
				}
			}

			if (blockCheck == false)
			{
				if (GetBlockType(Position{ y,x }) == BlockType::WALL)
				{
					ConsoleColor color = GetTileColor(Position{ y,x });
					ConsoleHelper::SetCursorColor(color);
					std::cout << _blockOutput;
				}
				else
					std::cout << "  ";
			}

			blockCheck = false;
		}
		std::cout << std::endl;
	}

	_blockEnterPosition.y += 1;
}

void Board::GenerateBoard()
{
	for (int32 x = 1; x < BOARD_ROW_SIZE - 1; x++)
	{
		_board[BOARD_COLUMN_SIZE - 1][x] = BlockType::WALL;
	}

	for (int32 y = 0; y < BOARD_COLUMN_SIZE; y++)
	{
		_board[y][0] = BlockType::WALL;
		_board[y][BOARD_ROW_SIZE - 1] = BlockType::WALL;
	}

	for (int32 y = 0; y < BOARD_COLUMN_SIZE; y++)
	{
		for (int32 x = 0; x < BOARD_ROW_SIZE; x++)
		{
			if (_board[y][x] != BlockType::WALL)
				_board[y][x] = BlockType::EMPTY;
		}
	}
}


BlockType Board::GetBlockType(Position position)
{
	if (position.x < 0 || position.x >= BOARD_ROW_SIZE)
		return BlockType::NONE;

	if (position.y < 0 || position.y >= BOARD_COLUMN_SIZE)
		return BlockType::NONE;

	return _board[position.y][position.x];
}

ConsoleColor Board::GetTileColor(Position position)
{
	BlockType blockType = GetBlockType(position);

	switch (blockType)
	{
	case BlockType::WALL:
		return ConsoleColor::GREEN;
		break;
	default:
		break;
	}

	return ConsoleColor::WHITE;
}
