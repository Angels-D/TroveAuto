#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

//big signatures for best guarantee (i just selected random length))

std::vector<int> player_offset_signature =
{
    0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, 0x83, 0xEC, 0x08, 0xF3, 0x0F, 0x2A, 0x45, 0x10, 0x56, 0x8B, 0xF1,
    0x57, 0x8B, 0x3D
};

std::vector<int> world_offset_signature =
{
    0x55, 0x8B, 0xEC, 0x83, 0x7D, 0x08, 0x04, 0x75, 0x10, 0xA1, -1, -1, -1, -1, 0x85, 0xC0, 0x74, 0x07,
    0xC6, 0x80, 0x59, 0x01, 0x00, 0x00, 0x01, 0x5D, 0xC2, 0x04, 0x00
};

std::vector<int> settings_offset_signature =
{
    0x89, 0x45, 0xF4, 0x8B, 0x11, 0xFF, 0x52, 0x0C, 0x8B, 0x0D, -1, -1, -1, -1, 0x8B, 0xD8,
    0x6A, 0x03, 0x68, -1, -1, -1, -1, 0x8B, 0x11, 0xFF, 0x52, 0x0C, 0x8B, 0x0D
};

std::vector<int> chat_state_offset_signature =
{
    0x8B, 0x0D, -1, -1, -1, -1, 0x6A, 0x00, 0x6A, 0x01, 0xC6, 0x41, 0x20, 0x00, 0xE8, -1,
    -1, -1, -1, 0x6A, 0x08, 0x8D, 0x8D, 0x60, 0xFF, 0xFF, 0xFF, 0xC7, 0x85, 0x60, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xC7, 0x85, 0x64, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x85, 0x68, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x45, 0xF0, 0x01
};

HANDLE process_handle = 0;
int process_id = 0;
MODULEENTRY32W process_module;
UINT32 module_address = 0;

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
    //ReadProcessMemory(process_handle, module_address, buffer);
    //ReadProcessMemory(process.Handle, moduleAddress, buffer, moduleSize, out _);

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

int main()
{
    SetConsoleTitle(L"Offsets finder");
    get_process_id(L"Trove.exe");
    while (process_id == 0)
    {
        printf("process not found\n");
        Sleep(1000);
        get_process_id(L"Trove.exe");
    }
    printf("process found: %X (%i)\n\n", process_id, process_id);
    get_process_module(L"Trove.exe");
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);

    UINT32 local_player_offset, world_offset, settings_offset, chat_state_offset;

    UINT32 address = find_signature_address(player_offset_signature) + player_offset_signature.size();
    address = read_int(address);
    local_player_offset = address - module_address;

    address = find_signature_address(world_offset_signature) + 10;
    address = read_int(address);
    world_offset = address - module_address;

    address = find_signature_address(settings_offset_signature) + settings_offset_signature.size();
    address = read_int(address);
    settings_offset = address - module_address;

    address = find_signature_address(chat_state_offset_signature) + 2;
    address = read_int(address);
    chat_state_offset = address - module_address;

    printf("Local Player offset: %X\nWorld offset: %X\nSettings offset: %X\nChat State offset: %X\n", local_player_offset, world_offset, settings_offset, chat_state_offset);

    getchar();
    return 0;
}