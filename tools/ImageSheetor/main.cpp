//
// Created by 桂明谦 on 2019/12/30.
//

#include "main.hpp"

const int ImageSheetor::Padding = 50;

string GetNameFromFile(const string& filename){
    size_t pos = filename.find_last_of('/');
    string substring;
    if(pos != filename.npos)
        substring = filename.substr(pos+1);
    else
        substring = filename;
    size_t final_pos = substring.find_first_of('.');
    if(final_pos == substring.npos)
        return substring;
    return substring.substr(0, final_pos);
}

ImageSheetor::ImageSheetor():App("ImageSheetor", 200, 200, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE){

}

void ImageSheetor::EventHandle(SDL_Event& event){
    App::EventHandle(event);
    if(event.type==SDL_DROPFILE){
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "filename:%s", event.drop.file);
        SDL_Surface* surface = IMG_Load(event.drop.file);
        if(surface==nullptr){
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s is a invalid image file", event.drop.file);
        }else{
            string filename = GetNameFromFile(event.drop.file);
            SDL_Rect rect = {0, 0, surface->w, surface->h};
            if(!images.empty()) {
                SDL_Rect lastsheet_rect = images[images.size() - 1].GetRect();
                rect.x = lastsheet_rect.x + lastsheet_rect.w;
            }
            ImageSheet::Image image(filename, surface, rect);
            images.push_back(image);
            Resize();
        }
        SDL_free(event.drop.file);
    }
    if(event.type==SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_RETURN){
            ImageSheetWriter writer(images);
            writer.Write2File("result");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "export", "导出为result.png 和result.json了", window);
        }
    }
}

void ImageSheetor::Resize() {
    if(!images.empty()) {
        SDL_Rect lastsheet_rect = images[images.size() - 1].GetRect();
        SDL_SetWindowSize(window, lastsheet_rect.w+lastsheet_rect.x+Padding, lastsheet_rect.h+Padding);
    }
}

void ImageSheetor::Update(){
    for(int i=0;i<images.size();i++){
        ImageSheet::Image image = images[i];
        SDL_Texture* texture = SDL_CreateTextureFromSurface(render, image.GetImage());
        SDL_Rect rect = image.GetRect();
        SDL_RenderCopy(render, texture, nullptr, &rect);
    }
}

ImageSheetor::~ImageSheetor(){
    for(int i=0;i<images.size();i++)
        SDL_FreeSurface(images[i].GetImage());
}

RUN_APP(ImageSheetor)
