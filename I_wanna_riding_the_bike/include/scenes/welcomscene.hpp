//
// Created by 桂明谦 on 2019/12/30.
//

#ifndef I_WANNA_RIDING_THE_BIKE_WELCOMSCENE_HPP
#define I_WANNA_RIDING_THE_BIKE_WELCOMSCENE_HPP

#include "engin/scene.hpp"
#include "engin/director.hpp"
#include "engin/sprite.hpp"
#include "engin/action/system_actions.hpp"

class WelcomeScene:public Scene {
public:
    WelcomeScene();
    void OnInit() override;
    void EventHandle(SDL_Event& event) override;
    void OnDestroy() override;
private:
    void step() override;
    FC_Font* font;
    Sprite kid;
    float angle;
    Sprite sprite;
};

#endif //I_WANNA_RIDING_THE_BIKE_WELCOMSCENE_HPP
