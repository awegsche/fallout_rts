#include "game.hpp"
#include "ui/ui.hpp"

void Game::loop()
{
    while (!WindowShouldClose()) {
        if (camera_move) { UpdateCamera(&camera, CAMERA_THIRD_PERSON); }

        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) { camera_move = !camera_move; }

        BeginDrawing();
        ClearBackground({ 220, 200, 150, 255 });

        BeginMode3D(camera);
        {
            world.draw(camera.target);
        }
        EndMode3D();

        gui.draw(*this);

        

        EndDrawing();
    }
}
