#pragma once

enum class EDirection {
	UP	  = 1,
	DOWN  = 2,
	LEFT  = 3,
	RIGHT = 4,
	ARROW = 224
};

bool operator==(int a, EDirection b)
{
	return a == static_cast<int>(b);
}

bool operator!=(int a, EDirection b)
{
	return a != static_cast<int>(b);
}