#include <raylib.h>
#include <rlgl.h>

#include "game.hpp"
#include "world/world.hpp"

#include "ui/building_menu.hpp"

#include <iostream>

int main()
{
    std::cout << "sizeof Matrix: " << sizeof(Matrix) << "\n";

    Game game{};

    ChunkMut chunk0{&game.world, 0, 0};

    for (int i = 10; i < 30; i += 2) {
        game.world.m_building_manager->place_building(BuildingKind::Shack01, chunk0, 20, i);
    }
    for (int i = 10; i < 30; i += 1) {
        game.world.m_building_manager->place_building(BuildingKind::StreetStraight, chunk0, 19, i);
    }

    game.loop();

}
