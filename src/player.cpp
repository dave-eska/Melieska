#include "player.hpp"

#include <raylib.h>

#include "global_variable.hpp"

#define P_WIDTH (17*9)
#define P_HEIGHT (34*9)

#define halfWidth ((body.width/2.5 + 30)/2.0f)/PIXELS_PER_METER
#define halfHeight ((body.height/5 + 30)/2.0f)/PIXELS_PER_METER

void Player::Move(float dt){
	float inputX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float inputY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    // Set velocity based on input
    b2Vec2 velocity(( inputX * speed ) * dt, ( inputY * speed ) * dt);
    kinematicBody->SetLinearVelocity(velocity);

    // Synchronize the Player's body position with Box2D body's position
    b2Vec2 position = kinematicBody->GetPosition();

    if(inputX==1) direction=DIRECTION_RIGHT;
    else if(inputX==-1) direction=DIRECTION_LEFT;

    if(inputY==1) direction=DIRECTION_DOWN;
    else if(inputY==-1) direction=DIRECTION_UP;

    //Diogonal Animations;
    if(inputX==1&&(inputY==1||inputY==-1)) direction=DIRECTION_RIGHT;
    if(inputX==-1&&(inputY==1||inputY==-1)) direction=DIRECTION_LEFT;

    int mod = direction == DIRECTION_LEFT ? body.width/16 : 0;
    body.x = ( position.x * PIXELS_PER_METER ) - ( (body.width - (body.width/2.5)) - mod);
    body.y = ( position.y * PIXELS_PER_METER ) - ( body.height - (body.height/7) );
}

void Player::Animate(){
	if((IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) && !isTyping){
		if(direction==DIRECTION_UP) current_animation=5;
		else if(direction==DIRECTION_DOWN) current_animation=1;
		else if(direction==DIRECTION_LEFT) current_animation=3;
		else if(direction==DIRECTION_RIGHT) current_animation=7;
	}else{
		if(direction==DIRECTION_UP) current_animation=4;
		else if(direction==DIRECTION_DOWN) current_animation=0;
		else if(direction==DIRECTION_LEFT) current_animation=2;
		else if(direction==DIRECTION_RIGHT) current_animation=6;
	}

	Rectangle dest={body.x,body.y,body.width, body.height};
	Vector2 origin = { 0 };
	DrawSpriteAnimationPro(animations[current_animation], dest, origin, 0, WHITE);

	if(isDebugging)
		for(b2Fixture* fixture = kinematicBody->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
			b2Shape* shape = fixture->GetShape();

			if (shape->GetType() == b2Shape::e_polygon) {
				b2PolygonShape* polyShape = static_cast<b2PolygonShape*>(shape);
				int vertexCount = polyShape->m_count;

				// Draw the collider outline
				for (int i = 0; i < vertexCount; ++i) {
					b2Vec2 vertexA = kinematicBody->GetWorldPoint(polyShape->m_vertices[i]);
					b2Vec2 vertexB = kinematicBody->GetWorldPoint(polyShape->m_vertices[(i + 1) % vertexCount]);

					b2Vec2 vertexAPixelPos = b2Vec2(vertexA.x * PIXELS_PER_METER, vertexA.y * PIXELS_PER_METER);
					b2Vec2 vertexBPixelPos = b2Vec2(vertexB.x * PIXELS_PER_METER, vertexB.y * PIXELS_PER_METER);

					// Directly draw using Raylib's DrawLine function
					// Remember, Raylib uses screen coordinates directly
					DrawLine(vertexBPixelPos.x, vertexBPixelPos.y, vertexAPixelPos.x, vertexAPixelPos.y, RED);
				}
			}
	}
}

Player::Player(const char* texture_path, Vector2 pos, int speed,
			   b2World& world) : body{pos.x, pos.y, P_WIDTH, P_HEIGHT}, speed{speed}{
	float meterX = body.x / PIXELS_PER_METER;
	float meterY = body.y / PIXELS_PER_METER;

	// Define the Box2D body definition
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(meterX, meterY); // Set initial position
	bodyDef.fixedRotation = true;

	// Create the body in the Box2D world
	kinematicBody = world.CreateBody(&bodyDef);

	// Define the shape and fixture
	b2PolygonShape boxShape;
	float hw = halfWidth;
	float hy = halfWidth;
	boxShape.SetAsBox(hw, hy);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;

	kinematicBody->CreateFixture(&fixtureDef);

	{
		texture = LoadTexture(texture_path);

		current_animation=1;
		//0=up || 1=down || 2=left || 3=right//
		direction=DIRECTION_DOWN;
		// Define separate arrays for rectangles
		Rectangle idleDownRect[] = {{0, 0, 18, 35},
			{18, 0, 18, 35},
			{36, 0, 18, 35},
			{54, 0, 18, 35},
			{72, 0, 18, 35}};

		Rectangle walkDownRect[] = {{0, 35, 18, 35},
			{18, 35, 18, 35},
			{36, 35, 18, 35},
			{54, 35, 18, 35},
			{72, 35, 18, 35},
			{90, 35, 18, 35}};

		Rectangle idleLeftRect[] = {{0, 70, 18, 35},
			{18, 70, 18, 35},
			{36, 70, 18, 35},
			{54, 70, 18, 35},
			{72, 70, 18, 35}};

		Rectangle walkLeftRect[] = {{0, 105, 18, 35},
			{18, 105, 18, 35},
			{36, 105, 18, 35},
			{54, 105, 18, 35},
			{72, 105, 18, 35},
			{90, 105, 18, 35}};

		Rectangle idleUpRect[] = {{0, 140, 18, 35},
			{18, 140, 18, 35},
			{36, 140, 18, 35},
			{54, 140, 18, 35},
			{72, 140, 18, 35}};

		Rectangle walkUpRect[] = {{0, 175, 18, 35},
			{18, 175, 18, 35},
			{36, 175, 18, 35},
			{54, 175, 18, 35},
			{72, 175, 18, 35},
			{90, 175, 18, 35}};

		Rectangle idleRightRect[] = {{0, 210, 18, 35},
			{18, 210, 18, 35},
			{36, 210, 18, 35},
			{54, 210, 18, 35},
			{72, 210, 18, 35}};

		Rectangle walkRightRect[] = {{0, 245, 18, 35},
			{18, 245, 18, 35},
			{36, 245, 18, 35},
			{54, 245, 18, 35},
			{72, 245, 18, 35},
			{90, 245, 18, 35}};

		// Use the arrays as arguments in CreateSpriteAnimation
		animations = {
			CreateSpriteAnimation(texture, 7, idleDownRect, 5), //0
			CreateSpriteAnimation(texture, 11, walkDownRect, 6), //1
			CreateSpriteAnimation(texture, 7, idleLeftRect, 5), //2
			CreateSpriteAnimation(texture, 11, walkLeftRect, 6), //3
			CreateSpriteAnimation(texture, 7, idleUpRect, 5), //4
			CreateSpriteAnimation(texture, 11, walkUpRect, 6), //5
			CreateSpriteAnimation(texture, 7, idleRightRect, 5), //6
			CreateSpriteAnimation(texture, 11, walkRightRect, 6), //7
		};
	}
}

Player::Player(){
}
