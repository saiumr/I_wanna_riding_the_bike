//
// Created by 桂明谦 on 2020/1/1.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IMAGESHEETWRITER_HPP
#define I_WANNA_RIDING_THE_BIKE_IMAGESHEETWRITER_HPP

#include "imagesheet.hpp"
#include "json/json.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <fstream>
using namespace std;

class ImageSheetWriter {
public:
    ImageSheetWriter() = default;
    explicit ImageSheetWriter(vector<ImageSheet::Image> s);
    void SetContent(vector<ImageSheet::Image> s);
    void AddImage(string name, SDL_Surface* surface, SDL_Rect rect);
    void DeleteImage(int idx);
    void DeleteImage(string name);
    void Write2File(string filename);
private:
    void writeImage(string filename);
    void writeJson(string filename, string image_name);
    SDL_Point FindMaxBorder();
    vector<ImageSheet::Image> sheet;
};

#endif //I_WANNA_RIDING_THE_BIKE_IMAGESHEETWRITER_HPP
