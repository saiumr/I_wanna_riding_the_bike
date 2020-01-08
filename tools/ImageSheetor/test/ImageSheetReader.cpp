//
// Created by 桂明谦 on 2020/1/1.
//

#include "ImageSheetor/imagesheetreader.hpp"
#include "app.hpp"
#include <vector>
using namespace std;

class TestReader:public App{
public:
    TestReader():App("test ImageSheetReader", 800, 600, SDL_WINDOW_SHOWN),reader("test.json"){
        sheet = reader.GetSheet();
        for(int i=0;i<sheet.GetLen();i++){
            SDL_Rect rect = sheet[i].GetRect();
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s:\nrect:%d,%d,%d,%d\n", sheet[i].GetName().c_str(), rect.x, rect.y, rect.w, rect.h);
        }
    }

    void EventHandle(SDL_Event& event) override{
        App::EventHandle(event);
        if(event.type==SDL_MOUSEMOTION){
            mouse_pos.x = event.motion.x;
            mouse_pos.y = event.motion.y;
        }
    }

    void Update() override{
        for(int i=0;i<sheet.GetLen();i++){
            const ImageSheet::Image image = sheet[i];
            SDL_Rect rect = image.GetRect();
            SDL_Surface* surface = image.GetImage();
            SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
            SDL_RenderCopy(render, texture, nullptr, &rect);
            if(SDL_PointInRect(&mouse_pos, &rect)){
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
                SDL_RenderDrawRect(render, &rect);
            }
            SDL_DestroyTexture(texture);
        }
    }
private:
    ImageSheetReader reader;
    ImageSheet sheet;
    SDL_Point mouse_pos;
};

RUN_APP(TestReader)

