#include "MapBlock.h"

struct _ColliShape{
    int*            _datas;
    unsigned int    _data_num;
    ColliType       _colli_type;
};

struct __basicMapBlockInfo{
    ColliShape*     shape;
    ObjectBasicInfo info;
};

void EnableDebug(){
    RenderDebugMode = true;
}

void DisabgleDebug(){
    RenderDebugMode = false;
}

MapBlock* CreateSysColliMapBlock(SDL_Renderer* render, char* texture_path, ColliType colli_type, ObjectBasicInfo info){
    MapBlock* block = (MapBlock*)malloc(sizeof(MapBlock));
    block->_basic_info = NULL;
    block->texture = NULL;
    if(block == NULL){
        log_error("<CreateSysColliMapBlock>:malloc mapblock failed");
        return NULL;
    }
    SDL_Size tex_size;
    block->texture = LoadTexutre(render, texture_path, &tex_size);
    if(block->texture == NULL){
        log_error("<CreateSysColliMapBlock>:create mapblock failed");
        FreeMapBlock(block);
        return NULL;
    }
    if(memcmp(&info.size, &DEFAULT_SIZE, sizeof(DEFAULT_SIZE))==0)
        info.size = tex_size;
    block->_basic_info = _createSysBasicMapBlockInfo(colli_type, &info);
    if(block->_basic_info == NULL){
        log_error("<CreateSysColliMapBlock>:create mapblock failed");
        FreeMapBlock(block);
        return NULL;
    }
    return block;
}

_basicMapBlockInfo* _createSysBasicMapBlockInfo(ColliType type, ObjectBasicInfo* obj_info){
    _basicMapBlockInfo* basicinfo = (_basicMapBlockInfo*)malloc(sizeof(_basicMapBlockInfo));
    if(basicinfo == NULL){
        log_error("create _basicMapBlockInfo failed");
        return NULL;
    }
    basicinfo->info = *obj_info;
    basicinfo->shape = CreateSysColliShape(obj_info->size, type);
    if(basicinfo->shape == NULL){
        _freeBasicMapBlockInfo(basicinfo);
        return NULL;
    }
    return basicinfo;
}

ColliShape* CreateSysColliShape(SDL_Size size, ColliType type){
    ColliShape* shape = (ColliShape*)malloc(sizeof(ColliShape));
    if(shape == NULL){
        log_error("Collishape create failed");
        return NULL;
    }
    shape->_colli_type = type;
    switch (type){
        case COLLI_RECTANGLE:
            shape->_data_num = 4;
            shape->_datas = (int*)malloc(sizeof(int)*4);
            shape->_datas[0] = 0;
            shape->_datas[1] = 0;
            shape->_datas[2] = size.w;
            shape->_datas[3] = size.h;
            break;
        case COLLI_TRIANGLE:
            shape->_data_num = 6;
            shape->_datas = (int*)malloc(sizeof(int)*6);
            shape->_datas[0] = 0;
            shape->_datas[1] = size.h;
            shape->_datas[2] = size.w;
            shape->_datas[3] = size.h;
            shape->_datas[4] = size.w/2;
            shape->_datas[5] = 0;
            break;
        case COLLI_CIRCLE:
            shape->_data_num = 3;
            shape->_datas = (int*)malloc(sizeof(int)*3);
            shape->_datas[0] = size.w/2;
            shape->_datas[1] = size.h/2;
            shape->_datas[2] = size.w/2;
            break;
        case COLLI_USER:
            log_error("CreateSysColliShape can't create user shape");
            Assert(false);
            break;
    }
    return shape;
}

MapBlock* CreateUserColliMapBlock(SDL_Renderer* render, char* texture_path, int colli_data[], int data_num, ObjectBasicInfo info){
    MapBlock* block = (MapBlock*)malloc(sizeof(MapBlock));
    if(block == NULL){
        log_error("<CreateSysColliMapBlock>:create mapblock failed");
        FreeMapBlock(block);
        return NULL;
    }
    SDL_Size tex_size;
    block->texture = LoadTexutre(render, texture_path, &tex_size);
    if(block->texture == NULL){
        log_error("<CreateSysColliMapBlock>:create mapblock failed");
        FreeMapBlock(block);
        return NULL;
    }
    if(memcmp(&info.size, &DEFAULT_SIZE, sizeof(DEFAULT_SIZE))==0)
        info.size = tex_size;
    block->_basic_info = _createUserBasicMapBlockInfo(colli_data, data_num, &info);
    if(block->_basic_info == NULL){
        log_error("<CreateSysColliMapBlock>:create mapblock failed");
        FreeMapBlock(block);
        return NULL;
    }
    return block;
}

_basicMapBlockInfo* _createUserBasicMapBlockInfo(int datas[], int data_num, ObjectBasicInfo* obj_info){
    _basicMapBlockInfo* basicinfo = (_basicMapBlockInfo*)malloc(sizeof(_basicMapBlockInfo));
    if(basicinfo == NULL){
        log_error("create _basicMapBlockInfo failed");
        return NULL;
    }
    basicinfo->info = *obj_info;
    basicinfo->shape = CreateUserColliShape(datas, data_num); 
    if(basicinfo->shape == NULL){
        _freeBasicMapBlockInfo(basicinfo);
        return NULL;
    }
    return basicinfo;
}

ColliShape* CreateUserColliShape(int datas[], int data_num){
    ColliShape* shape = (ColliShape*)malloc(sizeof(ColliShape));
    if(shape == NULL){
        log_error("Collishape create failed");
        return NULL;
    } 
    shape->_colli_type = COLLI_USER;
    shape->_data_num = data_num;
    shape->_datas = (int*)malloc(sizeof(int)*data_num);
    for(int i=0;i<data_num;i++)
        shape->_datas[i] = datas[i];
    return shape;
}

void FreeMapBlock(MapBlock* block){
    if(block->_basic_info)
        _freeBasicMapBlockInfo(block->_basic_info);
    block->_basic_info = NULL;
    free(block);
}

void FreeColliShape(ColliShape* shape){
    if(shape)
        free(shape->_datas);
    shape->_datas = NULL;
    free(shape);
}

void _freeBasicMapBlockInfo(_basicMapBlockInfo* basicinfo){
    if(basicinfo->shape)
        FreeColliShape(basicinfo->shape);
    basicinfo->shape = NULL;
    free(basicinfo);
}

SDL_Texture* LoadTexutre(SDL_Renderer* render, char* texture_path, SDL_Size* size){
    SDL_Surface* surface = IMG_Load(texture_path);
    if(surface == NULL){
        log_error("<LoadTexture>: image can't load");
        SDL_FreeSurface(surface);
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    if(texture == NULL){
        log_error("<LoadTexture>: texture can't create");
        SDL_FreeSurface(surface);
        return false;
    }
    if(size != NULL){
        size->w = surface->w;
        size->h = surface->h;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void DrawMapBlock(SDL_Renderer* render, MapBlock* block){
    SDL_Point p = GetMapBlockPosition(block);
    SDL_Size s = GetMapBlockSize(block);
    SDL_Rect dest = {p.x, p.y, s.w, s.h};
    SDL_RenderCopyEx(render, block->texture, NULL, &dest, GetMapBlockAngle(block), NULL, SDL_FLIP_NONE);
    if(RenderDebugMode){
        SDL_Color color = {0, 255, 0, 255};
        SDL_Point center = {dest.x+dest.w/2, dest.y+dest.h/2};
        DrawColliShape(render, GetMapBlockColliShape(block), GetMapBlockPosition(block), GetMapBlockAngle(block), &center, &color);
    }
}

void DrawColliShape(SDL_Renderer* render, ColliShape* shape, SDL_Point offset, double angle, SDL_Point* center, SDL_Color* color){
    SDL_SetRenderDrawColor(render, color->r, color->g, color->b, color->a);
    switch(GetColliType(shape)){
        case COLLI_RECTANGLE:{
            SDL_Rect rect = GetRectangleColliData(shape);
            rect.x += offset.x;
            rect.y += offset.y;
            SDL_RenderDrawRectEx(render, &rect, NULL, angle);
            break;
        }
        case COLLI_CIRCLE:{
            SDL_Circle circle = GetCircleColliData(shape);
            circle.center.x += offset.x;
            circle.center.y += offset.y;
            SDL_RenderDrawCircle(render, circle.center.x, circle.center.y, circle.r);
            break;
        }
        case COLLI_TRIANGLE:
        case COLLI_USER:{
            const int vertice_num= GetColliDataNum(shape)/2;
            SDL_Point points[vertice_num];
            GetUserColliData(shape, points);
            for(int i=0;i<vertice_num;i++){
                points[i].x += offset.x;
                points[i].y += offset.y;
                points[i] = RotatePoint(center, points[i], angle);
            }
            SDL_RenderDrawCloseLines(render, points, vertice_num);
            break;
        }
    }
}

ColliType GetColliType(ColliShape* shape){
    return shape->_colli_type;
}

ColliShape* GetMapBlockColliShape(MapBlock* block){
    return block->_basic_info->shape;
}

void SetMapBlockPosition(MapBlock* block, int x, int y){
    block->_basic_info->info.pos.x = x;
    block->_basic_info->info.pos.y = y;
}

void ResizeMapBlock(MapBlock* block, int w, int h){
    SDL_Size size = GetMapBlockSize(block);
    double scalex = w/(double)size.w,
            scaley = h/(double)size.h;
    SDL_Point center = GetMapBlockCenter(block);
    ColliShape* shape = GetMapBlockColliShape(block);
    SDL_Point lt = {center.x-w/2, center.y-h/2};
    block->_basic_info->info.pos.x = center.x-w/2;
    block->_basic_info->info.pos.y = center.y-h/2;
    block->_basic_info->info.size.w = w;
    block->_basic_info->info.size.h = h;
    switch (GetColliType(shape)){
        case COLLI_CIRCLE:
            shape->_datas[0] = w/2;
            shape->_datas[1] = h/2;
            shape->_datas[2] *= scalex;
            break;
        case COLLI_RECTANGLE:
            shape->_datas[2] = w;
            shape->_datas[3] = h;
            break;
        case COLLI_TRIANGLE:
        case COLLI_USER:
            for(int i=0;i<GetColliDataNum(shape)/2;i++){
                shape->_datas[i*2] = (shape->_datas[i*2]-size.w/2)*scalex + w/2;
                shape->_datas[i*2+1] = (shape->_datas[i*2+1]-size.h/2)*scaley + h/2;
            } 
    }
}

SDL_Point GetMapBlockCenter(MapBlock* block){
    SDL_Point lt = GetMapBlockPosition(block);
    SDL_Size size = GetMapBlockSize(block);
    SDL_Point center = {lt.x+size.w/2, lt.y+size.h/2};
    return center;
}

void GetUserColliData(ColliShape* shape, SDL_Point ret_data[]){
    for(int i=0;i<GetColliDataNum(shape)/2;i++){
        ret_data[i].x = shape->_datas[i*2];
        ret_data[i].y = shape->_datas[i*2+1];
    }
}

unsigned int GetColliDataNum(ColliShape* shape){
    return shape->_data_num;
}

SDL_Rect GetRectangleColliData(ColliShape* shape){
    SDL_Rect ret = {shape->_datas[0], shape->_datas[1], shape->_datas[2] - shape->_datas[0], shape->_datas[3]-shape->_datas[1]};
    return ret;
}

SDL_Point GetMapBlockPosition(MapBlock* block){
    return block->_basic_info->info.pos;
}

SDL_Size GetMapBlockSize(MapBlock* block){
    return block->_basic_info->info.size;
}

void RotateMapBlock(MapBlock* block, double angle){
    block->_basic_info->info.angle = angle;
}

double GetMapBlockAngle(MapBlock* block){
    return block->_basic_info->info.angle;
}

void GetTriangleColliData(ColliShape* shape, SDL_Point ret_data[]){
    for(int i=0;i<3;i++){
        ret_data[i].x = shape->_datas[i*2];
        ret_data[i].y = shape->_datas[i*2+1];
    }
}

SDL_Circle GetCircleColliData(ColliShape* shape){
    SDL_Circle circle = {
        {shape->_datas[0], shape->_datas[1]},
        shape->_datas[2]
    };
    return circle;
}

void Points2IntArray(SDL_Point points[], int point_num, int ret_arrya[]){
    for(int i=0;i<point_num;i++){
        ret_arrya[i*2] = points[i].x;
        ret_arrya[i*2+1] = points[i].y;
    }
}

void Rect2IntArray(SDL_Rect rect, int ret_arrya[]){
    ret_arrya[0] = rect.x;
    ret_arrya[1] = rect.y;
    ret_arrya[2] = rect.x+rect.w;
    ret_arrya[3] = rect.y+rect.h;
}

void Circle2IntArray(SDL_Circle circle, int ret_arrya[]){
    ret_arrya[0] = circle.center.x;
    ret_arrya[1] = circle.center.y;
    ret_arrya[2] = circle.r;
}