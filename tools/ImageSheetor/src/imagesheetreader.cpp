//
// Created by 桂明谦 on 2020/1/1.
//

#include "ImageSheetor/imagesheetreader.hpp"

ImageSheetReader::ImageSheetReader(string filename){
    Parse(std::move(filename));
}

void ImageSheetReader::Parse(string filename){
    string content = readIn(std::move(filename));
    parse2Sheet(content);
}

string ImageSheetReader::readIn(const string filename){
    ifstream file(filename);
    if(file.fail()){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "no such file:%s", filename.c_str());
        return "";
    }
    string content;
    string line;
    while((file>>line)){
        content += line;
    }
    return content;
}

void ImageSheetReader::parse2Sheet(const string& json_content){
    Json::CharReaderBuilder crb;
    Json::CharReader* cr = crb.newCharReader();
    JSONCPP_STRING error;
    Json::Value root;
    cr->parse(&json_content.c_str()[0], &json_content.c_str()[json_content.size()-1], &root, &error);

    if(!root.isMember("image_path")){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "no field `%s`, please check your json file", "image_path");
        return;
    }
    string image_path = root["image_path"].asString();
    SDL_Surface* bigimage = IMG_Load(image_path.c_str());
    bigimage = SDL_ConvertSurfaceFormat(bigimage, SDL_PIXELFORMAT_RGBA8888, 0);
    if(bigimage==nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "the image %s not found", image_path.c_str());
        return;
    }
    if(!root.isMember("images")){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "no field `%s`, please check your json file", "images");
        return;
    }
    Json::Value images = root["images"];
    vector<ImageSheet::Image> s;
    for(int i=0;i<images.size();i++){
        Json::Value image_info = images[i];
        if(!image_info.isMember("rect")){
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "no field `%s`, please check your json file", "images[\"rect\"]");
            break;
        }
        Json::Value image_rect = image_info["rect"];
        SDL_Rect rect = {image_rect["x"].asInt(), image_rect["y"].asInt(), image_rect["width"].asInt(), image_rect["height"].asInt()};
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
        SDL_BlitSurface(bigimage, &rect, surface, nullptr);
        ImageSheet::Image image(image_info["name"].asString(), surface, rect);
        s.push_back(image);
    }
    sheet.SetContent(s);
}

const ImageSheet& ImageSheetReader::GetSheet(){
    return sheet;
}
