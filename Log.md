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

**VisualGMQ**:

* 改变cmake配置使用c99标准编译
* 增加了SDL_FontCache库的使用，并且在main.c里面利用此库绘制了文字
* 增加了Fangsong.ttf字体资源
* 增加了Licenses文件夹用于保存使用的库的开源协议

**2019.9.22**

**VisualGMQ**

* 改变了工程的结构，将一些所有文件基本都要用到的文件和资源放在了common文件夹下，并且增加了对common文件夹的cmake配置
* 开始编写地图编辑器

**2019.9.22**

**VisualGMQ**

* 在地图编辑器中编写了一些UI框架，其中编写了Button和Image两个Widgets，并且进行了单元测试，未测试完全。

**2019.9.30**

**VisualGMQ**

* 编写了mmath数学库，写了一些向量相关的函数。
* 开始尝试写粒子系统

**2019.10.2**

**VisualGMQ**

* 完成了粒子系统，但是如果粒子数很多的话会造成卡顿。需要后期优化。

**2019.10.18**

**VisualGMQ**

* 增加了MapBlock文件，geomentry.h文件。

**2019.12.30**

* 将工程改为C++工程，去除日志库该用spdlog库，不再使用unittest库采用catch2库进行单元测试
* 去除了LinkList链表文件
* 去除了Tiled文件

**2020.1.1**

* 增加了工具ImageSheetor