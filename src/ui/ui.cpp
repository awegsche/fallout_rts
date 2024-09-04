#include "ui.hpp"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.hpp"

void Gui::draw(Game &game)
{
    if (GuiButton({ 10, (float)game.height - 30, 60, 20 }, "Food Gatherer")) {
        if (game.state == GameState::Building) {
            game.state = GameState::Running;
        } else {
            game.state            = GameState::Building;
            game.bld_to_construct = game.world.m_buildings.at("foodgatherer");
        }
    }
}
