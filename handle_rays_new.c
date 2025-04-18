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

void draw_ray(player_t *player, sfRenderWindow* window)
{
    int r;
    int mx;
    int my;
    int map_pos;
    int map_x;
    int map_y;
    int dof; //depth of view
    float rx; //
    float ry;
    float ray_angle = player->angle;
    float xo; //x offset
    float yo; // y offset
    float horizontal_ray_x;
    float horizontal_ray_y;
    float vertical_ray_x;
    float vertical_ray_y;
    float horizontal_len = 0.0;
    float vertical_len = 0.0;


    ray_angle = player->angle - RADIAN_DEGREE * 40;
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    if (ray_angle > 2 * PI)
        ray_angle -= 2 * PI;

    printf("ray angle is %f\n", ray_angle);
    for (r = 0; r < 80; r++) {
        //this cjhecks horizontal grid lines
        dof = 0;
        float aTan = -1 / tan(ray_angle);
        if (ray_angle > M_PI) { //loking down
            ry = (((int)(player->y)>>6)<<6)-0.0001; // thy is to round the value
            rx = ((player->y) - ry) * aTan + (player->x);
            yo = -64;
            xo = -yo * aTan;
        }
        if (ray_angle < M_PI) { //looking up
            ry = (((int)(player->y)>>6)<<6) + 64; // thy is to round the value
            rx = ((player->y) - ry) * aTan + (player->x);
            yo = 64;
            xo = -yo * aTan;
        }
        if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) { // looking staright eft or straight right
            rx = (player->x);
            ry = (player->y);
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mx = mx < 0 ? 0 : mx;
            mx = mx >= MAP_WIDTH ? MAP_WIDTH - 1 : mx;
            my = my < 0 ? 0 : my;
            my = my >= MAP_HEIGHT ? MAP_HEIGHT - 1 : my;
            if (mx >= 0 && mx < MAP_WIDTH && 
                my >= 0 && my < MAP_HEIGHT &&
                map[my][mx] == 1) {
                dof = 8;
                horizontal_ray_x = rx;
                horizontal_ray_y = ry;
                horizontal_len = distance_calculator(player->x, horizontal_ray_x,
                player->y, horizontal_ray_y);
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        ////check vertical lines
        dof = 0;
        float nTan = -tan(ray_angle);
        if (ray_angle > P2 && ray_angle < P3) { //looking left
            rx = (((int)(player->x)>>6)<<6)-0.0001; // thy is to round the value
            ry = ((player->x) - rx) * nTan + (player->y);
            xo = -64;
            yo = -xo * nTan;
        } 
        if (ray_angle < P2 || ray_angle > P3) { //looking right
            rx = (((int)(player->x)>>6)<<6) + 64; // thy is to round the value
            ry = ((player->x) - rx) * nTan + (player->y);
            xo = 64;
            yo = -xo * nTan;
        }
        if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591)) { // looking staright eft or straight right
            rx = (player->x);
            ry = (player->y);
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mx = mx < 0 ? 0 : mx;
            mx = mx >= MAP_WIDTH ? MAP_WIDTH - 1 : mx;
            my = my < 0 ? 0 : my;
            my = my >= MAP_HEIGHT ? MAP_HEIGHT - 1 : my;
            if (mx >= 0 && mx < MAP_WIDTH && 
                my >= 0 && my < MAP_HEIGHT &&
                map[my][mx] == 1) {
                dof = 8;
                vertical_ray_x = rx;
                vertical_ray_y = ry;
                vertical_len = distance_calculator(player->x, vertical_ray_x,
                player->y, vertical_ray_y);
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        if (vertical_len > horizontal_len) {
            rx = horizontal_ray_x;
            ry  = horizontal_ray_y;
        } else {
            rx = vertical_ray_x;
            ry  = vertical_ray_y;
        }
        // Draw the vertical ray (gibbidy don't forget to remove)
        sfVertexArray* v_line = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(v_line, sfLines);
    sfVertex v_start = {
        .position = {player->x, player->y},
        .color = sfColor_fromRGB(0, 150, 255)
    };
    sfVertex v_end = {
        .position = {rx, ry},
        .color = sfColor_fromRGB(0, 150, 255)
    };
    sfVertexArray_append(v_line, v_start);
    sfVertexArray_append(v_line, v_end);
    sfRenderWindow_drawVertexArray(window, v_line, NULL);
    sfVertexArray_destroy(v_line);
    ray_angle += RADIAN_DEGREE;
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    if (ray_angle > 2 * PI)
        ray_angle -= 2 * PI;
    }
}
