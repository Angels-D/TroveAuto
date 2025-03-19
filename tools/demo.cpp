// g++ ./tools/demo.cpp -static -Os -Wall -o demo.exe && sudo ./demo.exe

#include "../libs/Module.hpp"

void FindTarget(const bool &targetBoss = true,
                const bool &targetPlant = false,
                const bool &targetNormal = false,
                const std::vector<std::string> &targets = {},
                const std::vector<std::string> &noTargets = {},
                const uint32_t &aimRange = 45,
                const uint32_t &showRange = 0)
{
    printf("\033c");
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
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        UpdateAddress();
        target = Module::FindTarget(game, targetBoss, targetPlant, targetNormal, targets, noTargets, aimRange, showRange);
        if (!target)
        {
            printf("Finding ...\r");
            continue;
        }
        printf("--> %02d %+07.1f %+07.1f %+07.1f %s\n",
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
                   target->data.z.UpdateData().data) <= aimRange &&
               target->data.isDeath.UpdateData().data)
        {
            UpdateAddress();
            auto health = target->data.health.UpdateData().data;
            printf("\r%.3f ", health);
            if (health < 1)
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

int main(int argc, char *argv[])
{
    // FindAobScan(argv[1]);

    // Module::Tp2Forward(Memory::GetProcessPid("Trove.exe")[0], 50, 50);

    // FunctionOn(Memory::GetProcessPid("Trove.exe")[0],"FollowTarget",".*|.*pet.*,.*placeable.*,.*services.*,.*client.*,.*abilities.*,.*portal.*|50|50", true);

    // FunctionOn(Memory::GetProcessPid("Trove.exe")[0],"SetNoClip","1",true);

    FindTarget(true, false, false,
                {
                    ".*gameplay.*"
                    ".*quest_assault_trigger.*",
                    ".*gameplay/chest_quest_worldboss.*", 
                    ".*viking.*", 
                    ".*quest_spawn_trigger_fivestar_dep.*", 
                    ".*chest_quest_standard.*", 
                    ".*chest_quest_recipe.*"
                },
                {
                    ".*clam_depths_fire_boss.*",
                    ".*pet.*",
                    ".*placeable.*",
                    ".*services.*",
                    ".*client.*",
                    ".*abilities.*",
                    ".*portal.*"
                });

    return 0;
}