#pragma once

#include "player.hpp"
#include <map>
#include <string>
#include <vector>

#include <raylib.h>

enum class Abilities{
	None,
	FastWalk,
	FasterWalk,
};

inline std::map<Abilities, std::string> abilityToString = {
	{Abilities::None, "(abilities)None"},
	{Abilities::FastWalk, "FastWalk"},
	{Abilities::FasterWalk, "FasterWalk"}
};

// Emotes will be read from ./res/animations/emotes.json
// file structure should be:
// {
//		"emoteName": {
//			"file-path": "/path/to/.png"
//			"fps": [TOTAL_FPS]
//		}
// }

enum class Emotes{
	None,
	BDR,
};

inline std::map<Emotes, std::string> emoteToString = {
	{Emotes::None, "(emotes)None"},
	{Emotes::BDR, "BDR"}
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

	//Circles has slots. rn theres 2; ability and emote.
	Abilities ability;

	Vector2 center;
	Vector2 start_center;

	float timer{0.0f};
	float start_timer{0.0f};
	bool isTimerStart{false};

	Emotes emote;
	bool runEmote{false};

	bool applyAbility{false};

	Texture2D texture;

	int idx;
public:
	void setRadius(float newRadius){ radius = newRadius; }
	void setStartCenter(Vector2 newCenter){ start_center = newCenter; }
	void setCenter(Vector2 newCenter){ center = newCenter; }
	void setColor(Color newColor){ color = newColor; }

	Vector2 getCurrentCenter(){ return center; }
	Vector2 getStartCenter(){ return start_center; }

	Color getColor(){ return color; }
	Color getStartColor(){ return start_color; }

	float getRadius(){ return radius; }

	void setAbility(Abilities newAbility){ ability = newAbility; }

	Abilities getAbility(){ return ability; }
	bool getApplyAbility(){ return applyAbility; }

	void setEmote(Emotes newEmote){ emote = newEmote; }

	void setIDX(int idx){ this->idx = idx; }
	int getIDX(){ return idx; }

	void applyEffect(SelectorMode mode);

	//Ability timer
	void startTimer();
	void resetTimer(){ timer = start_timer; isTimerStart = false; }
	bool isTimerDone(){ return timer <= 0.0f; }

	void Update(Player& player);
	void Draw(SelectorMode mode);
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
