#pragma once

class Block;

class Information
{
public:
	static void InformationOutput(Block* nextBlock);

public:
	static int32	_gameScore;
	Block*			_nextBlock;
};

