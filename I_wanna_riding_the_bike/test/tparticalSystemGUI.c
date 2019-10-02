#include "SDL.h"
#include "particalSystem.h"
#include "log.h"
//#define TEST_WORLD
#define TEST_ALL

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN, &window, &render);
    SDL_Event event;
    bool isquit = false;

    SDL_Vector gravity = {0, 0};
    SDL_Color color = {0, 255, 0, 255};
    SDL_Color explodecolor = {255, 0, 0, 255};
    SDL_Vector direct = {5, -5};
    SDL_Point position = {400, 400};
    SDL_Point explodePositon = {300, 300};
    int partical_hp = 50;
    PS_World world;

    #ifdef TEST_WORLD
    world.gravity = gravity; 
    world.partical_num = 1;
    world.particals = (PS_Partical*)malloc(sizeof(PS_Partical));
    world.particals[0].color = color;
    world.particals[0].direct = direct;
    world.particals[0].hp = partical_hp;
    world.particals[0].isdead = false;
    world.particals[0].position = position;
    world.render = render;
    #endif
    #ifdef TEST_ALL
    world = PS_CreateWorld(gravity, render);
    PS_ParticalLauncher launcher = PS_CreateLauncher(position, direct, partical_hp, 30, color, &world, 10);
    #endif
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
            #ifdef TEST_ALL
            if(event.type == SDL_KEYDOWN)
                if(event.key.keysym.sym == SDLK_SPACE)
                    PS_Explode(&world, explodecolor, explodePositon, 100);
            #endif
        }
        PS_ShootPartical(&launcher);
        PS_WorldUpdate(&world);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    #ifdef TEST_ALL
    PS_DestroyLauncher(&launcher);
    #endif
    PS_DestroyWorld(&world);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    return 0;
}