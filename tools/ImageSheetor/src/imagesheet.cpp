//
// Created by 桂明谦 on 2019/12/31.
//

#include "imagesheet.hpp"

ImageSheet::Image ImageSheet::Image::Error_Image("", nullptr, {-1, -1, -1, -1});

ImageSheet::Image::Image(string nname, SDL_Surface* surface, SDL_Rect r):image(surface),rect(r),name(std::move(nname)){}

string ImageSheet::Image::GetName() const{
    return name;
}

SDL_Surface* ImageSheet::Image::GetImage() const{
    return image;
}

SDL_Rect ImageSheet::Image::GetRect() const{
    return rect;
}

ImageSheet::ImageSheet(){}

ImageSheet::ImageSheet(vector<Image> s):sheet(std::move(s)){}

int ImageSheet::GetLen() const{
    return sheet.size();
}

int ImageSheet::Length() const{
    return GetLen();
}

bool ImageSheet::Empty() const{
    return sheet.empty();
}

const ImageSheet::Image& ImageSheet::operator[](int idx) const{
    return sheet[idx];
}

void ImageSheet::Image::SetPos(int x, int y){
    rect.x = x;
    rect.y = y;
}

void ImageSheet::SetContent(vector<Image> s){
    sheet = s;
}
