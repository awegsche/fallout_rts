#include "world.hpp"

#include <spdlog/spdlog.h>

#include "game.hpp"

constexpr auto KILO = 1024;
constexpr auto MEGA = KILO * KILO;

void World::draw(Game &game)
{
    const auto pred = [this, &game](Chunk const &chunk) {
        m_terrain_manager->draw_chunk(chunk);
        // m_building_manager->draw(chunk, game);
    };
    do_for_visible_chunks(game.camera.target, pred);

    // draw all the buildings (todo: only in visible chunks)
    for (auto const& [key, building] : m_buildings) { building->draw(game.renderer); }

    //if (game.bld_to_construct && game.mouse_over) { game.bld_to_construct->draw_single(*game.mouse_over); }
}

World::World()
{
    m_terrain_manager = std::make_unique<TerrainManager>();
    Shader shader     = LoadShader(R"(shaders\lighting_single_vs.glsl)", R"(shaders\lighting_fs.glsl)");
    shader.locs[SHADER_LOC_MATRIX_MVP]  = GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

    // Set shader value: ambient light level
    int   ambientLoc = GetShaderLocation(shader, "ambient");
    float amb[4]     = { 0.2f, 0.2f, 0.2f, 1.0f };
    SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

    UpdateLightValues(shader, 0);

    // m_building_manager = std::make_unique<BuildingManager>(shader);

    std::random_device                    rd;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    std::mt19937                          gen{ rd() };

    const uint32_t ncells = m_height * m_width * m_chunk_size * m_chunk_size;
    m_cells.reserve(ncells);
    m_cell_transforms.reserve(ncells);

    const float mega_cells = (float)ncells / MEGA;
    spdlog::debug("reserving space for {} cells", ncells);
    spdlog::debug("{:.2} MB of cell data", (float)sizeof(Cell) * mega_cells);
    spdlog::debug("{:.2} MB of transform data", (float)sizeof(Matrix) * mega_cells);

    for (uint32_t j = 0; j < m_height * m_chunk_size; ++j) {
        for (uint32_t i = 0; i < m_width * m_chunk_size; ++i) {
            // m_chunks.emplace_back(m_chunk_size, i, j);

            const float value = dist(gen) * 0.1f + 0.5f;
            m_cells.emplace_back(TerrainType::Forest, value, -1);
            const float x           = ((float)i + 0.2f + 0.6f * dist(gen)) * GROUND_TILE_SIZE;
            const float y           = ((float)j + 0.2f + 0.6f * dist(gen)) * GROUND_TILE_SIZE;
            Matrix      translation = MatrixTranslate(x, 0.0f, y);
            Matrix      scale       = MatrixScale(1.0f + dist(gen) * 0.2f, dist(gen) * 0.3f + 1.0f, 1.0f);

            m_cell_transforms.push_back(MatrixMultiply(scale, translation));
        }
    }
}

std::optional<CellPosition> World::click(Camera3D const &camera) const
{
    std::optional<CellPosition> pos = {};

    const auto pred = [&pos, &camera](Chunk const &chunk) {
        const auto _pos = chunk.get_mouse_over(camera);
        if (_pos) { pos = _pos; }
    };

    do_for_visible_chunks(camera.position, pred);
    return pos;
}

void World::update(float dt)
{
    for (auto &[key, building] : m_buildings) { building->update(*this, dt); }
}

void World::place_building(const std::string identifier, CellPosition position)
{
    m_buildings.at(identifier)->place(*this, position);
    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {
            CellPosition p{ position.x + i, position.y + j };
            if (p.x >= 0 && p.x < m_chunk_size * m_width && p.y >= 0 && p.y < m_chunk_size * m_height) {
                get_cell_mut(p).terrain_type = TerrainType::Plain;
            }
        }
    }
}
