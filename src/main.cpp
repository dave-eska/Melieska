#include <memory>

#include <raylib.h>
#include <string>

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


	player = std::make_unique<Player>(Player("res/img/player_atlas.png", {0,0}, 500));
	rad = 40;

	for(int i=0;i<6;i++)
		circs.push_back({(float)rad, {0,0}});

	distCross = 45*2;
	distLines = 24*2;

	isStoringCircCoord = false;
	isDrawingCircs = false;

	circs[0].ability = Abilities::FastWalk;
	circs[0].start_color = RED;
	circs[0].color = RED;

	SetTargetFPS(MAX_FPS);
	while(!WindowShouldClose()){
		player->Move(GetFrameTime());

		isDrawingCircs = false;
		isStoringCircCoord = false;

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
			SetCircleCoord();
		}


		MakeCircleBigger();

		BeginDrawing();

		ClearBackground(GRAY);

		player->Animate();

		if(isDrawingCircs)
			for(auto& e : circs)
			DrawCircleV(e.center, e.radius, e.color);

		DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);

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
		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
			isDrawingCircs = true;
			if(isDrawingCircs && CheckCollisionPointCircle(GetMousePosition(), e.center, e.radius)){
				e.radius = rad + 10;
				e.color = {(unsigned char)(e.start_color.r-70), (unsigned char)(e.start_color.g-70), (unsigned char)(e.start_color.b-70), 255};
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
				e.color = e.start_color;
			}
		}
		if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
			if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)){
				switch(e.ability){
					case Abilities::FastWalk:
						player->setSpeed(600);
					break;

					default:
					break;
				}
			}
	}
}
