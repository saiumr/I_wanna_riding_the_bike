//TODO 增加了容器类和非容器类的区别，对容器类增加了子节点，对非容器类增加了父节点。现在需要改变所有会影响到节点的函数
#ifndef __UI_H__
#define __UI_H__

#include <stdbool.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_FontCache.h"
#include "header.h"
#include "log.h"
#include "linklist.h"
#define CONTAINER_INC_NUM 10

/**
 * @brief 初始化UI库
 */
void UI_Init(SDL_Renderer*);

/**
 * @brief 设置当前UI要用到的render
 * 
 * @warn 当循环中render改变的时候不要忘记使用这个函数来重新设置render
 * 
 */
void UI_SetRenderer(SDL_Renderer*);

/**
 * @brief 保存用到的Renderer
 * 
 */
static SDL_Renderer* _UI_Render = NULL;

/**
 * @brief 事件回调函数指针，第一个参数是SDL_Event*，第二个参数是UI组件
 */
typedef void (*UI_pEventCallBack)(SDL_Event*, void*);

/**
 * @brief 代表所有的UI，使用的时候需要强制转换
 */
typedef void* UI_Widget;

/**
 * @brief 组件的种类
 */
typedef enum{
    CONTAINER,
    BUTTON,
    IMAGE
}Widget_Type;

/**
 * @brief UI组件的基本信息,所有UI组件都会包含这个结构体
 */
typedef struct _UI_BasicInfo{
    SDL_Point   pos;    /**< 代表UI位置的点（取决于锚点）*/
    SDL_Size    size;   /**< UI的大小 */
    SDL_Pointf  anchor; /**< UI的锚点 */
    bool        show;   /**< 是否显示UI */
    UI_Widget   parent; /**< 父节点*/
    Widget_Type type;   /**< 组件的种类*/
}UI_BasicInfo;

/**
 * @brief 事件结构体
 */
typedef struct{
    UI_pEventCallBack   user_event;         /*< 用户自己的事件*/
    UI_pEventCallBack   default_event;      /*< 系统自带的事件*/
}_UI_EventStruct;

/**
 * @brief 存储所有事件的事件列表
 */
typedef struct{
    _UI_EventStruct pMouseDown;
    _UI_EventStruct pMouseRelease;
    _UI_EventStruct pMouseMotion;
    _UI_EventStruct pKeyDown;
    _UI_EventStruct pKeyRelease;
    _UI_EventStruct pClick;
    bool            bubble;             /*< 事件发生完之后是否要沿着渲染树发送给其父节点(默认不发送)*/         
}UI_EventTable;

/**
 * @brief 所有UI组件都必须包含在第一个成员的基本信息
 */
typedef struct{
    UI_BasicInfo  info;
    UI_EventTable table;
}UI_BasicUIInfo;

/**
 * @brief 部分UI组件会用到的，用于设定显示颜色的结构体
 * 
 */
typedef struct{
    SDL_Color   forecolor;  /**< 前景色*/
    SDL_Color   backcolor;  /**< 背景色*/
    Uint8       fontsize;   /**< 文字大小*/
    Uint8       ypadding;   /**< y方向上文字到边界的间距*/
    Uint8       xpadding;   /**< x方向上文字到边界的间距*/
}UI_DisplayInfo;

typedef struct{
    UI_BasicUIInfo  info;       /**< 基本信息*/
    LinkList*       children;   /**< 子节点*/
    Uint32          size;       /**< 总容量*/
    Uint32          num;        /**< 子节点个数*/
}UI_BasicContainerInfo;

/**
 * @brief 按钮UI的结构体
 */
typedef struct{
    UI_BasicUIInfo basicinfo;
    UI_DisplayInfo displayinfo;
    char text[50];  /**< 显示在按钮上的文字*/
}UI_Button;

/**
 * @brief 图像UI的结构体
 */
typedef struct{
    UI_BasicUIInfo  basicinfo;
    SDL_Texture*    image;
}UI_Image;

/**
 * @brief 用于存储所有UI，方便对所有UI进行一系列操作的UI仓库
 */
typedef struct{
    UI_BasicUIInfo info[1024];
    Uint32 size;
}UI_UIStorage;

static UI_UIStorage* UIStorage=NULL;

/**
 * @brief 默认的显示方案
 */
static const UI_DisplayInfo _UI_DEFAULT_DISPLAY_INFO={
    {0,     0,      0,  255},
    {255,   255,    255,  255},
    20,
    10,
    10
};

/**
 * @brief 默认的基本信息，其中大小随着不同的控件而不同
 * 
 */
static const UI_BasicInfo _UI_DEFAULT_BASIC_INFO={
    .pos={0,     0},
    .anchor={0.5,   0.5},
    .show = true,
    .parent = NULL
};

void UI_StorageAddComponent(UI_Widget item);

/**
 * @brief 通过pos和anchor，计算左上角点的位置
 * 
 * @param info      UI的基本信息
 * @return SDL_Point 
 */
SDL_Point _calcuTL(UI_BasicInfo* info);

/**
 * @brief 根据按钮的文字大小，自动改变宽度和高度
 * 
 * @param button 
 */
void _fixButtonSize(UI_Button* button);

void UI_ContainerAddChild(UI_Widget container, UI_BasicInfo* child);

void UI_DestroyContainer(UI_Widget container);

//item event trigger functions
void _trigItemEventClick(SDL_Event*, UI_Widget item);
void _trigItemEventMouseDown(SDL_Event*, UI_Widget item);
void _trigItemEventMouseRelease(SDL_Event*, UI_Widget item);
void _trigItemEventMouseMotion(SDL_Event*, UI_Widget item);
void _trigItemEventKeyDown(SDL_Event*, UI_Widget item);
void _trigItemEventKeyRelease(SDL_Event*, UI_Widget item);

void _createDefaultBasicUIInfo(UI_BasicUIInfo* info);

//event deliver
/**
 * @brief 分发事件给对应的UI组件
 * 
 * @param item 要分发事件的UI组件
 */
void _eventDeliver(SDL_Event*, UI_Widget item);

//common UI functions
/**
 * @brief 移动UI
 * 
 * @param item  UI组件
 * @param x     x坐标
 * @param y     y坐标
 */
void UI_MoveItem(UI_Widget item, int x, int y);

/**
 * @brief 获得UI的外包围矩形框，便于绘制
 * 
 * @param item 
 * @return SDL_Rect 
 */
SDL_Rect UI_GetRect(UI_Widget item);

/**
 * @brief 获得UI大小
 * 
 * @param item      UI组件
 * @return SDL_Size UI大小
 */
SDL_Size UI_GetSize(UI_Widget item);

/**
 * @brief 设置UI大小
 * 
 * @param item  UI组件 
 * @param w     宽度 
 * @param h     高度
 */
void UI_SetSize(UI_Widget item, int w, int h);

/**
 * @brief 获得UI位置（不是左上角的位置，取决于锚点）
 * 
 * @param item          UI组件
 * @return SDL_Point    位置
 */
SDL_Point UI_GetPosition(UI_Widget item);

/**
 * @brief 获得UI锚点
 * 
 * @param item          UI组件
 * @return SDL_Pointf   锚点
 * 
 * @warn 注意这里的锚点是`SDL_Pointf`类型而不是`SDL_Point`
 */
SDL_Pointf UI_GetAnchor(UI_Widget item);

/**
 * @brief 设置UI锚点
 * 
 * @param item 
 * @param x 
 * @param y 
 */
void UI_SetAnchor(UI_Widget item, float x, float y);

/**
 * @brief 显示UI
 * 
 * @param item 
 */
void UI_ShowItem(UI_Widget item);

/**
 * @brief 隐藏UI
 * 
 * @param item 
 */
void UI_HideItem(UI_Widget item);

/**
 * @brief UI是否显示
 * 
 * @param item 
 * @return true 
 * @return false 
 */
bool UI_GetVisiable(UI_Widget item);

/**
 * @brief 设置UI的父节点
 * 
 * @param item 
 * @param parent 
 */
void UI_SetParent(UI_Widget item, UI_Widget parent);

/**
 * @brief 获得UI的父节点
 * 
 * @param item 
 * @return UI_Widget 
 */
UI_Widget UI_GetParent(UI_Widget item);

//Item event functions
/**
 * @brief 设置UI的单击事件回调函数
 * 
 * @param item 
 * @param clickfunc 单击事件的回调函数
 */
void UI_SetClickEvent(UI_Widget item, UI_pEventCallBack clickfunc);
void UI_SetMouseDownEvent(UI_Widget item, UI_pEventCallBack mousedownfunc);
void UI_SetMouseReleaseEvent(UI_Widget item, UI_pEventCallBack mousereleasefunc);
void UI_SetMouseMotionEvent(UI_Widget item, UI_pEventCallBack mousemotionfunc);
void UI_SetKeyDownEvent(UI_Widget item, UI_pEventCallBack keydownfunc);
void UI_SetKeyReleaseEvent(UI_Widget item, UI_pEventCallBack keyreleasefunc);

// create functions
/**
 * @brief 创造一个按钮Button
 * 
 * @param title         要显示在按钮上的字
 * @param clickfunc     按钮的单击事件回调函数（可以给NULL表示没有回调函数）
 * @return UI_Button*   返回一个按钮
 */
UI_Button* UI_CreateButton(const char* title, UI_pEventCallBack clickfunc, UI_Widget parent);

/**
 * @brief 创造一个图像Image
 * 
 * @param path          图像的路径
 * @return UI_Image*    返回一个图像
 */
UI_Image* UI_CreateImage(const char* path, UI_Widget parent);


//free functions
/**
 * @brief 销毁一个按钮
 * 
 * @param button 
 */
void UI_DestroyButton(UI_Button* button);

/**
 * @brief 销毁一个图像
 * 
 * @param image 
 */
void UI_DestroyImage(UI_Image* image);

//Draw functions
/**
 * @brief 绘制按钮
 * 
 * @param button 
 */
void UI_DrawButton(UI_Button* button);

/**
 * @brief 绘制图像
 * 
 * @param image 
 */
void UI_DrawImage(UI_Image* image);

void UI_DAKER_MOUSEDOWN_FUNC(SDL_Event*, UI_Widget);

void UI_Quit();
#endif