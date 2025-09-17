/* Memory
 *    -> Author: Angels-D & AI
 *
 * AobScan
 *    -> Author: wanttobeno
 *    -> Src: https://github.com/wanttobeno/x64_AOB_Search
 *
 * LastChange
 *    -> 2025/04/16 04:40
 *    -> 1.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o Memory.dll -x c++ ./libs/Memory.hpp
 */

// Memory.h

#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <Windows.h>
#include <TlHelp32.h>
#include <functional>
#include <thread>
#include <vector>
#include <string>

#define DLL_EXPORT __declspec(dllexport)

#define RESERVED_ADDRESS_X32 0x00001000
#define SYSTEM_MEMORY_ADDRESS_X32 0x70000000
#define SYSTEM_MEMORY_ADDRESS_X32_MAX 0x7FFFFFFF

// 定义区段上限,一般的区段大小不会超过
#define SECTION_SIZE_X32_MAX 0x0f000000

namespace AobScan
{
    typedef unsigned long DWORD;
    typedef unsigned short WORD;
    typedef unsigned char BYTE;

    int SundayHex(char *Src, unsigned long dwSrcLen, char *Sub);
    // private: 注意，永远不要手动调用下面的函数
    std::vector<DWORD> FindSig(DWORD dwPid, const char *Value, ULONG64 Start = 0, ULONG64 End = 0, bool once = true);
    bool __SundayHexInit__(char *Sub, unsigned long *p, char *HexSub, unsigned long dwSubLen);
    ULONG64 __SundayHex__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen);
    ULONG64 __SundayHexV__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen, int v);
    std::vector<ULONG64> SundayHexV(char *Src, unsigned long dwSrcLen, char *Sub);
} // namespace AobScan

class Memory
{
public:
    typedef uint32_t Address;
    typedef std::vector<int32_t> Offsets;
    typedef AobScan::DWORD DWORD;
    typedef AobScan::WORD WORD;
    typedef AobScan::BYTE BYTE;

    static std::vector<uint32_t> GetProcessPid(const std::string &name);

    template <typename T>
    static std::string toHexByteString(const T &data);

    static std::string PatternScan(const std::string &signature);

    HANDLE hProcess;
    DWORD pid;

    // 构造函数：通过PID打开进程句柄
    Memory(const DWORD &pid);
    Memory(const Memory &memory);

    ~Memory();

    void Update(const DWORD &pid);

    std::string GetProcessName() const;

    std::vector<Address> FindAddress(
        const std::function<std::pair<std::vector<DWORD>, Address>(const Address &start, const Address &end)> &Pred,
        bool once = false, const uint32_t threads = std::thread::hardware_concurrency(),
        const std::string &moduleName = "",
        const Address &start = 0x0,
        const Address &end = SYSTEM_MEMORY_ADDRESS_X32_MAX);

    std::vector<Address> AobScan(
        const std::string &signature,
        bool once = false,
        uint32_t threads = std::thread::hardware_concurrency(),
        const std::string &moduleName = "",
        Address start = 0,
        Address end = SYSTEM_MEMORY_ADDRESS_X32_MAX);

    template <typename T>
    std::vector<Address> FastScan(
        const T &data,
        bool once = false,
        uint32_t threads = std::thread::hardware_concurrency(),
        const std::string &moduleName = "",
        Address start = 0,
        Address end = SYSTEM_MEMORY_ADDRESS_X32_MAX);

    template <typename T>
    std::vector<Address> FastScan(
        const std::vector<T> &data,
        bool once = false,
        uint32_t threads = std::thread::hardware_concurrency(),
        const std::string &moduleName = "",
        Address start = 0,
        Address end = SYSTEM_MEMORY_ADDRESS_X32_MAX);

    // 获取模块基地址
    Address GetModuleAddress(const std::string &moduleName, MODULEENTRY32 me = {}) const;

    // 读取地址
    Address GetAddress(const Memory::Address &base, const Memory::Offsets &offsets = {}) const;

    // 读取内存
    template <typename T>
    T ReadMemory(const Address &address, const Offsets &offsets = {}) const;

    std::string ReadMemory(const Address &address, const Offsets &offsets = {}, const size_t maxLen = 256) const;

    // 写入内存
    template <typename T>
    bool WriteMemory(const T &data, const Address &address, const Offsets &offsets = {}) const;

    // 申请内存空间
    Address AllocMemory(const size_t &size, const DWORD &allocationType, const DWORD &protect, const Address &address = (Address)NULL);

    // 释放内存空间
    bool FreeMemory(const size_t &size, const DWORD &freeType, const Address &address);

protected:
    // 泛型读取
    template <typename T>
    T Read(const Address &address) const;

    // 读取字符串
    std::string Read(const Address &address, const size_t &maxLen = 256) const;

    // 泛型写入
    template <typename T>
    bool Write(const Address &address, const T &data) const;

private:
    bool isRoot;
};

extern "C"
{
    DLL_EXPORT AobScan::DWORD AobScanFindSig(
        AobScan::DWORD *result,
        const AobScan::DWORD size,
        const AobScan::DWORD dwPid,
        const char *value, const ULONG64 start = 0x0,
        const ULONG64 end = SYSTEM_MEMORY_ADDRESS_X32_MAX,
        const bool once = true);

    DLL_EXPORT Memory *MemoryCreate(AobScan::DWORD dwPid);
    DLL_EXPORT void MemoryDelete(Memory *memory);
    DLL_EXPORT void MemoryUpdate(Memory *memory, const DWORD &pid);
    DLL_EXPORT uint32_t MemoryAobScan(
        Memory *memory,
        Memory::Address *result,
        const uint32_t size,
        const char *signature,
        const bool once = true,
        const uint32_t threads = std::thread::hardware_concurrency(),
        const char *moduleName = "",
        const ULONG64 start = 0x0,
        const ULONG64 end = SYSTEM_MEMORY_ADDRESS_X32_MAX);
    DLL_EXPORT uint32_t MemoryFastScan(
        Memory *memory,
        Memory::Address *result,
        const uint32_t size,
        const char *value,
        const bool once = true,
        const uint32_t threads = std::thread::hardware_concurrency(),
        const char *moduleName = "",
        const ULONG64 start = 0x0,
        const ULONG64 end = SYSTEM_MEMORY_ADDRESS_X32_MAX);
    DLL_EXPORT Memory::Address MemoryGetAddress(Memory *memory, const Memory::Address &address, const Memory::Address *Offsets = {}, const uint32_t offsetsLen = 0);
    // DLL_EXPORT Memory::Address MemoryRead(Memory *memory, const char* type, const Memory::Address &address, const Memory::Address *Offsets = {}, const uint32_t offsetsLen = 0);
}

// Memory.cpp

#include <regex>
#include <atomic>
#include <algorithm>
#include <codecvt>

AobScan::DWORD AobScanFindSig(
    AobScan::DWORD *result,
    const AobScan::DWORD size,
    const AobScan::DWORD dwPid,
    const char *value,
    const ULONG64 start,
    const ULONG64 end,
    const bool once)
{
    std::vector<AobScan::DWORD> v = AobScan::FindSig(dwPid, value, start, end, once);
    AobScan::DWORD _size = (std::min)(v.size(), size / sizeof(AobScan::DWORD));
    for (size_t i = 0; i < _size; i++)
        result[i] = v[i];
    return _size;
}

Memory *MemoryCreate(AobScan::DWORD dwPid)
{
    return new Memory(dwPid);
}

void MemoryDelete(Memory *memory)
{
    delete memory;
}

void MemoryUpdate(Memory *memory, const AobScan::DWORD &pid)
{
    memory->Update(pid);
}

uint32_t MemoryAobScan(
    Memory *memory,
    Memory::Address *result,
    const uint32_t size,
    const char *signature,
    const bool once,
    const uint32_t threads,
    const char *moduleName,
    const ULONG64 start,
    const ULONG64 end)
{
    std::vector<Memory::Address> v = memory->AobScan(signature, once, threads, moduleName, start, end);
    uint32_t num = (std::min)(v.size(), size / sizeof(Memory::Address));
    for (uint32_t i = 0; i < size; i++)
        result[i] = v[i];
    return num;
}

uint32_t MemoryFastScan(
    Memory *memory,
    Memory::Address *result,
    const uint32_t size,
    const char *value,
    const bool once,
    const uint32_t threads,
    const char *moduleName,
    const ULONG64 start,
    const ULONG64 end)
{
    return MemoryAobScan(memory, result, size, memory->toHexByteString(value).c_str(), once, threads, moduleName, start, end);
}

Memory::Address MemoryGetAddress(Memory *memory, const Memory::Address &address, const Memory::Address *offsets, const uint32_t offsetsLen)
{
    return memory->GetAddress(address, {offsets, offsets + offsetsLen});
}
namespace AobScan
{
    bool FHexCharValid(char c)
    {
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f') ||
            c == '?')
            return true;
        else
            return false;
    }

    bool FHexDecoder(char *Dec, char *Src)
    {
        char HighC, LowC;
        DWORD dwSrcLen = strlen(Src) / 2;
        for (DWORD i = 0; i < dwSrcLen; i++)
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

    bool __SundayHexInit__(char *Sub, DWORD *p, char *HexSub, unsigned long dwSubLen)
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

        // 扫描Sub, 初始化P表
        for (i = WildAddr + 1; i < dwSubLen; i++)
        {
            p[(BYTE)HexSub[i]] = dwSubLen - i;
        }

        for (i = 0; i < 0x100; i++)
        {
            if (p[i] == (DWORD)-1)
                p[i] = dwSubLen - WildAddr;
        }
        return true;
    }

    ULONG64 __SundayHex__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen)
    {
        // 开始配对字符串
        // j为Sub位置指标, k为当前匹配位置
        ULONG64 j, k;
        j = dwSubLen - 1; // 初始化位置为 dwSubLen - 1, 匹配顺序为从右到左

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

    ULONG64 __SundayHexV__(char *Src, unsigned long dwSrcLen, char *Sub, DWORD *p, char *HexSub, DWORD dwSubLen, int v)
    {
        // 开始配对字符串
        // j为Sub位置指标, k为当前匹配位置
        ULONG64 j, k;
        j = dwSubLen - 1 + v; // 初始化位置为 dwSubLen - 1, 匹配顺序为从右到左

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
    int SundayHex(char *Src, unsigned long dwSrcLen, char *Sub)
    {
        DWORD dwSubLen = strlen(Sub);
        if (dwSubLen % 2) // 长度必须为2的倍数
            return -1;
        dwSubLen /= 2;

        char *HexSub = new char[dwSubLen + 1];
        DWORD *p = new DWORD[0x100]; // table P,标志距离
        int i = -1;

        if (__SundayHexInit__(Sub, p, HexSub, dwSubLen))
        {
            i = __SundayHex__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen);
        }

        delete[] p;
        delete[] HexSub;
        return i;
    }

    std::vector<ULONG64> SundayHexV(char *Src, unsigned long dwSrcLen, char *Sub)
    {
        std::vector<ULONG64> v;
        DWORD dwSubLen = strlen(Sub);

        if (dwSubLen % 2) // 长度必须为2的倍数
            return v;
        dwSubLen /= 2;

        char *HexSub = new char[dwSubLen + 1];
        DWORD *p = new DWORD[0x100]; // table P,标志距离
        int i = -1;

        if (__SundayHexInit__(Sub, p, HexSub, dwSubLen))
        {
            i = __SundayHexV__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen, 0);
            while (i != -1)
            {
                v.push_back(i);
                i = __SundayHexV__(Src, dwSrcLen, Sub, p, HexSub, dwSubLen, i + dwSubLen);
            }
        }
        delete[] p;
        delete[] HexSub;
        return v;
    }

    std::vector<DWORD> FindSig(DWORD dwPid, const char *Value, ULONG64 Start, ULONG64 End, bool once)
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
                dwSectionSize = reinterpret_cast<uintptr_t>(mem_info.BaseAddress) + mem_info.RegionSize - Start;
                if (dwSectionSize > SECTION_SIZE_X32_MAX)
                    break;
                char *buf = new char[dwSectionSize + 1];
                if (buf == NULL)
                    break;
                if (ReadProcessMemory(hProcess, (LPCVOID)Start, buf, dwSectionSize, NULL))
                {
                    std::vector<ULONG64> dwValue = SundayHexV(buf, dwSectionSize, (char *)Value);
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
}

Memory::Memory(const DWORD &pid) : hProcess(nullptr), pid(pid), isRoot(true)
{
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess)
        throw std::runtime_error("Failed to open process");
}

Memory::Memory(const Memory &memory)
    : hProcess(memory.hProcess), pid(memory.pid), isRoot(false)
{
    if (!hProcess && !(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid)))
        throw std::runtime_error("Failed to open process");
}

Memory::~Memory()
{
    if (hProcess && isRoot)
        CloseHandle(hProcess);
}

std::string WCHARToString(const WCHAR *wideStr)
{
    int len = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    std::string str(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, &str[0], len, nullptr, nullptr);
    return str;
}

std::vector<uint32_t> Memory::GetProcessPid(const std::string &name)
{
    std::vector<uint32_t> pids;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return pids;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    std::regex re(name, std::regex::icase);

    if (Process32First(snapshot, &pe))
    {
        do
        {
#ifdef UNICODE
            std::string processName(WCHARToString(pe.szExeFile));
#else
            std::string processName(pe.szExeFile);
#endif
            if (std::regex_match(processName, re))
            {
                pids.push_back(pe.th32ProcessID);
            }
        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return pids;
}

std::string Memory::GetProcessName() const
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return "";

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pe))
    {
        do
        {
            if (pe.th32ProcessID == pid)
            {
                CloseHandle(snapshot);
#ifdef UNICODE
                return WCHARToString(pe.szExeFile);
#else
                return pe.szExeFile;
#endif
            }
        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return "";
}

std::vector<Memory::Address> Memory::FindAddress(
    const std::function<std::pair<std::vector<DWORD>, Address>(const Address &start, const Address &end)> &Pred,
    bool once, const uint32_t threads,
    const std::string &moduleName,
    const Address &start,
    const Address &end)
{
    Address baseAddr = 0;
    uint32_t startAddr = start, endAddr = end;

    if (moduleName.length())
    {
        baseAddr = GetModuleAddress(moduleName);
        if (!baseAddr)
            return {};

        MODULEENTRY32 me;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        me.dwSize = sizeof(me);
        if (Module32First(hSnapshot, &me))
        {
            do
            {
                if (me.modBaseAddr == reinterpret_cast<BYTE *>(baseAddr))
                {
                    startAddr = baseAddr;
                    endAddr = baseAddr + me.modBaseSize;
                    break;
                }
            } while (Module32Next(hSnapshot, &me));
        }
        CloseHandle(hSnapshot);
    }

    std::vector<std::thread> workers;
    std::vector<std::vector<Address>> results(threads);
    std::atomic<bool> found(false);

    const uint32_t chunkSize = (endAddr - startAddr) / threads;
    for (uint32_t i = 0; i < threads; ++i)
    {
        Address chunkStart = startAddr + i * chunkSize;
        Address chunkEnd = (i == threads - 1) ? endAddr : chunkStart + chunkSize;

        workers.emplace_back([this, chunkStart, chunkEnd, &Pred, &results, i, once, &found]()
                             {
            std::vector<Address> localResults;
            Address current = chunkStart;
            while (current < chunkEnd && !(once && found.load())) {
                MEMORY_BASIC_INFORMATION mbi;
                if (!VirtualQueryEx(hProcess, reinterpret_cast<LPCVOID>(current), &mbi, sizeof(mbi)))
                    break;

                if (mbi.State != MEM_COMMIT || mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) {
                    current += mbi.RegionSize;
                    continue;
                }

                Address regionStart = reinterpret_cast<uintptr_t>(mbi.BaseAddress);
                Address regionEnd = regionStart + mbi.RegionSize;
                regionStart = (std::max)(regionStart, chunkStart);
                regionEnd = (std::min)(regionEnd, chunkEnd);

                for (Address addr = regionStart; addr < regionEnd && !(once && found.load()); ++addr) {
                    std::pair<std::vector<DWORD>, Address> result = Pred(addr,regionEnd);
                    if (!result.first.empty()) {
                        localResults.insert(localResults.end(),result.first.begin(),result.first.end());
                        if (once) {
                            found.store(true);
                            break;
                        }
                    }
                    addr = result.second;
                }
                current = regionEnd;
            }
            results[i] = std::move(localResults); });
    }

    for (auto &t : workers)
        if (t.joinable())
            t.join();

    std::vector<Address> finalResults;
    for (auto &res : results)
    {
        finalResults.insert(finalResults.end(), res.begin(), res.end());
        if (once && !finalResults.empty())
            break;
    }

    return finalResults;
}

template <typename T>
std::string Memory::toHexByteString(const T &data)
{
    if constexpr (std::is_arithmetic_v<T>)
    { // 处理数值类型
        std::string result;
        const auto *bytes = reinterpret_cast<const unsigned char *>(&data);
        for (size_t i = 0; i < sizeof(T); ++i)
        {
            char buf[3];
            std::snprintf(buf, sizeof(buf), "%02X", bytes[i]);
            result += buf;
        }
        return result;
    }
    else if constexpr (std::is_convertible_v<T, std::string_view>)
    { // 处理字符串
        std::string result;
        for (char c : std::string_view(data))
        {
            char buf[3];
            std::snprintf(buf, sizeof(buf), "%02X", static_cast<uint8_t>(c));
            result += buf;
        }
        return result;
    }
    else
    { // 处理容器/数组
        std::string result;
        for (const auto &elem : data)
        {
            result += toHexByteString(elem);
        }
        return result;
    }
}

std::string Memory::PatternScan(const std::string &signature)
{
    std::string result;
    result.reserve(signature.size());
    for (char c : signature)
        switch (c)
        {
        case ',':
        case ' ':
            continue;
        case 'X':
        case 'x':
            c = '?';
        default:
            if (c >= 'a' && c <= 'f')
                c = toupper(c);
            else if (!((c >= '0' && c <= '9') ||
                       (c >= 'A' && c <= 'F') || c == '?'))
                throw std::invalid_argument(std::string("Invalid character detected: ") + c);
            result.push_back(c);
        }
    return result;
}

std::vector<Memory::Address> Memory::AobScan(
    const std::string &signature,
    bool once,
    uint32_t threads,
    const std::string &moduleName,
    Address start,
    Address end)
{
    const std::string &pattern = PatternScan(signature);
    return FindAddress([this, pattern, once](const Address &start, const Address &end)
                       { return std::pair(AobScan::FindSig(this->pid, pattern.c_str(), start, end, once), end); }, once, threads, moduleName, start, end);
}

template <typename T>
std::vector<Memory::Address> Memory::FastScan(
    const T &data,
    bool once,
    uint32_t threads,
    const std::string &moduleName,
    Address start,
    Address end)
{
    return AobScan(toHexByteString(data), once, threads, moduleName, start, end);
}

template <typename T>
std::vector<Memory::Address> Memory::FastScan(const std::vector<T> &data,
                                              bool once,
                                              uint32_t threads,
                                              const std::string &moduleName,
                                              Address start,
                                              Address end)
{
    return FasterScan(toByteString(data), once, threads, moduleName, start, end);
}

Memory::Address Memory::GetModuleAddress(const std::string &moduleName, MODULEENTRY32 me) const
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;
    me.dwSize = sizeof(me);
    if (!Module32First(hSnapshot, &me))
    {
        CloseHandle(hSnapshot);
        return 0;
    }
    do
    {
#ifdef UNICODE
        std::string szModule = WCHARToString(me.szModule);
#else
        std::string szModule = me.szModule;
#endif
        szModule.front() = toupper(szModule.front());
        if (moduleName == szModule)
        {
            CloseHandle(hSnapshot);
            return reinterpret_cast<uintptr_t>(me.modBaseAddr);
        }
    } while (Module32Next(hSnapshot, &me));

    CloseHandle(hSnapshot);
    return 0;
}

Memory::Address Memory::GetAddress(const Memory::Address &base, const Memory::Offsets &offsets) const
{
    if (offsets.empty())
        return base;
    Memory::Address address = base + offsets[0];
    for (size_t i = 1; i < offsets.size(); ++i)
    {
        if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address),
                               &address, sizeof(address), nullptr))
            return 0;
        address += offsets[i];
    }
    return address;
}

// 读取内存
template <typename T>
T Memory::ReadMemory(const Address &address, const Offsets &offsets) const
{
    Address finalAddr = GetAddress(address, offsets);
    if (!finalAddr)
        return T();
    return Read<T>(finalAddr);
}

std::string Memory::ReadMemory(const Address &address, const Offsets &offsets, const size_t maxLen) const
{
    Address finalAddr = GetAddress(address, offsets);
    if (!finalAddr)
        return {};
    return Read(finalAddr, maxLen);
}

// 写入内存
template <typename T>
bool Memory::WriteMemory(const T &data, const Address &address, const Offsets &offsets) const
{
    const Address &finalAddress = GetAddress(address, offsets);
    if (!finalAddress)
        return false;
    return Write(finalAddress, data);
}

Memory::Address Memory::AllocMemory(const size_t &size, const DWORD &allocationType, const DWORD &protect, const Address &address)
{
    return reinterpret_cast<uintptr_t>(VirtualAllocEx(
        hProcess, reinterpret_cast<LPVOID>(address),
        size, allocationType, protect));
}

bool Memory::FreeMemory(const size_t &size, const DWORD &freeType, const Address &address)
{
    return VirtualFreeEx(
        hProcess, reinterpret_cast<Memory::Address *>(address),
        size, freeType);
}

void Memory::Update(const DWORD &pid)
{
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess)
        throw std::runtime_error("Failed to open process");
}

template <typename T>
T Memory::Read(const Address &address) const
{
    T value = T();
    ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &value, sizeof(T), nullptr);
    return value;
}

std::string Memory::Read(const Address &address, const size_t &maxLen) const
{
    std::string str;
    char c;
    while (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address + str.size()), &c, 1, nullptr) &&
           c != '\0' && str.size() < maxLen)
        str += c;
    return str;
}

template <typename T>
bool Memory::Write(const Address &address, const T &data) const
{
    return WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), &data, sizeof(T), nullptr);
}

template <>
bool Memory::Write(const Address &address, const std::vector<BYTE> &bytes) const
{
    return WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), nullptr);
}

template <>
bool Memory::Write(const Address &address, const std::string &str) const
{
    return WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), str.c_str(), str.length() + 1, nullptr);
}

#endif
