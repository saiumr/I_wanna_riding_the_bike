#ifndef __MAPBLOCK_H__
#define __MAPBLOCK_H__
#include <string.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "header.h"
#include "log.h"
#include "SDL_FontCache.h"
#include "SDL_Draw.h"
#include "geomentry.h"

static bool RenderDebugMode = false;

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
    SDL_Size size;
    SDL_Point pos;
    double angle;
}ObjectBasicInfo;

typedef struct{
    ColliShape*     shape;
    ObjectBasicInfo info;
}_basicMapBlockInfo;

typedef struct{
    _basicMapBlockInfo* _basic_info;
    SDL_Texture*        texture;
}MapBlock;

static MapBlock ERROR_MAPBLOCK;
static SDL_Point DEFAULT_POS = {0, 0};
static SDL_Size DEFAULT_SIZE = {-1, -1};

void EnableDebug();
void DisabgleDebug();

SDL_Texture* LoadTexutre(SDL_Renderer* render, char* texture_path, SDL_Size* size);

void InitObjBasicInfo(ObjectBasicInfo* info, SDL_Size size, SDL_Point pos, double angle);
ColliShape* CreateColliShape(SDL_Size size, ColliType type);
ColliShape* CreateUserColliShape(int datas[], int data_num);
void _freeColliShape(ColliShape* shape);
_basicMapBlockInfo* _createSysBasicMapBlockInfo(ColliType type, ObjectBasicInfo* obj_info);
_basicMapBlockInfo* _createUserBasicMapBlockInfo(int datas[], int data_num, ObjectBasicInfo* obj_info);
void _freeBasicMapBlockInfo(_basicMapBlockInfo* basicinfo);
MapBlock* CreateSysColliMapBlock(SDL_Renderer* render, char* texture_path, ColliType colli_type, ObjectBasicInfo info);
MapBlock* CreateUserColliMapBlock(SDL_Renderer* render, char* texture_path, int colli_data[], int data_num, ObjectBasicInfo info);
void FreeMapBlock(MapBlock* block);

SDL_Point GetMapBlockPosition(MapBlock* block);
void SetMapBlockPosition(MapBlock* block, int x, int y);
SDL_Size GetMapBlockSize(MapBlock* block);
void ResizeMapBlock(MapBlock* block, int w, int h);
void RotateMapBlock(MapBlock* block, double angle);
double GetMapBlockAngle(MapBlock* block);
ColliShape* GetMapBlockColliShape(MapBlock* block);
ColliType GetColliType(ColliShape* shape);
unsigned int GetColliDataNum(ColliShape* shape);

SDL_Rect GetRectangleColliData(ColliShape* shape);
SDL_Circle GetCircleColliData(ColliShape* shape);
void GetUserColliData(ColliShape* shape, SDL_Point ret_data[]);
void GetTriangleColliData(ColliShape* shape, SDL_Point ret_data[]);

void Points2IntArray(SDL_Point points[], int point_num, int ret_arrya[]);
void Rect2IntArray(SDL_Rect rect, int ret_arrya[]);
void Circle2IntArray(SDL_Circle circle, int ret_arrya[]);

void DrawMapBlock(SDL_Renderer* render, MapBlock* block);
void DrawColliShape(SDL_Renderer* render, ColliShape* shape, SDL_Point offset, double angle, SDL_Point* center, SDL_Color* color);

#endif