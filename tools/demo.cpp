// g++ ./tools/demo.cpp -static -Os -Wall -o demo.exe && sudo ./demo.exe

#include "../libs/Module.hpp"

std::atomic<bool> findTarget = false;
void FindTarget(const bool &targetBoss = true,
                const bool &targetPlant = false,
                const bool &targetNormal = false,
                const std::vector<std::string> &targets = {},
                const std::vector<std::string> &noTargets = {},
                const uint32_t &range = 45)
{
    Game game(Memory::GetProcessPid("Trove.exe")[0]);
    game.UpdateAddress();
    std::unique_ptr<Game::World::Entity> target = nullptr;
    game.data.player.UpdateAddress();
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
    while (findTarget.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        UpdateAddress();
        target = Module::FindTarget(game, targetBoss, targetPlant, targetNormal, targets, noTargets, range);
        if (!target)
        {
            printf("Finding ...\r");
            continue;
        }
        printf("--> Level: %02d X: %+07.1f Y: %+07.1f Z: %+07.1f Name: %s\n",
               target->data.level.UpdateData().data % 100,
               target->data.x.UpdateData().data,
               target->data.y.UpdateData().data,
               target->data.z.UpdateData().data,
               target->data.name.UpdateData(128).data.c_str());
        while (CalculateDistance(
                   game.data.player.data.coord.data.x.UpdateData().data,
                   game.data.player.data.coord.data.y.UpdateData().data + Module::aimOffset.first,
                   game.data.player.data.coord.data.z.UpdateData().data,
                   target->data.x.UpdateData().data,
                   target->data.y.UpdateData().data + Module::aimOffset.second,
                   target->data.z.UpdateData().data) <= range &&
               target->data.isDeath.UpdateData().data && findTarget.load())
        {
            UpdateAddress();
            auto health = target->data.health.UpdateData().data;
            printf("\rDist: %09.3f Health: %-20.3f",
                   CalculateDistance(game.data.player.data.coord.data.x.data, 0,
                                     game.data.player.data.coord.data.z.data,
                                     target->data.x.data, 0, target->data.z.data),
                   std::clamp(health, 0.0, 999999999999999.0));
            if (health < 1 || (target->data.x.data < 1 && target->data.y.data < 1 && target->data.z.data < 1))
            {
                const auto &entitys = game.data.world.UpdateAddress().UpdateData().data.entitys;
                if (std::find(entitys.begin(), entitys.end(), *target) == entitys.end())
                    break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        printf("Done\n");
    }
}

void FindAobScan(const char *signature)
{
    Game game(Memory::GetProcessPid("Trove.exe")[0]);
    for (auto i : game.AobScan(signature, true))
        printf("%08X\n", i);
}

void AutoScan()
{
    printf("注意: 请以管理员权限运行\n");
    printf("按任意键退出\n");
    auto pid = Memory::GetProcessPid("Trove.exe")[0];

    FunctionOn(pid, "SetByPass", "1", false);
    FunctionOn(pid, "SetNoClip", "1", false);
    FunctionOn(pid, "SetAutoAttack", "300|1000", false);

    FunctionOn(pid, "FollowTarget", " |.*chest_quest_.*,.*quest_.*_trigger.*|.*quest_spawn_trigger_radiant.*,.*pet.*,.*placeable.*,.*services.*,.*client.*,.*abilities.*,.*portal.*|1|1|50|50", false);
    FunctionOn(pid, "AutoAim", "1|0|0|.*chest_quest_.*|.*quest_spawn_trigger_radiant.*,.*pet.*,.*placeable.*,.*services.*,.*client.*,.*abilities.*,.*portal.*|45|50", false);

    findTarget.store(true);
    new std::thread(
        FindTarget, true, false, false,
        std::vector<std::string>{
            ".*quest_.*_trigger.*", // 任意开关
            ".*chest_quest_.*",     // 任意奖励箱 gameplay/...
        },
        std::vector<std::string>{
            // radiantprism                    // 天空光辉碎片
            ".*clam_depths_fire_boss.*",       // 深渊蛤蜊
            ".*quest_spawn_trigger_radiant.*", // 天空黑暗之心开关
            ".*pet.*",                         // 任意宠物
            ".*portal.*",                      // 传送门
            ".*abilities.*",                   // 任意投射物
            ".*placeable.*",                   // 任意放置物
            // 其他未知项
            ".*services.*",
            ".*client.*",
        },
        9999);
    getchar();
    findTarget.store(false);

    FunctionOn(pid, "SetNoClip", "0", true);
    FunctionOn(pid, "SetByPass", "0", true);
    FunctionOff(pid, "SetAutoAttack");
}

void WhatItem()
{
    printf("注意: 请以管理员权限运行\n");
    printf("按任意键退出\n");
    findTarget.store(true);
    new std::thread(
        FindTarget, true, false, false,
        std::vector<std::string>{".*"},
        std::vector<std::string>{},
        5);
    getchar();
    findTarget.store(false);
}

int main(int argc, char *argv[])
{
    AutoScan();
    return 0;
}