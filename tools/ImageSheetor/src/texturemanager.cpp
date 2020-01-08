//
// Created by 桂明谦 on 2020/1/2.
//

#include "ImageSheetor/texturemanager.hpp"

TextureManager::TextureManager(SDL_Renderer* render, vector<ImageSheet::Image> images){
    for(auto& image : images){
        AddTexture(render, image);
    }
}

void TextureManager::AddTexture(SDL_Renderer* render, ImageSheet::Image& image){
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, image.GetImage());
    if(texture==nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "texture create failed");
    }else{
        TextureInfo info = {texture};
        textures.push_back(info);
    }
}

void TextureManager::AddTexture(SDL_Texture* texture){
    if(texture==nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "texture can't be nullptr");
    }else{
        TextureInfo info = {texture};
        textures.push_back(info);
    }
}

void TextureManager::DeleteTexture(int idx){
    if(Idx_Valid(idx)) {
        auto it = textures.begin() + idx;
        SDL_DestroyTexture(it->texture);
        textures.erase(it);
    }
}

bool TextureManager::Idx_Valid(const int idx){
    return idx>=0 && idx<textures.size();
}

SDL_Texture* TextureManager::operator[](const int idx) const{
    return textures[idx].texture;
}

TextureManager::~TextureManager(){
    for(auto& texture: textures)
        SDL_DestroyTexture(texture.texture);
}
