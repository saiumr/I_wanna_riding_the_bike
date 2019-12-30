#include "engin/mmath.hpp"
#include "unittest.hpp"
#define EPS 0.00001
#define COMPARE_FLOAT(n1, n2) fabs(n1-n2)<=EPS

int main(int argc, char** argv){
    SDL_Vector v1 = {2, 2},
                v2 = {3.5, 9};
    SDL_Vector ret = Vec_Add(&v1, &v2);

    ADD_TEST_TRUE("Vec_Add", ret.x, 5.5)
    ADD_TEST_TRUE("Vec_Add", ret.y, 11)

    ret = Vec_Sub(&v1, &v2);
    ADD_TEST_TRUE("Vec_Sub", ret.x, -1.5);
    ADD_TEST_TRUE("Vec_Sub", ret.y, -7);

    ret = Vec_Div(&v2, &v1);
    printf("div ret = (%f, %f)\n", ret.x, ret.y);
    ADD_TEST_TRUE("Vec_Div", COMPARE_FLOAT(ret.x, 3.5/2), true);
    ADD_TEST_TRUE("Vec_Div", COMPARE_FLOAT(ret.y, 9.0/2.0), true);
    

    ret = Vec_Mul(&v1, &v2);
    ADD_TEST_TRUE("Vec_Mul", ret.x, 7);
    ADD_TEST_TRUE("Vec_Mul", ret.y, 18);

    float dot = Vec_Dot(&v1, &v2);
    ADD_TEST_TRUE("Vec_Dot", dot, 2*3.5+2*9);

    ADD_TEST_TRUE("Vec_GetLen", COMPARE_FLOAT(Vec_GetLen(&v1), sqrtf(v1.x*v1.x+v1.y*v1.y)), true);

    ret = Vec_Normalize(&v2);
    ADD_TEST_TRUE("Vec_Normalize", COMPARE_FLOAT(Vec_GetLen(&ret), 1), true);

    ADD_TEST_TRUE("Degree2Radian", COMPARE_FLOAT(Degree2Radian(30), M_PI/6), true);
    ADD_TEST_TRUE("Degree2Radian", COMPARE_FLOAT(Degree2Radian(60), M_PI/3), true);
    ADD_TEST_TRUE("Degree2Radian", COMPARE_FLOAT(Degree2Radian(45), M_PI/4), true);
    ADD_TEST_TRUE("Degree2Radian", COMPARE_FLOAT(Degree2Radian(90), M_PI/2), true);

    ADD_TEST_TRUE("Radian2Degree", COMPARE_FLOAT(Radian2Degree(M_PI/2), 90), true);
    ADD_TEST_TRUE("Radian2Degree", COMPARE_FLOAT(Radian2Degree(M_PI/3), 60), true);
    ADD_TEST_TRUE("Radian2Degree", COMPARE_FLOAT(Radian2Degree(M_PI/4), 45), true);
    ADD_TEST_TRUE("Radian2Degree", COMPARE_FLOAT(Radian2Degree(M_PI/6), 30), true);

    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}