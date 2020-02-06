//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/imageinfoviewer.hpp"

ImageInfoViewer::ImageInfoViewer(SDL_Texture* image):texture(image){
    SDL_QueryTexture(texture, &format, &access, &w, &h);
}
int ImageInfoViewer::GetWidth() const{
    return w;
}

int ImageInfoViewer::GetHeight() const{
    return h;
}

Uint32 ImageInfoViewer::GetFormat() const {
    return format;
}

int ImageInfoViewer::GetAccess() const {
    return access;
}
