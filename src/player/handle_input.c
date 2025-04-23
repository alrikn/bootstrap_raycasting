/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_input
*/

#include "my.h"
#include "math.h"
#include "struct.h"
#include <SFML/Window/Keyboard.h>
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
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->angle -= ROTATION_SPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        player->angle += ROTATION_SPEED;
    }
    player->angle = normalize_angle(player->angle);
}

/*
**should only print if the player is in a new tile
*/
bool print_handle(int player_x, int player_y, int old_y, int old_x)
{
    player_x = player_x / TILE_SIZE;
    player_y = player_y / TILE_SIZE;
    old_x = old_x / TILE_SIZE;
    old_y = old_y / TILE_SIZE;
    if (player_x != old_x || player_y != old_y)
        return true;
    return false;
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
    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyE))
        rotate(event, player);
    if (sfKeyboard_isKeyPressed(sfKeyW) || sfKeyboard_isKeyPressed(sfKeyUp))
        move_player(player, 2, player->angle);
    if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
        move_player(player, -1.5, player->angle);
    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
        move_player(player, 1, player->angle + P2);
    if (sfKeyboard_isKeyPressed(sfKeyA) || sfKeyboard_isKeyPressed(sfKeyLeft))
        move_player(player, 1, player->angle - P2);
}
