//
// Created by 桂明谦 on 2019/12/30.
//

#include "main.hpp"

const int ImageSheetor::Padding = 25;
const int ImageSheetor::Error_Index = -1;

string GetNameFromFile(const string& filename){
    size_t pos = filename.find_last_of('/');
    string substring;
    if(pos != std::string::npos)
        substring = filename.substr(pos+1);
    else
        substring = filename;
    size_t final_pos = substring.find_first_of('.');
    if(final_pos == std::string::npos)
        return substring;
    return substring.substr(0, final_pos);
}

ImageSheetor::ImageSheetor():App("ImageSheetor", 200, 200, SDL_WINDOW_SHOWN),image_idx(Error_Index){
    SDL_LogSetPriority(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_INFO);
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
            textureManager.AddTexture(render, image);
            Resize();
        }
        SDL_free(event.drop.file);
    }
    if(event.type==SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_RETURN){
            saveSheet();
        }
        if(event.key.keysym.sym==SDLK_BACKSPACE){
            deleteImage();
        }
    }
}

void ImageSheetor::saveSheet(){
    if(images.empty())
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "export", "没有要导出的图片", window);
    else {
        ImageSheetWriter writer(images);
        writer.Write2File("result");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "export", "导出为result.png 和result.json了", window);
    }
}

bool ImageSheetor::idx_valid(){
    return image_idx>=0 && image_idx<images.size();
}

void ImageSheetor::deleteImage(){
    if(idx_valid()){
        auto it = images.begin() + image_idx;
        SDL_FreeSurface(it->GetImage());
        images.erase(it);
        relayout();
        Resize();
        image_idx = Error_Index;
        textureManager.DeleteTexture(image_idx);
    }
}

void ImageSheetor::Resize() {
    if(!images.empty()) {
        SDL_Point boarder = findBoarder();
        SDL_SetWindowSize(window, boarder.x+Padding*2, boarder.y+Padding*2);
    }
}

void ImageSheetor::Update(){
    for(int i=0;i<images.size();i++){
        SDL_Rect rect = images[i].GetRect();
        rect.x += Padding;
        rect.y += Padding;
        SDL_RenderCopy(render, textureManager[i], nullptr, &rect);
    }
    handleSelectedImage();
}

SDL_Point ImageSheetor::findBoarder(){
    SDL_Point boarder = {0, 0};
    for(auto & image : images){
        boarder.x = std::max(boarder.x, image.GetRect().x+image.GetRect().w);
        boarder.y = std::max(boarder.y, image.GetRect().y+image.GetRect().h);
    }
    return boarder;
}

void ImageSheetor::handleSelectedImage(){
    for(int i=0;i<images.size();i++){
        SDL_Rect rect = images[i].GetRect();
        rect.x += Padding;
        rect.y += Padding;
        if(SDL_PointInRect(&GetMouseInfo().pos, &rect)){
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            SDL_RenderDrawRect(render, &rect);
            if(GetMouseInfo().button[SDL_BUTTON_LEFT])
                image_idx = i;
            break;
        }
    }
    if(image_idx!=Error_Index){
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_Rect rect = images[image_idx].GetRect();
        rect.x += Padding;
        rect.y += Padding;
        SDL_RenderDrawRect(render, &rect);
    }
}

void ImageSheetor::relayout(){
    for(int i=0;i<images.size();i++){
        if(i==0)
            images[i].SetPos(0, 0);
        else
            images[i].SetPos(images[i-1].GetRect().x+images[i-1].GetRect().w, 0);
    }
}

ImageSheetor::~ImageSheetor(){
    for(auto & image : images)
        SDL_FreeSurface(image.GetImage());
}

RUN_APP(ImageSheetor)
