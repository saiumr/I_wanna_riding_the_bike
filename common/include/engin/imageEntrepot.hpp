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
#include <algorithm>
using namespace std;

enum FileType{
    FILE_TYPE_IMAGE,
    FILE_TYPE_JSON,
    FILE_TYPE_TXT,
    FILE_TYPE_UNRECOGNIZE
};

class Director;

class ImageEntrepot final{
public:
    static void LoadImage(const string& filename);
    static void LoadImageStrict(string filename);
    static void LoadTexture(string name, SDL_Texture* texture);
    static void DeleteImage(string filename);
    static void PrintContent();
    static SDL_Texture* GetImage(string name);
    static void Clear();
    ImageEntrepot() = delete;
    ImageEntrepot(const ImageEntrepot& other) = delete;
private:
    static map<string, SDL_Texture*> images;
};

string GetFilename(const string& filename);

string GetFilenameWithoutSuffix(const string& filename);

FileType GetFileType(const string& filename);

string GetBaseName(const string& filename);

#endif //FARTRACE_IMAGEENTREPOT_HPP
