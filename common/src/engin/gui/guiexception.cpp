//
// Created by 桂明谦 on 2020/1/10.
//

#include "engin/gui/guiexception.hpp"

using namespace GUI;

GUIException::GUIException(string msg):bad_exception(),message(std::move(msg)){
}

const char* GUIException::what() const noexcept{
    return message.c_str();
}
