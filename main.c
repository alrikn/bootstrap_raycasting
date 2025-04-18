/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** main
*/

#include "./include/my.h"
#include "struct.h"
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static int explanation(void)
{
    my_cooler_putstr("[MY_RADAR]\n\t-h shows this help message\n");
    my_cooler_putstr("Air traffic simulation panel\n");
    my_cooler_putstr("USAGE: \n\t");
    my_cooler_putstr("./my_radar [OPTIONS] path_to_script\n\t");
    my_cooler_putstr("path_to_script\tThe path to the script file\n OPTION\n");
    my_cooler_putstr("\t-h\tprint the usage and quit\nUSER INTERACTIONS\n");
    my_cooler_putstr("\t'L' key\tenable/disable hitboxes and areas.\n");
    my_cooler_putstr("\t'S' key\tenable/disable sprites.\n");
    return 0;
}

sfRenderWindow* create_window(void)
{
    sfVideoMode video_mode = {800, 600, 32};

    return sfRenderWindow_create(video_mode, "Raytracer",
    sfClose | sfTitlebar, NULL);
}

void handle_closure(sfRenderWindow* window, sfEvent event, player_t *player)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.key.type == sfEvtKeyPressed)
            key_pressed(&event, player);
    }
}

int main(int ac, char **av)
{
    player_t player;
    sfRenderWindow* window = create_window();
    sfEvent event;

    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h')
        return explanation();
    sfRenderWindow_setFramerateLimit(window, 60);
        init_player(&player);
    while (sfRenderWindow_isOpen(window)) {
        handle_closure(window, event, &player);
        sfRenderWindow_clear(window, sfBlack);
        draw_floor_and_ceiling(window);
        cast_all_rays(&player, window);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
