//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/engin.hpp"
#include "guitestframework.hpp"

class AnimationTest:public GUITestframework{
public:
    AnimationTest():GUITestframework("Animation Test", 800, 600){
        textures.push_back(IMG_LoadTexture(render, "resources/test/OKNinjaBackRun1.png"));
        textures.push_back(IMG_LoadTexture(render, "resources/test/OKNinjaBackRun2.png"));
        textures.push_back(IMG_LoadTexture(render, "resources/test/OKNinjaLeft.png"));
        textures.push_back(IMG_LoadTexture(render, "resources/test/OKNinjaLeftRun1.png"));
        textures.push_back(IMG_LoadTexture(render, "resources/test/OKNinjaLeftRun2.png"));
        vector<Frame> frames;
        for(SDL_Texture* texture : textures) {
            if(texture==nullptr)
                cout<<"image failed"<<endl;
            frames.push_back(Frame(texture, 50));
        }
        animation = Animation::create(frames);
        animation->Play();
    }
    void Update(){
        SDL_Texture* texture = animation->Step();
        ImageInfoViewer viewer(texture);
        SDL_Rect rect = {0, 0, viewer.GetWidth(), viewer.GetHeight()};
        SDL_RenderCopy(render, texture, nullptr, &rect);
    }

    ~AnimationTest(){
        for(SDL_Texture* texture : textures)
            SDL_DestroyTexture(texture);
    }
private:
    vector<SDL_Texture*> textures;
    Animation* animation;
};

RUN_APP(AnimationTest)

