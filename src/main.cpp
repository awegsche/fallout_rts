#include <raylib.h>
#include <rlgl.h>

#include "game.hpp"
#include "world/buildings/building.hpp"
#include "world/buildings/gatherer.hpp"
#include "world/buildings/vault.hpp"
#include "world/world.hpp"

#include "ui/building_menu.hpp"

#include <iostream>

int main()
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    Game game{};

    game.new_building_type<Gatherer>("foodgatherer", "vault", "assets/food_gatherer.obj");
    game.new_building_type<Vault>("vault", "assets/vault.obj");

    game.world->place_building("vault", { 10, 10 });
    game.world->place_building("foodgatherer", { 10, 15 });
    game.world->place_building("foodgatherer", { 20, 25 });

    game.loop();
}
