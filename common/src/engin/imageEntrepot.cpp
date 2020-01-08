//
// Created by 桂明谦 on 2019/12/18.
//

#include "engin/imageEntrepot.hpp"

map<string, SDL_Texture*> ImageEntrepot::images = map<string, SDL_Texture*>();

void ImageEntrepot::LoadImage(const string& filename){
    string image_name = GetFilenameWithoutSuffix(filename);
    auto it = images.find(image_name);
    if(it!=images.end())
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "%s is exists", image_name.c_str());
    else{
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(surface==nullptr){
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s load failed", filename.c_str());
            return ;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Director::GetDirector()->GetRender(), surface);
        SDL_FreeSurface(surface);
        if(texture==nullptr){
            SDL_DestroyTexture(texture);
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "texture can't create");
            return;
        }
        SDL_DestroyTexture(it->second);
        images[image_name] = texture;
    }
}

void ImageEntrepot::LoadImageStrict(string filename){
    string image_name = GetFilenameWithoutSuffix(filename);
    auto it = images.find(image_name);
    if(it!=images.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s is exists", image_name.c_str());
        return;
    }else{
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(surface==nullptr){
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s load failed", filename.c_str());
            return ;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Director::GetDirector()->GetRender(), surface);
        SDL_FreeSurface(surface);
        if(texture==nullptr){
            SDL_DestroyTexture(texture);
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "texture can't create");
            return;
        }
        SDL_DestroyTexture(it->second);
        images[image_name] = texture;
    }
}

void ImageEntrepot::LoadTexture(string name, SDL_Texture* texture){
    if(texture==nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "texture is nullptr");
        return;
    }
    images[name] = texture;
}

void ImageEntrepot::DeleteImage(string name){
    auto it = images.find(name);
    if(it!=images.end()) {
        SDL_DestroyTexture(it->second);
        images.erase(it);
    }
}

SDL_Texture* ImageEntrepot::GetImage(string name){
    auto it = images.find(name);
    if(it==images.end()){
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "%s is not in entrepot", name.c_str());
        return nullptr;
    }
    return it->second;
}

void ImageEntrepot::PrintContent(){
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "ImageEntrepot's content:");
    for(auto i : images){
        cout<<i.first<<endl;
    }
}

void ImageEntrepot::Clear(){
    for(auto i: images){
        SDL_DestroyTexture(i.second);
    }
    images.clear();
}

string GetFilenameWithoutSuffix(const string& filename){
    size_t pos = filename.find_last_of('/');
    string substring;
    if(pos != filename.npos)
        substring = filename.substr(pos+1);
    else
        substring = filename;
    size_t final_pos = substring.find_first_of('.');
    if(final_pos == substring.npos)
        return substring;
    return substring.substr(0, final_pos);
}

string GetFilename(const string& filename){
    auto pos = filename.find_last_of(Director::PathSplitSymbol);
    return filename.substr(pos+1);
}

FileType GetFileType(const string& filename){
    auto pos = filename.find_last_of('.');
    if(pos==filename.npos)
        return FILE_TYPE_UNRECOGNIZE;
    string suffix = filename.substr(pos);
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
    if(suffix==".png" || suffix==".bmp" || suffix==".jpg" || suffix==".jpeg" || suffix==".gif")
        return FILE_TYPE_IMAGE;
    if(suffix==".json")
        return FILE_TYPE_JSON;
    if(suffix==".txt")
        return FILE_TYPE_TXT;
    return FILE_TYPE_UNRECOGNIZE;
}

string GetBaseName(const string& filename){
    int pos = filename.find_last_of(Director::PathSplitSymbol);
    if(pos == filename.npos)
        return "";
    return filename.substr(0, pos);
}
