#include "SDL_Draw.h"

void SDL_RenderDrawCircle(SDL_Renderer* render, int x, int y, int r){
    float angle = 0;
    const float delta = 5;
    for(int i=0;i<360/delta;i++){
        float prevradian = Degree2Radian(angle),
                nextradian = Degree2Radian(angle+delta);
        SDL_RenderDrawLine(render, x+r*cosf(prevradian), y+r*sinf(prevradian), x+r*cosf(nextradian), y+r*sinf(nextradian));
        angle += delta;
    }
}