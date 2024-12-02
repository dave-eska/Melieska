#pragma once

#include <string>

#include <raylib.h>

class Scene{
protected:
    std::string title;

    Camera2D camera;

    int returnCode;

public:
    std::string getTitle(){ return title; }
    int getReturnCode(){ return returnCode; }

    void resetReturnCode();

    virtual void Update(float dt)=0;
    virtual void Draw()=0;

    virtual void Unload()=0;

    Scene();
    Scene(std::string title, float cameraZoom);

};

enum class Scenes{
    MainMenu,
    GamePlay,
    LevelEditor,
    Option
};
