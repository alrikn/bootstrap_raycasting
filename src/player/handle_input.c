/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_input
*/

#include "my.h"
#include "math.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>

static float normalize_angle(float angle)
{
    angle = fmodf(angle, 2 * M_PI);
    if (angle <= 0)
        angle += 2 * M_PI;
    return angle;
}

static void rotate(sfEvent *event, player_t *player)
{
    if (event->key.code == sfKeyQ) {
        player->angle -= ROTATION_SPEED;
    }
    if (event->key.code == sfKeyE) {
        player->angle += ROTATION_SPEED;
    }
    player->angle = normalize_angle(player->angle);
}

/*
**should only print if the player is in a new tile
*/
static bool print_handle(int player_x, int player_y, int old_y, int old_x)
{
    player_x = player_x / TILE_SIZE;
    player_y = player_y / TILE_SIZE;
    old_x = old_x / TILE_SIZE;
    old_y = old_y / TILE_SIZE;
    if (player_x != old_x || player_y != old_y)
        return true;
    return false;
}

/*
**this to make the player slide if it runs into a wall
*/
static void handle_sliding(player_t *player, float new_x, float new_y)
{
    if (!is_wall(new_x, player->y)) {
        if (print_handle(player->x, player->y, player->y, new_x))
            print_pos(new_x, player->y, player);
        player->x = new_x;
        return;
    }
    if (!is_wall(player->x, new_y)) {
        if (print_handle(player->x, player->y, new_y, player->x))
            print_pos(player->x, new_y, player);
        player->y = new_y;
        return;
    }
    printf("move not allowed\n");
    printf("new_x = %f, new_y = %f\n", new_x, new_y);
}

static void move_player(player_t *player, float move_dir, float angle)
{
    float move_x = cosf(angle) * MOVEMENT_SPEED * move_dir;
    float move_y = sinf(angle) * MOVEMENT_SPEED * move_dir;
    float new_x = player->x + move_x;
    float new_y = player->y + move_y;

    if (!is_wall(new_x, new_y) && new_x > 0 && new_y > 0) {
        if (print_handle(player->x, player->y, new_y, new_x))
            print_pos(new_x, new_y, player);
        player->x = new_x;
        player->y = new_y;
    } else
        handle_sliding(player, new_x, new_y);
}

void key_pressed(sfEvent *event, player_t *player)
{
    if (event->key.code == sfKeyQ || event->key.code == sfKeyE)
        rotate(event, player);
    if (event->key.code == sfKeyW)
        move_player(player, 2.5, player->angle);
    if (event->key.code == sfKeyS)
        move_player(player, -1.5, player->angle);
    if (event->key.code == sfKeyD)
        move_player(player, 2, player->angle + P2);
    if (event->key.code == sfKeyA)
        move_player(player, 2, player->angle - P2);
}
