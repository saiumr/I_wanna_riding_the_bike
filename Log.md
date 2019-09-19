**2019.9.18**

**VisualGMQ**:

* 增加了工程的大体框架
* 编写了unittest.h单元测试系统
* 编写了log.h日志系统
* 完成了用于测试的游戏主体文件main.c
* unittest.h单元测试系统测试完毕，确认无误
* log.h日志系统已经通过单元测试完毕，确认无误

**saiumr**:
* 增加了cmake工程在windows下的编译功能，解决了在windows下发现不了SDL2的错误

**2019.9.19**:

**VisualGMQ**:

* 增加了在Windows下cmake自动复制SDL2.dll文件到需要的exe文件目录下（没有在Windows下测试）
* 增加了log.h日志系统的一些功能，让测试程序在Windows下运行不会闪退。
* 控制了帧率在60FPS左右
* 增加了cmake中找到SDL2_image库的方法
* 增加了resources文件夹用于存放资源
* 在屏幕上绘制了一些kid...
**2019.9.20**

**saiumr**:

* 增加了Windows下找到SDL2_image库的cmake文件。可以编译成可执行文件，但是没有办法运行...
