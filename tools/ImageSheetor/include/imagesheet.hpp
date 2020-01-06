//
// Created by 桂明谦 on 2019/12/31.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IMAGESHEETOR_HPP
#define I_WANNA_RIDING_THE_BIKE_IMAGESHEETOR_HPP

#include "SDL.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

class ImageSheet final{
public:
    class Image{
    public:
        static Image Error_Image;
        Image(string nname, SDL_Surface* surface, SDL_Rect r);
        //Image(Image& otr) = delete;
        //Image& operator=(const Image& otr) = delete;
        SDL_Surface* GetImage() const;
        SDL_Rect     GetRect() const;
        string       GetName() const;
        void         SetPos(int x, int y);
    private:
        SDL_Surface* image;
        SDL_Rect rect;
        string name;
    };
    explicit ImageSheet(vector<Image> s);
    ImageSheet();
    void SetContent(vector<Image> s);
    int GetLen() const;
    int Length() const;
    bool Empty() const;
    const Image& operator[](int idx) const;
private:
    vector<Image> sheet;
};

#endif //I_WANNA_RIDING_THE_BIKE_IMAGESHEETOR_HPP
