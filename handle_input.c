/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_input
*/

#include "my.h"
#include "math.h"
#include "struct.h"
#include <stdio.h>

static float normalize_angle(float angle)
{
    angle = fmodf(angle, 2 * M_PI);
    if (angle < 0)
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

static void move_player(player_t *player, float move_dir)
{
    float move_x = cosf(player->angle) * MOVEMENT_SPEED * move_dir;
    float move_y = sinf(player->angle) * MOVEMENT_SPEED * move_dir;
    float new_x = player->x + move_x;
    float new_y = player->y + move_y;

    if (!is_wall(new_x, new_y)) {
        player->x = new_x;
        player->y = new_y;
        print_pos(player->x, player->y);
    } else {
        printf("move not allowed\n");
        printf("new_x = %f, new_y = %f\n", new_x, new_y);
    }
}

void key_pressed(sfEvent *event, player_t *player)
{
    if (event->key.code == sfKeyQ || event->key.code == sfKeyE) {
        rotate(event, player);
    }
    if (event->key.code == sfKeyW) {
        move_player(player, 1.5f);
    }
    if (event->key.code == sfKeyS) {
        move_player(player, -1.5f);
    }
}
