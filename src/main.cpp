#include <memory>

#include <raylib.h>

#define MAX_FPS 60

#include "player.hpp"
#include "UI.hpp"

static std::unique_ptr<Player> player;
static std::vector<CircleUI> circs;
static int rad;

static int distCross;
static int distLines;

static bool isStoringCircCoord;
static bool isDrawingCircs;

void SetCircleCoord();
void MakeCircleBigger();

int main(){

	InitWindow(1920, 1080, "Melieska p0.1");

	for(int i=0;i<6;i++)
		circs.push_back({40, {0,0}});

	player = std::make_unique<Player>(Player("res/img/player_atlas.png", {0,0}, 500));

	rad = 40;

	distCross = 45*2;
	distLines = 24*2;

	isStoringCircCoord = false;
	isDrawingCircs = false;

	SetTargetFPS(MAX_FPS);
	while(!WindowShouldClose()){
		player->Move(GetFrameTime());

		isDrawingCircs = false;
		isStoringCircCoord = false;

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
			SetCircleCoord();
		}

		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			isDrawingCircs = true;

		MakeCircleBigger();

		BeginDrawing();

		ClearBackground(GRAY);

		player->Animate();

		if(isDrawingCircs)
			for(auto& e : circs)
			DrawCircleV(e.center, e.radius, e.color);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void SetCircleCoord(){
	isStoringCircCoord = true;
	if(isStoringCircCoord){
		Vector2 mpos = GetMousePosition();
		circs[0].center = {mpos.x - distCross, mpos.y + distLines};
		circs[1].center = {mpos.x, mpos.y - distCross};
		circs[2].center = {mpos.x + distCross, mpos.y - distLines};
		circs[3].center = {mpos.x + distCross, mpos.y + distLines};
		circs[4].center = {mpos.x, mpos.y + distCross};
		circs[5].center = {mpos.x - distCross, mpos.y - distLines};
		for(auto& e:circs)
		e.start_center = e.center;
	}
	isStoringCircCoord = false;
}

void MakeCircleBigger(){
	for(int i=0;i<circs.size();i++){
		auto& e = circs[i];
		if(isDrawingCircs && CheckCollisionPointCircle(GetMousePosition(), e.center, e.radius)){
			e.radius = rad + 10;
			e.color = {100, 100, 100, 255};
			switch(i){
				case 0:
					e.center.x = e.start_center.x - 7;
					e.center.y = e.start_center.y + 7;
				break;

				case 1:
					e.center.y = e.start_center.y - 7;
				break;

				case 2:
					e.center.x = e.start_center.x + 7;
					e.center.y = e.start_center.y - 7;
				break;

				case 3:
					e.center.x = e.start_center.x + 7;
					e.center.y = e.start_center.y + 7;
				break;

				case 4:
					e.center.y = e.start_center.y + 7;
				break;

				case 5:
					e.center.x = e.start_center.x - 7;
					e.center.y = e.start_center.y - 7;
				break;
			}
		}else{
			e.center = e.start_center;
			e.radius = rad;
			e.color = BLACK;
		}
	}
}
