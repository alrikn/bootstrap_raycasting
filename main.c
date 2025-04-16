/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** main
*/

#include "./include/my.h"
#include "struct.h"
#include <SFML/Window/Event.h>
#include <math.h>
#include <stdbool.h>

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
//
//static void key_pressed(core_t *fm, sfEvent *event)
//{
//    if (event->key.code == sfKeyL) {
//        if (fm->status.disable_hitboxes == false)
//            fm->status.disable_hitboxes = true;
//        else
//            fm->status.disable_hitboxes = false;
//    }
//    if (event->key.code == sfKeyS) {
//        if (fm->status.invisible_sprites == false)
//            fm->status.invisible_sprites = true;
//        else
//            fm->status.invisible_sprites = false;
//    }
//}

sfRenderWindow* create_window(void)
{
    sfVideoMode video_mode = {800, 600, 32};

    return sfRenderWindow_create(video_mode, "Raytracer",
    sfClose | sfTitlebar, NULL);
}

void handle_closure(sfRenderWindow* window, sfEvent event)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
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
        handle_closure(window, event);
        sfRenderWindow_clear(window, sfBlack);
        draw_floor_and_ceiling(window);
        cast_all_rays(window, player);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
