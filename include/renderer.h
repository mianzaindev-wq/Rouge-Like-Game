#pragma once

#include "player.h" //Renderer needs to know about player
#include "map.h"    //Renderer needs to know about rooms

//All display/output functions
void renderHeader(float version, int width, int height);
void renderPlayer(const Player& player);
void renderStatusBar(const Player& player);
void renderMenu();
void renderRoom(int roomNumber);
void renderMap(const Room& room, int playerRow, int playerCol);