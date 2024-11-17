#include "ability.hpp"
#include "global_variable.hpp"
#include "raylib.h"

#define RAD 40

void AbilityUI::Draw(){
	DrawCircleV(center, radius, color);
}

AbilityUI::AbilityUI(float radius, Vector2 center, Color color, Abilities ability, float timer)
: radius{radius}, center{center}, start_center{center}, color{color}, start_color{color}, ability{ability}, timer{timer}{
}

AbilityUI::AbilityUI(){
}

/* Ability Manager */
AbilityManager::AbilityManager(){
	for(int i=0;i<6;i++)
		circs.push_back(AbilityUI(RAD, {0,0}, BLACK, Abilities::None, 2.0f));

	distCross = 45*2;
	distLines = 24*2;

	isStoringCircCoord = false;
	isDrawingCircs = false;

	circs[0].setAbility(Abilities::FastWalk);

}

void AbilityManager::Update(){
	isDrawingCircs = false;
	isStoringCircCoord = false;

	if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) SetCircleCoord();

	MakeCircleBigger();
}

void AbilityManager::Draw(){
	if(isDrawingCircs)
		for(auto& e : circs) e.Draw();
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

void AbilityManager::CallAbility(AbilityUI& aui){
	switch(aui.getAbility()){
		case Abilities::FastWalk:{
			player->setSpeed(600);
			break;
		}

		default:
		break;
	}
}

void AbilityManager::MakeCircleBigger(){
	for(int i=0;i<circs.size();i++){
		auto& e = circs[i];
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
		if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) CallAbility(e);
	}
}
