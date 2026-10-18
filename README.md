# Dzl Snake

一个基于 C++ 和 Windows 控制台的贪吃蛇小游戏，使用 Visual Studio 编写。

项目包含两个版本：

- `Snake Game`：英文界面版本，适合作为基础版本运行和学习
- `贪吃蛇（成功）`：中文界面版本，增加了中文菜单和游戏说明

## 游戏功能

- 开始游戏
- 游戏说明界面
- 上下左右方向键控制蛇移动
- 随机生成食物
- 吃到食物后蛇身变长并增加分数
- 撞到墙壁或自己的身体后游戏结束
- 游戏结束后可以返回主菜单
- 支持退出游戏

## 操作方法

启动游戏后：

- 使用 `↑`、`↓` 键选择菜单
- 按 `Enter` 确认
- 游戏过程中使用 `↑`、`↓`、`←`、`→` 控制蛇移动
- 游戏结束后按任意键返回主菜单

运行时请将输入法切换为英文状态。

## 开发环境

- 操作系统：Windows
- 开发工具：Visual Studio 2022
- 编译工具集：MSVC v143
- Windows SDK：10.0
- 编程语言：C++

## 编译运行

### 运行英文版本

1. 进入 `Snake Game` 文件夹。
2. 使用 Visual Studio 打开 `Snake Game.sln`。
3. 选择 `Debug` 或 `Release` 配置。
4. 选择 `x64` 平台。
5. 点击“生成解决方案”。
6. 运行项目。

主要工程文件：

```text
Snake Game/Snake Game.sln
Snake Game/Snake Game/Snake Game.vcxproj
Dzl Snake/
├── Snake Game/
│   ├── Snake Game.sln
│   └── Snake Game/
│       ├── main.cpp
│       ├── Snake.cpp
│       ├── Snake.h
│       ├── Food.cpp
│       ├── Food.h
│       ├── GameManager.cpp
│       ├── GameManager.h
│       ├── Config.cpp
│       └── Config.h
│
└── 贪吃蛇（成功）/
    ├── MFCApplication1.sln
    └── MFCApplication1/
        ├── MFCApplication1.vcxproj
        ├── main.cpp
        ├── Snake.cpp
        ├── Food.cpp
        ├── GameManager.cpp
        └── Config.cpp
