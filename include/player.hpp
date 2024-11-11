#pragma once

#include <raylib.h>

class Player{
private:
	Rectangle body;
	int speed;
public:

	void Update(float dt);
	void Draw();

	Player(Vector2 pos);
};
