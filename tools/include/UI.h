#ifndef __UI_H__
#define __UI_H__

#include <stdbool.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_FontCache.h"
#include "header.h"
#include "log.h"

typedef void (*UI_pEventCallBack)(SDL_Event*, void*);

typedef struct{
    SDL_Point   center;
    SDL_Size    size;
    SDL_Pointf  anchor;
    bool        show;
}UI_BasicInfo;

typedef struct{
    UI_pEventCallBack pMouseDown;
    UI_pEventCallBack pMouseRelease;
    UI_pEventCallBack pMouseMotion;
    UI_pEventCallBack pKeyDown;
    UI_pEventCallBack pKeyRelease;
    UI_pEventCallBack pClick;
}UI_EventTable;

typedef struct{
    UI_BasicInfo  info;
    UI_EventTable table;
}UI_BasicUIInfo;

typedef struct{
    SDL_Color   forecolor;
    SDL_Color   backcolor;
    Uint8       fontsize;
    Uint8       ypadding;
    Uint8       xpadding;
}UI_DisplayInfo;

typedef struct{
    UI_BasicUIInfo basicinfo;
    UI_DisplayInfo displayinfo;
    char text[50];
}UI_Button;

typedef struct{
    UI_BasicUIInfo  basicinfo;
    SDL_Texture*    image;
}UI_Image;

typedef struct{
    UI_BasicUIInfo info[1024];
    Uint8 size;
}UI_UIStorage;

static UI_UIStorage UIStorage={.size=0};
static const UI_DisplayInfo _UI_DEFAULT_DISPLAY_INFO={
    {0,     0,      0,  255},
    {255,   255,    255,  255},
    20,
    10,
    10
};
static const UI_BasicInfo _UI_DEFAULT_BASIC_INFO={
    {0,     0},
    {100,   100},
    {0.5,   0.5},
    true
};

void UI_StorageAddComponent(void* component);

SDL_Point _calcuTL(UI_BasicInfo* info);
void _fixButtonSize(UI_Button* button);

//item event trigger functions
void _trigItemEventClick(SDL_Event*, void* item);
void _trigItemEventMouseDown(SDL_Event*, void* item);
void _trigItemEventMouseRelease(SDL_Event*, void* item);
void _trigItemEventMouseMotion(SDL_Event*, void* item);
void _trigItemEventKeyDown(SDL_Event*, void* item);
void _trigItemEventKeyRelease(SDL_Event*, void* item);

//event deliver
void _eventDeliver(SDL_Event*, void* item);

//Item help functions
void        UI_MoveItem(void* item, int x, int y);
SDL_Size    UI_GetSize(void* item);
void        UI_SetSize(void* item, int w, int h);
SDL_Point   UI_GetPosition(void* item);
SDL_Pointf  UI_GetAnchor(void* item);
void        UI_SetAnchor(void* item, float x, float y);

//Item event functions
void UI_SetClickEvent(void* item, UI_pEventCallBack clickfunc);

// create functions
UI_Button* UI_CreateButton(const char* title, UI_pEventCallBack clickfunc);
UI_Image* UI_CreateImage(SDL_Renderer*, const char* path);

//free functions
void UI_DestroyButton(UI_Button* button);
void UI_DestroyImage(UI_Image* image);

//Draw functions
void UI_DrawButton(SDL_Renderer*, UI_Button* button);
void UI_DrawImage(SDL_Renderer*, UI_Image* image);

#endif