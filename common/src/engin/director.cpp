#include "engin/director.hpp"
using namespace GUI;

Director* Director::director = nullptr;
const string Director::Platform = SDL_GetPlatform();
const string Director::PathSplitSymbol = Director::Platform=="Windows"?"\\":"/";

Director* Director::GetDirector(){
    if(director==nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "no director, game destroyed!");
    }
    return director;
}

void Director::SetDirector(Director* d){
    director = d;
}

Director::Director(const string title, int width, int height, int nfps):fps(nfps), error_flag(NO_ERROR), isquit(false), scene(nullptr), isfullscreen(false), isLostFocus(false),
                     clear_color({100, 100, 100, 255}), debug_font(nullptr), debug_flag(NO_DEBUG){
    window_width = width;
    window_height = height;
    canva_width = width;
    canva_height = height;
    init();
}

void Director::init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(window == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "window create failed");
        ExitGame(WINDOW_ERROR);
        return;
    }
    render = SDL_CreateRenderer(window, -1, 0);
    if(render == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "render create failed");
        ExitGame(RENDER_ERROR);
        return;
    }
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    debug_font = FC_CreateFont();
    FC_LoadFont(debug_font, render, "resources/SimHei.ttf", 20, {255, 0, 0, 255}, TTF_STYLE_NORMAL);
    GUIResourceManager::InitGUI(render);
}

FC_Font* Director::GetDebugFont(){
    return debug_font;
}

unsigned int Director::GetDebugFlag(){
    return debug_flag;
}

void Director::EnableDebug(DebugType type){
    debug_flag|=type;
}

void Director::ChanegScene(Scene* scene){
    if(this->scene != nullptr){
        this->scene->OnDestroy();
        delete this->scene;
    }
    if(scene == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "loading scene is nullptr");
        this->error_flag = SCENE_ERROR;
        return;
    }
    this->scene = scene;
    this->LoadImage(this->scene->GetImageLoadFilename());
    this->scene->OnInit();
}

Scene* Director::GetCurrentScene(){
    return scene;
}

//TODO 这个函数还可以改善，可以根据前后两个场景来保留共同的图像
void Director::LoadImage(string config_filename){
    ifstream file(config_filename);
    if(file.fail()){
        SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO, "no image loader file %s", config_filename.c_str());
        director->error_flag = IMAGE_ERROR;
        return;
    }
    string filepath;
    while(file>>filepath)
        ImageEntrepot::LoadImage(filepath);
}

bool Director::IsQuit(){
    return isquit;
}

void Director::ExitGame(unsigned int exitcode){
    error_flag = exitcode;
    isquit = true;
}

int Director::GetFPS(){
    return Director::fps;
}

SDL_Window* Director::GetWindow(){
    return window;
}

SDL_Renderer* Director::GetRender(){
    return render;
}

int Director::GetWindowWidth(){
    return window_width;
}

int Director::GetWindowHeight(){
    return window_height;
}

int Director::GetCanvaWidth(){
    return canva_width;
}

int Director::GetCanvaHeight(){
    return canva_height;
}

bool Director::IsFullScreen(){
    return isfullscreen;
}

void Director::ToggleFullScreen(){
    FullScreen(!IsFullScreen());
}

void Director::FullScreen(bool enable){
    if(enable==true)
        SDL_SetWindowFullscreen(Director::GetWindow(), true);
    else
        SDL_SetWindowFullscreen(Director::GetWindow(), false);
    isfullscreen = enable;
}

void Director::destroy(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    FC_ClearFont(debug_font);
    if(scene != nullptr)
        scene->OnDestroy();
    delete scene;
}

Director::~Director(){
    destroy();
}