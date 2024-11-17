#include <memory>

#include <raylib.h>
#include <string>

#define MAX_FPS 60

#include "player.hpp"
#include "ability.hpp"

static std::unique_ptr<Player> player;
static std::vector<AbilityUI> circs;
static int rad;

static int distCross;
static int distLines;

static bool isStoringCircCoord;
static bool isDrawingCircs;

void SetCircleCoord();
void MakeCircleBigger();
void CallAbility(Abilities& ability);

int main(){
    InitWindow(1920, 1080, "Melieska p0.1");

    player = std::make_unique<Player>(Player("res/img/player_atlas.png", {0,0}, 500));
    rad = 40;

    for(int i=0;i<6;i++)
        circs.push_back(AbilityUI(rad, {0,0}, BLACK, Abilities::None));

    distCross = 45*2;
    distLines = 24*2;

    isStoringCircCoord = false;
    isDrawingCircs = false;

    circs[0].setAbility(Abilities::FastWalk);
    circs[0].setColor(RED);

    SetTargetFPS(MAX_FPS);
    while(!WindowShouldClose()){
        player->Move(GetFrameTime());

        isDrawingCircs = false;
        isStoringCircCoord = false;

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            SetCircleCoord();
        }

        MakeCircleBigger();

        BeginDrawing();

        ClearBackground(GRAY);

        player->Animate();

        if(isDrawingCircs)
            for(auto& e : circs)
            e.Draw();

        DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void SetCircleCoord(){
    isStoringCircCoord = true;
    if(isStoringCircCoord){
        Vector2 mpos = GetMousePosition();
        circs[0].setCenter({mpos.x - distCross, mpos.y + distLines});
        circs[0].setStartCenter({mpos.x - distCross, mpos.y + distLines});
        circs[1].setCenter({mpos.x, mpos.y - distCross});
        circs[1].setStartCenter({mpos.x, mpos.y - distCross});
        circs[2].setCenter({mpos.x + distCross, mpos.y - distLines});
        circs[2].setStartCenter({mpos.x + distCross, mpos.y - distLines});
        circs[3].setCenter({mpos.x + distCross, mpos.y + distLines});
        circs[3].setStartCenter({mpos.x + distCross, mpos.y + distLines});
        circs[4].setCenter({mpos.x, mpos.y + distCross});
        circs[4].setStartCenter({mpos.x, mpos.y + distCross});
        circs[5].setCenter({mpos.x - distCross, mpos.y - distLines});
        circs[5].setStartCenter({mpos.x - distCross, mpos.y - distLines});
    }
    isStoringCircCoord = false;
}

void CallAbility(AbilityUI& aui){
    switch(aui.getAbility()){
        case Abilities::FastWalk:{
            player->setSpeed(600);
            break;
        }

        default:
        break;
    }
}

void MakeCircleBigger(){
    for(int i=0;i<circs.size();i++){
        auto& e = circs[i];
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            isDrawingCircs = true;
            if(isDrawingCircs && CheckCollisionPointCircle(GetMousePosition(), e.getCurrentCenter(), e.getRadius())){
                e.setRadius(rad + 10);
                e.setColor({(unsigned char)(e.getStartColor().r-70), (unsigned char)(e.getStartColor().g-70), (unsigned char)(e.getStartColor().b-70), 255});
                switch(i){
                    case 0:
                        e.setCenter({e.getStartCenter().x - 7, e.getStartCenter().y + 7});
                    break;

                    case 1:
                        e.setCenter({e.getCurrentCenter().x, e.getStartCenter().y - 7});
                    break;

                    case 2:
                        e.setCenter({e.getStartCenter().x + 7, e.getStartCenter().y - 7});
                    break;

                    case 3:
                        e.setCenter({e.getStartCenter().x + 7, e.getStartCenter().y + 7});
                    break;

                    case 4:
                        e.setCenter({e.getCurrentCenter().x, e.getStartCenter().y + 7});
                    break;

                    case 5:
                        e.setCenter({e.getStartCenter().x - 7, e.getStartCenter().y - 7});
                    break;
                }
            }else{
                e.setCenter(e.getStartCenter());
                e.setRadius(rad);
                e.setColor(e.getStartColor());
            }
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) CallAbility(e);
    }
}
