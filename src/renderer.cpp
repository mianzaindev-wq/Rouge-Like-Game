#include "renderer.h"
#include <iostream>

void renderHeader(float version, int width, int height)
{
    std::cout << "=== RogueEngine v" << version << " ===\n";
    std::cout << "World: " << width << "x" << height << "\n\n";
}

void renderPlayer(const Player&  player)
{
    std::cout << player.symbol
                << " HP: " << player.health << "/" << player.maxHealth
                << " Gold: " << player.gold
                << " Room: " << player.room << "\n";
}

void renderStatusBar(const Player& player)
{
    std::cout << "Status: ";

    switch (getStatus(player))
    {
        case PlayerStatus::Healthy:  std::cout << "Healthy\n";   break;
        case PlayerStatus::Hurt:     std::cout << "Hurt\n";      break;
        case PlayerStatus::Wounded:  std::cout << "Wounded\n";   break;
        case PlayerStatus::Critical: std::cout << "Critical!\n"; break;
        case PlayerStatus::Dead:     std::cout << "Dead\n";      break;
    }
}

void renderMenu()
{
    std::cout << "\n1) Move North  2) Move South  "
              << "3) Rest (+20 HP)  4) Quit\n> ";
}

void renderRoom(int roomNumber)
{
    std::cout << "\n--- Room " << roomNumber << " ---\n";

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            if (row == 0 || row == 4 || col == 0 || col == 4)
                std::cout << "# ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}