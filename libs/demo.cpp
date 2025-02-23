// g++ .\libs\demo.cpp -Os -Wall -o demo.exe && sudo .\demo.exe

#include "Module.hpp"

void FindTarget()
{
    printf("\033c");
    Game game(Memory::GetProcessPid("Trove.exe")[0]);
    game.UpdateAddress();
    Game::World::Entity *target = nullptr;
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
        target = Module::FindTarget(
            game, true, false,
            {".*chest_quest_standard.*", ".*chest_quest_recipe.*"},
            {".*pet.*",
             ".*placeable.*",
             ".*services.*",
             ".*client.*",
             ".*abilities.*",
             ".*portal.*"},
            45, 0);
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
               target->data.name.UpdateData(32).data.c_str());
        while (CalculateDistance(
                   game.data.player.data.coord.data.x.UpdateData().data,
                   game.data.player.data.coord.data.y.UpdateData().data + Module::aimOffset.first,
                   game.data.player.data.coord.data.z.UpdateData().data,
                   target->data.x.UpdateData().data,
                   target->data.y.UpdateData().data + Module::aimOffset.second,
                   target->data.z.UpdateData().data) <= 45 &&
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
    // FindTarget();

    // FindAobScan(argv[1]);

    // Module::Tp2Forward(Memory::GetProcessPid("Trove.exe")[0], 50, 50);

    // FunctionOn(Memory::GetProcessPid("Trove.exe")[0],"FollowTarget","Artloot| |50|50",true);

    return 0;
}