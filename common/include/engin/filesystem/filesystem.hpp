//
// Created by 桂明谦 on 2020/1/21.
//

#ifndef I_WANNA_RIDING_THE_BIKE_FILESYSTEM_HPP
#define I_WANNA_RIDING_THE_BIKE_FILESYSTEM_HPP

#include "filenode.hpp
#include <vector>
using namespace std;

namespace FileSystem {

    /**
     * 表示一个路径下所有文件的文件系统
     */
    class FileSystem {
    public:
        /**
         * 功能同Open()（在构造函数里面调用Open)
         * @param path
         */
        FileSystem(string path);
        /**
         * 通过给入一个路径来得到路径下文件和文件夹的信息
         * @param path
         */
        void Open(string path):
        vector<FileNode> GetNodes() const;
        /**
         * 路径不存在返回false,存在返回true
         * @return
         */
        bool Failed() const;
    private:
        vector<FileNode> nodes;
    };

};


#endif //I_WANNA_RIDING_THE_BIKE_FILESYSTEM_HPP
