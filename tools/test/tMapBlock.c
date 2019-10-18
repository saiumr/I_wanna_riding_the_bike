#include <stdio.h>
#include "unittest.h"
#include "MapBlock.h"

int main(int argc, char** argv){
    MapBlock rectblock = CreateSysColliMapBlock(NULL, "image.bmp", COLLI_RECTANGLE, DEFAULT_SIZE, DEFAULT_POS);
    SDL_Point vertices[]={
        {0,  0},
        {5,  1},
        {1,  0}
    };
    MapBlock userblock = CreateUserColliMapBlock(NULL, "image.bmp", vertices, 3, DEFAULT_SIZE, DEFAULT_POS);
    SDL_Circle circleinfo={
        {5, 5},
        3
    };
    int circlearray[3];
    Circle2IntArray(circleinfo, circlearray);
    MapBlock temblock = CreateColliMapBlockByTemplate(NULL, "image.bmp", COLLI_CIRCLE, circlearray, DEFAULT_SIZE, DEFAULT_POS);

    ColliShape rectshape = GetColliShape(&rectblock);
    ADD_TEST_EQUALOBJ("rectblock created failed?", rectblock, ERROR_MAPBLOCK);
    ADD_TEST_TRUE("GetColliType", GetColliType(&rectshape), COLLI_RECTANGLE);
    //TODO 这里的测试没通过，表示设计需要变化了
    ADD_TEST_TRUE("vertice num", GetColliDataNum(&rectshape), 4);
    SDL_Rect collirect = GetRectangleColliData(&rectshape);
    //获得矩形碰撞检测的左下角点
    ADD_TEST_TRUE("collirect's lb.x", collirect.x, 0);
    ADD_TEST_TRUE("collirect's lb.y", collirect.y, 0);
    //测试矩形碰撞检测右上角点
    ADD_TEST_TRUE("collirect's rt.x", collirect.x+collirect.w, 1);
    ADD_TEST_TRUE("collirect's rt.y", collirect.y+collirect.h, 1);

    ColliShape usershape = GetColliShape(&userblock); 
    ADD_TEST_TRUE("usershape->vertice_num", GetColliDataNum(&usershape), 3);
    SDL_Point colliuser[GetColliDataNum(&usershape)];
    GetUserColliData(&usershape, colliuser);
    ADD_TEST_TRUE("colliuser", colliuser[0].x, 0);
    ADD_TEST_TRUE("colliuser", colliuser[1].x, 0.5);

    ColliShape usertemshape = GetColliShape(&temblock);
    ADD_TEST_TRUE("circle collisio data", GetCircleColliData(&usertemshape).r, 0.3);

    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}