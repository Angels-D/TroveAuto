/* 地址寻址
 * 玩家: (+Size Value) 55 8B EC 83 E4 F8 83 EC 08 F3 0F 2A 45 10 56 8B F1 57 8B 3D
 * 世界: (+10   Value) 55 8B EC 83 7D 08 04 75 10 A1 XX XX XX XX 85 C0 74 07 C6 80 59 01 00 00 01 5D C2 04 00
 * 设置: (+Size Value) 89 45 F4 8B 11 FF 52 0C 8B 0D XX XX XX XX 8B D8 6A 03 68 XX XX XX XX 8B 11 FF 52 0C 8B 0D
 * 聊天: (+2    Value) 8B 0D XX XX XX XX 6A 00 6A 01 C6 41 20 00 E8 XX XX XX XX 6A 08 8D 8D 60 FF FF FF C7 85 60 FF FF FF 00 00 00 00 C7 85 64 FF FF FF 00 00 00 00 C7 85 68 FF FF FF 00 00 00 00 C6 45 F0 01
 * 血量: (+4    Value) 40 3F 00 00 00 00 90 E5
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


// Author: wanttobeno
// Src: https://github.com/wanttobeno/x64_AOB_Search

#include <Windows.h>
#include <Psapi.h>
#include <algorithm>
#include <vector>

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

namespace AobScan
{
    int SundayHex(char *Src, unsigned long dwSrcLen, char *Sub);
    std::vector<DWORD> FindSig(DWORD dwPid, const char *Value, ULONG64 Start, ULONG64 End, bool once);
};

extern "C" __declspec(dllexport) DWORD FindSig(DWORD *Result, DWORD Size, DWORD dwPid, const char *Value, ULONG64 Start, ULONG64 End, bool once)
{
    std::vector<DWORD> v = AobScan::FindSig(dwPid, Value, Start, End, once);
    DWORD size = (std::min)(v.size(), Size / sizeof(DWORD));
    for (size_t i = 0; i < size; i++)
        Result[i] = v[i];
    return size;
}

#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    if (argc < 6)
        std::cout << 0xFFFFFFFF;
    else
    {
        for (DWORD result : AobScan::FindSig(
                 std::stoi(argv[1]),
                 argv[2],
                 std::stoi(argv[3]),
                 std::strtol(argv[4], nullptr, 0),
                 std::strtol(argv[5], nullptr, 0)))
            std::cout << result << ' ';
    }
    return 0;
}

bool FHexCharValid(char c)
{
    if (c >= '0' && c <= '9' ||
        c >= 'A' && c <= 'F' ||
        c >= 'a' && c <= 'f' ||
        c == '?')
        return true;
    else
        return false;
}

bool FHexDecoder(char *Dec, char *Src)
{
    char HighC, LowC;
    DWORD dwSrcLen = strlen(Src) / 2;
    int i;
    for (i = 0; i < dwSrcLen; i++)
    {
        HighC = Src[i * 2], LowC = Src[i * 2 + 1];
        if (!FHexCharValid(LowC) || !FHexCharValid(HighC))
            return false;
        HighC -= '0';
        if (HighC > 9)
            HighC -= 7;
        if (HighC > 0xf)
            HighC -= 0x20;
        LowC -= '0';
        if (LowC > 9)
            LowC -= 7;
        if (LowC > 0xf)
            LowC -= 0x20;
        Dec[i] = (HighC << 4) | LowC;
    }
    return true;
}

namespace AobScan
{
    // private: 注意，永远不要手动调用下面的函数
    std::vector<DWORD> FindSig(DWORD dwPid, const char *Value, ULONG64 Start = 0, ULONG64 End = 0, bool once = true);
    bool __SundayHexInit__(char *Sub, unsigned long *p, char *HexSub, unsigned long dwSubLen);
    ULONG64 __SundayHex__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen);
    ULONG64 __SundayHexV__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen, int v);
    std::vector<ULONG64> SundayHexV(char *Src, unsigned long dwSrcLen, char *Sub);
} // namespace AobScan

bool AobScan::__SundayHexInit__(char *Sub, DWORD *p, char *HexSub, unsigned long dwSubLen)
{
    if (!FHexDecoder(HexSub, Sub))
    {
        return false;
    }
    ULONG64 i;

    for (i = 0; i < 0x100; i++)
    {
        p[i] = -1;
    }

    int WildAddr = 0;
    for (i = 0; i < dwSubLen; i++)
    {
        if (Sub[i * 2] == '?')
            WildAddr = i;
    }

    for (i = WildAddr + 1; i < dwSubLen; i++)
    { // 扫描Sub，初始化 P 表
        p[(BYTE)HexSub[i]] = dwSubLen - i;
    }

    for (i = 0; i < 0x100; i++)
    {
        if (p[i] == -1)
            p[i] = dwSubLen - WildAddr;
    }
    return true;
}

ULONG64 AobScan::__SundayHex__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen)
{
    // 开始配对字符串
    // j为 Sub位置指标， k为 当前匹配位置
    ULONG64 j, k;
    j = dwSubLen - 1; // 初始化位置为 dwSubLen - 1,匹配顺序为从右到左

    bool bContinue = true;
    bool bSuccess;
    while (bContinue)
    {
        bSuccess = true;
        for (k = 0; k < dwSubLen; k++)
        {
            if (Sub[(dwSubLen - k - 1) * 2] != '?' && Src[j - k] != HexSub[dwSubLen - k - 1])
            {
                bSuccess = false;
                break;
            }
        }
        if (bSuccess)
            bContinue = false;
        else
        {                         // 移动j指针
            if (j < dwSrcLen - 1) // 防止j+1 >= dwSrcLen造成溢出
                j += p[(BYTE)Src[j + 1]];
            else
                j++;
        }
        if (j >= dwSrcLen)
            break;
    }
    if (j < dwSrcLen)
        return j - dwSubLen + 1;
    else
        return -1;
}

ULONG64 AobScan::__SundayHexV__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen, int v)
{
    // 开始配对字符串
    // j为 Sub位置指标， k为 当前匹配位置
    ULONG64 j, k;
    j = dwSubLen - 1 + v; // 初始化位置为 dwSubLen - 1,匹配顺序为从右到左

    bool bContinue = true;
    bool bSuccess;
    while (bContinue)
    {
        bSuccess = true;
        for (k = 0; k < dwSubLen; k++)
        {
            if (Sub[(dwSubLen - k - 1) * 2] != '?' && Src[j - k] != HexSub[dwSubLen - k - 1])
            {
                bSuccess = false;
                break;
            }
        }
        if (bSuccess)
            bContinue = false;
        else
        {                         // 移动j指针
            if (j < dwSrcLen - 1) // 防止j+1 >= dwSrcLen造成溢出
                j += p[(BYTE)Src[j + 1]];
            else
                j++;
        }
        if (j >= dwSrcLen)
            break;
    }
    if (j < dwSrcLen)
        return j - dwSubLen + 1;
    else
        return -1;
}
int AobScan::SundayHex(char *Src, unsigned long dwSrcLen, char *Sub)
{
    DWORD dwSubLen = strlen(Sub);
    if (dwSubLen % 2) // 长度必须为2的倍数
        return -1;
    dwSubLen /= 2;

    char *HexSub = new char[dwSubLen + 1];
    DWORD *p = new DWORD[0x100]; // table P,标志距离
    int i = -1;

    if (AobScan::__SundayHexInit__(Sub, p, HexSub, dwSubLen))
    {
        i = AobScan::__SundayHex__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen);
    }

    delete[] p;
    delete[] HexSub;
    return i;
}

std::vector<ULONG64> AobScan::SundayHexV(char *Src, unsigned long dwSrcLen, char *Sub)
{
    std::vector<ULONG64> v;
    DWORD dwSubLen = strlen(Sub);

    if (dwSubLen % 2) // 长度必须为2的倍数
        return v;
    dwSubLen /= 2;

    char *HexSub = new char[dwSubLen + 1];
    DWORD *p = new DWORD[0x100]; // table P,标志距离
    int i = -1;

    if (AobScan::__SundayHexInit__(Sub, p, HexSub, dwSubLen))
    {
        i = AobScan::__SundayHexV__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen, 0);
        while (i != -1)
        {
            v.push_back(i);
            i = AobScan::__SundayHexV__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen, i + dwSubLen);
        }
    }
    delete[] p;
    delete[] HexSub;
    return v;
}

#define RESERVED_ADDRESS_X32 0x00327000
#define SYSTEM_MEMORY_ADDRESS_X32 0x70000000
#define SYSTEM_MEMORY_ADDRESS_X32_MAX 0x7FFFFFFF

// 定义区段上限,一般的区段大小不会超过
#define SECTION_SIZE_X32_MAX 0x0f000000

std::vector<DWORD> AobScan::FindSig(DWORD dwPid, const char *Value, ULONG64 Start, ULONG64 End, bool once)
{
    std::vector<DWORD> vFindResult;
    if (dwPid == 0)
        return vFindResult;
    if (Start < RESERVED_ADDRESS_X32)
        Start = RESERVED_ADDRESS_X32;
    if (End < 0)
        End = SYSTEM_MEMORY_ADDRESS_X32;
    if (Start >= End)
        return vFindResult;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPid);

    if (hProcess == NULL)
        return vFindResult;

    DWORD dwSectionSize = 0;
    MEMORY_BASIC_INFORMATION mem_info;
    while (VirtualQueryEx(hProcess, (LPCVOID)Start, &mem_info, sizeof(MEMORY_BASIC_INFORMATION)))
    {
        if (mem_info.Protect != 16 && mem_info.RegionSize != 1 && mem_info.Protect != 512)
        {
            dwSectionSize = (DWORD)mem_info.BaseAddress + mem_info.RegionSize - Start;
            if (dwSectionSize > SECTION_SIZE_X32_MAX)
                break;
            char *buf = new char[dwSectionSize + 1];
            if (buf == NULL)
                break;
            if (ReadProcessMemory(hProcess, (LPCVOID)Start, buf, dwSectionSize, NULL))
            {
                std::vector<ULONG64> dwValue = AobScan::SundayHexV(buf, dwSectionSize, (char *)Value);
                for (size_t i = 0; i < dwValue.size(); i++)
                {
                    vFindResult.push_back(Start + dwValue[i]);
                    if (once)
                        return vFindResult;
                }
            }
            delete[] buf;
        }
        if (End == 0)
            break;
        Start += mem_info.RegionSize;
        if (Start > SYSTEM_MEMORY_ADDRESS_X32)
            break;
        if (Start > End)
            break;
    }
    CloseHandle(hProcess);
    return vFindResult;
}
