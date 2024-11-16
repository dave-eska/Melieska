#pragma once

#include <raylib.h>

enum class Skills{
	FastWalk,
	FasterWalk
};

struct CircleUI{
	float radius;
	Vector2 center;
	Vector2 start_center;
	Color color{BLACK};
};
