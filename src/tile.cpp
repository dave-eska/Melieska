#include "tile.hpp"
#include "global_variable.hpp"

#include <fstream>

#include <iostream>
#include <raylib.h>

#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include <json/json.h>
#include <string>

bool Tile::hasAnimation(){
    return texture.width / 32 > 1;
}

void Tile::Update(){
}

void Tile::Draw(){
    if(animationOnDefault){
        DrawSpriteAnimationPro(animation, {body.x, body.y, TILE_SIZE, TILE_SIZE}, {0, 0}, 0, WHITE);
    }
    else if(isRunningAnimation) {
        DrawSpriteAnimationPro(animation, {body.x, body.y, TILE_SIZE, TILE_SIZE}, {0, 0}, 0, WHITE, isRunningAnimation);
    }

	if(isDebugging)
		for (b2Fixture* fixture = b2body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
			b2Shape* shape = fixture->GetShape();

			if (shape->GetType() == b2Shape::e_polygon) {
				b2PolygonShape* polyShape = static_cast<b2PolygonShape*>(shape);
				int vertexCount = polyShape->m_count;

				// Draw the collider outline
				for (int i = 0; i < vertexCount; ++i) {
					b2Vec2 vertexA = b2body->GetWorldPoint(polyShape->m_vertices[i]);
					b2Vec2 vertexB = b2body->GetWorldPoint(polyShape->m_vertices[(i + 1) % vertexCount]);

					b2Vec2 vertexAPixelPos = b2Vec2(vertexA.x * PIXELS_PER_METER, vertexA.y * PIXELS_PER_METER);
					b2Vec2 vertexBPixelPos = b2Vec2(vertexB.x * PIXELS_PER_METER, vertexB.y * PIXELS_PER_METER);

					// Directly draw using Raylib's DrawLine function
					// Remember, Raylib uses screen coordinates directly
					DrawLine(vertexBPixelPos.x, vertexBPixelPos.y, vertexAPixelPos.x, vertexAPixelPos.y, RED);
				}
			}
		}
}

void Tile::initCollision(b2World*& world) {
	if (!world) {
		std::cerr << "Error: world is null" << std::endl;
		return;
	}

	// Convert pixel coordinates to Box2D meters
	float meterX = body.x / PIXELS_PER_METER;
	float meterY = body.y / PIXELS_PER_METER;
	float halfWidth = (body.width / 2.0f) / PIXELS_PER_METER;
	float halfHeight = (body.height / 2.0f) / PIXELS_PER_METER;

	// Define the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(meterX + halfWidth, meterY + halfHeight); // Center the body

	b2body = world->CreateBody(&bodyDef);
	if (!b2body) {
		std::cerr << "Error: b2body is null after CreateBody" << std::endl;
		return;
	}

	// Define the shape
	boxShape.SetAsBox(halfWidth, halfHeight);

	// Define the fixture
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f; // Static bodies don't need density, but it's good practice to define it
	fixtureDef.friction = 0.3f;

	b2Fixture* fixture = b2body->CreateFixture(&fixtureDef);
	if (!fixture) {
		std::cerr << "Error: fixture is null after CreateFixture" << std::endl;
	}
}

Tile::Tile(){
}

Tile::Tile(int id, Vector2 pos, int z_level) : id{id}, body{pos.x, pos.y, TILE_SIZE, TILE_SIZE}, z_level{z_level}{
	int fps;

	Json::Reader jsonreader;

	std::ifstream file("res/items.json");
	Json::Value jsonvalue;
	jsonreader.parse(file, jsonvalue);

	if(!jsonvalue.isArray()) return;
	if(id <= jsonvalue.size() && id >= 0){
		auto jsonTile = jsonvalue[id];

		name = jsonTile["name"].asString();
		type = jsonTile["type"].asString();

		if(jsonTile.isMember("animationOnDefault")) animationOnDefault = jsonTile["animationOnDefault"].asBool();

		if(jsonTile["fps"].isArray()){
			int probabulity = GetRandomValue(0, jsonTile["fps"].size()-1);
			fps = jsonTile["fps"][probabulity].asInt();
		}else{
			fps = jsonTile["fps"].asInt();
		}

		if(jsonTile["texture"].isArray()){
			int probabulity = GetRandomValue(0, jsonTile["texture"].size()-1);
			texture = LoadTexture(jsonTile["texture"][probabulity].asString().c_str());
		}else{
			texture = LoadTexture(jsonTile["texture"].asString().c_str());
		}
	}

	int totalFrame = texture.width/32;

	Rectangle animRect[totalFrame];
	for(int i=0;i<totalFrame;i++){
		animRect[i] = {(float)32*i, 0, 32, 32};
	}

	animation = CreateSpriteAnimation(texture, fps, animRect, totalFrame);
}
