/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** cast_all_rays
*/

#include "my.h"
#include "struct.h"
#include <math.h>
#include <stdio.h>

static float ray_angle_maker(const float i, const player_t *player)
{
    const float start_angle = player->angle - FOV / 2;
    const float angle_step = FOV / NUM_RAYS;
    float ray_angle = 0.0;

    ray_angle = fmod(start_angle + i * angle_step, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    if (ray_angle > 2 * PI)
        ray_angle -= 2 * PI;
    return ray_angle;
}

/*
** fish eye correcter
*/
float draw_handler(float ray_angle, float full_dist, player_t *player)
{
    float delta_angle;
    float corrected_dist;

    delta_angle = ray_angle - player->angle;
    corrected_dist = full_dist * cos(delta_angle);
    if (corrected_dist <= 0)
        corrected_dist = 0.0001;
    return corrected_dist;
}

/*
** here we find the dist as well as the colour
*/
float find_dist(sfColor *colour, player_t *player, float ray_angle)
{
    float horizontal_ray_x;
    float horizontal_ray_y;
    float vertical_ray_x;
    float vertical_ray_y;
    float horizontal_len = 0.0;
    float vertical_len = 0.0;
    float full_dist;

    horizontal_len = draw_horizontal(ray_angle, &horizontal_ray_x,
    &horizontal_ray_y, player);
    vertical_len = draw_vertical(ray_angle, &vertical_ray_x,
    &vertical_ray_y, player);
    if (vertical_len > horizontal_len) {
        full_dist = horizontal_len;
        *colour = sfColor_fromRGB(100, 100, 200);
    } else {
        full_dist = vertical_len;
        *colour = sfColor_fromRGB(100, 200, 100);
    }
    return full_dist;
}

void draw_all_ray(player_t *player, sfRenderWindow* window)
{
    float ray_angle = player->angle;
    float wall_height = 0.0;
    float full_dist = 0.0;
    sfColor colour;

    for (int i = 0; i < NUM_RAYS; i++) {
        ray_angle = ray_angle_maker(i, player);
        full_dist = find_dist(&colour, player, ray_angle);
        wall_height = (TILE_SIZE / draw_handler(ray_angle, full_dist,
        player)) * PROJECTION_PLANE;
        render_wall_column(window, i, wall_height, colour);
    }
}
