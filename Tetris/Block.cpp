#include "pch.h"
#include "Block.h"

uint16 Block::_blockIndex[BLOCK_MODEL] = { 0, 4, 8, 12, 16, 20, 24 };
Block::AllBlockBitModel Block::_blockShape = {
		0x4640, 0x0E40, 0x4C40, 0x4E00,		//	'T'
		0x8C40, 0x6C00, 0x8C40, 0x6C00,		//	'S'
		0x4C80, 0xC600, 0x4C80, 0xC600,		//	'Z'
		0x4444, 0x0F00, 0x4444, 0x0F00,		//	'I'
		0x44C0, 0x8E00, 0xC880, 0xE200,		//	'J'
		0x88C0, 0xE800, 0xC440, 0x2E00,		//	'L'
		0xCC00, 0xCC00, 0xCC00, 0xCC00 };	//	'O'

Block::Block()
{
	BlockModelInitialization();
	RandomBlockGenerate();
}

Block::~Block()
{

}

Block* Block::RandomBlockGenerate()
{
	int randomValue = std::rand() % BLOCK_MODEL;

	_randomBlockBit = _blockShape[_blockIndex[randomValue]];
	_blockModelIndex = _blockIndex[randomValue];
	_blockModelMaxIndex = _blockModelIndex + 4;

	BlockBitConversionToArray(_randomBlockBit);

	return this;
}

void Block::BlockBitConversionToArray(uint16 randomBlockBit)
{
	uint16 tempValue;

	for (int i = 0; i < 4; i++)
	{
		tempValue = randomBlockBit & (FOUR_BIT_COMPARE_MASK << (12 - (i * 4)));
		tempValue = tempValue >> (12 - (i * 4));

		for (int j = 0; j < 4; j++)
		{
			_blockBitModel[i][j] &= tempValue;

			if (_blockBitModel[i][j] > 0)
				_blockModel[i][j] = BlockType::WALL;
		}
	}
}

Block::BlockModel Block::BlockModelChange()
{
	//	12 13 14 15 -> 12 13 14 15
	_blockModelIndex = _blockModelIndex + 1;
	if (_blockModelIndex == _blockModelMaxIndex)
		_blockModelIndex = _blockModelIndex - 4;
	
	_randomBlockBit = _blockShape[_blockModelIndex];

	BlockModelInitialization();
	BlockBitConversionToArray(_randomBlockBit);

	return _blockModel;
}

void Block::BlockModelInitialization()
{
	for (int i = 0; i < 4; i++)
		_blockBitModel[i] = { ZERO_INDEX_BIT_MASK,FIRST_INDEX_BIT_MASK,SECONDE_INDEX_BIT_MASK,THIRD_INDEX_BIT_MASK };

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			_blockModel[i][j] = BlockType::EMPTY;
}
