#include "UI.h"

SDL_Point _calcuTL(UI_BasicInfo* info){
    int offsetx = info->anchor.x*info->size.w,
        offsety = info->anchor.y*info->size.h;
    SDL_Point p = {info->center.x - offsetx, info->center.y - offsety};
    return p;
}

void _fixButtonSize(UI_Button* button){
    int len = strlen(button->text);
    int w = button->displayinfo.fontsize/2*len + 2*button->displayinfo.xpadding;
    int h = button->displayinfo.fontsize + 2*button->displayinfo.ypadding;
    UI_SetSize(button, w, h); 
}

void _trigItemEventClick(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pClick)
        info->table.pClick(event, item);
}
void _trigItemEventMouseDown(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseDown)
        info->table.pMouseDown(event, item);
}
void _trigItemEventMouseRelease(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseRelease)
        info->table.pMouseRelease(event, item);
}
void _trigItemEventMouseMotion(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseMotion)
        info->table.pMouseMotion(event, item); 
}
void _trigItemEventKeyDown(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pKeyDown)
        info->table.pKeyDown(event, item);  
}
void _trigItemEventKeyRelease(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pKeyRelease)
        info->table.pKeyRelease(event, item); 
}

void _eventDeliver(SDL_Event* event, void* item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    switch(event->type){
        case SDL_MOUSEMOTION:
            _trigItemEventMouseMotion(event, item);
            break;
        case SDL_MOUSEBUTTONDOWN:
            _trigItemEventMouseDown(event, item);
            break;
        case SDL_MOUSEBUTTONUP:
            _trigItemEventMouseRelease(event, item);
            _trigItemEventClick(event, item);
            break;
        case SDL_KEYDOWN:
            _trigItemEventKeyDown(event, item);
            break;
        case SDL_KEYUP:
            _trigItemEventKeyRelease(event, item);
            break;
    }
}

void UI_MoveItem(void* item, int x, int y){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.center.x = x;
    info->info.center.y = y;
}

SDL_Size UI_GetSize(void* item){
    SDL_Size size = {((UI_BasicUIInfo*)item)->info.size.w, ((UI_BasicUIInfo*)item)->info.size.h};
    return size;
}

SDL_Point UI_GetPosition(void* item){
   SDL_Point p = {((UI_BasicUIInfo*)item)->info.center.x, ((UI_BasicUIInfo*)item)->info.center.y}; 
   return p;
}
SDL_Pointf  UI_GetAnchor(void* item){
    SDL_Pointf p = {((UI_BasicUIInfo*)item)->info.anchor.x, ((UI_BasicUIInfo*)item)->info.anchor.y};
    return p;
}

void UI_SetSize(void* item, int w, int h){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.size.w = w;
    info->info.size.h = h;
}

void UI_SetAnchor(void* item, float x, float y){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.anchor.x = x;
    info->info.anchor.y = y;
}

UI_Button* UI_CreateButton(const char* title, UI_pEventCallBack clickfunc){ 
    UI_BasicUIInfo info = {
        _UI_DEFAULT_BASIC_INFO,
        {NULL, NULL, NULL, NULL, NULL, NULL}
    };
    UI_Button* button = (UI_Button*)malloc(sizeof(UI_Button));
    button->basicinfo = info;
    button->displayinfo = _UI_DEFAULT_DISPLAY_INFO;

    strcpy(button->text, title);
    button->basicinfo.table.pClick = clickfunc;
    _fixButtonSize(button);

    return button;
}

UI_Image* UI_CreateImage(SDL_Renderer* render, const char* path){
    UI_Image* image = (UI_Image*)malloc(sizeof(UI_Image*));
    UI_BasicUIInfo info = {
        _UI_DEFAULT_BASIC_INFO,
        {NULL, NULL, NULL, NULL, NULL, NULL}
    };
    image->basicinfo = info;
    SDL_Surface* surface = IMG_Load(path);
    if(!surface){
        log_error("surface not found");
        free(surface);
        return NULL;
    }
    UI_SetSize(image, surface->w, surface->h);
    image->image = SDL_CreateTextureFromSurface(render, surface);
    if(!image->image){
        log_error("texture create failed");
        free(image->image);
        return NULL;
    }
    return image;
}

void UI_DrawImage(SDL_Renderer*render, UI_Image* image){
    SDL_Point lt = _calcuTL((UI_BasicInfo*)image);
    SDL_Size size = UI_GetSize(image);
    SDL_Rect rect = {lt.x, lt.y, size.w, size.h};
    SDL_RenderCopy(render, image->image, NULL, &rect);
}

void UI_DestroyButton(UI_Button* button){
    if(button)
        free(button);
    button = NULL;
}

void UI_DestroyImage(UI_Image* image){
    if(image)
        free(image);
    image = NULL;
}

void UI_DrawButton(SDL_Renderer*render, UI_Button* button){
    SDL_Point lt = _calcuTL(&button->basicinfo.info);
    SDL_Size size = UI_GetSize(button);
    SDL_Rect rect = {lt.x, lt.y, size.w, size.h};
    SDL_Color color;
    SDL_Color* backcolor = &button->displayinfo.backcolor;
    Uint8 xpadding = button->displayinfo.xpadding,
        ypadding = button->displayinfo.ypadding;
    SDL_GetRenderDrawColor(render, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(render, backcolor->r, backcolor->g, backcolor->b, backcolor->a);
    SDL_RenderFillRect(render, &rect);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderDrawRect(render, &rect);
    FC_Font* font = FC_CreateFont();
    FC_LoadFont(font, render, "Fangsong.ttf", button->displayinfo.fontsize, button->displayinfo.forecolor, TTF_STYLE_NORMAL);
    FC_Draw(font, render, lt.x+xpadding, lt.y+ypadding, button->text);
    FC_FreeFont(font);
}

//TODO 这里的函数还没有完成
void UI_StorageAddComponent(void* component){}