//
// Created by 桂明谦 on 2019/12/31.
//

#ifndef I_WANNA_RIDING_THE_BIKE_APP_HPP
#define I_WANNA_RIDING_THE_BIKE_APP_HPP

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_FontCache.h"
#include <string>
#include <map>
using namespace std;

/**
 * 使用这个函数来运行你的类
 */
#define RUN_APP(appname) \
int main(int argc, char** argv){ \
    appname app; \
    app.Run(); \
    return 0; \
}

using namespace std;

/**
 * 这个类方便你创建你自己的程序
 */
class GUITestframework {
public:
    using KeyMap = map<SDL_Keycode, bool>;
    /**
     * 用于存储鼠标按键和位置的结构体
     */
    struct MouseInfo{
        SDL_Point pos;
        map<Uint32, bool> button;
        MouseInfo();
    };
    /**
     * 延时的长度(ms计)
     */
    static const int delay_time = 10;
    GUITestframework(const string& title, int width, int height, Uint32 flag=SDL_WINDOW_SHOWN);
    /**
     * 用于处理事件的函数，每次重写之后都需要调用GUITestframework::EventHandle()
     * @param event
     */
    virtual void EventHandle(SDL_Event& event);
    /**
     * 每一帧都会调用这个函数来更新程序
     */
    virtual void Update() = 0;

    void Run();
    /**
     * 获得后台画布大小，也就是原始大小
     * @return
     */
    SDL_Point GetOriginalSize();
    /**
     * 这个函数在程序退出的时候会被调用
     */
    virtual void OnExit();
    /**
     * 不问结果强制退出程序
     */
    void Quit();
    MouseInfo& GetMouseInfo();
    bool KeyPressing(SDL_Keycode key);
    bool KeyPressed(SDL_Keycode key);
    bool KeyReleased(SDL_Keycode key);
    ~GUITestframework();
protected:
    SDL_Window* window;
    SDL_Renderer* render;
    bool isquit;
    MouseInfo mouseinfo;
    KeyMap keystate;
    KeyMap oldkeystate;
private:
    SDL_Point size;
};

#endif //I_WANNA_RIDING_THE_BIKE_APP_HPP
