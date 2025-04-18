/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** print_pos
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>

void print_map_matrix(int x, int y, int tile_x, int tile_y)
{
    if (x == tile_x && y == tile_y) {
        my_cooler_putstr("P ");
        return;
    }
    if (map[y][x] == 1) {
        my_cooler_putstr("X ");
        return;
    }
    if (map[y][x] == 0) {
        my_cooler_putstr(". ");
        return;
    }
}

void print_pos(int player_x, int player_y)
{
    int tile_x = player_x / TILE_SIZE;
    int tile_y = player_y / TILE_SIZE;

    my_cooler_putstr("\n\n");
    printf("player x = %d, player y = %d\n", player_x, player_y);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            print_map_matrix(x, y, tile_x, tile_y);
        }
        my_cooler_putstr("\n");
    }
}
