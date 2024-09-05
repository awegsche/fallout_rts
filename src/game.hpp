#ifndef __GAME_H__
#define __GAME_H__

#include <raylib.h>
#include <spdlog/spdlog.h>

#include "ui/ui.hpp"
#include "utils/cell_position.hpp"
#include "world/world.hpp"

constexpr int WIDTH  = 1024;
constexpr int HEIGHT = 512;
constexpr size_t LOG_MSG_BUF_SIZE = 1024;

enum class GameState {
    Running,
    Building,
    Paused,
};

inline void log_callback(int msg_type, const char *fmt_str, va_list args)
{
    static char buffer[LOG_MSG_BUF_SIZE];
    vsprintf(buffer, fmt_str, args);

    switch (msg_type) {
    case LOG_INFO:
        spdlog::info(buffer);
        break;
    case LOG_DEBUG:
        spdlog::debug(buffer);
        break;
    default:
        spdlog::error(buffer);
        break;
    }
}

struct WindowContext
{
    WindowContext(uint32_t width, uint32_t height)
    {
        InitWindow(width, height, "Fallout RTS");
        SetTraceLogCallback(log_callback);
        SetTargetFPS(60);
    }

    WindowContext(WindowContext const &)            = delete;
    WindowContext &operator=(WindowContext const &) = delete;

    WindowContext(WindowContext &&)            = delete;
    WindowContext &operator=(WindowContext &&) = delete;


    ~WindowContext() { CloseWindow(); }
};

struct Game
{
    Game() : ctx(width, height)
    {
        camera.position   = { -10.0f, 10.0f, -10.0f };
        camera.target     = { 5.0f, 5.0f, 5.0f };
        camera.up         = { 0.0f, 1.0f, 0.0f };
        camera.fovy       = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    Game(Game const &)            = delete;
    Game &operator=(Game const &) = delete;
    Game(Game &&)                 = delete;
    Game &operator=(Game &&)      = delete;

    ~Game() = default;

    void loop();

    // todo: private and const access
    // ctx must be declared first
    uint32_t      width  = WIDTH;
    uint32_t      height = HEIGHT;
    WindowContext ctx;

    Camera3D    camera = {};
    std::string msg;
    World       world;
    Gui         gui{};
    GameState   state;
    size_t      ticks       = 0;
    bool        camera_move = false;
    std::optional<CellPosition> mouse_over;

    std::shared_ptr<Building> bld_to_construct = nullptr;
};

#endif
