#include "ui.hpp"
#include "raylib.h"
#include "world/buildings.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.hpp"

void Gui::draw(Game &game)
{
    if (GuiButton({ 10, (float)game.height - 30, 40, 20 }, "Street")) {
        if (game.state == GameState::Building && game.buildin_kind == BuildingKind::StreetStraight) {
            game.state = GameState::Running;
        } else {
            game.state        = GameState::Building;
            game.buildin_kind = BuildingKind::StreetStraight;
        }
    }
}
