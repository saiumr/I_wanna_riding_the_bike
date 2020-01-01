//
// Created by 桂明谦 on 2020/1/1.
//

#include "imagesheetwriter.hpp"

#include <utility>

void ImageSheetWriter::AddImage(string name, SDL_Surface* surface, SDL_Rect rect){
    sheet.push_back(ImageSheet::Image(std::move(name), surface, rect));
}

ImageSheetWriter::ImageSheetWriter(vector<ImageSheet::Image> s){
    SetContent(s);
}

void ImageSheetWriter::SetContent(vector<ImageSheet::Image> s){
    sheet = s;
}

void ImageSheetWriter::DeleteImage(const int idx){
    auto it = sheet.cbegin()+idx;
    sheet.erase(it);
}

void ImageSheetWriter::DeleteImage(const string name){
    for(auto it=sheet.begin();it!=sheet.end();it++)
        if(it->GetName() == name)
            sheet.erase(it);
}

void ImageSheetWriter::Write2File(const string filename){
    writeImage(filename + ".png");
    writeJson(filename + ".json", filename + ".png");
}

void ImageSheetWriter::writeImage(string filename){
    if(sheet.empty()){
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "sheet has no image");
        return;
    }
    SDL_Point boarder = FindMaxBorder();
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, boarder.x, boarder.y, 32, SDL_PIXELFORMAT_RGBA8888);
    if(surface==nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "can't write to PNG image");
        return;
    }
    SDL_Rect surface_rect = {0, 0, surface->w, surface->h};
    SDL_FillRect(surface, &surface_rect, SDL_MapRGB(surface->format, 255, 255, 255));
    for(int i=0;i<sheet.size();i++) {
        SDL_Surface* converted_surface = SDL_ConvertSurfaceFormat(sheet[i].GetImage(), SDL_PIXELFORMAT_RGBA8888, 0);
        SDL_Rect rect = sheet[i].GetRect();
        SDL_BlitSurface(converted_surface, nullptr, surface, &rect);
    }
    IMG_SavePNG(surface, filename.c_str());
    SDL_FreeSurface(surface);
}

SDL_Point ImageSheetWriter::FindMaxBorder(){
    int max_width = 0;
    int max_height = 0;
    for(int i=0;i<sheet.size();i++){
        max_width = SDL_max(sheet[i].GetRect().w+sheet[i].GetRect().x, max_width);
        max_height = SDL_max(sheet[i].GetRect().h+sheet[i].GetRect().y, max_height);
    }
    return {max_width, max_height};
}

void ImageSheetWriter::writeJson(string filename, string image_name){
    Json::Value root;
    root["image_path"] = image_name;
    Json::Value pics;
    for(int i=0;i<sheet.size();i++){
        ImageSheet::Image image = sheet[i];
        Json::Value image_value;
        image_value["name"] = image.GetName();
        Json::Value rect_value;
        SDL_Rect image_rect = image.GetRect();
        rect_value["x"] = image_rect.x;
        rect_value["y"] = image_rect.y;
        rect_value["width"] = image_rect.w;
        rect_value["height"] = image_rect.h;
        image_value["rect"] = rect_value;
        pics.append(image_value);
    }
    root["images"] = pics;
    Json::StreamWriterBuilder swb;
    Json::writeString(swb, root);
    Json::StreamWriter* sw = swb.newStreamWriter();
    ofstream file(filename);
    sw->write(root, &file);
    file.close();
}
