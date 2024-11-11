#include "player.hpp"
#include "raylib.h"

void Player::Update(float dt){
    float inputX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float inputY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

	body.x += inputX * speed * dt;
	body.y += inputY * speed * dt;
}

void Player::Draw(){
	DrawRectangleRec(body, DARKBLUE);
}

Player::Player(Vector2 pos): body{pos.x, pos.y, 120, 120}, speed{250}{
}
