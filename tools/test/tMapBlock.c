#include <stdio.h>
#include "unittest.h"
#include "SDL.h"
#include "MapBlock.h"

int main(int argc, char** argv){
    EnableDebug();
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("test MapBlock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    bool isquit = false;

    ObjectBasicInfo rectinfo = {DEFAULT_SIZE, DEFAULT_POS, 30};
    MapBlock* rectblock = CreateSysColliMapBlock(render, "resources/image.bmp", COLLI_TRIANGLE, rectinfo);
    ResizeMapBlock(rectblock, 100, 100);

    ObjectBasicInfo userinfo = {DEFAULT_SIZE, {200, 200}, 60};
    SDL_Point points[]={
        {-50, -50},
        {30, 50},
        {0, 0}
    };
    int array[6];
    Points2IntArray(points, 3, array);
    MapBlock* userblock = CreateUserColliMapBlock(render, "resources/image.bmp", array, 6, userinfo);
    ResizeMapBlock(userblock, 100, 100);
    ADD_TEST_FALSE("rectblock is NULL?", rectblock, NULL);
    ColliShape* shape = GetMapBlockColliShape(userblock);
    ADD_TEST_TRUE("GetColliType", GetColliType(shape), COLLI_USER);
    if(rectblock == NULL)
        return 1;
    
    float angle = 0;
    SDL_Point p = {200, 200};
    SDL_Point center = {400, 400};
    
    while(!isquit){
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
        }
        SDL_Point pos = GetMapBlockPosition(rectblock);
        pos.x+=20;
        if(pos.x>800)
            pos.x = 0;
        SetMapBlockPosition(rectblock, pos.x, pos.y);
        DrawMapBlock(render, rectblock);
        DrawMapBlock(render, userblock);
        SDL_RenderPresent(render);
        SDL_Delay(60);
    }
    FreeMapBlock(rectblock); 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    IMG_Quit();
    SDL_Quit();

    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}