//
// Created by 桂明谦 on 2020/1/2.
//

#ifndef I_WANNA_RIDING_THE_BIKE_TEXTUREMANAGER_HPP
#define I_WANNA_RIDING_THE_BIKE_TEXTUREMANAGER_HPP

#include "imagesheet.hpp"
#include <vector>
using namespace std;

class TextureManager {
public:
    struct TextureInfo{
        SDL_Texture* texture;
    };
    TextureManager() = default;
    TextureManager(SDL_Renderer* render, vector<ImageSheet::Image> images);
    void AddTexture(SDL_Renderer* render, ImageSheet::Image& image);
    void AddTexture(SDL_Texture* texture);
    void DeleteTexture(int idx);
    bool Idx_Valid(int idx);
    SDL_Texture* operator[](const int idx) const;
    ~TextureManager();
private:
    vector<TextureInfo> textures;
};


#endif //I_WANNA_RIDING_THE_BIKE_TEXTUREMANAGER_HPP
