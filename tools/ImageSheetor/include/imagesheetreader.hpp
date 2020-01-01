//
// Created by 桂明谦 on 2020/1/1.
//
/**
 * 这个文件用来读取使用ImageSheetor产生的大文件的。
 *
 * 使用方法：
 * * 在你的代码中包含这个头文件，并且链接libImageSheetReader.a库
 * * 你可以直接使用构造函数，或者在构造之后使用`Parse()`函数来解析一个大文件:
 *  `ImageSheetReader("result") 或 reader.Parse("result")`
 *  注意不需要给出后缀
 * * 然后可以使用`GetSheet()`函数获得解析后的`ImageSheet`对象。
 * * `ImageSheet`对象有一些方法可以获得图片和图片在总图片中的位置，详情请看`ImageSheet.hpp`类的声明
 */

#ifndef I_WANNA_RIDING_THE_BIKE_IMAGESHEETREADER_HPP
#define I_WANNA_RIDING_THE_BIKE_IMAGESHEETREADER_HPP

#include "imagesheet.hpp"
#include "SDL_image.h"
#include "json/json.h"
#include <string>
#include <fstream>
#include <utility>
using namespace std;

class ImageSheetReader {
public:
    ImageSheetReader() = default;
    explicit ImageSheetReader(string filename);
    void Parse(string filename);
    const ImageSheet& GetSheet();
private:
    string readIn(string filename);
    void parse2Sheet(const string& json_content);
    ImageSheet sheet;
};


#endif //I_WANNA_RIDING_THE_BIKE_IMAGESHEETREADER_HPP
