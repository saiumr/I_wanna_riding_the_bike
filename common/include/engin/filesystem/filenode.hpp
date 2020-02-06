//
// Created by 桂明谦 on 2020/1/21.
//

#ifndef I_WANNA_RIDING_THE_BIKE_FILENODE_HPP
#define I_WANNA_RIDING_THE_BIKE_FILENODE_HPP
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

namespace FileSystem{

    /**
     * 用于表示文件和文件夹的抽象数据类型
     */
    class FileNode {
    public:
        /**
         * 文件节点的类型
         */
        enum class Type{
            FILE,       /** 文件*/
            DIRECTORY,  /** 文件夹*/
            UNKNOWN     /** 不知道的文件（管道，套接字文件等）*/
        };
        /**
         * 构造函数，以给入任意的路径path来得到一个FileNode
         * @param path
         */
        FileNode(string path);
        /**
         * 获得文件名称
         * @return 文件名称
         */
        string GetName() const;
        /**
         * 获得这个文件节点的绝对路径
         * @return 文件节点的绝对路径
         */
        string GetAbsolutePath() const;
        /**
         * 获得这个文件节点的相对路径
         * @return 文件节点的相对路径
         */
        string GetRelativePath() const;
        /**
         * 获得这个文件节点的类型
         * @return 文件节点的类型
         */
        Type GetType() const;
    private:
        Type type;
        string path;
        bool failed;
    };

};

/**
 * 用于输出的重载运算符，让FileNode对象可以直接以`cout<<node`的形式输出文件节点名称和文件节点类型
 * @param o
 * @param node
 * @return
 */
ostream& operator<<(ostream& o, FileSystem::FileNode& node);

#endif //I_WANNA_RIDING_THE_BIKE_FILENODE_HPP
