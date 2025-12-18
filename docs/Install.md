# How to Run or Dev this project

> 请保证严格按照文档步骤进行，部分因 **平台差异和编译器差异** 导致的命令不尽相同，可以询问大模型得到合适的意见

Use CMake to build enviroment

```bash
mkdir build
cd build
cmake ..
```
> 如果这里 cmake .. 出现问题，请检查一下编译器是否为 MinGW 或 MSVC，使用 vscode / visual studio 的编译器一般为上述两者之一
如果构建失败
1. 请检查一下编译器是否为 MinGW 或 MSVC（使用 vscode / visual studio 的编译器一般为上述两者之一）
2. 解决问题以后，使用如下指令重新进行

```bash
cd ..
rm -r build
mkdir build
cd build
cmake .. -G "$<你的编译器>"
```

Compile

```bash
cmake --build .
```

Check whether the environment is available

点击 test/enviroment.cpp，使用 `ctrl + shift + B` 运行代码
正常运行结果的截图如下：
[](/docs/attachment/run_enviroment.png)
