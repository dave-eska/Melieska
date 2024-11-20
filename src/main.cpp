#include "ability.hpp"
#include <memory>

#include <raylib.h>
#include <string>

#define MAX_FPS 60

#include "global_variable.hpp"

#include "player.hpp"

int main(){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1920, 1080, "Melieska p0.1");

    player = std::make_unique<Player>(Player("res/img/player_atlas.png", {0,0}, 500));
	AbilityManager am;

    SetTargetFPS(MAX_FPS);
    while(!WindowShouldClose()){
        player->Move(GetFrameTime());

		am.Update();

        BeginDrawing();

        ClearBackground(GRAY);

        player->Animate();

		am.Draw();
		am.DrawUI();

        DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
