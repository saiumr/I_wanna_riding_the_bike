//
// Created by 桂明谦 on 2020/1/10.
//

#ifndef I_WANNA_RIDING_THE_BIKE_GUIEXCEPTION_HPP
#define I_WANNA_RIDING_THE_BIKE_GUIEXCEPTION_HPP

#include <exception>
#include <string>
using namespace std;

namespace GUI {

    class GUIException : public bad_exception {
    public:
        GUIException(string msg);
        const char *what() const noexcept override;
    private:
        string message;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_GUIEXCEPTION_HPP
