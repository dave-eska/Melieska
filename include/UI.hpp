#pragma once

#include <raylib.h>

enum class Abilities{
	FastWalk,
	FasterWalk
};

struct CircleUI{
	float radius;

	Vector2 center;
	Vector2 start_center;

	Color color{BLACK};
	Color start_color{BLACK};

	Abilities ability;
};
