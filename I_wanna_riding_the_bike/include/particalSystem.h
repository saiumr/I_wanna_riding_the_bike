/**
 * @file particalSystem.h
 * @author VisualGMQ
 * @brief 简单的粒子系统
 * @version 0.1
 * @date 2019-10-02
 * 
 * @copyright Copyright (c) 2019
 * 
 * 使用方法：
 *  1. 首先需要PS_CreateWorld()来诞生一个世界
 *  2. 然后需要PS_CreateLauncher()来产生一个发射器
 *  3. 然后在游戏循环中，需要发射的时候调用PS_ShootPartical()
 *  4. 在游戏循环的最后调用PS_WorldUpdate()来更新世界中的粒子.
 *  5. 使用完之后不要忘记PS_DestroyWorld()和PS_DestroyLauncher()
 */

//Warning: 这个粒子系统的效率很低，后期要想办法优化
#ifndef __PARTICALSYSTEM_H__
#define __PARTICALSYSTEM_H__

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "engin/mmath.h"
#include "engin/SDL_Draw.h"
#define WORLD_PARTICAL_INIT_NUM 100
#define PARTICAL_SINK_INC 50
#define PARTICAL_R 5
#define PARTICALS_PER_DEGREE 0.15

typedef struct __PS_Partical _PS_Partical;

typedef struct{
    SDL_Vector      gravity;
    int             partical_num;   /**< 粒子池中的粒子个数*/
    _PS_Partical*   particals;      /**< 粒子池*/
    SDL_Renderer*   render;
}PS_World;

typedef struct{
    SDL_Vector  shoot_dir;
    int         partical_hp;
    float       half_degree;
    SDL_Color   color;
    PS_World*   world;
    int         shoot_num;      /**<一次性发射出去的粒子个数*/
    SDL_Point   position;
}PS_ParticalLauncher;

/**
 * @brief 创建一个世界
 * 
 * @param gravity 世界中的引力方向
 * @param render 
 * @return PS_World 
 */
PS_World    PS_CreateWorld(SDL_Vector gravity, SDL_Renderer* render);
void        _PS_IncreaseParticalSink(PS_World* world);
/**
 * @brief 销毁世界
 * 
 * @param world 
 */
void        PS_DestroyWorld(PS_World* world);      
/**
 * @brief 更新世界（需逐帧调用）
 * 
 * @param world 
 */
void        PS_WorldUpdate(PS_World* world);
/**
 * @brief 创建一个粒子发射器
 * 
 * @param position      发射器位置
 * @param shoot_dir     发射方向
 * @param partical_hp   每一个粒子的生命值
 * @param half_degree   发射半径的一半
 * @param color         粒子颜色
 * @param world         发射器所在的世界
 * @param shoot_num     每一帧发射的粒子数目
 * @return PS_ParticalLauncher
 */
PS_ParticalLauncher PS_CreateLauncher(SDL_Point position, SDL_Vector shoot_dir, int partical_hp, float half_degree, SDL_Color color, PS_World* world, int shoot_num);
/**
 * @brief 销毁粒子发射器
 * 
 * @param launcher 
 */
void                PS_DestroyLauncher(PS_ParticalLauncher* launcher);

/**
 * @brief 发射粒子(在需要发射的时候需逐帧调用)
 * 
 * @param launcher 
 */
void PS_ShootPartical(PS_ParticalLauncher* launcher);

/**
 * @brief 产生一阵粒子爆炸（以圆的方向发射粒子）
 * 
 * @param world 
 * @param color 
 * @param position 
 * @param partical_hp 
 */
void PS_Explode(PS_World* world, SDL_Color color, SDL_Point position, int partical_hp);
_PS_Partical* _PS_GetNextDeadPartical(PS_World* world, int* idx);
_PS_Partical* _PS_GetNextUndeadPartical(PS_World* world, int* idx);
void _PS_DrawPartical(SDL_Renderer* render, _PS_Partical* partical);
#endif