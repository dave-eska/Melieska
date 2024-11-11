#include <raylib.h>

#define MAX_FPS 60

#include "player.hpp"

int main(){

	InitWindow(1920, 1080, "Melieska p0.1");

	Player player({(float)GetScreenWidth()/2, (float)GetScreenHeight()/2});

	SetTargetFPS(MAX_FPS);

	while(!WindowShouldClose()){
		player.Update(GetFrameTime());

		BeginDrawing();

		ClearBackground(GRAY);

		player.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
