#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "SDL.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief 场景类
 * 
 * @warning 所有的场景类都必须在堆上分配内存，因为Director在场景退出的时候会调用delete自动销毁
 * 
 */
class Scene{
public:
    /**
     * 场景创建时会自动调用这个函数。
     * 你需要在这个函数里
     *
     * * 初始化资源，并且设定场景的名称（场景的基类Scene)
     * * 设置图像加载文件的名称，这样方便加载图像（或者你也可以不给名称来表示不加载任何图像）
     *
     * @warning 不要在场景的构造函数里面初始化资源。所有资源的初始化只能在OnInit中。场景类需要构造函数来初始化name和image_load_filename两个字段.
     */
    virtual void OnInit() = 0;
    /**
     * 场景的事件处理函数，每一帧会调用一次，并且将当前的事件传递给这个函数
     * @param event
     */
    virtual void EventHandle(SDL_Event& event) = 0;
    /**
     * 场景的更新函数，每一帧调用一次
     */
    void Update();
    virtual void OnDestroy() = 0;
    /**
     * 获得场景的名称
     * @return 场景的名称
     */
    string GetName();
    /**
     * 获得图像加载文件的名称
     * @return 图像加载文件的名称(带有相对路径)
     */
    string GetImageLoadFilename();

    virtual ~Scene();
protected:
    string name;
    string image_load_filename;
    /**
     * 子类需要重写这个函数来完成每一帧的迭代。
     * 每一帧被Update()函数调用
     */
    virtual void step() = 0;
};

#endif