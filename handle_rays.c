/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_rays
*/

#include "my.h"
#include "struct.h"
#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdio.h>

/*
** here we move through the array and increment each time
*/
static float step_ray(player_t player, float ray_angle,
    float dir_x, float dir_y)
{
    float ray_x = 0.0;
    float ray_y = 0.0;
    int hit_wall = 0;
    float dx = 0.0;
    float dy = 0.0;

    ray_x = player.x;
    ray_y = player.y;
    hit_wall = 0;
    while (!hit_wall) {
        ray_x += dir_x * STEP_SIZE;
        ray_y += dir_y * STEP_SIZE;
        hit_wall = is_wall(ray_x, ray_y);
    }
    dx = ray_x - player.x;
    dy = ray_y - player.y;
    return sqrt(dx * dx + dy * dy);
}

float cast_single_ray(player_t player, float ray_angle, sfRenderWindow* window)
{
    float dir_x = 0.0;
    float dir_y = 0.0;
    float correction = 0.0;
    float distance = 0.0;

    ray_angle = fmod(ray_angle, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;
    dir_x = cos(ray_angle);
    dir_y = sin(ray_angle);
    distance = step_ray(player, ray_angle, dir_x, dir_y);
    correction = cos(player.angle - ray_angle);
    return distance * correction;
}

static sfVector2f get_ray_hit_position(float distance, player_t player,
    float ray_angle)
{
    sfVector2f hit;

    hit.x = (player.x + cosf(ray_angle) * distance);
    hit.y = (player.y + sinf(ray_angle) * distance);
    return hit;
}

/*
** first is east west sencound is south north
*/
static sfColor make_colour(float distance, player_t player, float ray_angle)
{
    sfColor colour;
    float hit_x = player.x + cos(ray_angle) * distance;
    float hit_y = player.y + sin(ray_angle) * distance;
    cardinal_t card = find_cardinal(hit_x, hit_y);
    float x_offset = fmod(hit_x, TILE_SIZE);
    float y_offset = fmod(hit_y, TILE_SIZE);

    if (card == NORTH || card == SOUTH)
        colour = sfColor_fromRGB(100, 100, 200);
    if (card == WEST || card == EAST)
        colour = sfColor_fromRGB(100, 200, 100);
    if (card == PERIM)
        colour = sfColor_fromRGB(237, 237, 19);
    if (card == NOWHERE)
        colour = sfColor_fromRGB(100, 100, 100);
    return colour;
}

/*
**
*/
void cast_all_rays(sfRenderWindow* window, player_t player)
{
    float start_angle = player.angle - FOV / 2;
    float angle_step = FOV / NUM_RAYS;
    float ray_angle = 0.0;
    float distance = 0.0;
    float corrected_dist = 0.0;
    float wall_height = 0.0;

    for (int i = 0; i < NUM_RAYS; i++) {
        ray_angle = fmod(start_angle + i * angle_step, 2 * M_PI);
        distance = cast_single_ray(player, ray_angle, window);
        corrected_dist = distance;
        wall_height = (TILE_SIZE / corrected_dist) * (PROJECTION_PLANE);
        render_wall_column(window, i, wall_height,
        make_colour(distance, player, ray_angle));
    }
    draw_ray(&player, window);
}
