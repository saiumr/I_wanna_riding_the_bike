//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IMAGEINFOVIEWER_HPP
#define I_WANNA_RIDING_THE_BIKE_IMAGEINFOVIEWER_HPP

#include "SDL.h"
#include "SDL_image.h"

class ImageInfoViewer final{
public:
    ImageInfoViewer(SDL_Texture* image);
    int GetWidth() const;
    int GetHeight() const;
    Uint32 GetFormat() const;
    int GetAccess() const;
private:
    SDL_Texture* texture;
    int w;
    int h;
    Uint32 format;
    int access;
};


#endif //I_WANNA_RIDING_THE_BIKE_IMAGEINFOVIEWER_HPP
