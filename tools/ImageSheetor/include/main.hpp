//
// Created by 桂明谦 on 2019/12/31.
//
/**
 * 这个程序还存在以下的问题：
 * * 不能够通过Json文件读取图片
 * * 不能够指定输出的地点和图片，只能够按下enter键导出到这个程序运行的目录，并且命名为test
 * * 程序只会将图片从左向右排列，人工不能干涉，也不能删除图片
 */

#ifndef I_WANNA_RIDING_THE_BIKE_MAIN_HPP
#define I_WANNA_RIDING_THE_BIKE_MAIN_HPP

#include "app.hpp"
#include "imagesheetreader.hpp"
#include "imagesheetwriter.hpp"

string GetNameFromFile(const string& filename);

class ImageSheetor:public App{
public:
    static const int Padding;
    ImageSheetor();
    void EventHandle(SDL_Event& event) override;
    void Resize();
    void Update() override;
    ~ImageSheetor();
private:
    vector<ImageSheet::Image> images;
};

#endif //I_WANNA_RIDING_THE_BIKE_MAIN_HPP
