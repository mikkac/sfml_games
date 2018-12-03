#include "zombie_arena.h"
#include "utils.h"
namespace game
{
int create_background(VertexArray& vert_arr, IntRect arena) {
    const int kTileSize{64};
    const int kTileTypes{4};
    const int kVertsInQuad{4};

    unsigned world_width{static_cast<unsigned>(arena.width / kTileSize)};   // num of tiles
    unsigned world_height{static_cast<unsigned>(arena.height / kTileSize)}; // num of tiles

    vert_arr.setPrimitiveType(Quads);
    vert_arr.resize(world_width * world_height * kVertsInQuad);

    int current_vertex{0};

    for (unsigned w = 0; w < world_width; ++w) {
        for (unsigned h = 0; h < world_height; ++h) {
            vert_arr[current_vertex + 0].position = Vector2f(w * kTileSize, h * kTileSize);

            vert_arr[current_vertex + 1].position =
                Vector2f(w * kTileSize + kTileSize, h * kTileSize);

            vert_arr[current_vertex + 2].position =
                Vector2f(w * kTileSize + kTileSize, h * kTileSize + kTileSize);

            vert_arr[current_vertex + 3].position =
                Vector2f(w * kTileSize, h * kTileSize + kTileSize);

            if (h == 0 || h == world_height - 1 || w == 0 || w == world_width - 1) {
                // Use the wall texture
                vert_arr[current_vertex + 0].texCoords = Vector2f(0, kTileSize);
                vert_arr[current_vertex + 1].texCoords = Vector2f(kTileSize, kTileSize);
                vert_arr[current_vertex + 2].texCoords = Vector2f(kTileSize, kTileSize * 2);
                vert_arr[current_vertex + 3].texCoords = Vector2f(0, kTileSize * 2);
            } else {
                // Use a random floor texture
                int random = rand_num(3);
                int vert_offset{random * kTileSize};

                vert_arr[current_vertex + 0].texCoords = Vector2f(0, 0 + vert_offset);
                vert_arr[current_vertex + 1].texCoords = Vector2f(kTileSize, 0 + vert_offset);
                vert_arr[current_vertex + 2].texCoords =
                    Vector2f(kTileSize, kTileSize + vert_offset);
                vert_arr[current_vertex + 3].texCoords = Vector2f(0, kTileSize + vert_offset);
            }
            current_vertex += kVertsInQuad;
        }
    }

    return kTileSize;
}
} // namespace game