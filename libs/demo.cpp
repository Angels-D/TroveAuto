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
            {".*chest_quest_standard.*"},
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
            printf("%.3f\r", target->data.health.UpdateData().data);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

int main()
{
    FindTarget();
    return 0;
}