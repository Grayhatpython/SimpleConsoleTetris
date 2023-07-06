#include "pch.h"
#include "Time.h"

timeTick Time::moveCurrentTick;
timeTick Time::keyInputCurrentTick;
std::chrono::nanoseconds Time::deltaTick;
std::chrono::nanoseconds Time::keyInputTick;