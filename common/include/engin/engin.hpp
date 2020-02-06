#ifndef __ENGIN_HPP__
#define  __ENGIN_HPP__
#include "director.hpp"
#include "stage.hpp"
#include "imageEntrepot.hpp"
#include "engin/action/animation.hpp"
#include "imageinfoviewer.hpp"
#include "SDL_FontCache.h"

void InitEngin(Director* director);
void RunEngin();
unsigned int QuitEngin();

#endif