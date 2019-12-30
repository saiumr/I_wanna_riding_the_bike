#ifndef __DIRECTOR_HPP__
#define __DIRECTOR_HPP__
#include <iostream>
#include <string>
#include <fstream>
#include "spdlog/spdlog.h"
#include "stage.hpp"
#include "scene.hpp"
#include "error.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_FontCache.h"
#include "imageEntrepot.hpp"
using namespace std;

class ImageEntrepot;

//NOTE 这里是预留给用户的，用于自定义调试模式的
enum DebugType{
    NO_DEBUG = 0x00
};

class Stage;

/**
 * 导演类，存储着全局的信息（包括窗体，渲染器等）
 */
class Director final{
public:
    friend Stage;

    /**
     * 获得现在的导演
     * @return 现在的导演
     */
    static Director* GetDirector();
    /**
     * 设置现在的导演
     * @param d
     *
     * @warning 这个函数只应当在InitEngin()函数中使用，参数应当建立在堆上
     */
    static void SetDirector(Director* d);

    int error_flag;
    bool isLostFocus;
    SDL_Color clear_color;

    Director(const string title, int width, int height, int fps);
    int GetFPS();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRender();
    int GetWindowWidth();
    int GetWindowHeight();
    int GetCanvaWidth();
    int GetCanvaHeight();
    void ExitGame(unsigned int exitcode);
    bool IsQuit();
    void ChanegScene(Scene* scene);
    Scene* GetCurrentScene();
    bool IsFullScreen();
    void FullScreen(bool enable);
    void ToggleFullScreen();
    unsigned int GetDebugFlag();
    void EnableDebug(DebugType type);
    FC_Font* GetDebugFont();
    void LoadImage(string filename);
    ~Director();
private:
    Director(Director& other) = delete;
    Director& operator=(const Director&) = delete;
    void init();
    void destroy();

    const int fps;
    bool isfullscreen;
    SDL_Window* window;
    SDL_Renderer* render;
    int window_width;
    int window_height;
    string title;
    bool isquit;
    unsigned int debug_flag;
    Scene* scene;
    FC_Font* debug_font;
    int canva_height;
    int canva_width;

    static Director* director;
};

#endif