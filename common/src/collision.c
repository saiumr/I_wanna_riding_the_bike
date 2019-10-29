#include "collision.h"

bool RectPoint(SDL_Rect rect, SDL_Point point){
    return SDL_PointInRect(&point, &rect);
}

bool RectRect(SDL_Rect rect1, SDL_Rect rect2){
    return SDL_IntersectRect(&rect1, &rect2, NULL);
}

bool RectLine(SDL_Rect rect, SDL_Line line){
    return SDL_IntersectRectAndLine(&rect, &line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y);
}

bool CircleCircle(SDL_Circle c1, SDL_Circle c2){
    double distance = GetDistance(c1.center.x, c1.center.y, c2.center.x, c2.center.y);
    if(fabs(distance-(c1.r+c2.r))>EPS)
        return false;
    return true;
}