#include "map.h"

void initRoom(Room& room, const std::string& name)
{
    room.name       = name;
    room.visited    = false;
    room.enemyCount = 0;

    // Fill entire room with walls first
    for (int row = 0; row < MAP_HEIGHT; ++row)
    {
        for (int col = 0; col < MAP_WIDTH; ++col)
        {
            room.tiles[row][col] = static_cast<int>(TileType::Wall);
        }
    }

    // Carve out floor — leave border as walls
    for (int row = 1; row < MAP_HEIGHT - 1; ++row)
    {
        for (int col = 1; col < MAP_WIDTH - 1; ++col)
        {
            room.tiles[row][col] = static_cast<int>(TileType::Floor);
        }
    }
}

void setTile(Room& room, int row, int col, int tileType)
{
    if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
        return;    // bounds check — never write outside the array
    room.tiles[row][col] = tileType;
}

int getTile(const Room& room, int row, int col)
{
    if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
        return static_cast<int>(TileType::Wall);  // treat out-of-bounds as wall
    return room.tiles[row][col];
}

bool isWalkable(const Room& room, int row, int col)
{
    int tile = getTile(room, col, col);
    return tile == static_cast<int>(TileType::Floor) ||
           tile == static_cast<int>(TileType::Door);
}