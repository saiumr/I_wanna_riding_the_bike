//
// Created by 桂明谦 on 2020/1/14.
//

#include "engin/gui/messagebox.hpp"

//FIXME 解决频闪的问题
GUI::ResultType GUI::ShowMessageBox(SDL_Point pos, SDL_Size size, ButtonType buttontype, string title, string content){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    FC_Font* font = FC_CreateFont();
    SDL_Rect rect = {pos.x, pos.y, size.w, size.h};
    SDL_RenderSetClipRect(render, &rect);
    while(true) {
        SDL_Renderer *render = GUIResourceManager::GetRender();
        SDL_SetRenderDrawColor(render, 220, 200, 220, 255);
        SDL_RenderFillRect(render, &rect);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderDrawRect(render, &rect);
        FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), 15, FC_MakeColor(0, 0, 0, 255),
                    TTF_STYLE_NORMAL);
        int height = FC_GetHeight(font, title.c_str());
        FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), 20, FC_MakeColor(0, 0, 0, 255),
                    TTF_STYLE_NORMAL);
        FC_Draw(font, render, rect.x, rect.y+5, title.c_str());
        SDL_RenderDrawLine(render, rect.x, rect.y + height + 10, rect.x + rect.w, rect.y + height + 10);
        const int width_padding = 50, height_padding = 50;
        FC_Draw(font, render, rect.x + width_padding, rect.y + height_padding, content.c_str());
        const SDL_Size button_size = {70, 30};
        SDL_Rect buttonrect1 = {rect.x+50, rect.y+rect.h-button_size.h-50, button_size.w, button_size.h},
                 buttonrect2 = {rect.x+rect.w-50-button_size.w, rect.y+rect.h-button_size.h-50, button_size.w, button_size.h};
        vector<SDL_Rect> buttons({buttonrect1, buttonrect2});
        switch (buttontype) {
            case ButtonType::YES_NO:
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                SDL_RenderFillRect(render, &buttonrect1);
                SDL_RenderFillRect(render, &buttonrect2);
                SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                SDL_RenderDrawRect(render, &buttonrect1);
                SDL_RenderDrawRect(render, &buttonrect2);
                FC_Draw(font, render, buttonrect1.x, buttonrect1.y, "YES");
                FC_Draw(font, render, buttonrect2.x, buttonrect2.y, "NO");
                break;
            case ButtonType::OK_CANCEL:
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                SDL_RenderFillRect(render, &buttonrect1);
                SDL_RenderFillRect(render, &buttonrect2);
                SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                SDL_RenderDrawRect(render, &buttonrect1);
                SDL_RenderDrawRect(render, &buttonrect2);
                FC_Draw(font, render, buttonrect1.x, buttonrect1.y, "OK");
                FC_Draw(font, render, buttonrect2.x, buttonrect2.y, "CANCEL");
                break;
        }
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_MOUSEBUTTONDOWN){
                for(int i=0;i<buttons.size();i++){
                    SDL_Point pos = {event.button.x, event.button.y};
                    SDL_Rect buttonrect = buttons[i];
                    if(SDL_PointInRect(&pos, &buttonrect)){
                        switch(buttontype){
                            case ButtonType::YES_NO:
                                if(i==0) {
                                    FC_FreeFont(font);
                                    SDL_RenderSetClipRect(render, nullptr);
                                    return ResultType::YES;
                                }
                                if(i==1) {
                                    FC_FreeFont(font);
                                    SDL_RenderSetClipRect(render, nullptr);
                                    return ResultType::NO;
                                }
                                break;
                            case ButtonType::OK_CANCEL:
                                if(i==0) {
                                    FC_FreeFont(font);
                                    SDL_RenderSetClipRect(render, nullptr);
                                    return ResultType::OK;
                                }
                                if(i==1) {
                                    FC_FreeFont(font);
                                    SDL_RenderSetClipRect(render, nullptr);
                                    return ResultType::CANCEL;
                                }
                                break;
                        }
                    }
                }
            }
        }
        SDL_Delay(10);
        SDL_RenderPresent(render);
    }
    return ResultType::CANCEL;
}

/* NOTE Unfinish
unsigned int GUI::ShowUserMessageBox(SDL_Point pos, SDL_Size size, vector<MsgButton> buttons, string title, string content){
    return -1;
}
 */
