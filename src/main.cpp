#include <iostream>
#include "player.h"
#include "renderer.h"
#include "map.h"

enum class GameState { Running, PlayerDead, PlayerQuit };

int main()
{
    constexpr int   WINDOW_WIDTH  = 80;
    constexpr int   WINDOW_HEIGHT = 24;
    constexpr float VERSION       = 0.6f;

    // Initialize player
    Player player;
    int playerRow = 3;
    int playerCol = 2;

    // Initialize room
    Room currentRoom;
    initRoom(currentRoom, "Entrance Hall");

    // Place special tiles
    setTile(currentRoom, 1, 5,
            static_cast<int>(TileType::Chest));
    setTile(currentRoom, 6, 6,
            static_cast<int>(TileType::Stairs));
    setTile(currentRoom, 0, 6,
            static_cast<int>(TileType::Door));

    GameState gameState = GameState::Running;

    renderHeader(VERSION, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (gameState == GameState::Running)
    {
        // Render
        renderMap(currentRoom, playerRow, playerCol);
        renderPlayer(player);
        renderStatusBar(player);

        std::cout << "Move: [W]orth [S]outh [A]est [D]ast"
                  << "  [R]est  [Q]uit\n> ";

        // Input
        char input = ' ';
        std::cin >> input;
        std::cout << "\n";

        // Store previous position
        int newRow = playerRow;
        int newCol = playerCol;

        // Update
        switch (input)
        {
            case 'w': case 'W': --newRow; break;
            case 's': case 'S': ++newRow; break;
            case 'a': case 'A': --newCol; break;
            case 'd': case 'D': ++newCol; break;
            case 'r': case 'R':
                heal(player, 20);
                std::cout << "You rest. HP restored.\n\n";
                break;
            case 'q': case 'Q':
                gameState = GameState::PlayerQuit;
                break;
            default:
                std::cout << "Unknown command.\n\n";
                break;
        }

        // Only move if walkable
        if (isWalkable(currentRoom, newRow, newCol))
        {
            playerRow = newRow;
            playerCol = newCol;

            // Check tile events
            int tile = getTile(currentRoom, playerRow, playerCol);
            if (tile == static_cast<int>(TileType::Chest))
            {
                player.gold += 25;
                std::cout << "You found a chest! +25 gold.\n\n";
                setTile(currentRoom, playerRow, playerCol,
                        static_cast<int>(TileType::Floor));
            }
            else if (tile == static_cast<int>(TileType::Stairs))
            {
                std::cout << "You found the stairs! "
                          << "Deeper dungeon coming soon...\n\n";
            }
        }
        else
        {
            std::cout << "Blocked.\n\n";
        }

        if (!isAlive(player))
            gameState = GameState::PlayerDead;
    }

    // End screen
    switch (gameState)
    {
        case GameState::PlayerDead:
            std::cout << "=== YOU DIED ===\n";
            break;
        case GameState::PlayerQuit:
            std::cout << "=== QUIT === Gold: "
                      << player.gold << "\n";
            break;
        default:
            break;
    }

    return 0;
}