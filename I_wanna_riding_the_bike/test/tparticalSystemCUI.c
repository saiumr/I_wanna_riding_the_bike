#include "unittest.h"
#include "particalSystem.h"

int main(int argc, char** argv){
    SDL_Vector gravity = {0, 0};
    PS_World world;
    world = PS_CreateWorld(gravity, NULL);
    world.particals[2].isdead = false;
    world.particals[3].isdead = false;
    world.particals[4].isdead = false;
    world.particals[5].isdead = false;
    world.particals[11].isdead = false;
    world.particals[12].isdead = false;
    world.particals[13].isdead = false;
    world.particals[22].isdead = false;
    world.particals[29].isdead = false;
    world.particals[31].isdead = false;
    world.particals[39].isdead = false;
    world.particals[44].isdead = false;

    int idx = 0;
    _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", idx, 2);
    _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", idx, 3);
    _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", idx, 4);
    _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", idx, 5);
    _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", idx, 11);
    _PS_GetNextDeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextDeadPartical", idx, 14);
    _PS_GetNextDeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextDeadPartical", idx, 15);
    _PS_GetNextDeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextDeadPartical", idx, 16);
    idx = 30;
    _PS_GetNextDeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextDeadPartical", idx, 32);

    for(int i=0;i<world.partical_num;i++)
        world.particals[i].isdead = true;
    _PS_Partical* partical = _PS_GetNextUndeadPartical(&world, &idx);
    ADD_TEST_TRUE("GetNextUndeadPartical", partical, NULL);
    world.particals[4].isdead = false;
    world.particals[5].isdead = false;
    world.particals[11].isdead = false;
    world.particals[12].isdead = false;
    _PS_IncreaseParticalSink(&world);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.partical_num, 100+PARTICAL_SINK_INC);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.particals[4].isdead, false);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.particals[5].isdead, false);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.particals[11].isdead, false);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.particals[12].isdead, false);
    ADD_TEST_TRUE("_PS_IncreaseParticalSink", world.particals[120].isdead, true);

    PS_DestroyWorld(&world);
    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}