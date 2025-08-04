# Trove自动脚本

## AutoHotKey

[![Static Badge](https://img.shields.io/badge/Fork-TroveAutoFish(2020)-gray?style=flat&labelColor=black)](https://github.com/MiraculousB/TroveAutoFish) [![Static Badge](https://img.shields.io/badge/AHK__H-2.1--alpha.18_64bit-blue?style=flat&labelColor=green)](https://github.com/thqby/AutoHotkey_H/tree/v2.1-alpha.18) [![Static Badge](https://img.shields.io/badge/C++-MinGW--W64.11.2.0-yellow?style=flat&labelColor=red)](https://www.mingw-w64.org/)

### Chinese

- 构建
  1. 准备编译环境：**v2版AutoHotKey_H**、**Ahk2Exe**、**C++ MinGW-w64**
  2. 下载源代码：`git clone https://github.com/Angels-D/TroveAuto.git && cd TroveAuto`
  3. 编译DLL依赖：`g++ -shared -static -Os -Wall -o Module.dll -x c++ ./libs/Module.hpp`
  4. 编译ahk脚本：`<Ahk2Exe路径>/Ahk2Exe.exe /compress 2 /base <AHK_Hv2路径>/AutoHotkey64.exe /in ./TroveAuto.ahk`
     > - `/compress 2` 使用UPX进行代码压缩
     > - 注意文件字符编码格式
     > - 编译ahk前注意目录下需要存在`Module.dll`文件
  5. (可选)使用单文件打包工具将`TroveAuto.exe`和`Module.dll`打包成一个可执行文件
     > - 打包工具请自行查找

- 已知问题

  - 自动按键时干扰用户输入, 并行按键越多越容易卡键
  - 热键与UI变化概率导致崩溃
  - `瞎子模式`功能失效，寻址方式待更新
- 脚本功能

  > - 各功能的CE参考
  >   - [https://www.mpgh.net/forum/forumdisplay.php?f=848](https://www.mpgh.net/forum/forumdisplay.php?f=848)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1533609](https://www.mpgh.net/forum/showthread.php?t=1533609)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1583283](https://www.mpgh.net/forum/showthread.php?t=1583283)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1583596](https://www.mpgh.net/forum/showthread.php?t=1583596)
  > - 寻址查找教程：[https://www.youtube.com/watch?v=FYzix68bxFA](https://www.youtube.com/watch?v=FYzix68bxFA)
  >   - 账号指针偏移：`"Trove.exe" + 0x115EF64 + 0x10 + 0`
  >

  - [X] `自动钓鱼`: 使用CE进行内存检测游戏账号和钓鱼判定

    - 钓鱼上钩判定：`"Trove.exe" + 0x113268C + 0x68 + 0xE4`
      - 水：`+ 0x3C4`
      - 熔岩：`+ 0x898`
      - 巧克力：`+ 0x62C`
      - 等离子体：`+ 0xB00 `
    - 钓鱼状态判定：`"Trove.exe" + 0x113268C + 0x68 + 0xF4`
      - 水：`+ 0xBA0`
      - 熔岩：`+ 0x938`
      - 巧克力：`+ 0xE08`
      - 等离子体：`+ 0x6CC`

  |    | 功能&nbsp;&nbsp;&nbsp;&nbsp; |    | 功能&nbsp;&nbsp;&nbsp;&nbsp; |
  | -- | ---------------------------- | -- | ---------------------------- |
  | ✅ | 自动按键                     | ✅ | 游戏多开                     |
  | ✅ | 自动寻址                     | ✅ | 自动复活                     |
  | ✅ |自动攻击                      | ✅ | 保持骑乘                     |
  | ✅ | 打破障碍                     | ✅ | 地图放大                     |
  | ✅ | 视野调整                     | ✅ | 快速挖矿                     |
  | ✅ | 物品栏计数                   | ✅ | 坐标传送                     |
  | ✅ | 穿墙                         | ✅ | 失量移动                     |
  | ✅ | 跟随目标                     | ✅ | 全反重力                     |
  | ✅ | 透视                         | ✅ | 自动瞄准                     |

### English

- Build
  1. Prepare the build environment: **AutoHotKey_H v2**, **Ahk2Exe**, **C++ MinGW-w64**
  2. Download the source code: `git clone https://github.com/Angels-D/TroveAuto.git && cd TroveAuto`
  3. Compile the DLL dependency: `g++ -shared -static -Os -Wall -o Module.dll -x c++ ./libs/Module.hpp`
  4. Compile the AHK script: `<Ahk2Exe path>/Ahk2Exe.exe /compress 2 /base <AHK_Hv2 path>/AutoHotkey64.exe /in ./TroveAuto.ahk`
     > - `/compress 2` uses UPX for code compression
     > - Note the file character encoding format
     > - Before compiling the AHK script, ensure the `Module.dll` file exists in the directory
  5. (Optional) Use a single-file packing tool to pack `TroveAuto.exe` and `Module.dll` into a single executable file
     > - Find a packing tool by yourself

- Known Issues

  - Auto-keypress may interfere with user input. More concurrent keypresses increase the likelihood of key jamming.
  - Hotkey combinations and UI changes may probabilistically cause crashes.
  - `Blind Mode` function is invalid, and the addressing method needs to be updated
- Script Features

  > - CE References for Features
  >   - [https://www.mpgh.net/forum/forumdisplay.php?f=848](https://www.mpgh.net/forum/forumdisplay.php?f=848)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1533609](https://www.mpgh.net/forum/showthread.php?t=1533609)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1583283](https://www.mpgh.net/forum/showthread.php?t=1583283)
  >   - [https://www.mpgh.net/forum/showthread.php?t=1583596](https://www.mpgh.net/forum/showthread.php?t=1583596)
  > - Address Finding Tutorial: [https://www.youtube.com/watch?v=FYzix68bxFA](https://www.youtube.com/watch?v=FYzix68bxFA)
  >   - Account pointer offset: `"Trove.exe" + 0x115EF64 + 0x10 + 0`
  >

  - [X] `Auto Fishing`: Uses CE for memory detection of game account and fishing judgment.

    - Bite detection: `"Trove.exe" + 0x113268C + 0x68 + 0xE4`
      - Water: `+ 0x3C4`
      - Lava: `+ 0x898`
      - Chocolate: `+ 0x62C`
      - Plasma: `+ 0xB00 `
    - Fishing state detection: `"Trove.exe" + 0x113268C + 0x68 + 0xF4`
      - Water: `+ 0xBA0`
      - Lava: `+ 0x938`
      - Chocolate: `+ 0xE08`
      - Plasma: `+ 0x6CC`

|    | Feature&nbsp;&nbsp;&nbsp;&nbsp; |    | Feature&nbsp;&nbsp;&nbsp;&nbsp; |
| -- | ------------------------------- | -- | ------------------------------- |
| ✅ | Auto Keypress                   | ✅ | Multi-instance Support          |
| ✅ | Auto Addressing                 | ✅ | Auto Resurrection               |
| ✅ | Vector Movement                 | ✅ | Auto Attack                     |
| ✅ | Persistent Mount                | ✅ | Barrier Break                   |
| ✅ | Map Zoom                        | ✅ | FOV Adjustment                  |
| ✅ | Fast Mining                     | ✅ | Inventory Counter               |
| ✅ | Coordinate Teleport             | ✅ | Wall Clipping                   |
| ✅ | Target Following                | ✅ | X-ray Vision                    |
| ✅ | Anti-gravity                    | ✅ | Auto Aim                        |
