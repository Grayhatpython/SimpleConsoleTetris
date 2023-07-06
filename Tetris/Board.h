#pragma once

#include "ConsoleHelper.h"

class Block;
//	행 가로 ( row )
//	열 세로 ( column )

enum
{
	BOARD_ROW_SIZE = 14,
	BOARD_COLUMN_SIZE = 26
};

enum
{
	BLOCK_START_Y_POSITION = 0,
	BLOCK_START_X_POSITION = 5,
};


enum class BlockType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Board : public std::enable_shared_from_this<Board>
{
public:
	Board();
	~Board();

	void			Init();
	void			Logic(Block* block);
	void			Render();
	void			GenerateBoard();

	bool			DownMoveBlockCheck(Block* block);
	bool			LeftRightMoveBlockCheck(Block* block);
	bool			BlockRotation(Block* block);
	void			BlockMoveability(Block* block);
	bool			GameAvailability(Block* block);
	bool			ContinuesBlockDownToBottom(Block* block);

	void			RemoveBlockLines();

	bool			GetblockMoveability() { return _blockMoveability; }
	void			SetBlockMoveability() { _blockMoveability = true; }
	void			SetBlockEnterPosition() { _blockEnterPosition = { BLOCK_START_Y_POSITION,BLOCK_START_X_POSITION }; }


	BlockType		GetBlockType(Position position);
	ConsoleColor	GetTileColor(Position position);
	std::shared_ptr<Board> GetSharedPtr() { return shared_from_this(); }

public:
	int test = 0;

private:
	BlockType		_board[BOARD_COLUMN_SIZE][BOARD_ROW_SIZE] = {};
	Position		_blockEnterPosition = { BLOCK_START_Y_POSITION,BLOCK_START_X_POSITION };
	Position		_blockPreviewPosition[4] = {};
	const char*		_blockOutput = "■";	
	bool			_blockMoveability = true;
};

