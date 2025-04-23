/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** player_potential
*/

#include "my.h"
#include "struct.h"
#include "math.h"
#include <stdio.h>

/*
**this to make the player slide if it runs into a wall
*/
void handle_sliding(player_t *player, float new_x, float new_y)
{
    if (!is_wall(new_x, player->y) && new_x > 0) {
        if (print_handle(player->x, player->y, player->y, new_x))
            print_pos(new_x, player->y, player);
        player->x = new_x;
        return;
    }
    if (!is_wall(player->x, new_y) && new_y > 0) {
        if (print_handle(player->x, player->y, new_y, player->x))
            print_pos(player->x, new_y, player);
        player->y = new_y;
        return;
    }
    printf("forbiden move: new_x = %f, new_y = %f\n", new_x, new_y);
}

void apply_potential(player_t *player)
{
    float new_x = player->x + (player->force_x / 1.5);
    float new_y = player->y + (player->force_y / 1.5);

    if (!is_wall(new_x, new_y) && new_x > 0 && new_y > 0) {
        if (print_handle(player->x, player->y, new_y, new_x))
            print_pos(new_x, new_y, player);
        player->x = new_x;
        player->y = new_y;
    } else
        handle_sliding(player, new_x, new_y);
    player->force_x = player->force_x / 1.5;
    player->force_y = player->force_y / 1.5;
    if (player->force_x < 2 && player->force_x > -2)
        player->force_x = 0;
    if (player->force_x < 2 && player->force_x > -2)
        player->force_x = 0;
}

/*
** pot force is the amount of force you want to apply to the player
(knockback purposes mostly)
** force angle is where your applying the force
** we handle the actual movement in another func
*/
void move_potential(player_t *player, float pot_force, float force_angle)
{
    float move_x = cosf(force_angle) * MOVEMENT_SPEED * pot_force;
    float move_y = sinf(force_angle) * MOVEMENT_SPEED * pot_force;

    player->force_x += move_x;
    player->force_y += move_y;
}
