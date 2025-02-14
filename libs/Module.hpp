/* Module
 *    -> Auther: Angels-D
 *
 * LastChange
 *    -> 2025/02/12 18:56
 *    -> 1.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o Module.dll -x c++ .\libs\Module.hpp
 */

/* 地址寻址
 * 玩家: (+Size Value) 55 8B EC 83 E4 F8 83 EC 08 F3 0F 2A 45 10 56 8B F1 57 8B 3D
 * 世界: (+10   Value) 55 8B EC 83 7D 08 04 75 10 A1 XX XX XX XX 85 C0 74 07 C6 80 59 01 00 00 01 5D C2 04 00
 * 设置: (+Size Value) 89 45 F4 8B 11 FF 52 0C 8B 0D XX XX XX XX 8B D8 6A 03 68 XX XX XX XX 8B 11 FF 52 0C 8B 0D
 * 聊天: (+2    Value) 8B 0D XX XX XX XX 6A 00 6A 01 C6 41 20 00 E8 XX XX XX XX 6A 08 8D 8D 60 FF FF FF C7 85 60 FF FF FF 00 00 00 00 C7 85 64 FF FF FF 00 00 00 00 C7 85 68 FF FF FF 00 00 00 00 C6 45 F0 01
 * 隐藏特效: (+3 Address) F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50
 * 自动攻击: (+1 Address) DF F1 DD D8 72 1F
 * 打破障碍: (+3 Address) 80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18
 * 视角遮挡: (+0 Address) 0F 29 01 C7 41 34 00 00 00 00 0F
 * 保持骑乘: (+0 Address) 74 XX 8B 07 8B CF 6A 00 6A 00 FF 50
 * 钓鱼地址: (+0 Address) 10 14 XX XX 00 00 00 00 FF 00 00 00 00
 * 视角固定: (+0 Address) 74 05 8B 01 FF 50 0C 8B E5
 * 地图放大: (+0 Address) 77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89
 * 快速挖矿: (+1 Address) DF F1 DD D8 72 61
 * 快速挖矿（晶洞）: (+1 Address) DF F1 DD D8 72 35 8D
 * 账号地址: (-9 Address) FF 70 1C FF 70 18 8D 45 B0
 * 视野放大: (+3 Address) F3 0F 11 5F 2C
 * 穿墙: (+0 Address) 74 31 FF 73 14 8B 47 04 2B 07
 * 绕道: (+1 Address) DC 67 68 C6
 * 技能栏: 5X CF XX XX 55 CF XX XX 5X CF XX XX 55 CF XX XX FE FF FF FF 00 00 00 00 65 CF XX XX 0X 00 00 00 55 CF XX XX XX XX XX XX 55 CF XX XX 55 CF XX XX
 *            (-170H Value) 数量
 *            (+0 Value) 55释放,5D按下
 *            (+8 Value) 55未装备,5D装备
 *            (+28 Value) 00 右键 | 02 1技能 | 04 2技能 | 06 SHIFT | 08 未知 | 0A 药瓶 | 0C R物品 | 0E T物品
 */

#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include "AFK.hpp"
#include "Game.hpp"

// Mdoule.h

class Module : public Game
{

};

// Module.cpp

#endif