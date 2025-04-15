/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** draw_floor_ceiling
*/

#include "my.h"

void draw_floor_and_ceiling(sfRenderWindow* window)
{
    sfRectangleShape* ceiling = sfRectangleShape_create();
    sfRectangleShape* floor = sfRectangleShape_create();

    sfRectangleShape_setSize(ceiling, (sfVector2f){800, 300});
    sfRectangleShape_setFillColor(ceiling, sfColor_fromRGB(3, 15, 252));
    sfRenderWindow_drawRectangleShape(window, ceiling, NULL);
    sfRectangleShape_setSize(floor, (sfVector2f){800, 300});
    sfRectangleShape_setPosition(floor, (sfVector2f){0, 300});
    sfRectangleShape_setFillColor(floor, sfColor_fromRGB(232, 35, 9));
    sfRenderWindow_drawRectangleShape(window, floor, NULL);
    sfRectangleShape_destroy(ceiling);
    sfRectangleShape_destroy(floor);
}
