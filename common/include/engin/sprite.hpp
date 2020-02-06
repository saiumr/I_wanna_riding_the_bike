//
// Created by 桂明谦 on 2019/12/19.
//

#ifndef FARTRACE_SPRITE_HPP
#define FARTRACE_SPRITE_HPP

#include "SDL.h"
#include "object.hpp"
#include "imageEntrepot.hpp"
#include "action/action.hpp"
#include <string>
using namespace std;

using Sprite_Image = SDL_Texture;

enum Flip_Flag{
    FLIP,
    NO_FLIP
};

class Action;

class Sprite:public Object{
public:
    Sprite();
    Sprite(int x, int y, string image_name);
    Sprite_Image* GetImage();
    void SetImage(string name);
    void SetImage(Sprite_Image* image);
    SDL_Point GetOriginalSize();
    void Show();
    void Hide();
    void SuitSize();
    bool IsVisiable();
    void Flip(Flip_Flag flag);
    bool IsFlip();
    virtual void Draw();
    void Update();
    void RunAction(Action* action);
    //void StopAction(string name);
    void StopAllAction();
    void PauseAllAction();
protected:
    virtual void step();
    Sprite_Image* image;
    bool isshow;
    Flip_Flag flip;
    Action* action;
};

#endif //FARTRACE_SPRITE_HPP
