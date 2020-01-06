//
// Created by 桂明谦 on 2019/12/31.
//
/**
 * 这个程序还存在以下的问题：
 * * 不能够通过Json文件读取图片
 * * 不能够指定输出的地点和图片，只能够按下enter键导出到这个程序运行的目录，并且命名为test
 * * 程序只会将图片从左向右排列，人工不能干涉，也不能删除图片
 */

//TODO 这里我希望可以将图片移动并且自动吸附到大图的边缘（可以使用碰撞检测来完成）
//FIXME 这里可以优化，不使用TextureManager而是首先将Image::image全部绘制在Surface上，再将surface转化Texture绘制

#ifndef I_WANNA_RIDING_THE_BIKE_MAIN_HPP
#define I_WANNA_RIDING_THE_BIKE_MAIN_HPP

#include "app.hpp"
#include "imagesheetreader.hpp"
#include "imagesheetwriter.hpp"
#include "texturemanager.hpp"
#include "engin/collisionapproch.hpp"
#include <map>
using namespace std;

string GetNameFromFile(const string& filename);

class ImageSheetor:public App{
public:
    static const int Padding;
    static const int Error_Index;
    ImageSheetor();
    void EventHandle(SDL_Event& event) override;
    void Resize();
    void Update() override;
    ~ImageSheetor();
private:
    SDL_Point findBoarder();
    void handleSelectedImage();
    void handleImageMovement();
    void relayout();
    void deleteImage();
    bool idx_valid();
    void saveSheet();
    int image_idx;
    int moving_idx;
    vector<ImageSheet::Image> images;
    TextureManager textureManager;
    bool oldleftbutton;
};

#endif //I_WANNA_RIDING_THE_BIKE_MAIN_HPP
