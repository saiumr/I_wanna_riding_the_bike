#ifndef __MAPBLOCK_H__
#define __MAPBLOCK_H__
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "header.h"
#include "log.h"
#include "SDL_FontCache.h"
#include "SDL_Draw.h"
#include "geomentry.h"

typedef enum{
    COLLI_RECTANGLE,
    COLLI_TRIANGLE,
    COLLI_CIRCLE,
    COLLI_USER
}ColliType;

/**
 * @brief 存储碰撞数据的结构体
 * 
 * 
 * 当是
 * * COLLI_RECTANGLE：_vertices[0|1]表示左上角点,_vertices[2|3]表示右下角点。_vertic_num=2
 * * COLLI_TRIANGLE：_vertices[0-5]分别表示第一个，第二个，第三个点,_vertic_num=3
 * * COLLI_CIRCLE：_vertices[0|1]表示中心点，_verties[2]表示半径
 * * COLLI_USER：(_vertices[0], _vertices[1]) i=2k，代表多边形上的各个点（按照CCW或者CW排列）。其坐标系位原点位于属于其Block的左上角
 */
typedef struct{
    int*            _datas;
    unsigned int    _data_num;
    ColliType       _colli_type;
}ColliShape;

typedef struct{
    ColliShape      shape;
    SDL_Point       pos;
    SDL_Size        size;
    SDL_Texture*    texture;
}MapBlock;

static MapBlock ERROR_MAPBLOCK;
static SDL_Point DEFAULT_POS = {0, 0};
static SDL_Size DEFAULT_SIZE = {-1, -1};

bool _InitBasicMapBlockInfo(SDL_Renderer* render, char* texture_path, MapBlock* block, SDL_Size size, SDL_Point pos);
MapBlock CreateSysColliMapBlock(SDL_Renderer* render, char* texture_path, ColliType colli_type, SDL_Size size, SDL_Point pos);
MapBlock CreateUserColliMapBlock(SDL_Renderer* render, char* texture_path, SDL_Point vertices[], unsigned int len,  SDL_Size size, SDL_Point pos);
MapBlock CreateColliMapBlockByTemplate(SDL_Renderer* render, char* texture_path, ColliType colli_type, int colli_info[], SDL_Size size, SDL_Point pos);
ColliType GetColliType(ColliShape* shape);
ColliShape GetColliShape(MapBlock* block);
unsigned int GetColliDataNum(ColliShape* shape);
void GetUserColliData(ColliShape* shape, SDL_Point ret_data[]);
SDL_Rect GetRectangleColliData(ColliShape* shape);
SDL_Circle GetCircleColliData(ColliShape* shape);
void Points2IntArray(SDL_Point points[], int point_num, int ret_arrya[]);
void Rect2IntArray(SDL_Rect rect, int ret_arrya[]);
void Circle2IntArray(SDL_Circle circle, int ret_arrya[]);
#endif