#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include <box2d/b2_body.h>

#include "animation.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

class Player{
private:
    Rectangle body;

    Texture2D texture;
    std::vector<SpriteAnimation> animations;

    int current_animation;
    int direction;

	b2Body* kinematicBody;
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;

	int speed;
public:
	Rectangle getBody(){ return body; }
	Vector2 getPos(){ return {body.x, body.y}; }

	int getSpeed(){ return speed; }
	void setSpeed(int newSpeed){ speed = newSpeed; }

	std::string getDirection();

	void Move(float dt);
	void Animate();

	Player(const char* texture_path, Vector2 pos, int speed,
               b2World& world);
	Player();
};
