//
// Created by 桂明谦 on 2019/12/18.
//

#ifndef FARTRACE_IMAGEENTREPOT_HPP
#define FARTRACE_IMAGEENTREPOT_HPP

#include "SDL.h"
#include "SDL_image.h"
#include "director.hpp"
#include <map>
#include <string>
#include <utility>
#include <iostream>
using namespace std;

class Director;

class ImageEntrepot final{
public:
    static void LoadImage(const string& filename);
    static void LoadImageStrict(string filename);
    static void DeleteImage(string filename);
    static void PrintContent();
    static SDL_Texture* GetImage(string name);
    static void Clear();
    ImageEntrepot() = delete;
    ImageEntrepot(const ImageEntrepot& other) = delete;
private:
    static map<string, SDL_Texture*> images;
};

string GetNameFromFile(const string& filename);

#endif //FARTRACE_IMAGEENTREPOT_HPP
