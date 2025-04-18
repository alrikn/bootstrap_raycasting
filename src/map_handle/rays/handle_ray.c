/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_rays_new
*/

#include "my.h"
#include "struct.h"
#include <math.h>


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

static float exception_horizontal(player_t *player, float *horiz_x,
    float *horiz_y)
{
    int search_level = 0;

    *horiz_x = (player->x);
    *horiz_y = (player->y);
    search_level = 10;
    return search_level;
}

static int horizontal_not_found(float *horiz_x,
    float *horiz_y, float *offset, int search_level)
{
    *horiz_x += offset[X_OFFSET];
    *horiz_y += offset[Y_OFFSET];
    search_level += 1;
    return search_level;
}

static float horizontal_loop(float *offset, float *horiz_x,
    float *horiz_y, player_t *player)
{
    int map_x;
    int map_y;
    int level = 0;

    while (level < 10) {
        map_x = (int)(*horiz_x) >> 6;
        map_y = (int)(*horiz_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= MAP_WIDTH ? MAP_WIDTH - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= MAP_HEIGHT ? MAP_HEIGHT - 1 : map_y;
        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT && map[map_y][map_x] == 1) {
            return distance_calculator(player->x, *horiz_x,
            player->y, *horiz_y);
        } else
            level = horizontal_not_found(horiz_x, horiz_y, offset, level);
    }
    return 100000;
}

/*
** this checks horizontal intersections
*/
float draw_horizontal(float ray_angle, float *horiz_x,
    float *horiz_y, player_t *player)
{
    int search_level = 0;
    float aTan = -1 / tan(ray_angle);
    float offset[2];

    if (ray_angle > M_PI) {
        *horiz_y = (((int)(player->y) >> 6) << 6) - 0.0001;
        *horiz_x = ((player->y) - *horiz_y) * aTan + (player->x);
        offset[Y_OFFSET] = -64;
        offset[X_OFFSET] = -offset[Y_OFFSET] * aTan;
    }
    if (ray_angle < M_PI) {
        *horiz_y = (((int)(player->y) >> 6) << 6) + 64;
        *horiz_x = ((player->y) - *horiz_y) * aTan + (player->x);
        offset[Y_OFFSET] = 64;
        offset[X_OFFSET] = -offset[Y_OFFSET] * aTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591))
        search_level = exception_horizontal(player, horiz_x, horiz_y);
    return horizontal_loop(offset, horiz_x, horiz_y, player);
}

static int vertical_not_found(float *vertical_x,
    float *vertical_y, float *offset, int search_level)
{
    *vertical_x += offset[X_OFFSET];
    *vertical_y += offset[Y_OFFSET];
    search_level += 1;
    return search_level;
}

static float vertical_loop(player_t *player, float *vertical_x,
    float *vertical_y, float *offset)
{
    int map_x;
    int map_y;
    int search_level = 0;

    while (search_level < 10) {
        map_x = (int)(*vertical_x) >> 6;
        map_y = (int)(*vertical_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= MAP_WIDTH ? MAP_WIDTH - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= MAP_HEIGHT ? MAP_HEIGHT - 1 : map_y;
        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT && map[map_y][map_x] == 1) {
            return distance_calculator(player->x, *vertical_x,
            player->y, *vertical_y);
        } else
            search_level = vertical_not_found(vertical_x, vertical_y,
            offset, search_level);
    }
    return 1000000;
}

static float exception_vertical(player_t *player, float *vertical_x,
    float *vertical_y)
{
    int search_level = 0;

    *vertical_x = (player->x);
    *vertical_y = (player->y);
    search_level = 10;
    return search_level;
}

/*
** this checks vertical intersections
*/
float draw_vertical(float ray_angle, float *vertical_x,
    float *vertical_y, player_t *player)
{
    int search_level = 0;
    float nTan = -tan(ray_angle);
    float offset[2];

    if (ray_angle > P2 && ray_angle < P3) {
        *vertical_x = (((int)(player->x) >> 6) << 6) - 0.0001;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        offset[X_OFFSET] = -64;
        offset[Y_OFFSET] = -offset[X_OFFSET] * nTan;
    }
    if (ray_angle < P2 || ray_angle > P3) {
        *vertical_x = (((int)(player->x) >> 6) << 6) + 64;
        *vertical_y = ((player->x) - *vertical_x) * nTan + (player->y);
        offset[X_OFFSET] = 64;
        offset[Y_OFFSET] = -offset[X_OFFSET] * nTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591))
        search_level = exception_vertical(player, vertical_x, vertical_y);
    return vertical_loop(player, vertical_x, vertical_y, offset);
}
