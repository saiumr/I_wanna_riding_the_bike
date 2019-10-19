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

void SDL_RenderDrawCloseLines(SDL_Renderer* render, SDL_Point points[], const int num){
    SDL_Point npoints[num+1];
    for(int i=0;i<num;i++)
        npoints[i] = points[i];
    npoints[num] = points[0];
    SDL_RenderDrawLines(render, npoints, num+1);
}

void SDL_RenderDrawRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree){
    SDL_Point points[4]={
        {rect->x, rect->y},
        {rect->x+rect->w, rect->y},
        {rect->x+rect->w, rect->y+rect->h},
        {rect->x, rect->y+rect->h}
    };
    if((int)degree%360!=0){
        if(center == NULL){
            SDL_Point p = {rect->x+rect->w/2, rect->y+rect->h/2};
            RotatePointGroup(&p, points, 4, degree);
        }else
            RotatePointGroup(center, points, 4, degree);
    }
    SDL_RenderDrawCloseLines(render, points, 4);
}