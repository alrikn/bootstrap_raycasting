/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** render_wall
*/

#include "my.h"
#include <math.h>

void render_wall_column(sfRenderWindow* window, int column,
    float wall_height, sfColor color)
{
    sfRectangleShape* column_rect = sfRectangleShape_create();
    sfVector2f size = {SCREEN_WIDTH / (float)NUM_RAYS, wall_height};
    float y_pos = ((float)SCREEN_HEIGHT / 2) - (wall_height / 2);
    float darkness = fmin(1.0f, wall_height / 400.0f);

    sfRectangleShape_setSize(column_rect, size);
    sfRectangleShape_setPosition(column_rect,
    (sfVector2f){column *size.x, y_pos});
    color.r *= darkness;
    color.g *= darkness;
    color.b *= darkness;
    sfRectangleShape_setFillColor(column_rect, color);
    sfRenderWindow_drawRectangleShape(window, column_rect, NULL);
    sfRectangleShape_destroy(column_rect);
}
