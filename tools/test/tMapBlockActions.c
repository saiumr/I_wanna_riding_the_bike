#include "SDL.h"
#include "MapBlockActions.h"
#include "unittest.h"

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test MapBlockAction", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    ObjectBasicInfo info;
    SDL_Point pos = {400, 400};
    InitObjBasicInfo(&info, DEFAULT_SIZE, pos, 0);
    MapBlock* rectblock = CreateSysColliMapBlock(NULL, "resources/image.bmp", COLLI_RECTANGLE, info);
    MapBlockActionGroup* actions = CreateMapBlockActionGroup(rectblock);
    SDL_Point newpos = {300, 300};
    AttachMoveActionByTime(actions, &newpos, 4, 5);
    AttachRotateActionByTime(actions, 60, 5, 6);
    SDL_Size newsize = {70, 70};
    AttachScaleActionByTime(actions, &newsize, 9, 3);
    SDL_Rect trigger_area = {300, 300, 100, 50};
    AttachRotateActionByRectArea(actions, 30, 9, &trigger_area);
    SDL_Circle circle_area = {200, 200, 5};
    SDL_Point newpos2 = {200, 200};
    AttachMoveActionByCircleArea(actions, &newpos2, 5, &circle_area);
    SDL_Event event;
    bool isquit = false;
    while(!isquit){
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            MapBlockActionDealEvent(actions);
            if(event.type == SDL_QUIT)
                isquit = true;
        }
        DrawMapBlockAction(actions);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    FreeMapBlock(rectblock);
    FreeMapBlockActionGroup(actions);
    return 0;
}
