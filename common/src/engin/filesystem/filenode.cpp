//
// Created by 桂明谦 on 2020/1/21.
//

#include "engin/filesystem/filenode.hpp"

using namespace FileSystem;

FileNode::FileNode(string path):failed(false) {
    this->path = std::move(path);
    struct stat s;
    if(lstat(path.c_str(), &s) == -1)
        failed = true;
    if(S_ISDIR(s.st_mode))
        type = Type::DIRECTORY;
    else if(S_ISREG(s.st_mode)||S_ISLNK(s.st_mode))
        type = Type::FILE;
    else
        type = Type::UNKNOWN;
}

string FileNode::GetName() const {
    auto pos = filename.find_last_of("/");
    if(pos == filename.npos)
        name = std::move(path);
    name = std::move(path.substr(pos));
}

string FileNode::GetAbsolutePath() const {
}

string FileNode::GetRelativePath() const {
    return path;
}
