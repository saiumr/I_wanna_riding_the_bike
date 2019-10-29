#include "MapBlockActions.h"
//TODO 实现.h中的函数
MapBlockActionGroup* CreateMapBlockActionGroup(MapBlock* block){
    MapBlockActionGroup* group = (MapBlockActionGroup*)malloc(sizeof(MapBlockActionGroup));
    group->block = (MapBlock*)malloc(sizeof(MapBlock));
    memcpy(group->block, block, sizeof(MapBlock));
    group->action = LinkList_Create();
}

void AttachMoveActionByTime(MapBlockActionGroup* action, SDL_Point* position, int display_time, int delay_time){
    Action action_info;
    _setActionTypeMove(&action, position, action->block);
    _setActionConditionTime(&action, delay_time);
    _setActionDisplayTime(&action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachRotateActionByTime(MapBlockActionGroup* action, float degree, int display_time, int delay_time){
    Action action_info;
    _setActionTypeRotate(&action_info, &degree, action->block);
    _setActionConditionTime(&action, delay_time);
    _setActionDisplayTime(&action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachScaleActionByTime(MapBlockActionGroup* action, SDL_Size* size, int display_time, int delay_time){
    Action action_info;
    _setActionTypeScale(&action_info, size, action->block);
    _setActionConditionTime(&action ,delay_time);
    _setActionDisplayTime(&action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachRotateActionByRectArea(MapBlockActionGroup* action, float* degree, int display_time, SDL_Rect* area){
    Action action_info;
    _setActionTypeRotate(&action_info, &degree, action->block);
    _setActionConditionRectArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachMoveActionByRectArea(MapBlockActionGroup* action, SDL_Point* pos, int display_time, SDL_Rect* area){
    Action action_info;
    _setActionTypeMove(&action_info, pos, action->block);
    _setActionConditionRectArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachScaleActionByRectArea(MapBlockActionGroup* action, SDL_Size* size, int display_time, SDL_Rect* area){
    Action action_info;
    _setActionTypeScale(&action_info, size, action->block);
    _setActionConditionRectArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachRotateActionByCircleArea(MapBlockActionGroup* action, float* degree, int display_time, SDL_Circle* area){
    Action action_info;
    _setActionTypeRotate(&action_info, degree, action->block);
    _setActionConditionCircleArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachMoveActionByCircleArea(MapBlockActionGroup* action, SDL_Point* pos, int display_time, SDL_Circle* area){
    Action action_info;
    _setActionTypeMove(&action_info, pos, action->block);
    _setActionConditionCircleArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void AttachScaleActionByCircleArea(MapBlockActionGroup* action, SDL_Size* size, int display_time, SDL_Circle* area){
    Action action_info;
    _setActionTypeScale(&action_info, size, action->block);
    _setActionConditionCircleArea(&action_info, area);
    _setActionDisplayTime(action, display_time);
    _addAction2Tail(action, &action_info);
}

void _setActionConditionRectArea(Action* action_info, SDL_Rect* area){
    action_info->condition.type = AREA_RECTANGLE;
    action_info->condition.time = NO_DELATTIME;
    action_info->condition.area_data = (int*)malloc(sizeof(int)*4);
    action_info->condition.area_data[0] = area->x;
    action_info->condition.area_data[1] = area->y;
    action_info->condition.area_data[2] = area->w;
    action_info->condition.area_data[3] = area->h;
}

void _setActionConditionCircleArea(Action* action_info, SDL_Circle* area){
    action_info->condition.type = AREA_CIRCLE;
    action_info->condition.time = NO_DELATTIME;
    action_info->condition.area_data = (int*)malloc(sizeof(int)*3);
    action_info->condition.area_data[0] = area->center.x;
    action_info->condition.area_data[1] = area->center.y;
    action_info->condition.area_data[2] = area->r;
}

SDL_Rect GetActionRectArea(Action* action_info){
    SDL_Rect rect = {action_info->condition.area_data[0], action_info->condition.area_data[1], 
                     action_info->condition.area_data[2], action_info->condition.area_data[3]};
    return rect;
}

SDL_Circle GetActionCircleArea(Action* action_info){
    SDL_Circle circle = {{action_info->condition.area_data[0], action_info->condition.area_data[1]},
                         action_info->condition.area_data[2]};
    return circle;
}

void _addAction2Tail(MapBlockActionGroup* action, Action* action_info){
    LinkList_Add2Tail(&(action->action), (void*)&action_info, sizeof(Action));
}

void _setActionTypeMove(Action* action_info, SDL_Point* position, MapBlock* block){
    action_info->type = ACTION_MOVE;
    ObjectBasicInfo* objbasicinfo = GetMapBlockBasicInfo(block); 
    ObjectBasicInfo newbasicinfo = {objbasicinfo->size, *position, objbasicinfo->angle};
    action_info->info = newbasicinfo;
}

void _setActionTypeRotate(Action* action_info, float* angle, MapBlock* block){
    action_info->type == ACTION_ROTATE;
    ObjectBasicInfo* objbasicinfo = GetMapBlockBasicInfo(block);
    action_info->info = *objbasicinfo;
    action_info->info.angle = *angle;
}

void _setActionTypeScale(Action* action_info, SDL_Size* size, MapBlock* block){
    action_info->type = ACTION_SCALE;
    ObjectBasicInfo* objbasicinfo = GetMapBlockBasicInfo(block);
    action_info->info = *objbasicinfo;
    action_info->info.size = *size;
}

void _setActionConditionTime(Action* action_info, int delay_time){
    action_info->condition.time = delay_time;
    action_info->condition.area_data = NO_TRIGAREA;
    action_info->condition.type = TIME;
}

void _setActionDisplayTime(Action* action_info, int display_time){
    action_info->display_time = display_time;
}

void _freeAction(MapBlockLinkList list){
    LinkList* root = list;
    if(root != NULL && *root != NULL && *root != &EmptyLinkList){
        LinkList_Destroy(&((*root)->next));
        free((*root)->data);
        free(((Action*)root)->condition.area_data);
        free(*root);
        *root = NULL;
    }
}

void FreeMapBlockActionGroup(MapBlockActionGroup* action){
    _freeAction(action->action);
    free(action->block);
}