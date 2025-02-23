/* Module
 *    -> Auther: Angels-D
 *
 * LastChange
 *    -> 2025/02/23 16:45
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

#define DLL_EXPORT __declspec(dllexport)

#include <map>
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
    };

    static uint32_t bossLevel = 4;
    static uint32_t tpStep = 4;
    static std::pair<float, float> aimOffset = {1.25, 0.25};

    static Feature hideAnimation = {
        {0x741BC5},
        {0x4C},
        {0x44},
        {0x3, "F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50"}};
    static Feature autoAttack = {
        {0x9B14A8},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 1F"}};
    static Feature breakBlocks = {
        {0xB237E3},
        {0x01},
        {0x00},
        {0x3, "80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18"}};
    static Feature byPass = {
        {0x187A16},
        {0x47},
        {0x67},
        {0x1, "DC 67 68 C6"}};
    static Feature clipCam = {
        {0xADA36A},
        {0x90, 0x90, 0x90},
        {0x0F, 0x29, 0x01},
        {0x0, "0F 29 01 C7 41 34 00 00 00 00 0F"}};
    static Feature disMount = {
        {0x375E2E},
        {0xEB},
        {0x74},
        {0x0, "74 XX 8B 07 8B CF 6A 00 6A 00 FF 50"}};
    static Feature lockCam = {
        {0x80AF25},
        {0xEB},
        {0x74},
        {0x0, "74 05 8B 01 FF 50 0C 8B E5"}};
    static Feature locakMapLimit = {
        {0x89E15D},
        {0xEB},
        {0x77},
        {0x0, "77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89"}};
    static Feature quickMining = {
        {0xB08D98},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 61"}};
    static Feature quickMiningGeode = {
        {0x90E6F7},
        {0xF0},
        {0xF1},
        {0x1, "DF F1 DD D8 72 35 8D"}};
    static Feature noGravity = {
        {0xA03168, 0xC},
        {0x42, 0xC8},
        {0x0, 0x0},
        {-0x4, "F3 0F 11 45 FC D9 45 FC 8B E5 5D C3 D9 05 XX XX XX XX 8B E5 5D C3 D9 05 XX XX XX XX 8B E5 5D C3"}};
    static Feature noClip = {
        {0x635A25},
        {0xEB},
        {0x74},
        {0x0, "74 31 FF 73 14 8B 47 04 2B 07"}};
    static Feature unlockZoomLimit = {
        {0xAD82E6},
        {0x57},
        {0x5F},
        {0x3, "F3 0F 11 5F 2C"}};

    static std::map<std::string, void *> configMap =
        {{"Module::bossLevel", &Module::bossLevel},
         {"Module::tpStep", &Module::tpStep},
         {"Module::aimOffset", &Module::aimOffset},
         {"Module::hideAnimation", &Module::hideAnimation},
         {"Module::autoAttack", &Module::autoAttack},
         {"Module::breakBlocks", &Module::breakBlocks},
         {"Module::byPass", &Module::byPass},
         {"Module::clipCam", &Module::clipCam},
         {"Module::disMount", &Module::disMount},
         {"Module::lockCam", &Module::lockCam},
         {"Module::locakMapLimit", &Module::locakMapLimit},
         {"Module::quickMining", &Module::quickMining},
         {"Module::quickMiningGeode", &Module::quickMiningGeode},
         {"Module::noGravity", &Module::noGravity},
         {"Module::noClip", &Module::noClip},
         {"Module::unlockZoomLimit", &Module::unlockZoomLimit},
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
         {"Game::Player::Data::nameSignature", &Game::Player::Data::nameSignature},
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

    static std::map<std::pair<int, std::string>, std::atomic<bool>> funtionRunMap;

    void SetFeature(const Feature &feature, const Memory::DWORD &pid, const bool &on = true);
    void SetAutoAttack(const Memory::DWORD &pid, const uint32_t &keep, const uint32_t &delay = 50);
    void SetAutoRespawn(const Memory::DWORD &pid, const uint32_t &delay = 50);

    void AutoAim(const Memory::DWORD &pid, const bool &targetBoss = true, const bool &targetPlant = false, const std::vector<std::string> &targets = {}, const std::vector<std::string> &noTargets = {}, const uint32_t &aimRange = 45, const uint32_t &showRange = 0, const uint32_t &delay = 50);
    void SpeedUp(const Memory::DWORD &pid, const float &speed = 50, const uint32_t &delay = 50, const std::vector<std::string> &hotKey = {"W", "A", "S", "D", "Space", "Shift"});

    void Tp2Forward(const Memory::DWORD &pid, const float &tpRange = tpStep, const uint32_t &delay = 50);
    float Tp2Target(const Memory::DWORD &pid, const float &targetX, const float &targetY, const float &targetZ, const uint32_t &delay = 50, const uint32_t &tryAgainMax = 10);
    void FollowTarget(const Memory::DWORD &pid, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets = {}, const float &speed = 50, const uint32_t &delay = 50);

    Game::World::Player *FindPlayer(Game &game, const std::vector<std::string> &targets);
    Game::World::Entity *FindTarget(Game &game, const bool &targetBoss = true, const bool &targetPlant = false, const std::vector<std::string> &targets = {}, const std::vector<std::string> &noTargets = {}, const uint32_t &aimRange = 45, const uint32_t &showRange = 0);

};

extern "C"
{
    DLL_EXPORT void UpdateConfig(const char *key, const char *value);
    DLL_EXPORT void FunctionOn(const Memory::DWORD pid, const char *funtion, const char *argv = "", const bool waiting = false);
    DLL_EXPORT void FunctionOff(const Memory::DWORD pid, const char *funtion);
}

// Module.cpp

#include <chrono>
#include <thread>
#include <cmath>

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
    void SetFeature(const Feature &feature, const Memory::DWORD &pid, const bool &on)
    {
        Game game(pid);
        game.UpdateAddress();
        const Memory::Address address = game.GetAddress(game.baseAddress, feature.offsets);
        for (size_t i = 0; i < feature.dataOn.size(); i++)
            game.WriteMemory<BYTE>(on ? feature.dataOn[i] : feature.dataOff[i],
                                   address + i * sizeof(BYTE));
    }

    void SetAutoAttack(const Memory::DWORD &pid, const uint32_t &keep, const uint32_t &delay)
    {
        while (funtionRunMap[{pid, "AutoAttack"}].load())
        {
            SetFeature(autoAttack, pid, true);
            std::this_thread::sleep_for(std::chrono::milliseconds(keep));
            SetFeature(autoAttack, pid, false);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    void SetAutoRespawn(const Memory::DWORD &pid, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        while (funtionRunMap[{pid, "AutoAim"}].load() &&
               game.data.player.data.health.UpdateAddress().UpdateData().data == 0)
        {
            // 未完工
            // 复活: 模拟按键 E
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    void AutoAim(const Memory::DWORD &pid, const bool &targetBoss, const bool &targetPlant, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const uint32_t &aimRange, const uint32_t &showRange, const uint32_t &delay)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        Game::World::Entity *target = nullptr;
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
        while (funtionRunMap[{pid, "AutoAim"}].load())
        {
            UpdateAddress();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            target = FindTarget(game, targetBoss, targetPlant, targets, noTargets, aimRange, showRange);
            if (!target)
                continue;
            while (funtionRunMap[{pid, "AutoAim"}].load() &&
                   CalculateDistance(
                       game.data.player.data.coord.data.x.UpdateData().data,
                       game.data.player.data.coord.data.y.UpdateData().data + aimOffset.first,
                       game.data.player.data.coord.data.z.UpdateData().data,
                       target->data.x.UpdateData().data,
                       target->data.y.UpdateData().data + aimOffset.second,
                       target->data.z.UpdateData().data) <= aimRange &&
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
                if (target->data.health.UpdateData().data < 1)
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
        // while (funtionRunMap[{pid, "SpeedUp"}].load())
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

    float Tp2Target(const Memory::DWORD &pid, const float &targetX, const float &targetY, const float &targetZ, const uint32_t &delay, const uint32_t &tryAgainMax)
    {
        Game game(pid);
        game.UpdateAddress().data.player.UpdateAddress();
        uint32_t tryAgain = 0;
        float dist = 0, lastDist = 0, x = 0, y = 0, z = 0;
        if (tryAgainMax)
            SetFeature(byPass, pid, true);
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
        if (tryAgainMax)
            SetFeature(byPass, pid, false);
        return dist;
    }

    void FollowTarget(const Memory::DWORD &pid, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const float &speed, const uint32_t &delay)
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
        while (funtionRunMap[{pid, "FollowTarget"}].load())
        {
            UpdateAddress();
            Game::World::Player *player = nullptr;
            Game::World::Entity *target = nullptr;
            float x = 0, y = 0, z = 0, targetX = 0;
            float targetY = 0, targetZ = 0, dist = 0, lastDist = 9999;
            uint32_t step = 0;
            player = FindPlayer(game, targets);
            if (!player)
                target = FindTarget(game, false, false, targets, noTargets, 9999, 0);
            SetFeature(byPass, pid, true);
            while ((player || target) && funtionRunMap[{pid, "FollowTarget"}].load())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                UpdateAddress();
                x = game.data.player.data.coord.data.x.UpdateData().data;
                y = game.data.player.data.coord.data.y.UpdateData().data;
                z = game.data.player.data.coord.data.z.UpdateData().data;
                targetX = player ? player->data.x.UpdateAddress().UpdateData().data : target->data.x.UpdateData().data;
                targetY = player ? player->data.y.UpdateAddress().UpdateData().data : target->data.y.UpdateData().data;
                targetZ = player ? player->data.z.UpdateAddress().UpdateData().data : target->data.z.UpdateData().data;
                game.data.player.data.coord.data.xVel.UpdateAddress() = 0;
                game.data.player.data.coord.data.yVel.UpdateAddress() = 0;
                game.data.player.data.coord.data.zVel.UpdateAddress() = 0;
                if ((dist = CalculateDistance(x, y, z, targetX, targetY, targetZ)) <= 1 || std::isnan(dist))
                    break;
                if (step % (1000 / delay) == 0 && tpStep && lastDist - dist < tpStep)
                {
                    if (Tp2Target(pid, targetX, targetY, targetZ, delay, 0) < tpStep)
                        break;
                }
                else
                {
                    game.data.player.data.coord.data.xVel.UpdateAddress() = (targetX - x) / dist * speed;
                    game.data.player.data.coord.data.yVel.UpdateAddress() = (targetY - y) / dist * speed;
                    game.data.player.data.coord.data.zVel.UpdateAddress() = (targetZ - z) / dist * speed;
                }
                if (step % (500 / delay) == 0)
                    lastDist = dist;
                step = (step + 1) % (2000 / delay);
                if (player && (player = FindPlayer(game, targets)))
                    continue;
                if (target && target->data.health.UpdateData().data < 1)
                {
                    const auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
                    if (std::find(entitys.begin(), entitys.end(), *target) == entitys.end())
                        break;
                }
            }
            SetFeature(byPass, pid, false);
        }
    }

    Game::World::Player *FindPlayer(Game &game, const std::vector<std::string> &targets)
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
                    return &player;
        }
        return nullptr;
    }

    Game::World::Entity *FindTarget(Game &game, const bool &targetBoss, const bool &targetPlant, const std::vector<std::string> &targets, const std::vector<std::string> &noTargets, const uint32_t &aimRange, const uint32_t &showRange)
    {
        auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
        std::vector<std::regex> targetRegexs, noTargetRegexs;
        for (auto target : targets)
            targetRegexs.emplace_back(target);
        for (auto noTarget : noTargets)
            noTargetRegexs.emplace_back(noTarget);
        for (auto &entity : entitys)
        {
            entity.UpdateAddress().UpdateData();
            if (entity.data.isDeath.UpdateData().data == 0)
                continue;
            if (CalculateDistance(
                    game.data.player.data.coord.data.x.UpdateData().data,
                    game.data.player.data.coord.data.y.UpdateData().data,
                    game.data.player.data.coord.data.z.UpdateData().data,
                    entity.data.x.UpdateData().data,
                    entity.data.y.UpdateData().data,
                    entity.data.z.UpdateData().data) > aimRange)
                continue;
            auto name = entity.data.name.UpdateData(64).data;
            auto isNoTarget = false;
            for (auto noTargetRegex : noTargetRegexs)
                if (std::regex_match(name, noTargetRegex))
                {
                    isNoTarget = true;
                    break;
                }
            if (isNoTarget)
                continue;
            if (targetBoss &&
                ((entity.data.level.UpdateData().data >= bossLevel &&
                  std::regex_match(name, std::regex(".*npc.*"))) ||
                 std::regex_match(name, std::regex(".*boss.*"))))
                return &entity;
            if (targetPlant &&
                std::regex_match(name, std::regex(".*plant.*")) &&
                !std::regex_match(name, std::regex(".*npc.*")))
                return &entity;
            for (auto targetRegex : targetRegexs)
                if (std::regex_match(name, targetRegex))
                    return &entity;
        }
        return nullptr;
    }
}

void UpdateConfig(const char *key, const char *value)
{
    const std::string _key = key;
    const std::string _value = value;
    if (Module::configMap.find(_key) == Module::configMap.end())
        return;
    size_t index = 0;
    if (_key == "Module::bossLevel")
        Module::bossLevel = std::stoul(_value);
    else if (_key == "Module::aimOffset")
        Module::aimOffset = {std::stof(_value, &index), std::stof(_value.substr(index + 1), &index)};
    else if (_key.find("Offsets") != std::string::npos)
    {
        Memory::Offsets *offsets = (Memory::Offsets *)Module::configMap[_key];
        offsets->clear();
        size_t pos = 0;
        do
        {
            offsets->push_back(std::stol(_value.substr(pos), &index, 16));
            pos += index + 1;
        } while (pos < _value.length());
    }
    else
    {
        Object<>::Signature *signature = (Object<>::Signature *)Module::configMap[_key];
        signature->first = std::stol(_value, &index, 16);
        signature->second = _value.substr(index + 1);
    }
}

void FunctionOn(const Memory::DWORD pid, const char *funtion, const char *argv, const bool waiting)
{
    std::thread *thread = nullptr;
    std::vector<std::string> _argv = split(argv, '|');
    Module::funtionRunMap[{pid, funtion}].store(true);
    if (std::strcmp(funtion, "AutoAim") == 0)
        thread = new std::thread(
            Module::AutoAim, pid,
            std::stoul(_argv[0]),
            std::stoul(_argv[1]),
            split(_argv[2], ','),
            split(_argv[3], ','),
            std::stoul(_argv[4]),
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
            std::stof(_argv[2]),
            std::stoul(_argv[3]));
    else if (std::strcmp(funtion, "SetAutoAttack") == 0)
        thread = new std::thread(Module::SetAutoAttack, pid, std::stoul(_argv[0]), std::stoul(_argv[1]));
    else if (std::strcmp(funtion, "SetAutoRespawn") == 0)
        thread = new std::thread(Module::SetAutoRespawn, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetHideAnimation") == 0)
        thread = new std::thread(Module::SetFeature, Module::hideAnimation, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetBreakBlocks") == 0)
        thread = new std::thread(Module::SetFeature, Module::breakBlocks, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetByPass") == 0)
        thread = new std::thread(Module::SetFeature, Module::byPass, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetClipCam") == 0)
        thread = new std::thread(Module::SetFeature, Module::clipCam, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetDisMount") == 0)
        thread = new std::thread(Module::SetFeature, Module::disMount, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetLockCam") == 0)
        thread = new std::thread(Module::SetFeature, Module::lockCam, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetLocakMapLimit") == 0)
        thread = new std::thread(Module::SetFeature, Module::locakMapLimit, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetQuickMining") == 0)
        thread = new std::thread(Module::SetFeature, Module::quickMining, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetQuickMiningGeode") == 0)
        thread = new std::thread(Module::SetFeature, Module::quickMiningGeode, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetNoGravity") == 0)
        thread = new std::thread(Module::SetFeature, Module::noGravity, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetNoClip") == 0)
        thread = new std::thread(Module::SetFeature, Module::noClip, pid, std::stoul(_argv[0]));
    else if (std::strcmp(funtion, "SetUnlockZoomLimit") == 0)
        thread = new std::thread(Module::SetFeature, Module::unlockZoomLimit, pid, std::stoul(_argv[0]));
    if (thread && waiting)
    {
        thread->join();
        Module::funtionRunMap[{pid, funtion}].store(false);
    }
}

void FunctionOff(const Memory::DWORD pid, const char *funtion)
{
    Module::funtionRunMap[{pid, funtion}].store(false);
}

#endif