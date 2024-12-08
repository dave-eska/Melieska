#include <iostream>
#include <ostream>
#include <string>

#include <raylib.h>

#include "gameplay.hpp"
#include "global_variable.hpp"

int main(int argc, char *argv[]){
	if(argc < 2){
		std::cerr << "Usage: ./main1 [server | game]\n";
		return 1;
	}

	std::string appMode = argv[1];

	if(appMode == "server"){
	}else if(appMode == "game"){
		SetTraceLogLevel(LOG_NONE);
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);

		InitWindow(1920, 1080, "Melieska");

		Gameplay* gameplay = new Gameplay();

		isDebugging = false;
		isTyping = false;

		SetTargetFPS(60);
		while(!WindowShouldClose()){
			if(IsKeyPressed(KEY_X))
				isDebugging = !isDebugging;

			gameplay->Update(GetFrameTime());

			BeginDrawing();

			ClearBackground(GRAY);

			gameplay->Draw();

			EndDrawing();
		}

		CloseWindow();
	}else{
		std::cerr << "Invalid appmode! \n Usage: ./main1 [server | game]\n";
		return 1;
	}

	return 0;
}
