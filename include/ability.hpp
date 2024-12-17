#pragma once

#include "player.hpp"
#include <vector>

#include <raylib.h>

enum class Abilities{
	None,
	FastWalk,
	FasterWalk,
};

enum class SelectorMode{
	None,
	Ability,
	Emotes,
};

class Circle{
private:
	float radius;
	Color color{BLACK};
	Color start_color{BLACK};

	Abilities ability;

	Vector2 center;
	Vector2 start_center;

	float timer{0.0f};
	float start_timer{0.0f};
	bool isTimerStart{false};

	bool applyAbility{false};

	Texture2D texture;

	int idx;
public:
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

	void setIDX(int idx){ this->idx = idx; }
	int getIDX(){ return idx; }

	bool getApplyAbility(){ return applyAbility; }

	void applyEffect(SelectorMode mode);

	//Ability timer
	void startTimer();
	void resetTimer(){ timer = start_timer; isTimerStart = false; }
	bool isTimerDone(){ return timer <= 0.0f; }

	void Update(Player& player);
	void Draw();
	void DrawUI();

	Circle(float radius, Vector2 center, Color color, Abilities ability, float timer);
	Circle();

};

class AbilityManager{
private:
	SelectorMode mode{SelectorMode::Ability};

	std::vector<Circle> circs;

	int distCross;
	int distLines;

	int isStoringCircCoord;
	int isDrawingCircs;

	Player& player;

	void SetCircleCoord();
	void MakeCircleBigger(Circle& e, int i);
public:

	void Update();
	void Draw();
	void DrawUI();

	AbilityManager(Player& player);
	AbilityManager();
};
