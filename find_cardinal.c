/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** find_cardinal
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static cardinal_t wall_direction(float hit_x, float hit_y, int tile_x,
    int tile_y)
{
    float diff_x = hit_x - tile_x;
    float diff_y = hit_y - tile_y;

    if (diff_x < 0)
        diff_x *= -1;
    if (diff_y < 0)
        diff_y *= -1;
    if (diff_x < diff_y)
        return NORTH;
    return WEST;
}

/*
** only call this func when you have confirmed a ray hit
** this func determines the side of the wall you are hitting
** tile_x and tile_y are the center of the square
*/
cardinal_t find_cardinal(float hit_x, float hit_y)
{
    int x = (int)hit_x;
    int y = (int)hit_y;
    int tile_x = x / TILE_SIZE;
    int tile_y = y / TILE_SIZE;

    //if(is_wall(hit_x, hit_y)) {
    //    printf("we are actually hitting a wall \n");
    //}
    if (tile_x < 0 || tile_x >= MAP_WIDTH || tile_y < 0 ||
    tile_y >= MAP_HEIGHT)
        return PERIM;
    if (map[tile_y][tile_x] == 1) {
        if (hit_x < 0)
            hit_x *= -1;
        if (hit_y < 0)
            hit_y *= -1;
        return wall_direction(hit_x, hit_y, tile_x, tile_y);
    }
    return NOWHERE;
}
