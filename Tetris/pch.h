#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <chrono>
#include <iomanip>
#include <random>
#include <Windows.h>
#include <memory>
#include <array>
#include <iomanip>

#include "Types.h"
#include "Time.h"
#include "ConsoleHelper.h"
#include "Key.h"

struct Position
{
	bool operator==(Position& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Position& other)
	{
		return !(*this == other);
	}

	bool operator<(const Position& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	Position operator+(Position& other)
	{
		Position ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Position& operator+=(Position& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4,
};