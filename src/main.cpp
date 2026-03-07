#include <iostream>
#include "renderer.h"
#include "player.h"

enum class GameState { Running, PlayerDead, PlayerQuit };

int main ()
{
    constexpr int WINDOW_WIDTH = 80;
    constexpr int WINDOW_HEIGHT = 24;
    constexpr float GAME_VERSION = 0.5f;

    Player player;
    GameState gameState = GameState::Running;

    renderHeader (GAME_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (gameState == GameState::Running)
    {
        // Render
        renderRoom(player.room);  
        renderPlayer(player);
        renderStatusBar(player);
        renderMenu();

        // Input
        int choice;
        std::cin >> choice;
        std::cout << "\n";

        // Update
        switch (choice)
        {
            case 1:
                ++player.room;
                takeDamage(player, 10);
                player.gold += 5;
                std::cout << "You move North and encounter a trap! You take 10 damage but find 5 gold.\n";
                break;
        
            case 2:
                if (player.room > 1)
                {
                    --player.room;
                    std::cout << "You move South. \n\n";
                    break;
                }
                else
                {
                    std::cout << "You can't move further South.\n\n";
                }
                break;

            case 3:
                heal(player, 20);
                std::cout << "You rest and recover 20 HP.\n\n";
                break;

            case 4:
                gameState = GameState::PlayerQuit;
                std::cout << "You quit the game. Goodbye!\n";
                break;
        }

        if (!isAlive(player))
        {
            gameState = GameState::PlayerDead;
            std::cout << "You have died. Game Over.\n";
        }
    }

    //End Screen
    switch (gameState)
    {
        case GameState::PlayerDead: 
            std::cout << "=== YOU DIED === Reached room "
                      << player.room << "\n";
            break;

        case GameState::PlayerQuit:
            std::cout << "=== GAME QUIT === Reached room "
                      << player.room << " with "
                      << player.gold << " gold.\n";
            break;

        default:
            break;
    }

    return 0;
}