#ifndef __MAPBLOCKACTIONS_H__
#define __MAPBLOCKACTIONS_H__
#include "MapBlock.h"
#include "linklist.h"

#define NO_DELATTIME -1
#define NO_TRIGAREA NULL

typedef enum{
    ACTION_MOVE,
    ACTION_ROTATE,
    ACTION_SCALE
}MapBlockActionType;

typedef enum{
    TIME,
    AREA_RECTANGLE,
    AREA_CIRCLE
}TrigType;

typedef struct{
    int             time;
    int*            area_data;
    TrigType    type;
    //ColliType       area_type; 我们现在暂时只支持圆形区域和无旋转的矩形区域。
}TrigCondition;

typedef struct{
    ObjectBasicInfo     info;
    MapBlockActionType  type;
    unsigned int        display_time;
    TrigCondition       condition;
}Action;

typedef LinkList MapBlockLinkList;  //LinkList data type: Action

typedef struct
{
    MapBlock*           block;
    MapBlockLinkList*   action;
}MapBlockActionGroup;

MapBlockActionGroup* CreateMapBlockActionGroup(MapBlock* block);

void AttachMoveActionByTime(MapBlockActionGroup* action, SDL_Point* position, int display_time, int delay_time); 
void AttachRotateActionByTime(MapBlockActionGroup* action, float degree, int display_time, int delay_time);
void AttachScaleActionByTime(MapBlockActionGroup* action, SDL_Size* size, int display_time, int delay_time);

void AttachRotateActionByRectArea(MapBlockActionGroup* action, float* degree, int display_time, SDL_Rect* area);
void AttachMoveActionByRectArea(MapBlockActionGroup* action, SDL_Point* pos, int display_time, SDL_Rect* area);
void AttachScaleActionByRectArea(MapBlockActionGroup* action, SDL_Size* size, int display_time, SDL_Rect* area);

void AttachRotateActionByCircleArea(MapBlockActionGroup* action, float* degree, int display_time, SDL_Circle* area);
void AttachMoveActionByCircleArea(MapBlockActionGroup* action, SDL_Point* pos, int display_time, SDL_Circle* area);
void AttachScaleActionByCircleArea(MapBlockActionGroup* action, SDL_Size* size, int display_time, SDL_Circle* area);

/*这些函数还没决定要不要写，觉得太麻烦了。。。不写的话好像也不影响功能，就是用起来会麻烦一些
void MapBlockMoveActionByTime(MapBlockActionGroup* action, MapBlock* block, int display_time, int delay_time);
void MapBlockRotateActionByTime(MapBlockActionGroup* action, MapBlock* block, int display_time, int delay_time);
void MapBlockScaleActionByTime(MapBlockActionGroup* action, MapBlock* block, int display_time, int delay_time);

void MapBlockMoveActionByRectArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Rect* area);
void MapBlockRotateActionByRectArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Rect* area);
void MapBlockScaleActionByRectArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Rect* area);

void MapBlockMoveActionByCircleArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Circle* area);
void MapBlockRotateActionByCircleArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Circle* area);
void MapBlockScaleActionByCircleArea(MapBlockActionGroup* action, MapBlock* block, int display_time, SDL_Circle* area);
*/

void FreeMapBlockActionGroup(MapBlockActionGroup* action);
void DeleteAction(Action* action);

//TODO没写完
void DrawMapBlockAction(MapBlockActionGroup* action);
void MapBlockActionDealEvent(MapBlockActionGroup* action);

#endif