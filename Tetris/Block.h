#pragma once

#include "Board.h"

enum
{
	BLOCK_MODEL				= 7,	
	BLOCK_ROW_SIZE			= 4,	//	가로
	BLOCK_COLUMN_SIZE		= 4,	//	세로
	BLOCK_MAX_SIZE	= 28,	//	세로
};

enum
{
	ZERO_INDEX_BIT_MASK = 8,
	FIRST_INDEX_BIT_MASK = 4,
	SECONDE_INDEX_BIT_MASK = 2,
	THIRD_INDEX_BIT_MASK = 1,
	FOUR_BIT_COMPARE_MASK = 15,
};

class Block
{
public:
	using AllBlockBitModel = std::array<uint16, BLOCK_MAX_SIZE>;
	using BlockBitModel = std::array<std::array<uint16, BLOCK_ROW_SIZE>, BLOCK_COLUMN_SIZE>;
	using BlockModel = std::array<std::array<BlockType, BLOCK_ROW_SIZE>, BLOCK_COLUMN_SIZE>;

	Block();
	~Block();

	BlockModel	GetBlockModel() const { return _blockModel; }
	void		SetBlockModel(const BlockModel& blockModel) { _blockModel = blockModel; }

	Block*		RandomBlockGenerate();
	void		BlockBitConversionToArray(uint16 randomBlockBit);
	BlockModel	BlockModelChange();
	void		BlockModelInitialization();

private:

	static AllBlockBitModel _blockShape;
	static uint16			_blockIndex[BLOCK_MODEL];
	BlockBitModel			_blockBitModel;
	BlockModel				_blockModel;
	uint16					_blockModelIndex = 0;
	uint16					_blockModelMaxIndex = 0;
	uint16					_randomBlockBit = 0;
};
