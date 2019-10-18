#include "MapBlock.h"

bool _InitBasicMapBlockInfo(SDL_Renderer* render, char* texture_path, MapBlock* block, SDL_Size size, SDL_Point pos){
    SDL_Surface* surface = IMG_Load(texture_path);
    if(surface == NULL){
        log_error("<CreateSysColliMapBlock>: image can't load");
        block->texture = NULL;
        SDL_FreeSurface(surface);
        return false;
    }
    block->texture = SDL_CreateTextureFromSurface(render, surface);
    if(block->texture == NULL){
        log_error("<CreateSysColliMapBlock>: texture can't create");
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(block->texture);
        block->texture = NULL;
        return false;
    }
    block->pos = pos;
    if(size.w == DEFAULT_SIZE.w && size.h == DEFAULT_SIZE.h){
        block->size.w = surface->w;
        block->size.h = surface->h;
    }else
        block->size = size;
    SDL_FreeSurface(surface);
    return true;
}

MapBlock CreateSysColliMapBlock(SDL_Renderer* render, char* texture_path, ColliType colli_type, SDL_Size size, SDL_Point pos){
    MapBlock block;
    if(!_InitBasicMapBlockInfo(render, texture_path, &block, size, pos))
        return ERROR_MAPBLOCK;
    block.shape._colli_type = colli_type;
    switch(colli_type){
        case COLLI_RECTANGLE:
            block.shape._data_num = 4;
            block.shape._datas[0] = 0;
            block.shape._datas[1] = 0;
            block.shape._datas[2] = block.size.w;
            block.shape._datas[3] = block.size.h;
            break;
        case COLLI_TRIANGLE:
            block.shape._data_num = 6;
            block.shape._datas[0] = 0;
            block.shape._datas[1] = block.size.h;
            block.shape._datas[2] = block.size.w/2;
            block.shape._datas[3] = 0;
            block.shape._datas[4] = block.size.w;
            block.shape._datas[5] = block.size.h;
            break;
        case COLLI_CIRCLE:
            block.shape._data_num = 3;
            block.shape._datas[0] = block.pos.x/2;
            block.shape._datas[1] = block.pos.y/2;
            block.shape._datas[2] = block.size.w/2;
            break;
        case COLLI_USER:
            log_error("system collision shape can't be \"COLLI_USER\"");
            Assert(false);
            break;
    }
    return block;
}

MapBlock CreateUserColliMapBlock(SDL_Renderer* render, char* texture_path, SDL_Point vertices[], unsigned int len,  SDL_Size size, SDL_Point pos){
    MapBlock block;
    if(!_InitBasicMapBlockInfo(render, texture_path, &block, size, pos))
        return ERROR_MAPBLOCK;
    block.shape._data_num = len;
    block.shape._colli_type = COLLI_USER;
    block.shape._datas = (int*)malloc(sizeof(int)*len*2);
    for(int i=0;i<len;i++){
        block.shape._datas[i*2] = vertices[i].x;
        block.shape._datas[i*2+1] = vertices[i].y;
    }
    return block;
}

MapBlock CreateColliMapBlockByTemplate(SDL_Renderer* render, char* texture_path, ColliType colli_type, int colli_data[], SDL_Size size, SDL_Point pos){
    MapBlock block;
    if(!_InitBasicMapBlockInfo(render, texture_path, &block, size, pos))
        return ERROR_MAPBLOCK;
    block.shape._colli_type = COLLI_USER;
    switch(block.shape._colli_type){
        case COLLI_RECTANGLE:
            block.shape._data_num = 4;
            break;
        case COLLI_TRIANGLE:
            block.shape._data_num = 6;
            break;
        case COLLI_CIRCLE:
            block.shape._data_num = 3;
            break;
        default:
            log_error("template collision shape must be COLLI_RECTANLE, COLLI_TRIANGLE, COLLI_CIRCLE");
            Assert(false);
    }
    for(int i=0;i<block.shape._data_num;i++)
        block.shape._datas[i] = colli_data[i];
    return block;
}

ColliType GetColliType(ColliShape* shape){
    return shape->_colli_type;
}

ColliShape GetColliShape(MapBlock* block){
    return block->shape;
}

unsigned int GetColliDataNum(ColliShape* shape){
    return shape->_data_num;
}

void GetUserColliData(ColliShape* shape, SDL_Point ret_data[]){
    for(int i=0;i<GetColliDataNum(shape)/2;i+=2){
        ret_data[i].x = shape->_datas[i];
        ret_data[i].y = shape->_datas[i+1];
    }
}

SDL_Rect GetRectangleColliData(ColliShape* shape){
    SDL_Rect ret = {shape->_datas[0], shape->_datas[1], shape->_datas[2] - shape->_datas[0], shape->_datas[3]-shape->_datas[1]};
    return ret;
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