#include "ui.hpp"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.hpp"

struct BuildingButton
{
    std::string building_name;
    std::string button_label;
};

constexpr std::vector<BuildingButton> get_buttons()
{
    std::vector<BuildingButton> buttons;
    buttons.push_back({ "foodgatherer", "Food Gatherer" });
    buttons.push_back({ "vault", "Vault" });
    return buttons;
}

void Gui::draw(Game &game)
{
    float x = 10.0;
    for (const auto &[bname, label] : get_buttons()) {
        if (GuiButton({ x, (float)game.height - 30, 60, 20 }, label.c_str())) {
            if (game.state == GameState::Running
                || (game.state == GameState::Building && game.bld_to_construct->identifier() != bname)) {
                game.state            = GameState::Building;
                game.bld_to_construct = game.world->m_buildings.at(bname);
            } else if (game.state == GameState::Building && game.bld_to_construct->identifier() == bname) {
                game.state = GameState::Running;
                game.bld_to_construct.reset();
            }
        }
        x += 65.0;
    }
}
