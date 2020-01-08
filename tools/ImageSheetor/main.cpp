//
// Created by 桂明谦 on 2019/12/30.
//

#include "ImageSheetor/main.hpp"

const int ImageSheetor::Padding = 100;
const int ImageSheetor::Error_Index = -1;

string GetNameFromFileWithoutSuffix(const string& filename){
    const char* platform = SDL_GetPlatform();
    string split_symbol;
    if(strcmp(platform, "Windows")==0)
        split_symbol = "\\";
    else
        split_symbol = "/";
    size_t pos = filename.find_last_of(split_symbol);
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

ImageSheetor::ImageSheetor():App("ImageSheetor", 200, 200, SDL_WINDOW_SHOWN),image_idx(Error_Index),oldleftbutton(false),moving_idx(Error_Index){
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
            string filename = GetNameFromFileWithoutSuffix(event.drop.file);
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
    SDL_Point rb = {0, 0};
    for(auto& i : images){
        rb.x = std::max(i.GetRect().x+i.GetRect().w, rb.x);
        rb.y = std::max(i.GetRect().y+i.GetRect().h, rb.y);
    }
    SDL_Point lt = {INT_MAX, INT_MAX};
    for(auto& i : images){
        lt.x = std::min(lt.x, i.GetRect().x);
        lt.y = std::min(lt.y, i.GetRect().y);
    }
    rb.x-=lt.x;
    rb.y-=lt.y;
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_Rect bgrect = {lt.x+Padding, lt.y+Padding, rb.x, rb.y};
    SDL_RenderFillRect(render, &bgrect);

    for(int i=0;i<images.size();i++){
        SDL_Rect rect = images[i].GetRect();
        rect.x += Padding;
        rect.y += Padding;
        SDL_RenderCopy(render, textureManager[i], nullptr, &rect);
    }
    handleSelectedImage();
    oldleftbutton = GetMouseInfo().button[SDL_BUTTON_LEFT];
}

void ImageSheetor::handleSelectedImage(){
    int i;
    for(i=0;i<images.size();i++){
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
    if(i==images.size() && GetMouseInfo().button[SDL_BUTTON_LEFT])
        image_idx = Error_Index;
        SDL_Point mousepos = GetMouseInfo().pos;
        if(moving_idx==Error_Index && image_idx!=Error_Index) {
            SDL_Rect oldrect = images[image_idx].GetRect();
            oldrect.x += Padding;
            oldrect.y += Padding;
            if (moving_idx == Error_Index && SDL_PointInRect(&mousepos, &oldrect) && !oldleftbutton &&
                mouseinfo.button[SDL_BUTTON_LEFT])
                moving_idx = image_idx;
        }
        if(!mouseinfo.button[SDL_BUTTON_LEFT]) {
            moving_idx = Error_Index;
            relayout();
        }
        if(moving_idx!=Error_Index)
            handleImageMovement();
    if(image_idx!=Error_Index){
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_Rect rect = images[image_idx].GetRect();
        rect.x += Padding;
        rect.y += Padding;
        SDL_RenderDrawRect(render, &rect);
    }
}

void ImageSheetor::handleImageMovement(){
    SDL_Rect oldrect = images[moving_idx].GetRect();
    MouseInfo mouseinfo = GetMouseInfo();
    SDL_Point mousepos = mouseinfo.pos;
    oldrect.x += Padding;
    oldrect.y += Padding;
    SDL_Rect rect = {mousepos.x-oldrect.w/2,mousepos.y-oldrect.h/2, oldrect.w, oldrect.h};
    Vector2D speed(rect.x-oldrect.x, rect.y-oldrect.y);
    for(int i=0;i<images.size();i++) {
        if(i==moving_idx)
            continue;
        SDL_Rect dstrect = images[i].GetRect();
        dstrect.x += Padding;
        dstrect.y += Padding;
        if(RectRect(rect, dstrect)){
            RectCollisionInfo info = GetRectRectInfo(rect, speed, dstrect);
            HandleRectColliWithInfo(rect, dstrect, info);
        }
    }
    images[moving_idx].SetPos(rect.x-Padding, rect.y-Padding);
}

SDL_Point ImageSheetor::findBoarder(){
    SDL_Point boarder = {0, 0};
    for(auto & image : images){
        boarder.x = std::max(boarder.x, image.GetRect().x+image.GetRect().w);
        boarder.y = std::max(boarder.y, image.GetRect().y+image.GetRect().h);
    }
    return boarder;
}

void ImageSheetor::relayout() {
    SDL_Point min_boarder = {INT_MAX, INT_MAX};
    for(auto & image : images){
        min_boarder.x = std::min(min_boarder.x, image.GetRect().x);
        min_boarder.y = std::min(min_boarder.y, image.GetRect().y);
    }
    for (auto &i : images) {
        i.SetPos(i.GetRect().x - min_boarder.x, i.GetRect().y - min_boarder.y);
    }
    Resize();
}

ImageSheetor::~ImageSheetor(){
    for(auto & image : images)
        SDL_FreeSurface(image.GetImage());
}

RUN_APP(ImageSheetor)
