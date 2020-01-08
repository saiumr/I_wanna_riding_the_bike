//
// Created by 桂明谦 on 2020/1/1.
//

#include "ImageSheetor/imagesheetwriter.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
    ImageSheetWriter writer;
    SDL_Surface* fireland = IMG_Load("resources/test/fireland.bmp");
    SDL_Surface* grassland = IMG_Load("resources/test/grassland.bmp");
    SDL_Surface* gravel = IMG_Load("resources/test/gravel.bmp");
    SDL_Surface* green_land = IMG_Load("resources/test/green_land.bmp");
    if(!(fireland || grassland || gravel || green_land)){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "image load failed");
        SDL_Quit();
        IMG_Quit();
    }
    int w = fireland->w;
    int h = fireland->h;
    writer.AddImage("fireland",fireland, {0, 0, w, h});
    writer.AddImage("grassland",grassland, {w, 0,w, h});
    writer.AddImage("gravel", gravel, {2*w, 0, w,h});
    writer.AddImage("green_land", green_land, {3*w, 0, w, h});
    writer.Write2File("test");
    SDL_Quit();
    IMG_Quit();
    return 0;
}

