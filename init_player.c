/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** init_player
*/

#include "my.h"


void init_player(player_t *player)
{
    player->x = 1.5f * TILE_SIZE;
    player->y = 1.5f * TILE_SIZE;
    player->angle = 0.0f;
}
