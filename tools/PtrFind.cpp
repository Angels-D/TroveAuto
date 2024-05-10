#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>

HANDLE process_handle = 0;
int process_id = 0;
MODULEENTRY32W process_module;
UINT32 module_address = 0;

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
 * 账号地址: (+6 Address) E8 XX XX XX FF A1 XX XX XX 01 68 XX XX XX 01 FF
 *           00 00 00 00 E8 X9 XX XX FF A1 XX 6X XX 01 68 XX XX XX 01 FF 70 1C FF 70 18 8D 45 B0 50 E8 X0 7X XX FF 83 C4 10 8D 45 B0
 *           75 06 8B 01 6A 01 FF 10 C7 05 XX XX XX 01 00 00 00 00 C3 CC CC CC 8B 0D XX 6X XX 01 85 C9 74 16 83 41 08 FF 75 06 8B 01
 * 视野放大: (+3 Address) F3 0F 11 5F 2C
 */

void get_process_id(const wchar_t* process_name)
{
    HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot_handle != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 process_entry;
        process_entry.dwSize = sizeof(process_entry);

        if (Process32First(snapshot_handle, &process_entry))
        {
            do
            {
                if (!_wcsicmp(process_entry.szExeFile, process_name))
                {
                    process_id = process_entry.th32ProcessID;
                    goto End;
                }
            } while (Process32Next(snapshot_handle, &process_entry));

        }
    }
End:
    CloseHandle(snapshot_handle);
}

void get_process_module(const wchar_t* module_name)
{
    MODULEENTRY32W moduleEntry;
    HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
    if (snapshot_handle != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 mod_entry;
        mod_entry.dwSize = sizeof(mod_entry);
        if (Module32First(snapshot_handle, &mod_entry))
        {
            do
            {
                if (!_wcsicmp(mod_entry.szModule, module_name))
                {
                    process_module = mod_entry;
                    module_address = (UINT32)mod_entry.modBaseAddr;
                    goto End;
                }
            } while (Module32Next(snapshot_handle, &mod_entry));
        }
    }
End:
    CloseHandle(snapshot_handle);
}

int read_int(UINT32 address)
{
    return ReadProcessMemory(process_handle, (LPCVOID)address, &address, sizeof(int), 0) ? (int)address : 0;
}

int find_signature_address(std::vector<int> pattern)
{
    DWORD module_size = process_module.modBaseSize;
    auto buffer = (byte*)malloc(module_size);
    ReadProcessMemory(process_handle, (LPCVOID)module_address, buffer, module_size, 0);

    int compare = 0;
    UINT32 count = pattern.size();

    int first_byte = pattern[0];
    auto is_first_empty = first_byte == -1;
    for (int i = 0; i < module_size; i++)
    {
        if (buffer[i] != first_byte && !is_first_empty) continue;
        for (int g = 1; g < count; g++)
        {
            if (buffer[i + g] != pattern[g] && pattern[g] != -1)
            {
                compare = 1;
                break;
            }

            compare++;
            if (compare == count)
            {
                free(buffer);
                return i + module_address;
            }
        }
    }

    free(buffer);
    return 0;
}

int main(int argc,char *argv[])
{
    get_process_id(L"Trove.exe");
    get_process_module(L"Trove.exe");
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);
    std::vector<int> offset_signature;
    char * str;
    for(int i = 1; argv[i]; i++)
        offset_signature.push_back(strcmp(argv[i],"XX")?strtol(argv[i],&str,16):-1);
    printf("0x%0X",find_signature_address(offset_signature) - module_address);
    return 0;
}