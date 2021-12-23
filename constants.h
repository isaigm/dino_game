#pragma once
#include <SFML/Graphics.hpp>
static const char *SPRITESHEET_FILE = "sprites.png";
static const int WIDTH = 600;
static const int HEIGHT = 320;
static const float GRAVITY = 900.0f;
static const int N_CLOUDS = 5;
static const float ground = 125 + 47;
static const int player_speed = 130;
static const sf::IntRect dino_frames[] = {
    {936, 2, 44, 47},
    {980, 2, 44, 47},
    {848, 2, 44, 47}};
static const sf::IntRect cactus_frames[] =
    {
        {228, 2, 17, 35},
        {245, 2, 34, 35},
        {279, 2, 51, 35},
        {332, 2, 49, 50},
        {382, 2, 25, 50},
        {407, 2, 75, 50}};
static const sf::IntRect cloud_frame = {86, 1, 46, 17};
static const sf::IntRect die_frame = {1024, 2, 44, 47};
static const sf::IntRect game_over_frame = {655, 15, 191, 11};
static const int N_CACTUS = sizeof(cactus_frames) / sizeof(sf::IntRect);
