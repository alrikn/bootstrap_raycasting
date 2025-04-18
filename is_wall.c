/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** is_wall
*/

#include "my.h"

int is_wall(int x, int y)
{
    int tile_x = x / TILE_SIZE;
    int tile_y = y / TILE_SIZE;

    if (tile_x < 0 || tile_x >= MAP_WIDTH || tile_y < 0 ||
    tile_y >= MAP_HEIGHT)
        return 1;
    return map[tile_y][tile_x] == 1;
}
