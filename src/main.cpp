#include "ability.hpp"
#include "tile.hpp"
#include "world.hpp"
#include <memory>

#include <raylib.h>
#include <string>

#define MAX_FPS 60

#include "global_variable.hpp"

#include "player.hpp"

int main(){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1920, 1080, "Melieska p0.1");

	level = new Level("res/levels/test.json");

    player = std::make_unique<Player>(Player("res/img/player_atlas.png", {TILE_SIZE*2,TILE_SIZE*3}, 500, *level->b2world));
	AbilityManager am;

	camera = { 0 };
	camera.target = (Vector2){ player->getBody().x + (player->getBody().width/2), player->getBody().y + (player->getBody().height/2) };
	camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 0.6f;

	float minZoom = 0.1f;
    float maxZoom = 3.0f;

	isDebugging = false;

	SetTargetFPS(MAX_FPS);
	while(!WindowShouldClose()){

		float wheelMove = GetMouseWheelMove();
		if (wheelMove != 0.0f) {
			camera.zoom += wheelMove * 0.1f; // Adjust zoom sensitivity if needed
			if (camera.zoom < minZoom) camera.zoom = minZoom;
			if (camera.zoom > maxZoom) camera.zoom = maxZoom;
		}

		if(IsKeyPressed(KEY_X))
			isDebugging = !isDebugging;

		player->Move(GetFrameTime());
		camera.target = (Vector2){ player->getBody().x + (player->getBody().width/2), player->getBody().y + (player->getBody().height/2) };

		level->Update(GetFrameTime());

		am.Update();

		BeginDrawing();

		ClearBackground(GRAY);

		BeginMode2D(camera);

		level->Draw();
		player->Animate();

		EndMode2D();

		am.Draw();
		am.DrawUI();

		if(isDebugging){
			DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);
			DrawText(std::to_string(GetFPS()).c_str(), 0, GetScreenHeight() - 50, 35, GREEN);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
