#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "animation.h"

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

    int speed;
public:
    Rectangle getBody(){ return body; }
    Vector2 getPos(){ return {body.x, body.y}; }

    std::string getDirection();

    void Move(float dt);
    void Animate();

    Player(const char* texture_path, Vector2 pos, int speed);
};
