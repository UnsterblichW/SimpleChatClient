# 仿微信界面的全栈聊天项目

## 项目简介
本项目仅仅用于个人学习提升。客户端使用QT5模仿微信界面，实现添加好友，好友聊天等功能，客户端和服务端之间通过短链接http或长连接tcp进行通信，服务端采用了分布式的设计

服务端仓库地址 https://github.com/UnsterblichW/SimpleChatServer


## 项目平台
1. 客户端：Qt 5.12.2 ，构建文件使用qmake，构建套件使用 Desktop Qt 5.15.2 MinGW 32-bit / Desktop Qt 5.15.2 MinGW 64-bit （编译器为MINGW 8.1.0），C++ 11
2. 服务端：Visual Studio 2022，使用sln项目构建，平台工具集 Visual Studio 2022(v143)，C++语言标准 std:C++17


## 项目所用技术
1. 客户端界面的实现中大量运用到Qt的信号槽机制，元对象机制，使用MVC的设计思想来实现聊天对话框等需要展现数据的界面，使用QSS来美化界面。支持添加好友，展示好友列表，好友之间聊天，查看好友信息等功能；
2. 后端采用分布式设计，分为GateServer网关服务，多个ChatServer聊天服务，StatusServer状态服务以及VerifyServer验证服务；
3. 核心框架采用boost库提供的asio进行封装，采用多线程模式封装iocontext池提升并发性能；
4. 服务端的实现引入了多种广泛使用的开源库，利用gRPC在各个职责的服务器之间通信，利用mysqlconnector连接mysql数据库对用户数据进行持久化处理，利用hiredis连接redis作为缓存数据来提升服务端性能；
5. 在本项目中大量使用了池化设计，实现了数据库连接池，grpc连接池，iocontext连接池，充分利用现代CPU的多核优势；


## 项目架构
本项目的服务端为分布式架构，主要分为以下几个角色：
1. GateServer: 网关服务器，和每个客户端交互的第一站，使用boost::beast库实现http解析和响应，将会使用http短连接和客户端通信，处理客户端发出的注册、登录、重置密码、获取验证码的请求；
2. VerifyServer: 验证码服务器，使用js实现，利用qq邮箱的stmp服务给客户端用户注册的邮箱发验证码邮件，获取验证码的过程中会向redis中写入限制了ttl的键值对，从而保证验证码的有效期；
4. StatusServer: 状态服务器，记录了每个ChatServer的位置，同时会在每一个用户发生登录操作的时候，给每个用户生成一个唯一的token。StatusServer还会查询每个ChatServer的负载情况，每当用户登录时，分配到压力最小的ChatServer；
5. ChatServer: 聊天服务器，客户端获得了ChatServer的位置之后，会之间和某一个ChatServer建立tcp长连接，[消息格式定义在这](https://github.com/UnsterblichW/SimpleChatServer/blob/master/ChatServer/ChatServer/MsgNode.h)，如果聊天的双方在同一个ChatServer，那么将直接由ChatServer转发消息，如果聊天的双方在两个不同的ChatServer，那么会由ChatServer直接发起gRPC调用来传递消息。

**大致的架构图如下：**
![项目架构图](ShowPics/SimpleWeChat.png)
```mermaid
graph TD
    WeChat["WeChat系统架构"]

    %% 主要组件
    Server["服务器集群"]
    Storage["数据存储"]
    Client["客户端应用"]

    %% 服务器集群子组件
    GateServer["GateServer (网关服务器)"]
    VerifyServer["VerifyServer (验证服务器)"]
    StatusServer["StatusServer (状态服务器)"]
    ChatServer["ChatServer (聊天服务器)"]

    %% 数据存储子组件
    MySQL["MySQL"]
    Redis["Redis"]

    %% 客户端子组件
    QtClient["Qt客户端"]
    Login["登录/注册模块"]
    ChatUI["聊天界面"]
    FriendManage["好友管理"]
    MessageHistory["消息历史查询"]

    %% 服务器功能
    GateServerFunc["处理HTTP请求，验证码生成，用户注册登录"]
    VerifyServerFunc["提供身份验证服务，验证码校验"]
    StatusServerFunc["管理用户状态，ChatServer分配"]
    ChatServerFunc["处理实时消息，好友管理，聊天历史"]

    %% 数据存储功能
    MySQLFunc["用户信息，好友关系，消息历史"]
    RedisFunc["令牌存储，验证码缓存，临时状态"]

    %% 连接关系
    WeChat --> Server
    WeChat --> Storage
    WeChat --> Client

    %% 服务器连接
    Server --> GateServer
    Server --> VerifyServer
    Server --> StatusServer
    Server --> ChatServer

    GateServer --> GateServerFunc
    VerifyServer --> VerifyServerFunc
    StatusServer --> StatusServerFunc
    ChatServer --> ChatServerFunc

    %% 数据存储连接
    Storage --> MySQL
    Storage --> Redis
    MySQL --> MySQLFunc
    Redis --> RedisFunc

    %% 客户端连接
    Client --> QtClient
    QtClient --> Login
    QtClient --> ChatUI
    QtClient --> FriendManage
    QtClient --> MessageHistory
```


## 项目展示
![登录界面](ShowPics/登录界面.png)
![注册界面](ShowPics/注册界面.png)
![聊天界面](ShowPics/chat.png)
![好友界面](ShowPics/friend.png)
![数据库格式界面](ShowPics/mysql_data.png)
![验证码服务器](ShowPics/VerifyServer.png)
