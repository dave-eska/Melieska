#include "scene.hpp"

#include "scene.hpp"
#include "raylib.h"

void Scene::resetReturnCode(){
    if(returnCode != 0)
        returnCode = 0;
}

void Scene::Update(float dt){
}

void Scene::Draw(){
}

void Scene::Unload(){

}

Scene::Scene(){
}

Scene::Scene(std::string title, float cameraZoom) : title{title}{
    SetWindowTitle(title.c_str());

    camera = { 0 };
    camera.zoom = cameraZoom;

    returnCode = 0;
}
