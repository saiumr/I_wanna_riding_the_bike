#include "particalSystem.h"

PS_World PS_CreateWorld(SDL_Vector gravity, SDL_Renderer* render){
    srand((unsigned)time(NULL));
    PS_World world;
    world.gravity = gravity;
    world.render = render;
    world.partical_num = WORLD_PARTICAL_INIT_NUM;
    world.particals = (_PS_Partical*)malloc(sizeof(_PS_Partical)*WORLD_PARTICAL_INIT_NUM);
    if(world.particals == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "memory not enough, world partical malloc failed!!");
    for(int i=0;i<world.partical_num;i++)
        world.particals[i].isdead = true;
    return world;
}

void _PS_IncreaseParticalSink(PS_World* world){
    world->particals = (_PS_Partical*)realloc(world->particals, sizeof(_PS_Partical)*(world->partical_num+PARTICAL_SINK_INC));
    if(world->particals == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "memory not enough, partical sink realloc failed!!");
    for(int i=world->partical_num-1;i<world->partical_num+PARTICAL_SINK_INC;i++)
        world->particals[i].isdead = true;
    world->partical_num += PARTICAL_SINK_INC;
}

void PS_DestroyWorld(PS_World* world){
    free(world->particals);
    world->particals = NULL;
    world->partical_num = 0;
    world->render = NULL;
}

PS_ParticalLauncher PS_CreateLauncher(SDL_Point position, SDL_Vector shoot_dir, int partical_hp, float half_degree, SDL_Color color, PS_World* world, int shoot_num){
    PS_ParticalLauncher launcher;
    launcher.color = color;
    launcher.half_degree = half_degree;
    launcher.partical_hp = partical_hp;
    launcher.shoot_dir = shoot_dir;
    launcher.world = world;
    launcher.shoot_num = (int)ceil(half_degree*2*PARTICALS_PER_DEGREE);
    launcher.position = position;
    return launcher;
}

void PS_DestroyLauncher(PS_ParticalLauncher* launcher){
    launcher->world = NULL;
}

_PS_Partical* _PS_GetNextDeadPartical(PS_World* world, int* idx){
    int sum = 0;
    (*idx)++;
    if(*idx >= world->partical_num)
        *idx = 0;
    while(world->particals[*idx].isdead != true){
        (*idx)++;
        if(*idx >= world->partical_num)
            (*idx) = 0;
        sum++;
        if(sum >= world->partical_num)
            break;
    }
    if(sum >= world->partical_num)
        return NULL;
    return &world->particals[*idx];
}

_PS_Partical* _PS_GetNextUndeadPartical(PS_World* world, int* idx){
    int sum = 0;
    (*idx)++;
    if(*idx >= world->partical_num)
        *idx = 0;
    while(world->particals[*idx].isdead == true){
        (*idx)++;
        if(*idx >= world->partical_num)
            (*idx) = 0;
        sum++;
        if(sum >= world->partical_num)
            return NULL;
    }
    return &world->particals[*idx];
}

void PS_ShootPartical(PS_ParticalLauncher* launcher){
    PS_World* world = launcher->world;
    int idx = 0;
    for(int i=0;i<launcher->shoot_num;i++){
        _PS_Partical* partical; 
        while((partical=_PS_GetNextDeadPartical(world, &idx))==NULL){
            _PS_IncreaseParticalSink(world);
        }
        int randnum = rand()%(int)(2*launcher->half_degree*1000+1)-(int)launcher->half_degree*1000;
        float randdegree = randnum/1000.0f;   //产生[-30, 30]的五位随机浮点数
        //srand((unsigned)randnum);
        //TODO 这个地方的赋值要不要使用指针呢？放在最后的时候优化吧
        partical->color = launcher->color;
        SDL_Vector direct = Vec_Rotate(&launcher->shoot_dir, randdegree);
        partical->direct = direct;
        partical->hp = launcher->partical_hp + rand()%(10+1)-5;
        partical->isdead = false;
        partical->position.x = launcher->position.x;
        partical->position.y = launcher->position.y;
    }
}

void PS_WorldUpdate(PS_World* world){
    _PS_Partical* partical;
    for(int i=0;i<world->partical_num;i++){
        partical = &world->particals[i];
        if(partical->isdead == false){
            if(partical->hp > 0){
                partical->position.x += partical->direct.x+world->gravity.x/2.0;
                partical->position.y += partical->direct.y+world->gravity.y/2.0;
                _PS_DrawPartical(world->render, partical);
            }
            partical->hp--;
        }
        if(partical->hp <= 0)
            partical->isdead = true;
    }
}

void _PS_DrawPartical(SDL_Renderer* render, _PS_Partical* partical){
    SDL_Color* color = &partical->color;
    SDL_SetRenderDrawColor(render, color->r, color->g, color->b, color->a);
    SDL_RenderDrawCircle(render, partical->position.x, partical->position.y, PARTICAL_R);
}

void PS_Explode(PS_World* world, SDL_Color color, SDL_Point position, int partical_hp){
    int idx = 0;
    for(int i=0;i<PARTICALS_PER_DEGREE*360*2;i++){
        _PS_Partical* partical; 
        while((partical = _PS_GetNextDeadPartical(world, &idx)) == NULL)
            _PS_IncreaseParticalSink(world);
        partical->color = color;
        SDL_Vector v = {0, 3};
        int lowbounder = partical_hp*0.7;
        partical->direct = Vec_Rotate(&v, rand()%(360+1)-180);
        partical->hp = rand()%(partical_hp-lowbounder+1)+lowbounder;
        partical->isdead = false;
        partical->position.x = position.x;
        partical->position.y = position.y;
    }
}