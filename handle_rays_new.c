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

void draw_ray(player_t *player, sfRenderWindow* window)
{
    int r;
    int mx;
    int my;
    int map_pos;
    int map_x;
    int map_y;
    int dof; //depth of view
    float rx;
    float ry;
    float ray_angle = player->angle;
    float xo; //x offset
    float yo; // y offset

    if (player->x < 0 || player->y < 0) {
        printf("POS IS NEGATIVE AAAAAAAAAAAAAAAA\n");
    }
    for (r = 0; r < 1; r++) {
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
        if (ray_angle == 0 || ray_angle == PI) { // looking staright eft or straight right
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
            printf("map y = %d, map x = %d\n", my, mx);
            if (mx >= 0 && mx < MAP_WIDTH && 
                my >= 0 && my < MAP_HEIGHT &&
                map[my][mx] == 1) {
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        // Draw thehorizontal ray (gibiddy)
    sfVertexArray* h_line = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(h_line, sfLines);
    sfVertex h_start = {
        .position = {player->x, player->y},
        .color = sfColor_fromRGB(255, 0, 0)  // Bright red
    };
    sfVertex h_end = {
        .position = {rx, ry},
        .color = sfColor_fromRGB(255, 0, 0)
    };
    sfVertexArray_append(h_line, h_start);
    sfVertexArray_append(h_line, h_end);
    sfRenderStates states = {
        .transform = sfTransform_Identity,
        .texture = NULL,
        .shader = NULL,
        .blendMode = sfBlendAlpha
    };
    
    for(int i = -1; i <= 1; i++) {
        states.transform = sfTransform_Identity;
        sfTransform_translate(&states.transform, i, 0);
        sfRenderWindow_drawVertexArray(window, h_line, &states);
    }
    sfVertexArray_destroy(h_line);
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
            printf("we looking right\n");
            rx = (((int)(player->x)>>6)<<6) + 64; // thy is to round the value
            ry = ((player->x) - rx) * nTan + (player->y);
            xo = 64;
            yo = -xo * nTan;
        }
        if (ray_angle == 0 || ray_angle == PI) { // looking staright eft or straight right
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
            printf("map y = %d, map x = %d\n", my, mx);
            if (mx >= 0 && mx < MAP_WIDTH && 
                my >= 0 && my < MAP_HEIGHT &&
                map[my][mx] == 1) {
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        // Draw the vertical ray (also gibbidy don't forget to remove)
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
    }
}
