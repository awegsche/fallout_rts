#include "chunk.hpp"

#include "world/world.hpp"


[[nodiscard]] Cell const &Chunk::get_cell(int i, int j) const { return m_world->m_cells[get_cell_position(i, j)]; }

Cell &ChunkMut::get_cell_mut(int i, int j)
{
    return m_world_mut->m_cells[get_cell_position(i,j)];
}

float Chunk::get_x_offset() const { return GROUND_TILE_SIZE * static_cast<float>(m_world->m_chunk_size * pos_x); }

float Chunk::get_y_offset() const { return GROUND_TILE_SIZE * static_cast<float>(m_world->m_chunk_size * pos_y); }

std::optional<CellPosition> Chunk::get_mouse_over(Camera3D const &cam) const
{
    const float size = static_cast<float>(m_world->m_chunk_size);
    const Ray   ray  = GetMouseRay(GetMousePosition(), cam);

    const auto mouse_collision = GetRayCollisionQuad(ray,
        { get_x_offset(), 0.0f, get_y_offset() },
        { get_x_offset(), 0.0f, get_y_offset() + size },
        { get_x_offset() + size, 0.0f, get_y_offset() + size },
        { get_x_offset() + size, 0.0f, get_y_offset() });

    if (mouse_collision.hit) {
        return CellPosition{ static_cast<int>(mouse_collision.point.x / GROUND_TILE_SIZE),
            static_cast<int>(mouse_collision.point.z / GROUND_TILE_SIZE) };
    } else {
        return {};
    }
}
uint32_t Chunk::chunk_size() const { return m_world->m_chunk_size; }

Matrix const &Chunk::get_cell_transform(int i, int j) const
{
    return m_world->m_cell_transforms[get_cell_position(i, j)];
}

size_t Chunk::get_cell_position(int i, int j) const
{
    // position inside chunk to global pos
    const size_t x            = pos_x * m_world->m_chunk_size + i;
    const size_t y            = pos_y * m_world->m_chunk_size + j;
    return y * m_world->m_chunk_size * m_world->m_width + x;
}
bool Chunk::contains_position(CellPosition const &pos) const
{
    return pos.x >= m_world->m_chunk_size * pos_x && pos.x < m_world->m_chunk_size * (pos_x + 1)
           && pos.y >= m_world->m_chunk_size * pos_y && pos.y < m_world->m_chunk_size * (pos_y + 1);
}
