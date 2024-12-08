#include "gameplay.hpp"
#include "ability.hpp"
#include "global_variable.hpp"
#include "raylib.h"
#include "scene.hpp"
#include <cstring>
#include <string>

void Gameplay::TypingCode(){
    char c = GetCharPressed();
    if (c){
        userInput.push_back(c);
    }

    if(IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
		userInput.pop_back();
	if(IsKeyPressed(KEY_ENTER)){
		if(!userInput.empty()){
			chatlog.push_back(userInput);
			userInput.clear();
		}
		isTyping=false;
	}
}

void Gameplay::Update(float dt){
	if(clearChat > 0 && !chatlog.empty()) clearChat -= GetFrameTime();

	if(clearChat <= 0){
		std::string strText;
		for(auto& e : chatlog){
			strText.append("\n");
			strText.append(e);
		}

		char* text = new char[strText.length() + 1];
		std::strcpy(text, strText.c_str());

		SaveFileText("chatLogs.txt", text);

		delete[] text;
		chatlog.clear();
	}

	if(clearChat <= 0) clearChat = 10.0f;


	float wheelMove = GetMouseWheelMove();

	if(wheelMove != 0.0f) {
		camera.zoom += wheelMove * 0.1f; // Adjust zoom sensitivity if needed
		if (camera.zoom > camMax) camera.zoom = camMax;
		if (camera.zoom < camMin) camera.zoom = camMin;
	}

	if(!isTyping){
        camera.target = {player->getBody().x + (player->getBody().width/2), player->getBody().y + (player->getBody().height/2)};
        player->Move(GetFrameTime());
    }

	if(IsKeyPressed(KEY_PAGE_UP))
		isTyping = true;

	if(isTyping)
		TypingCode();

	level->Update(GetFrameTime());

	am->Update();

}

void Gameplay::Draw(){
	BeginMode2D(camera);

	level->Draw();
	player->Animate();

	EndMode2D();

	am->Draw();
	am->DrawUI();

	for(int i=0;i<chatlog.size();i++){
		auto& chat = chatlog[i];
		DrawText(chat.c_str(), 0, GetScreenHeight()/2 + i*20, 20, WHITE);
	}

	if(isTyping){
        DrawRectangleRec({(float)GetScreenWidth()-520, 10, 500, 35}, {20,20,20,130});
        DrawText(userInput.c_str(), (float)GetScreenWidth()-500, 10, 35, BLACK);
    }

	if(isDebugging){
		DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);
		DrawText(isTyping ? "IsTyping" : "NotTyping", 0, 35, 35, BLACK);
		DrawText(std::to_string(GetFPS()).c_str(), 0, GetScreenHeight() - 50, 35, GREEN);
	}
}

void Gameplay::Unload(){
}

Gameplay::Gameplay() : Scene("Gameplay Test", 0.5){
	level = new Level("res/levels/test.json");

	camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };

	player = new Player("res/img/player_atlas.png", {TILE_SIZE*2,TILE_SIZE*3}, 500, *level->b2world);
	am = new AbilityManager(*player);

	camMax = 3.0f;
	camMin = 0.1f;

	clearChat = 10.0f;
}
