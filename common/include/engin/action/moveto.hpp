//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_MOVETO_HPP
#define I_WANNA_RIDING_THE_BIKE_MOVETO_HPP

#include "action.hpp"

class MoveTo : public Action {
public:
    static MoveTo* create(int time, int x, int y);
    MoveTo(int time, int x, int y);
    void Step(Sprite* sprite) override;
private:
    static vector<MoveTo> instances;
    SDL_Pointf distance;
    SDL_Point dstpos;
};


#endif //I_WANNA_RIDING_THE_BIKE_MOVETO_HPP
