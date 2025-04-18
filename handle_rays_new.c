/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_rays_new
*/

#include "my.h"
#include "struct.h"
#include <math.h>
#include <stdio.h>


/*
**pythagorean method
** always positive
*/
float distance_calculator(float init_x, float end_x, float init_y, float end_y)
{
    float distance = sqrt(((end_x - init_x) * (end_x - init_x)) +
    ((end_y - init_y) * (end_y - init_y)));

    if (distance < 0)
        distance *= -1;
    return distance;
}

/*
** this checks horizontal intersections
*/
float draw_horizontal(float ray_angle, float *horizontal_x,
    float *horizontal_y, player_t *player)
{
    int dof = 0;
    float aTan = -1 / tan(ray_angle);
    float yo;
    float xo;
    int mx;
    int my;
    float horizontal_len = 100000;

    if (ray_angle > M_PI) {
        *horizontal_y = (((int)(player->y) >> 6) << 6) - 0.0001;
        *horizontal_x = ((player->y) - *horizontal_y) * aTan + (player->x);
        yo = -64;
        xo = -yo * aTan;
    }
    if (ray_angle < M_PI) {
        *horizontal_y = (((int)(player->y) >> 6) << 6) + 64;
        *horizontal_x = ((player->y) - *horizontal_y) * aTan + (player->x);
        yo = 64;
        xo = -yo * aTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) {
        *horizontal_x = (player->x);
        *horizontal_y = (player->y);
        dof = 8;
    }
    while (dof < 8) {
        mx = (int)(*horizontal_x) >> 6;
        my = (int)(*horizontal_y) >> 6;
        mx = mx < 0 ? 0 : mx;
        mx = mx >= MAP_WIDTH ? MAP_WIDTH - 1 : mx;
        my = my < 0 ? 0 : my;
        my = my >= MAP_HEIGHT ? MAP_HEIGHT - 1 : my;
        if (mx >= 0 && mx < MAP_WIDTH &&
            my >= 0 && my < MAP_HEIGHT &&
            map[my][mx] == 1) {
            dof = 8;
            horizontal_len = distance_calculator(player->x, *horizontal_x,
            player->y, *horizontal_y);
        } else {
            *horizontal_x += xo;
            *horizontal_y += yo;
            dof += 1;
        }
    }
    return horizontal_len;
}

/*
** this checks vertical intersections
*/
float draw_vertical(float ray_angle, float *vertical_x,
    float *vertical_y, player_t *player)
{
    int dof = 0;
    float nTan = -tan(ray_angle);
    float yo;
    float xo;
    int mx;
    int my;
    float vertical_len = 100000;

    if (ray_angle > P2 && ray_angle < P3) {
        *vertical_x = (((int)(player->x)>>6)<<6)-0.0001;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        xo = -64;
        yo = -xo * nTan;
    } 
    if (ray_angle < P2 || ray_angle > P3) {
        *vertical_x = (((int)(player->x)>>6)<<6) + 64;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        xo = 64;
        yo = -xo * nTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) {
        *vertical_x = (player->x);
        *vertical_y = (player->y);
        dof = 8;
    }
    while (dof < 8) {
        mx = (int)(*vertical_x) >> 6;
        my = (int)(*vertical_y) >> 6;
        mx = mx < 0 ? 0 : mx;
        mx = mx >= MAP_WIDTH ? MAP_WIDTH - 1 : mx;
        my = my < 0 ? 0 : my;
        my = my >= MAP_HEIGHT ? MAP_HEIGHT - 1 : my;
        if (mx >= 0 && mx < MAP_WIDTH && 
            my >= 0 && my < MAP_HEIGHT &&
            map[my][mx] == 1) {
            dof = 8;
            vertical_len = distance_calculator(player->x, *vertical_x,
            player->y, *vertical_y);
        } else {
            *vertical_x += xo;
            *vertical_y += yo;
            dof += 1;
        }
    }
    return vertical_len;
}

void draw_ray(player_t *player, sfRenderWindow* window)
{
    int i;
    float rx;
    float ry;
    float ray_angle = player->angle;
    float horizontal_ray_x;
    float horizontal_ray_y;
    float vertical_ray_x;
    float vertical_ray_y;
    float horizontal_len = 0.0;
    float vertical_len = 0.0;
    float start_angle = player->angle - FOV / 2;
    float angle_step = FOV / NUM_RAYS;
    float wall_height = 0.0;
    float full_dist = 0.0;
    sfColor colour;

    printf("player angle = %f\n", player->angle);
    for (i = 0; i < NUM_RAYS; i++) {
        ray_angle = fmod(start_angle + i * angle_step, 2 * M_PI);
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        horizontal_len = draw_horizontal(ray_angle, &horizontal_ray_x,
        &horizontal_ray_y, player);
        vertical_len = draw_vertical(ray_angle, &vertical_ray_x,
        &vertical_ray_y, player);
        if (vertical_len > horizontal_len) {
            rx = horizontal_ray_x;
            ry  = horizontal_ray_y;
            full_dist = horizontal_len;
            colour = sfColor_fromRGB(100, 100, 200);
        } else {
            rx = vertical_ray_x;
            ry  = vertical_ray_y;
            full_dist = vertical_len;
            colour = sfColor_fromRGB(100, 200, 100);
        }
        float delta_angle = ray_angle - player->angle;
    float corrected_dist = full_dist * cos(delta_angle);
    if (corrected_dist <= 0)
        corrected_dist = 0.0001;
    wall_height = (TILE_SIZE / corrected_dist) * PROJECTION_PLANE;
    render_wall_column(window, i, wall_height, colour);
        }
}
