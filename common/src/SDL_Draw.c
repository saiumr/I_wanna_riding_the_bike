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

//TODO 这里还有bug没有改完，编译通过，绘制不出来
void SDL_RenderFillRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree){
    if((int)degree%360 == 0)
        SDL_RenderFillRect(render, rect);
    else{
        SDL_Point points[4]={
            {rect->x, rect->y},
            {rect->x+rect->w, rect->y},
            {rect->x+rect->w, rect->y+rect->h},
            {rect->x, rect->y+rect->h}
        };
        if(center == NULL){
            SDL_Point p = {rect->x+rect->w/2, rect->y+rect->h/2};
            RotatePointGroup(&p, points, 4, degree);
        }else
            RotatePointGroup(center, points, 4, degree);
        SDL_Vector vectors[4];
        for(int i=0;i<3;i++)
            vectors[i] = Vec_CreateVecByPoints(&points[i], &points[i+1]);
        vectors[3] = Vec_CreateVecByPoints(&points[3], &points[0]);
        int left = (int)min(min(points[0].x, points[1].x), min(points[2].x, points[3].x)),
            right = (int)max(max(points[0].x, points[1].x), max(points[2].x, points[3].x)),
            top = (int)min(min(points[0].y, points[1].y), min(points[2].y, points[3].y)),
            bottom = (int)max(max(points[0].y, points[1].y), max(points[2].y, points[3].y));

        bool inRect = true;
        float lastresult = 0;
        for(int i=left;i<=right;i++){
            for(int j=top;j<bottom;j++){
                SDL_Point innerpoint = {i, j};
                for(int k=0;k<3;k++){
                    SDL_Vector point_vec = Vec_CreateVecByPoints(&innerpoint, &points[k]);
                    float result = Vec_Cross(&point_vec, &vectors[k]);
                    if(result*lastresult<0){
                        inRect = false;
                    }
                }
                if(inRect)
                    SDL_RenderDrawPoint(render, i, j);
                inRect = true;
            }
        }
    }
}

void SDL_RenderFillPolygon(SDL_Renderer* render, SDL_Point points[]){

}