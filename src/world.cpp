#include "world.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include <json/json.h>

#include "box2d/b2_world.h"
#include "utils/fileUtil.hpp"
#include "utils/numUtils.hpp"

void Level::loadPath(std::string path){
    tiles = loadLevelFromFile(path);
    name = path;

    std::cout<<"Successly loaded level '"<<path<<"'."<<std::endl;
}

void Level::Update(float dt){
    for(auto& tile : tiles){
        tile->Update();
    }

    b2world->Step(1.0f / 60.0f, 6, 2);
}

void Level::Draw(){
    for(auto& tile : tiles){
        tile->Draw();
    }
}

Level::Level(){
}

Level::Level(std::string path){
    name = path;

    b2Vec2 gravity(0.0f, 0.0f);
    b2world = new b2World(gravity);

    tiles = loadLevelFromFile(path);

    std::cout<<"Successly loaded level '"<<path<<"'."<<std::endl;
}

std::vector<std::unique_ptr<Tile>> Level::loadLevelFromFile(std::string file_path){
    std::vector<std::unique_ptr<Tile>> vec;
    std::string text = readFile(file_path);
    Json::Value root;
    Json::Reader jsonreader;

    Vector2 canvas_size{0, 0};

    jsonreader.parse(text, root);

    Vector3 pos;
    int x = 0;
    int y = 0;
    int z = 0;

    std::string id;
    std::string destination;

    bool isReadingDestination;

    Vector2 starting_pos={root["x"].asFloat(), root["y"].asFloat()};

    for(const auto& layer : root["layers"]) {
        y = 0;
        x = 0;
        for (const auto& e : layer.asString()) {
            if((e == ' ' or e == '\n' or e == ',') && !id.empty()){
                int tile_id = std::stoi(id);
                Vector2 tile_pos = {starting_pos.x+x*TILE_SIZE, starting_pos.y+(y*TILE_SIZE)};
                if(isStrDigit(id)){
                    Tile tile = Tile(tile_id, {starting_pos.x+x*TILE_SIZE, starting_pos.y+(y*TILE_SIZE)}, z);
                    if(tile.getType() == "block")
                        tile.initCollision(b2world);
                    tile.setSlot(vec.size());

                    vec.push_back(std::make_unique<Tile>(tile));
                    id.clear();
                }

                if(e == ' '){
                    x++;
                    canvas_size.x = x;
                }else if(e == '\n' or ','){
                    y++;
                    canvas_size.y = y;
                    x = 0;
                }

            }else if (isdigit(e)) {
                id.push_back(e);
            }else if(isEnglishAlphabet(e)){
                destination.push_back(e);
            }
            canvas_size.y = y;
        }
        if(!id.empty()){
            Tile tile = Tile(std::stoi(id), {starting_pos.x+x*TILE_SIZE, starting_pos.y+(y*TILE_SIZE)}, z);
            tile.setSlot(vec.size());
            vec.push_back(std::make_unique<Tile>(tile));
            id.clear();
        }
        z++;
    }

    total_layers = z;
    size = {canvas_size.x+1, canvas_size.y+1};
    this->starting_pos = starting_pos;

    return vec;
}
