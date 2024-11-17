#pragma once

#include <vector>

#include <raylib.h>

enum class Abilities{
	None,
	FastWalk,
	FasterWalk
};

class AbilityUI{
private:
	float radius;

	Color color{BLACK};
	Color start_color{BLACK};

	Abilities ability;

	float timer{0.0f};
public:
	Vector2 center;
	Vector2 start_center;
	void setRadius(float newRadius){ radius = newRadius; }
	void setStartCenter(Vector2 newCenter){ start_center = newCenter; }
	void setCenter(Vector2 newCenter){ center = newCenter; }
	void setAbility(Abilities newAbility){ ability = newAbility; }
	void setColor(Color newColor){ color = newColor; }

	Vector2 getCurrentCenter(){ return center; }
	Vector2 getStartCenter(){ return start_center; }

	Color getColor(){ return color; }
	Color getStartColor(){ return start_color; }

	float getRadius(){ return radius; }

	Abilities getAbility(){ return ability; }

	void Draw();

	AbilityUI(float radius, Vector2 center, Color color, Abilities ability, float timer);
	AbilityUI();

};

class AbilityManager{
private:
	std::vector<AbilityUI> circs;

	int distCross;
	int distLines;

	int isStoringCircCoord;
	int isDrawingCircs;

	void SetCircleCoord();
	void MakeCircleBigger();
	void CallAbility(AbilityUI& aui);
public:

	void Update();
	void Draw();

	AbilityManager();
};
