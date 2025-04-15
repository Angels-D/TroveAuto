/* Module
 *    -> Auther: Angels-D
 *
 * LastChange
 *    -> 2025/04/16 04:40
 *    -> 1.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o Module.dll -x c++ ./libs/Module.hpp
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

#define DLL_EXPORT __declspec(dllexport)

#include <map>
#include <queue>
#include <unordered_set>

// #include "WindowInput.hpp"
#include "Game.hpp"

// Module.h

namespace Module
{
    struct Feature
    {
        Memory::Offsets offsets;
        std::vector<BYTE> dataOn, dataOff;
        Game::Signature signature;
        std::vector<BYTE> dataIn;
        static Feature hideAnimation;
        static Feature autoAttack;
        static Feature breakBlocks;
        static Feature byPass;
        static Feature clipCam;
        static Feature disMount;
        static Feature lockCam;
        static Feature unlockMapLimit;
        static Feature quickMining;
        static Feature quickMiningGeode;
        static Feature noGravity;
        static Feature noClip;
        static Feature unlockZoomLimit;
    };

    static uint32_t bossLevel = 4;
    static uint32_t tpStep = 4;
    static uint32_t mapWidth = 4300;
    static uint32_t entityScand = 100;
    static std::pair<float, float> aimOffset = {1.25, 0.25};

    static std::map<std::string, void *> configMap =
        {{"Module::bossLevel", &Module::bossLevel},
         {"Module::tpStep", &Module::tpStep},
         {"Module::mapWidth", &Module::mapWidth},
         {"Module::entityScand", &Module::entityScand},
         {"Module::aimOffset", &Module::aimOffset},
         {"Module::Feature::hideAnimation", &Module::Feature::hideAnimation},
         {"Module::Feature::autoAttack", &Module::Feature::autoAttack},
         {"Module::Feature::breakBlocks", &Module::Feature::breakBlocks},
         {"Module::Feature::byPass", &Module::Feature::byPass},
         {"Module::Feature::clipCam", &Module::Feature::clipCam},
         {"Module::Feature::disMount", &Module::Feature::disMount},
         {"Module::Feature::lockCam", &Module::Feature::lockCam},
         {"Module::Feature::unlockMapLimit", &Module::Feature::unlockMapLimit},
         {"Module::Feature::quickMining", &Module::Feature::quickMining},
         {"Module::Feature::quickMiningGeode", &Module::Feature::quickMiningGeode},
         {"Module::Feature::noGravity", &Module::Feature::noGravity},
         {"Module::Feature::noClip", &Module::Feature::noClip},
         {"Module::Feature::unlockZoomLimit", &Module::Feature::unlockZoomLimit},
         {"Game::moduleName", &Game::moduleName},
         {"Game::World::signature", &Game::World::signature},
         {"Game::World::offsets", &Game::World::offsets},
         {"Game::World::Data::playerCountOffsets", &Game::World::Data::playerCountOffsets},
         {"Game::World::NodeInfo::offsets", &Game::World::NodeInfo::offsets},
         {"Game::World::NodeInfo::Data::baseAddressOffsets", &Game::World::NodeInfo::Data::baseAddressOffsets},
         {"Game::World::NodeInfo::Data::stepOffsets", &Game::World::NodeInfo::Data::stepOffsets},
         {"Game::World::NodeInfo::Data::sizeOffsets", &Game::World::NodeInfo::Data::sizeOffsets},
         {"Game::World::Entity::offsets", &Game::World::Entity::offsets},
         {"Game::World::Entity::Data::levelOffsets", &Game::World::Entity::Data::levelOffsets},
         {"Game::World::Entity::Data::nameOffsets", &Game::World::Entity::Data::nameOffsets},
         {"Game::World::Entity::Data::isDeathOffsets", &Game::World::Entity::Data::isDeathOffsets},
         {"Game::World::Entity::Data::healthOffsets", &Game::World::Entity::Data::healthOffsets},
         {"Game::World::Entity::Data::xOffsets", &Game::World::Entity::Data::xOffsets},
         {"Game::World::Entity::Data::yOffsets", &Game::World::Entity::Data::yOffsets},
         {"Game::World::Entity::Data::zOffsets", &Game::World::Entity::Data::zOffsets},
         {"Game::World::Player::offsets", &Game::World::Player::offsets},
         {"Game::World::Player::Data::nameOffsets", &Game::World::Player::Data::nameOffsets},
         {"Game::World::Player::Data::xOffsets", &Game::World::Player::Data::xOffsets},
         {"Game::World::Player::Data::yOffsets", &Game::World::Player::Data::yOffsets},
         {"Game::World::Player::Data::zOffsets", &Game::World::Player::Data::zOffsets},
         {"Game::Player::signature", &Game::Player::signature},
         {"Game::Player::offsets", &Game::Player::offsets},
         {"Game::Player::Data::itemRSignature", &Game::Player::Data::itemRSignature},
         {"Game::Player::Data::itemTSignature", &Game::Player::Data::itemTSignature},
         {"Game::Player::Data::nameOffsets", &Game::Player::Data::nameOffsets},
         {"Game::Player::Data::healthOffsets", &Game::Player::Data::healthOffsets},
         {"Game::Player::Data::itemROffsets", &Game::Player::Data::itemROffsets},
         {"Game::Player::Data::itemTOffsets", &Game::Player::Data::itemTOffsets},
         {"Game::Player::Camera::offsets", &Game::Player::Camera::offsets},
         {"Game::Player::Camera::Data::xPerOffsets", &Game::Player::Camera::Data::xPerOffsets},
         {"Game::Player::Camera::Data::yPerOffsets", &Game::Player::Camera::Data::yPerOffsets},
         {"Game::Player::Camera::Data::zPerOffsets", &Game::Player::Camera::Data::zPerOffsets},
         {"Game::Player::Camera::Data::vOffsets", &Game::Player::Camera::Data::vOffsets},
         {"Game::Player::Camera::Data::hOffsets", &Game::Player::Camera::Data::hOffsets},
         {"Game::Player::Coord::offsets", &Game::Player::Coord::offsets},
         {"Game::Player::Coord::Data::xOffsets", &Game::Player::Coord::Data::xOffsets},
         {"Game::Player::Coord::Data::yOffsets", &Game::Player::Coord::Data::yOffsets},
         {"Game::Player::Coord::Data::zOffsets", &Game::Player::Coord::Data::zOffsets},
         {"Game::Player::Coord::Data::xVelOffsets", &Game::Player::Coord::Data::xVelOffsets},
         {"Game::Player::Coord::Data::yVelOffsets", &Game::Player::Coord::Data::yVelOffsets},
         {"Game::Player::Coord::Data::zVelOffsets", &Game::Player::Coord::Data::zVelOffsets},
         {"Game::Player::Fish::signature", &Game::Player::Fish::signature},
         {"Game::Player::Fish::offsets", &Game::Player::Fish::offsets},
         {"Game::Player::Fish::Data::waterTakeOffsets", &Game::Player::Fish::Data::waterTakeOffsets},
         {"Game::Player::Fish::Data::lavaTakeOffsets", &Game::Player::Fish::Data::lavaTakeOffsets},
         {"Game::Player::Fish::Data::chocoTakeOffsets", &Game::Player::Fish::Data::chocoTakeOffsets},
         {"Game::Player::Fish::Data::plasmaTakeOffsets", &Game::Player::Fish::Data::plasmaTakeOffsets},
         {"Game::Player::Fish::Data::waterStatusOffsets", &Game::Player::Fish::Data::waterStatusOffsets},
         {"Game::Player::Fish::Data::lavaStatusOffsets", &Game::Player::Fish::Data::lavaStatusOffsets},
         {"Game::Player::Fish::Data::chocoStatusOffsets", &Game::Player::Fish::Data::chocoStatusOffsets},
         {"Game::Player::Fish::Data::plasmaStatusOffsets", &Game::Player::Fish::Data::plasmaStatusOffsets},
         {"Game::Player::Bag::offset", &Game::Player::Bag::offsets}};

    static std::map<std::pair<int, std::string>, std::atomic<bool>> functionRunMap;

    void SetFeature(const Feature &feature, const Memory::DWORD &pid, const bool &on = true);
    void SetNoClip(const Feature &feature, const Memory::DWORD &pid, const bool &on = true);
    void SetAutoAttack(const Memory::DWORD &pid, const uint32_t &keep = 300, const uint32_t &delay = 1000);
    void SetAutoRespawn(const Memory::DWORD &pid, const uint32_t &delay = 50);

    void AutoAim(const Memory::DWORD &pid, const bool &targetBoss = true, const bool &targetPlant = false, const bool &targetNormal = false, const std::vector<std::string> &targets = {}, const std::vector<std::string> &noTargets = {}, const uint32_t &range = 45, const uint32_t &delay = 50);
    void SpeedUp(const Memory::DWORD &pid, const float &speed = 50, const uint32_t &delay = 50, const std::vector<std::string> &hotKey = {"W", "A", "S", "D", "Space", "Shift"});

    void Tp2Forward(const Memory::DWORD &pid, const float &tpRange = tpStep, const uint32_t &delay = 50);
    void Tp2Target(const Memory::DWORD &pid, const float &targetX, const float &targetY, const float &targetZ, const uint32_t &delay = 50, const uint32_t &tryAgainMax = 10);
    void FollowTarget(const Memory::DWORD &pid, const std::vector<std::string> &players = {}, const std::vector<std::string> &targets = {}, const std::vector<std::string> &noTargets = {}, const bool &targetBoss = false, const bool &scanAll = false, const float &speed = 50, const uint32_t &delay = 50);

    std::unique_ptr<Game::World::Player> FindPlayer(Game &game, const std::vector<std::string> &targets);
    std::unique_ptr<Game::World::Entity> FindTarget(Game &game, const bool &targetBoss = true, const bool &targetPlant = false, const bool &targetNormal = false, const std::vector<std::string> &targets = {}, const std::vector<std::string> &noTargets = {}, const uint32_t &range = 45);

    void GetNextPoint(float &x, float &z, std::unordered_set<std::string> &visitedPoints);
};

extern "C"
{
    DLL_EXPORT void UpdateConfig(const char *key, const char *value);
    DLL_EXPORT void FunctionOn(const Memory::DWORD pid, const char *funtion, const char *argv = "", const bool waiting = false);
    DLL_EXPORT void FunctionOff(const Memory::DWORD pid, const char *funtion = nullptr);

    DLL_EXPORT void WhichTarget(const Memory::DWORD pid, char *result, const uint32_t size, const char *argv = "");
}

// Module.cpp

#include <chrono>
#include <thread>
#include <cmath>
#include <random>

float CalculateDistance(const float &ax, const float &ay, const float &az, const float &bx, const float &by, const float &bz)
{
    float dx = ax - bx;
    float dy = ay - by;
    float dz = az - bz;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : str)
        if (ch == delimiter)
        {
            if (!token.empty())
            {
                tokens.emplace_back(token);
                token.clear();
            }
        }
        else
            token += ch;
    if (!token.empty())
        tokens.emplace_back(token);
    return tokens;
}

std::pair<float, float> CalculateAngles(const float &ax, const float &ay, const float &az, const float &bx, const float &by, const float &bz)
{
    float dx = bx - ax;
    float dy = ay - by;
    float dz = bz - az;

    // 计算水平角h
    float ah = std::atan2(dx, dz); // 参数顺序为Δx（东向分量）, Δz（南向分量）

    // 计算俯仰角v
    float horizontal_dist = std::sqrt(dx * dx + dz * dz);
    float av = std::atan2(dy, horizontal_dist);
    return {ah, av};
}

namespace Module
{
    Feature Feature::hideAnimation = {
        {0x74AB35},
        {0x4C},
        {0x44},
        {0x3, "F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50"}};
    Feature Feature::autoAttack = {
        {0x84E198},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 1F"}};
    Feature Feature::breakBlocks = {
        {0x9E9683},
        {0x01},
        {0x00},
        {0x3, "80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18"}};
    Feature Feature::byPass = {
        {0x193716},
        {0x47},
        {0x67},
        {0x1, "DC 67 68 C6"}};
    Feature Feature::clipCam = {
        {0x9354EA},
        {0x90, 0x90, 0x90},
        {0x0F, 0x29, 0x01},
        {0x0, "0F 29 01 C7 41 34 00 00 00 00 0F"}};
    Feature Feature::disMount = {
        {0x384ADE},
        {0xEB},
        {0x74},
        {0x0, "74 XX 8B 07 8B CF 6A 00 6A 00 FF 50"}};
    Feature Feature::lockCam = {
        {0x8D4B95},
        {0xEB},
        {0x74},
        {0x0, "74 05 8B 01 FF 50 0C 8B E5"}};
    Feature Feature::unlockMapLimit = {
        {0xAE09FD},
        {0xEB},
        {0x77},
        {0x0, "77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89"}};
    Feature Feature::quickMining = {
        {0x9E6768},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 61"}};
    Feature Feature::quickMiningGeode = {
        {0xAB25B7},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 35 8D"}};
    Feature Feature::noGravity = {
        {0xEDE158, 0xC},
        {0x42, 0xC8},
        {0x0, 0x0},
        {-0x4, "F3 0F 11 45 FC D9 45 FC 8B E5 5D C3 D9 05 XX XX XX XX 8B E5 5D C3 D9 05 XX XX XX XX 8B E5 5D C3"}};
    /*
        code:
            pop eax
            add esp,8
            push eax
            mov eax,[ebx+14]

            push ebx
            push ecx
            sub esp, 10*3
            movdqu [esp+20], xmm0
            movdqu [esp+10], xmm1
            movdqu [esp], xmm2

            mov ebx, [Trove.exe+108BD70]
            mov ecx, 0

        offsetLoop:
            add ebx, dword ptr [offsetArray+ecx*4]
            mov ebx, [ebx]
            cmp ebx, 0
            je return
            inc ecx
            cmp ecx, 4
            jl offsetLoop

            movups xmm0, [ebx+80]

            movaps xmm1, xmm0
            cmpps xmm1, xmm4, 2
            movaps xmm2, xmm5
            cmpps xmm2, xmm0, 2
            pand xmm1, xmm2

            movmskps ecx, xmm1
            and ecx, 7
            cmp ecx, 7
            jne return

            mov byte ptr [eax+1], 0

        return:
            movdqu xmm2, [esp]
            movdqu xmm1, [esp+10]
            movdqu xmm0, [esp+20]
            add esp, 10*3
            pop ecx
            pop ebx
            ret
        offsetArray:
            dd 00 28 E8 04
     */
    Feature Feature::noClip = {
        {0x640062},
        {0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0x90},
        {0x8B, 0x43, 0x14, 0x83, 0xC4, 0x8},
        {-0x5A3, "74 31 FF 73 14 8B 47 04 2B 07"},
        {0x58, 0x83, 0xC4, 0x08, 0x50, 0x8B, 0x43, 0x14, 0x53, 0x51, 0x83, 0xEC, 0x30, 0xF3, 0x0F, 0x7F, 0x44, 0x24, 0x20, 0xF3, 0x0F, 0x7F, 0x4C, 0x24, 0x10, 0xF3, 0x0F, 0x7F, 0x14, 0x24, 0xBB, 0xE0, 0xE6, 0x30, 0x1D, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1C, 0x8D, 0xFF, 0xFF, 0xFF, 0xFF, 0x8B, 0x1B, 0x83, 0xFB, 0x00, 0x0F, 0x84, 0x32, 0x00, 0x00, 0x00, 0x41, 0x83, 0xF9, 0x04, 0x7C, 0xE8, 0x0F, 0x10, 0x83, 0x80, 0x00, 0x00, 0x00, 0x0F, 0x28, 0xC8, 0x0F, 0xC2, 0xCC, 0x02, 0x0F, 0x28, 0xD5, 0x0F, 0xC2, 0xD0, 0x02, 0x66, 0x0F, 0xDB, 0xCA, 0x0F, 0x50, 0xC9, 0x83, 0xE1, 0x07, 0x83, 0xF9, 0x07, 0x0F, 0x85, 0x04, 0x00, 0x00, 0x00, 0xC6, 0x40, 0x01, 0x00, 0xF3, 0x0F, 0x6F, 0x14, 0x24, 0xF3, 0x0F, 0x6F, 0x4C, 0x24, 0x10, 0xF3, 0x0F, 0x6F, 0x44, 0x24, 0x20, 0x83, 0xC4, 0x30, 0x59, 0x5B, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00}};
    Feature Feature::unlockZoomLimit = {
        {0x933466},
        {0x57},
        {0x5F},
        {0x3, "F3 0F 11 5F 2C"}};

    void SetFeature(const Feature &feature, const Memory::DWORD &pid, const bool &on)
    {
        Game game(pid);
        game.UpdateAddress();
        const Memory::Address address = game.GetAddress(game.baseAddress, feature.offsets);
        game.WriteMemory(on ? feature.dataOn : feature.dataOff, address);
    }

    void SetNoClip(const Feature &feature, const Memory::DWORD &pid, const bool &on)
    {
        Game game(pid);
        game.UpdateAddress();
        const Memory::Address address = game.GetAddress(game.baseAddress, feature.offsets);
        Memory::Address inAddress;
        memcpy(&inAddress, feature.dataOn.data() + 0x1, sizeof(Memory::Address));
        inAddress += address + 5;
        if (inAddress != 0x0 && inAddress != 0xFFFFFFFF)
            game.FreeMemory(0, MEM_RELEASE, inAddress);
        if (on)
        {
            DWORD temp;
            memcpy((void *)(feature.dataIn.data() + 0x1F), &game.data.player.UpdateAddress().address, sizeof(Memory::Address));
            inAddress = game.AllocMemory(feature.dataIn.size(), MEM_COMMIT, PAGE_READWRITE);
            temp = inAddress + 0x83;
            memcpy((void *)(feature.dataIn.data() + 0x2B), &temp, sizeof(Memory::Address));
            temp = inAddress - address - 5;
            memcpy((void *)(feature.dataOn.data() + 0x1), &temp, sizeof(Memory::Address));
            game.WriteMemory(feature.dataIn, inAddress);
            VirtualProtectEx(game.hProcess, reinterpret_cast<LPVOID>(inAddress), feature.dataIn.size(), PAGE_EXECUTE, &temp);
        }
        game.WriteMemory(on ? feature.dataOn : feature.dataOff, address);
    }

    void SetAutoAttack(const Memory::DWORD &pid, const uint32_t &keep, const uint32_t &delay)
    {
        while (functionRunMap[{pid, "SetAutoAttack"}].load())
        {
            SetFeature(Feature::autoAttack, pid, true);
            std::this_thread::sleep_for(std::chrono::milliseconds(keep));
            SetFeature(Feature::autoAttack, pid, false);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    void SetAutoRespawn(const Memory::DWORD &pid, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        while (functionRunMap[{pid, "AutoAim"}].load() &&
               game.data.player.data.health.UpdateAddress().UpdateData().data == 0)
        {
            // 未完工
            // 复活: 模拟按键 E
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    void AutoAim(const Memory::DWORD &pid, const bool &targetBoss, const bool &targetPlant, const bool &targetNormal, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const uint32_t &range, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        std::unique_ptr<Game::World::Entity> target = nullptr;
        auto UpdateAddress = [&game]()
        {
            game.data.player.data.coord.UpdateAddress();
            game.data.player.data.camera.UpdateAddress();
            game.data.player.data.coord.data.x.UpdateAddress();
            game.data.player.data.coord.data.y.UpdateAddress();
            game.data.player.data.coord.data.z.UpdateAddress();
            game.data.player.data.camera.data.v.UpdateAddress();
            game.data.player.data.camera.data.h.UpdateAddress();
        };
        while (functionRunMap[{pid, "AutoAim"}].load())
        {
            uint32_t step = 0;
            UpdateAddress();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            target = FindTarget(game, targetBoss, targetPlant, targetNormal, targets, noTargets, range);
            if (!target)
                continue;
            while (functionRunMap[{pid, "AutoAim"}].load() &&
                   CalculateDistance(
                       game.data.player.data.coord.data.x.UpdateData().data,
                       game.data.player.data.coord.data.y.UpdateData().data + aimOffset.first,
                       game.data.player.data.coord.data.z.UpdateData().data,
                       target->data.x.UpdateData().data,
                       target->data.y.UpdateData().data + aimOffset.second,
                       target->data.z.UpdateData().data) <= range &&
                   target->data.isDeath.UpdateData().data)
            {
                UpdateAddress();
                auto vh = CalculateAngles(
                    game.data.player.data.coord.data.x.data,
                    game.data.player.data.coord.data.y.data,
                    game.data.player.data.coord.data.z.data,
                    target->data.x.data,
                    target->data.y.data,
                    target->data.z.data);
                game.data.player.data.camera.data.v = vh.first;
                game.data.player.data.camera.data.h = vh.second;
                if (((step = (step + 1) % 100) == 0) ||
                    target->data.health.UpdateData().data < 1 ||
                    (target->data.x.data < 1 && target->data.y.data < 1 && target->data.z.data < 1))
                {
                    const auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
                    if (std::find(entitys.begin(), entitys.end(), *target) == entitys.end())
                        break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
        }
    }

    void SpeedUp(const Memory::DWORD &pid, const float &speed, const uint32_t &delay, const std::vector<std::string> &hotKey)
    {
        // Game game(pid);
        // game.UpdateAddress().data.player.UpdateAddress();
        // float xVel = 0, yVel = 0, zVel = 0;
        // float xPer = 0, zPer = 0;
        // float hrzMagnitude = 0, xMagnitude = 0, zMagnitude = 0;
        // while (functionRunMap[{pid, "SpeedUp"}].load())
        // {
        //     game.data.player.data.coord.UpdateAddress();
        //     game.data.player.data.camera.UpdateAddress();
        //     xVel = yVel = zVel = 0;
        //     xPer = game.data.player.data.camera.data.xPer.UpdateAddress().UpdateData().data;
        //     zPer = game.data.player.data.camera.data.zPer.UpdateAddress().UpdateData().data;
        //     hrzMagnitude = std::sqrt(xPer * xPer + zPer * zPer);
        //     xMagnitude = xPer / hrzMagnitude;
        //     zMagnitude = zPer / hrzMagnitude;
        //     // 未完工, 按键触发
        //     // if()
        //     // {
        //     //     xVel += xMagnitude * speed;
        //     //     zVel += zMagnitude * speed;
        //     // }
        //     // if()
        //     // {
        //     //     xVel += zMagnitude * speed;
        //     //     zVel -= xMagnitude * speed;
        //     // }
        //     // if()
        //     // {
        //     //     xVel -= xMagnitude * speed;
        //     //     zVel -= zMagnitude * speed;
        //     // }
        //     // if()
        //     // {
        //     //     xVel -= zMagnitude * speed;
        //     //     zVel += xMagnitude * speed;
        //     // }
        //     // if()
        //     //     yVel += speed;
        //     // if()
        //     //     yVel -= speed;
        //     game.data.player.data.coord.data.xVel.UpdateAddress() = xVel;
        //     game.data.player.data.coord.data.yVel.UpdateAddress() = yVel;
        //     game.data.player.data.coord.data.zVel.UpdateAddress() = zVel;
        //     std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        // }
    }

    void Tp2Forward(const Memory::DWORD &pid, const float &tpRange, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        game.data.player.data.coord.UpdateAddress();
        game.data.player.data.camera.UpdateAddress();
        Tp2Target(
            pid,
            game.data.player.data.coord.data.x.UpdateAddress().UpdateData().data +
                game.data.player.data.camera.data.xPer.UpdateAddress().UpdateData().data * tpRange,
            game.data.player.data.coord.data.y.UpdateAddress().UpdateData().data +
                game.data.player.data.camera.data.yPer.UpdateAddress().UpdateData().data * tpRange,
            game.data.player.data.coord.data.z.UpdateAddress().UpdateData().data +
                game.data.player.data.camera.data.zPer.UpdateAddress().UpdateData().data * tpRange,
            delay);
    }

    void Tp2Target(const Memory::DWORD &pid, const float &targetX, const float &targetY, const float &targetZ, const uint32_t &delay, const uint32_t &tryAgainMax)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        uint32_t tryAgain = 0;
        float dist = 0, lastDist = 0, x = 0, y = 0, z = 0;
        do
        {
            game.data.player.data.coord.UpdateAddress();
            x = game.data.player.data.coord.data.x.UpdateAddress().UpdateData().data;
            y = game.data.player.data.coord.data.y.UpdateAddress().UpdateData().data;
            z = game.data.player.data.coord.data.z.UpdateAddress().UpdateData().data;
            dist = CalculateDistance(x, y, z, targetX, targetY, targetZ);
            tryAgain += dist >= lastDist || dist <= tpStep;
            game.data.player.data.coord.data.x = (dist > tpStep ? x + (targetX - x) / dist * tpStep : targetX);
            game.data.player.data.coord.data.y = (dist > tpStep ? y + (targetY - y) / dist * tpStep : targetY);
            game.data.player.data.coord.data.z = (dist > tpStep ? z + (targetZ - z) / dist * tpStep : targetZ);
            lastDist = dist;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        } while (tryAgain < tryAgainMax && dist > tpStep);
    }

    void FollowTarget(const Memory::DWORD &pid, const std::vector<std::string> &players, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const bool &targetBoss, const bool &scanAll, const float &speed, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        auto UpdateAddress = [&game]()
        {
            game.data.player.data.coord.UpdateAddress();
            game.data.player.data.coord.data.x.UpdateAddress();
            game.data.player.data.coord.data.y.UpdateAddress();
            game.data.player.data.coord.data.z.UpdateAddress();
        };
        float x = 0, y = 0, z = 0, targetX = 0;
        float targetY = 0, targetZ = 0, dist = 0, lastDist = 9999;
        uint32_t step = 0;
        auto MoveEvent = [&game, &x, &y, &z, &dist, &lastDist, &step, &delay, &speed](
                             const float &targetX, float targetY, const float &targetZ)
        {
            x = game.data.player.data.coord.data.x.UpdateData().data;
            y = game.data.player.data.coord.data.y.UpdateData().data;
            z = game.data.player.data.coord.data.z.UpdateData().data;
            game.data.player.data.coord.data.xVel.UpdateAddress() = 0;
            game.data.player.data.coord.data.yVel.UpdateAddress() = 0;
            game.data.player.data.coord.data.zVel.UpdateAddress() = 0;
            if ((dist = CalculateDistance(x, y, z, targetX, targetY, targetZ)) <= 1 || std::isnan(dist))
                return;
            if (step % (250 / delay) == 0)
                lastDist = dist;
            step = (step + 1) % (1000 / delay);
            if (step % (500 / delay) == 0 && tpStep && abs(lastDist - dist) < tpStep)
                Tp2Target(game.pid, targetX, targetY, targetZ, delay, abs(lastDist - dist) < 1 ? 10 : 1);
            else
            {
                game.data.player.data.coord.data.xVel.UpdateAddress() = (targetX - x) / dist * speed;
                game.data.player.data.coord.data.yVel.UpdateAddress() = (targetY - y) / dist * speed;
                game.data.player.data.coord.data.zVel.UpdateAddress() = (targetZ - z) / dist * speed;
            }
        };
        std::unordered_set<std::string> visitedPoints;
        while (functionRunMap[{pid, "FollowTarget"}].load())
        {
            std::unique_ptr<Game::World::Player> player = nullptr;
            std::unique_ptr<Game::World::Entity> target = nullptr;
            UpdateAddress();
            if (scanAll)
            {
                step = dist = 0;
                lastDist = 9999;
                GetNextPoint(
                    targetX = game.data.player.data.coord.data.x.UpdateData().data,
                    targetZ = game.data.player.data.coord.data.z.UpdateData().data, visitedPoints);
                targetY = game.data.player.data.coord.data.y.UpdateData().data;
            }
            do
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                UpdateAddress();
                if (scanAll)
                    MoveEvent(targetX, targetY = (std::max)(targetY, game.data.player.data.coord.data.y.UpdateData().data), targetZ);
                player = FindPlayer(game, players);
                target = FindTarget(game, targetBoss, false, false, targets, noTargets, 9999);
            } while (!player && !target && scanAll &&
                     dist > 1 && functionRunMap[{pid, "FollowTarget"}].load());
            if (!player && !target)
                continue;
            step = dist = 0;
            lastDist = 9999;
            while (functionRunMap[{pid, "FollowTarget"}].load())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                if (player && !(player = FindPlayer(game, players)))
                    break;
                targetX = player ? player->data.x.UpdateAddress().UpdateData().data : target->data.x.UpdateData().data;
                targetY = (player ? player->data.y.UpdateAddress().UpdateData().data : target->data.y.UpdateData().data) - 0.5;
                targetZ = player ? player->data.z.UpdateAddress().UpdateData().data : target->data.z.UpdateData().data;
                if (target)
                {
                    if (!target->data.isDeath.UpdateData().data)
                        break;
                    if ((step % 100) == 0 ||
                        target->data.health.UpdateData().data < 1 ||
                        (targetX < 1 && targetY < 1 && targetZ < 1))
                    {
                        const auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
                        if (std::find(entitys.begin(), entitys.end(), *target) == entitys.end())
                            break;
                    }
                }
                UpdateAddress();
                MoveEvent(targetX, targetY, targetZ);
            }
        }
    }

    std::unique_ptr<Game::World::Player> FindPlayer(Game &game, const std::vector<std::string> &targets)
    {
        auto &players = game.data.world.UpdateAddress().UpdateData().data.players;
        std::vector<std::regex> targetRegexs;
        for (auto target : targets)
            targetRegexs.emplace_back(target);
        for (auto &player : players)
        {
            auto name = player.UpdateAddress().data.name.UpdateAddress().UpdateData(64).data;
            for (auto targetRegex : targetRegexs)
                if (std::regex_match(name, targetRegex))
                    return std::make_unique<Game::World::Player>(player);
        }
        return nullptr;
    }

    std::unique_ptr<Game::World::Entity> FindTarget(Game &game, const bool &targetBoss, const bool &targetPlant, const bool &targetNormal, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const uint32_t &range)
    {
        auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
        std::vector<std::regex> targetRegexs, noTargetRegexs;
        std::unique_ptr<Game::World::Entity> result = nullptr;
        float dist = 0, bestDist = 9999;
        uint32_t bestIndex = 0x7FFFFFFF;
        for (auto target : targets)
            targetRegexs.emplace_back(target);
        for (auto noTarget : noTargets)
            noTargetRegexs.emplace_back(noTarget);

        game.data.player.data.coord.data.x.UpdateData();
        game.data.player.data.coord.data.y.UpdateData();
        game.data.player.data.coord.data.z.UpdateData();

        for (auto &entity : entitys)
        {
            entity.UpdateAddress().UpdateData();
            if (entity.data.isDeath.UpdateData().data == 0)
                continue;
            if ((dist = CalculateDistance(
                     game.data.player.data.coord.data.x.data,
                     game.data.player.data.coord.data.y.data,
                     game.data.player.data.coord.data.z.data,
                     entity.data.x.UpdateData().data,
                     entity.data.y.UpdateData().data,
                     entity.data.z.UpdateData().data)) > range ||
                dist >= bestDist)
                continue;
            auto name = entity.data.name.UpdateData(128).data;
            size_t i = 0;
            while (i < noTargetRegexs.size() && !std::regex_match(name, noTargetRegexs[i]))
                i++;
            if (i < noTargetRegexs.size())
                continue;
            i = 0;
            while (i <= bestIndex && i < targetRegexs.size() && !std::regex_match(name, targetRegexs[i]))
                i++;
            if (i > bestIndex)
                continue;
            if (i < targetRegexs.size())
            {
                bestDist = dist;
                bestIndex = i;
                result = std::make_unique<Game::World::Entity>(entity);
                continue;
            }
            if (targetPlant && std::regex_match(name, std::regex(".*plant.*")))
            {
                bestDist = dist;
                bestIndex = i;
                result = std::make_unique<Game::World::Entity>(entity);
                continue;
            }
            if (std::regex_match(name, std::regex(".*npc.*")))
            {
                i++;
                if (i > bestIndex)
                    continue;
                if (targetBoss &&
                    (entity.data.level.UpdateData().data >= bossLevel ||
                     std::regex_match(name, std::regex(".*boss.*"))))
                {
                    bestDist = dist;
                    bestIndex = i;
                    result = std::make_unique<Game::World::Entity>(entity);
                    continue;
                }
                i++;
                if (i > bestIndex)
                    continue;
                if (targetNormal)
                {
                    bestDist = dist;
                    bestIndex = i;
                    result = std::make_unique<Game::World::Entity>(entity);
                    continue;
                }
            }
        }
        return result;
    }

    void GetNextPoint(float &x, float &z, std::unordered_set<std::string> &visitedPoints)
    {
        const float sqrt3 = std::sqrt(3);
        const float e = entityScand;
        const int R = static_cast<int>(mapWidth / (2 * e));
        auto alignToGrid = [&](float &x, float &z)
        {
            int j = static_cast<int>(std::round(z / (e * sqrt3)));
            int i = static_cast<int>(std::round((x - e * j) / (2 * e)));
            auto clampIndex = [&](int &i, int &j)
            {
                i = std::clamp(i, -R, R);
                j = std::clamp(j, -R, R);
                while (i * i + i * j + j * j > R * R)
                {
                    if (std::abs(i) > std::abs(j))
                        i > 0 ? i-- : i++;
                    else
                        j > 0 ? j-- : j++;
                }
            };
            clampIndex(i, j);
            x = e * (2 * i + j);
            z = e * sqrt3 * j;
        };
        auto getKey = [](float x, float z)
        {
            return std::to_string(static_cast<int>(std::round(x))) + "|" +
                   std::to_string(static_cast<int>(std::round(z)));
        };
        alignToGrid(x, z);
        if (visitedPoints.insert(getKey(x, z)).second)
            return;
        std::vector<std::pair<float, float>> directions = {
            {2 * e, 0}, {-2 * e, 0}, {e, e * sqrt3}, {-e, e * sqrt3}, {e, -e * sqrt3}, {-e, -e * sqrt3}};
        std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device{}()));
        std::queue<std::pair<float, float>> searchQueue;
        std::unordered_set<std::string> checkedPoints;
        searchQueue.push({x, z});
        checkedPoints.insert(getKey(x, z));
        while (!searchQueue.empty())
        {
            auto [currentX, currentZ] = searchQueue.front();
            searchQueue.pop();
            for (const auto &[dx, dz] : directions)
            {
                float newX = currentX + dx;
                float newZ = currentZ + dz;
                alignToGrid(newX, newZ);
                std::string key = getKey(newX, newZ);
                float dist = std::sqrt(newX * newX + newZ * newZ);
                if (dist > mapWidth)
                    continue;
                if (!checkedPoints.count(key))
                {
                    checkedPoints.insert(key);
                    if (!visitedPoints.count(key))
                    {
                        visitedPoints.insert(key);
                        x = newX;
                        z = newZ;
                        return;
                    }
                    searchQueue.push({newX, newZ});
                }
            }
        }
        visitedPoints.clear();
        visitedPoints.insert(getKey(x, z));
    }
}

void UpdateConfig(const char *key, const char *value)
{
    const std::string _key = key;
    const std::vector<std::string> _value = split(value, '|');
    if (_value.empty() ||
        Module::configMap.find(_key) == Module::configMap.end())
        return;
    if (_value.size() >= 1 &&
        (_key == "Module::bossLevel" ||
         _key == "Module::tpStep" ||
         _key == "Module::mapWidth" ||
         _key == "Module::entityScand"))
        Module::bossLevel = std::stoul(_value[0]);
    else if (_value.size() >= 2 &&
             _key == "Module::aimOffset")
        Module::aimOffset = {std::stof(_value[0]), std::stof(_value[1])};
    else if (_key.find("ffsets") != std::string::npos)
    {
        Memory::Offsets *offsets = (Memory::Offsets *)Module::configMap[_key];
        offsets->clear();
        for (auto offset : _value)
            offsets->push_back(std::stol(offset, nullptr, 16));
    }
    else if (_value.size() >= 2 &&
             _key.find("ignature") != std::string::npos)
    {
        Object<>::Signature *signature = (Object<>::Signature *)Module::configMap[_key];
        signature->first = std::stol(_value[0], nullptr, 16);
        signature->second = _value[1];
    }
    else if (_value.size() >= 4 &&
             _key.find("Module::Feature") != std::string::npos)
    {
        Module::Feature *feature = (Module::Feature *)Module::configMap[_key];
        if (_value[0] != "-")
        {
            feature->offsets.clear();
            for (auto offset : split(_value[0], ','))
                feature->offsets.emplace_back(std::stol(offset, nullptr, 16));
        }
        if (_value[1] != "-")
        {
            feature->dataOn.clear();
            for (auto dataOn : split(_value[1], ','))
                feature->dataOn.emplace_back(std::stoul(dataOn, nullptr, 16));
        }
        if (_value[2] != "-")
        {
            feature->dataOff.clear();
            for (auto dataOff : split(_value[2], ','))
                feature->dataOff.emplace_back(std::stoul(dataOff, nullptr, 16));
        }
        if (_value[3] != "-")
        {
            const auto signature = split(_value[3], ',');
            feature->signature.first = std::stol(signature[0], nullptr, 16);
            feature->signature.second = signature[1];
        }
    }
}

void FunctionOn(const Memory::DWORD pid, const char *funtion, const char *argv, const bool waiting)
{
    std::thread *thread = nullptr;
    const std::vector<std::string> _argv = split(argv, '|');
    Module::functionRunMap[{pid, funtion}].store(true);
    if (std::strcmp(funtion, "AutoAim") == 0)
        thread = new std::thread(
            Module::AutoAim, pid,
            std::stoul(_argv[0]),
            std::stoul(_argv[1]),
            std::stoul(_argv[2]),
            split(_argv[3], ','),
            split(_argv[4], ','),
            std::stoul(_argv[5]),
            std::stoul(_argv[6]));
    else if (std::strcmp(funtion, "SpeedUp") == 0)
        thread = new std::thread(
            Module::SpeedUp, pid,
            std::stof(_argv[0]),
            std::stoul(_argv[1]),
            split(_argv[2], ','));
    else if (std::strcmp(funtion, "Tp2Forward") == 0)
        thread = new std::thread(
            Module::Tp2Forward, pid,
            std::stof(_argv[0]),
            std::stoul(_argv[1]));
    else if (std::strcmp(funtion, "Tp2Target") == 0)
        thread = new std::thread(
            Module::Tp2Target, pid,
            std::stof(_argv[0]),
            std::stof(_argv[1]),
            std::stof(_argv[2]),
            std::stoul(_argv[3]),
            std::stoul(_argv[4]));
    else if (std::strcmp(funtion, "FollowTarget") == 0)
        thread = new std::thread(
            Module::FollowTarget, pid,
            split(_argv[0], ','),
            split(_argv[1], ','),
            split(_argv[2], ','),
            std::stoul(_argv[3]),
            std::stoul(_argv[4]),
            std::stof(_argv[5]),
            std::stoul(_argv[6]));
    else if (std::strcmp(funtion, "SetNoClip") == 0)
        thread = new std::thread(Module::SetNoClip, Module::Feature::noClip, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetAutoAttack") == 0)
        thread = new std::thread(Module::SetAutoAttack, pid, std::stoul(_argv[0]), std::stoul(_argv[1]));
    else if (std::strcmp(funtion, "SetAutoRespawn") == 0)
        thread = new std::thread(Module::SetAutoRespawn, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetHideAnimation") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::hideAnimation, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetBreakBlocks") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::breakBlocks, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetByPass") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::byPass, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetClipCam") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::clipCam, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetDisMount") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::disMount, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetLockCam") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::lockCam, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetUnlockMapLimit") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::unlockMapLimit, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetQuickMining") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::quickMining, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetQuickMiningGeode") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::quickMiningGeode, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetNoGravity") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::noGravity, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetUnlockZoomLimit") == 0)
        thread = new std::thread(Module::SetFeature, Module::Feature::unlockZoomLimit, pid, std::stoul(_argv[0]));
    if (thread && waiting)
    {
        thread->join();
        Module::functionRunMap[{pid, funtion}].store(false);
    }
}

void FunctionOff(const Memory::DWORD pid, const char *funtion)
{
    if (funtion == nullptr)
        for (auto &runThread : Module::functionRunMap)
            runThread.second.store(false);
    else
        Module::functionRunMap[{pid, funtion}].store(false);
}

void WhichTarget(const Memory::DWORD pid, char *result, const uint32_t size, const char *argv)
{
    Game game(pid);
    game.UpdateAddress().data.player.UpdateAddress().data.coord.UpdateAddress();
    game.data.player.data.coord.data.x.UpdateAddress();
    game.data.player.data.coord.data.y.UpdateAddress();
    game.data.player.data.coord.data.z.UpdateAddress();
    const std::vector<std::string> _argv = split(argv, '|');
    auto target = Module::FindTarget(
        game,
        std::stoul(_argv[0]),
        std::stoul(_argv[1]),
        std::stoul(_argv[2]),
        split(_argv[3], ','),
        split(_argv[4], ','),
        std::stoul(_argv[5]));
    if (target == nullptr)
        result[0] = '\0';
    else
    {
        auto vh = CalculateAngles(
            game.data.player.data.coord.data.x.data,
            game.data.player.data.coord.data.y.data,
            game.data.player.data.coord.data.z.data,
            target->data.x.data,
            target->data.y.data,
            target->data.z.data);

        game.data.player.data.camera.UpdateAddress();
        game.data.player.data.camera.data.v.UpdateAddress() = vh.first;
        game.data.player.data.camera.data.h.UpdateAddress() = vh.second;

        char buffer[1024] = "";
        sprintf(buffer, "%s,%d,%.3f,%.1f,%.1f,%.1f,%.1f",
                target->data.name.UpdateData(128).data.c_str(),
                std::clamp(target->data.level.UpdateData().data, 0u, 99u),
                std::clamp(target->data.health.UpdateData().data, 0.0, 999999999999999.0),
                CalculateDistance(game.data.player.data.coord.data.x.data,
                                  game.data.player.data.coord.data.y.data,
                                  game.data.player.data.coord.data.z.data,
                                  target->data.x.data,
                                  target->data.y.data,
                                  target->data.z.data),
                target->data.x.data,
                target->data.y.data,
                target->data.z.data);
        std::memcpy(result, buffer, std::min<uint32_t>(size, strlen(buffer)));
    }
}

#endif