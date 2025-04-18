/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** draw_floor_ceiling
*/

#include "my.h"
#include "math.h"

/*
** closer to the middle the darker
*/
void draw_ceiling(sfRenderWindow* window, const int center_y,
    const float max_distance, float distance)
{
    float normalized = 0.0;
    float brightness = 0.0;
    sfColor ceiling_color;
    sfRectangleShape* line;

    for (int y = 0; y < center_y; y++) {
        distance = center_y - y;
        normalized = distance / max_distance;
        brightness = powf(normalized, 2.0f);
        ceiling_color = sfColor_fromRGB(10, 10, 20);
        ceiling_color.r *= brightness;
        ceiling_color.g *= brightness;
        ceiling_color.b *= brightness;
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){SCREEN_WIDTH, 1});
        sfRectangleShape_setPosition(line, (sfVector2f){0, y});
        sfRectangleShape_setFillColor(line, ceiling_color);
        sfRenderWindow_drawRectangleShape(window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

void draw_floor(sfRenderWindow* window, const int center_y,
    const float max_distance, float distance)
{
    float normalized = 0.0;
    float brightness = 0.0;
    sfColor floor_color;
    sfRectangleShape* line;

    for (int y = center_y; y < SCREEN_HEIGHT; y++) {
        distance = y - center_y;
        normalized = distance / max_distance;
        brightness = powf(normalized, 2.0f);
        floor_color = sfColor_fromRGB(140, 80, 15);
        floor_color.r *= brightness;
        floor_color.g *= brightness;
        floor_color.b *= brightness;
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){SCREEN_WIDTH, 1});
        sfRectangleShape_setPosition(line, (sfVector2f){0, y});
        sfRectangleShape_setFillColor(line, floor_color);
        sfRenderWindow_drawRectangleShape(window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

void draw_floor_and_ceiling(sfRenderWindow* window)
{
    const int center_y = SCREEN_HEIGHT / 2;
    const float max_distance = center_y;

    draw_ceiling(window, center_y, max_distance, 0);
    draw_floor(window, center_y, max_distance, 0);
}
