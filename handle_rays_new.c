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
    int search_level = 0;
    float aTan = -1 / tan(ray_angle);
    float y_off;
    float x_off;
    int map_x;
    int map_y;
    float horizontal_len = 100000;

    if (ray_angle > M_PI) {
        *horizontal_y = (((int)(player->y) >> 6) << 6) - 0.0001;
        *horizontal_x = ((player->y) - *horizontal_y) * aTan + (player->x);
        y_off = -64;
        x_off = -y_off * aTan;
    }
    if (ray_angle < M_PI) {
        *horizontal_y = (((int)(player->y) >> 6) << 6) + 64;
        *horizontal_x = ((player->y) - *horizontal_y) * aTan + (player->x);
        y_off = 64;
        x_off = -y_off * aTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) {
        *horizontal_x = (player->x);
        *horizontal_y = (player->y);
        search_level = 10;
    }
    while (search_level < 10) {
        map_x = (int)(*horizontal_x) >> 6;
        map_y = (int)(*horizontal_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= MAP_WIDTH ? MAP_WIDTH - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= MAP_HEIGHT ? MAP_HEIGHT - 1 : map_y;
        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT &&
            map[map_y][map_x] == 1) {
            search_level = 10;
            horizontal_len = distance_calculator(player->x, *horizontal_x,
            player->y, *horizontal_y);
        } else {
            *horizontal_x += x_off;
            *horizontal_y += y_off;
            search_level += 1;
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
    int search_level = 0;
    float nTan = -tan(ray_angle);
    float y_off;
    float x_off;
    int map_x;
    int map_y;
    float vertical_len = 100000;

    if (ray_angle > P2 && ray_angle < P3) {
        *vertical_x = (((int)(player->x) >> 6 ) << 6)-0.0001;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        x_off = -64;
        y_off = -x_off * nTan;
    } 
    if (ray_angle < P2 || ray_angle > P3) {
        *vertical_x = (((int)(player->x) >> 6) << 6) + 64;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        x_off = 64;
        y_off = -x_off * nTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) {
        *vertical_x = (player->x);
        *vertical_y = (player->y);
        search_level = 8;
    }
    while (search_level < 10) {
        map_x = (int)(*vertical_x) >> 6;
        map_y = (int)(*vertical_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= MAP_WIDTH ? MAP_WIDTH - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= MAP_HEIGHT ? MAP_HEIGHT - 1 : map_y;
        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT &&
            map[map_y][map_x] == 1) {
            search_level = 10;
            vertical_len = distance_calculator(player->x, *vertical_x,
            player->y, *vertical_y);
        } else {
            *vertical_x += x_off;
            *vertical_y += y_off;
            search_level += 1;
        }
    }
    return vertical_len;
}
