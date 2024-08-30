#include "ui.hpp"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.hpp"

void Gui::draw(Game &game)
{
    if (GuiButton({ 10, (float)game.height - 30, 40, 20 }, "Street")) { game.state = GameState::Building; }
}
