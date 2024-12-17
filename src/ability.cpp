#include "ability.hpp"

#include <iostream>
#include <ostream>
#include <string>

#include <raylib.h>

#include "global_functions.hpp"

#define RAD 40

void Circle::Update(Player& player){
	if(isTimerStart && timer > 0){
		timer -= GetFrameTime();
		if(applyAbility){
			std::cout<<(int)ability<<std::endl;
			switch(getAbility()){
				case Abilities::FastWalk:{
					std::string temp = getAbility() == Abilities::FastWalk ? "Fastwalk" : "Not Fastwalk lol kys nerd!";
					std::cout<< temp <<std::endl;
					player.setSpeed(600);
					break;
				}

				default:
				break;
			}
			applyAbility = false;
		}
	}

	if(isTimerDone()){
		switch(getAbility()){
			case Abilities::FastWalk:{
				player.setSpeed(500);
				break;
			}

			default:
			break;
		}
		resetTimer();
	}

}

void Circle::Draw(){
	DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, {center.x-radius, center.y-radius, radius*2, radius*2}, {0, 0}, 0, WHITE);
}

void Circle::DrawUI(){
	if(isTimerStart)
		DrawText(std::to_string((int)timer).c_str(), GetScreenWidth()-75, GetScreenHeight()-75, 60, GetRainbowColor());
}

void Circle::applyEffect(SelectorMode mode){
	switch(mode){
		case SelectorMode::Ability:
			startTimer();
		break;

		case SelectorMode::Emotes:
		break;

		default:
		break;
	}

}

void Circle::startTimer(){
	isTimerStart = true;
	applyAbility = true;
}

Circle::Circle(float radius, Vector2 center, Color color, Abilities ability, float timer)
: radius{radius}, center{center}, start_center{center}, color{color}, start_color{color}, ability{ability}, timer{timer}, start_timer{timer}{
	texture = LoadTexture("res/img/inventory_outline.png");
}

Circle::Circle(){
}

/* Ability Manager */
AbilityManager::AbilityManager(Player& player) : player(player){
	for(int i=0;i<6;i++){
		auto temp = Circle(RAD, {0,0}, BLACK, Abilities::None, 15.0f);
		temp.setIDX(circs.size());
		circs.push_back(temp);
	}

	distCross = 45*2;
	distLines = 24*2;

	isStoringCircCoord = false;
	isDrawingCircs = false;

	circs[0].setAbility(Abilities::FastWalk);
}

void AbilityManager::Update(){
	if(!IsKeyDown(KEY_E)) mode = SelectorMode::Ability;
	isDrawingCircs = false;
	isStoringCircCoord = false;

	if(IsKeyDown(KEY_E)) mode = SelectorMode::Emotes;

	if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) SetCircleCoord();
	for(int i=0;i<circs.size();i++){
		auto& e = circs[i];
		e.Update(player);
		MakeCircleBigger(e, i);
	}

}

void AbilityManager::Draw(){
	if(isDrawingCircs)
		for(auto& e : circs){
			e.Draw();
			switch(mode){
				case SelectorMode::Emotes:
					DrawCircleV(e.getCurrentCenter(), e.getRadius(), {DARKPURPLE.r, DARKPURPLE.g, DARKPURPLE.b, 255/2});
				break;
				case SelectorMode::Ability:
					//DrawCircleV(e.getCurrentCenter(), e.getRadius(), {DARKPURPLE.r, DARKPURPLE.g, DARKPURPLE.b, 255/2});
				break;
				default:
				break;
			}
	}
}

void AbilityManager::DrawUI(){
	for(auto& e : circs) e.DrawUI();
	DrawText("Mode:",  10, GetScreenHeight()-30, 25, BLACK);
	DrawText(std::to_string((int)mode).c_str(), 100, GetScreenHeight()-30, 25, BLACK);
}

void AbilityManager::SetCircleCoord(){
	isStoringCircCoord = true;
	if(isStoringCircCoord){
		Vector2 mpos = GetMousePosition();
		circs[0].setCenter({mpos.x - distCross, mpos.y + distLines});
		circs[0].setStartCenter({mpos.x - distCross, mpos.y + distLines});
		circs[1].setCenter({mpos.x, mpos.y - distCross});
		circs[1].setStartCenter({mpos.x, mpos.y - distCross});
		circs[2].setCenter({mpos.x + distCross, mpos.y - distLines});
		circs[2].setStartCenter({mpos.x + distCross, mpos.y - distLines});
		circs[3].setCenter({mpos.x + distCross, mpos.y + distLines});
		circs[3].setStartCenter({mpos.x + distCross, mpos.y + distLines});
		circs[4].setCenter({mpos.x, mpos.y + distCross});
		circs[4].setStartCenter({mpos.x, mpos.y + distCross});
		circs[5].setCenter({mpos.x - distCross, mpos.y - distLines});
		circs[5].setStartCenter({mpos.x - distCross, mpos.y - distLines});
	}
	isStoringCircCoord = false;
}

void AbilityManager::MakeCircleBigger(Circle& e, int i){
	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
		isDrawingCircs = true;
		if(isDrawingCircs && CheckCollisionPointCircle(GetMousePosition(), e.getCurrentCenter(), e.getRadius())){
			e.setRadius(RAD + 10);
			e.setColor({(unsigned char)(e.getStartColor().r-70), (unsigned char)(e.getStartColor().g-70), (unsigned char)(e.getStartColor().b-70), 255});
			switch(i){
				case 0:
					e.setCenter({e.getStartCenter().x - 7, e.getStartCenter().y + 7});
				break;

				case 1:
					e.setCenter({e.getCurrentCenter().x, e.getStartCenter().y - 7});
				break;

				case 2:
					e.setCenter({e.getStartCenter().x + 7, e.getStartCenter().y - 7});
				break;

				case 3:
					e.setCenter({e.getStartCenter().x + 7, e.getStartCenter().y + 7});
				break;

				case 4:
					e.setCenter({e.getCurrentCenter().x, e.getStartCenter().y + 7});
				break;

				case 5:
					e.setCenter({e.getStartCenter().x - 7, e.getStartCenter().y - 7});
				break;
			}
		}else{
			e.setCenter(e.getStartCenter());
			e.setRadius(RAD);
			e.setColor(e.getStartColor());
		}
	}
	if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && CheckCollisionPointCircle(GetMousePosition(), e.getCurrentCenter(), e.getRadius()) && e.getAbility() != Abilities::None){
		e.applyEffect(mode);
	}
}
