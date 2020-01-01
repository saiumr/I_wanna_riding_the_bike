# ImageSheetor小工具

## 简介

这个工具可以将你想要的图片拼接成大图片，并且会生成一个描述大图片的Json文件。比如:  

```json
{
	"image1" : 
	{
		"name" : "image1",
		"rect" : 
		{
			"height" : 200,
			"width" : 100,
			"x" : 0,
			"y" : 0
		}
	},
	"image2" : 
	{
		"name" : "image2",
		"rect" : 
		{
			"height" : 300,
			"width" : 100,
			"x" : 1,
			"y" : 0
		}
	},
}
```

而你可以通过使用ImageSheetReader库来将图片读取。

## 使用方法

打开这个软件之后，将图片拖拽进窗口即可，软件会自动帮助你排列。
再按下`enter`键就可以在软件目录下生成`result.json`和`result.png`

## 相关的库

我们还提供了`ImageSheetReader`库（如果你编译好了源代码应该可以在`lib`下看到这个库）  
使用的方法写在`include/imagesheetreader.hpp`中了