//
// Created by 桂明谦 on 2019/12/30.
//

#include "scenes/welcomscene.hpp"

WelcomeScene::WelcomeScene(){
    name = "welcome";
    image_load_filename = "I_wanna_riding_the_bike/image_loader/welcomeScene.txt";
}

void WelcomeScene::OnInit(){
    name = "welcome";
    font = FC_CreateFont();
    FC_LoadFont(font, Director::GetDirector()->GetRender(), "resources/Fangsong.ttf", 20, {255, 255 ,255 ,255}, TTF_STYLE_NORMAL);
    kid.SetImage("testImage");
    kid.Resize(kid.GetOriginalSize().x*10, kid.GetOriginalSize().y*10);
    angle = 0;
}

void WelcomeScene::EventHandle(SDL_Event& event){

}

void WelcomeScene::OnDestroy(){
    FC_FreeFont(font);
}

void WelcomeScene::step(){
    const int radius = 50;
    Director* director = Director::GetDirector();
    float radian = angle*M_PI/180;
    SDL_Point pos;

    SDL_Size kid_size = kid.GetSize();
    for(int i=0;i<director->GetWindowWidth()/kid.GetSize().w;i++)
        for(int j=0;j<director->GetWindowHeight()/kid.GetSize().h;j++){
            pos.x = kid_size.w*i+radius*cos(radian)+50;
            pos.y = kid_size.h*j+radius*sin(radian)+50;
            kid.Move(pos.x, pos.y);
            kid.Draw();
        }
    angle+=2;
    if(angle >= 360)
        angle-=360;
    FC_Draw(font, Director::GetDirector()->GetRender(), 500, 750, "由 saiumr 和 VisualGMQ 制作");
}
