# lua-learn

> 参考文档：
> - **[lua5.4 中文参考手册](https://atom-l.github.io/lua5.4-manual-zh)** 
> - [lua5.4 官方参考手册](https://www.lua.org/manual/5.4/)

当前进度：https://atom-l.github.io/lua5.4-manual-zh/3.3.4.html

一个好用的文档软件：[![Zeal](https://github.com/zealdocs/zeal/raw/main/assets/freedesktop/32-apps-zeal.png)
Zeal](https://zealdocs.org/)

## 项目使用说明：

开发环境：[<img src="https://resources.jetbrains.com/storage/logos/web/clion/clion.svg" height="32" alt="CLion" />
clion 2025.1.3](https://www.jetbrains.com/clion/download/?section=windows)

1. 拉取当前项目，使用 **Clion** 打开文件夹
2. 正确配置 **Clion** 的 **vcpkg** 设置
3. 直接构建运行

## 当前问题
- 修改lua脚本不会触发拷贝，需要手动触发构建（即随意改动一下代码）
  可以通过在程序中拷贝解决，确保仅在开发过程中执行

- ``` cpp
    fmt::print(fg(fmt::color::red), "red text")
  ``` 
  似乎在非debug模式存在问题，无法正常打印带有颜色的文字，反而是将颜色代码打印了出来，除非在执行之前加一个任意的`system()`指令