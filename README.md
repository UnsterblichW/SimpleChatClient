# 仿微信界面的全栈聊天项目

## 项目简介
客户端使用QT5模仿微信界面，实现添加好友，好友聊天等功能，客户端和服务端之间通过短链接http或长连接tcp进行通信，服务端采用了分布式的设计

## 项目平台
1. 客户端：Qt 5.12.2 ，构建文件使用qmake，构建套件使用 Desktop Qt 5.15.2 MinGW 32-bit / Desktop Qt 5.15.2 MinGW 64-bit （编译器为MINGW 8.1.0），C++ 11
2. 服务端：Visual Studio 2022，使用sln项目构建，平台工具集 Visual Studio 2022(v143)，C++语言标准 std:C++17
