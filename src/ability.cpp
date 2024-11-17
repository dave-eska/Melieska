#include "ability.hpp"
#include "raylib.h"


void AbilityUI::Draw(){
	DrawCircleV(center, radius, color);
}

AbilityUI::AbilityUI(float radius, Vector2 center, Color color, Abilities ability)
: radius{radius}, center{center}, start_center{center}, color{color}, start_color{color}, ability{ability}{
}

AbilityUI::AbilityUI(){
}
