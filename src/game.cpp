#include "game.hpp"
#include "raylib.h"
#include "ui/ui.hpp"

void Game::loop()
{
    while (!WindowShouldClose()) {
        if (camera_move) { UpdateCamera(&camera, CAMERA_THIRD_PERSON); }

        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) { camera_move = !camera_move; }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || state == GameState::Building) {
            mouse_over = world.click(camera);
        }

        world.update(1.0f);

        BeginDrawing();
        ClearBackground({ 220, 200, 150, 255 });

        BeginMode3D(camera);
        {
            world.draw(*this);
        }
        EndMode3D();

        gui.draw(*this);

        

        EndDrawing();
    }
}
