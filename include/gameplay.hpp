#pragma once

#include <string>
#include <vector>

#include "world.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "ability.hpp"

class Gameplay : public Scene{
private:
	Level* level;

	Player* player;
	AbilityManager* am;

	std::vector<std::string> chatlog;
	std::string userInput;

	float camMax;
	float camMin;

	void TypingCode();
public:
	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	Gameplay();
};
