/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** struct
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H
    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics/CircleShape.h>
    #include <SFML/Graphics/RectangleShape.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Window/Event.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>
    #include <SFML/Audio/Music.h>
    #define TILE_SIZE 64
    #define MAP_WIDTH 11
    #define MAP_HEIGHT 11
    #define PI 3.14159265
    #define FOV (M_PI / 3)
    #define NUM_RAYS 800
    #define STEP_SIZE 0.1f
    #define SCREEN_WIDTH 800
    #define SCREEN_HEIGHT 600
    #define PROJECTION_PLANE ((float)SCREEN_WIDTH / 2) / tan(FOV / 2)
    #define ROTATION_SPEED 0.005f
    #define MOVEMENT_SPEED 0.2f
    #define P2 PI / 2
    #define P3 3 * PI / 2
    #define RADIAN_DEGREE 0.0175533
    #define X_OFFSET 0
    #define Y_OFFSET 1
    #define DOOR 4

typedef struct {
    float x;
    float y;
    float angle;
    float force_angle;
    float pot_force;
} player_t;

typedef enum {
    PERIM,
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NOWHERE,
} cardinal_t;

void init_player(player_t *player); // Inits the player's position and angle
int is_wall(int x, int y);// Returns 1 if the position corresponds to a wall
void draw_floor_and_ceiling(sfRenderWindow *window);//Drw floor&celing > screen
float cast_single_ray(player_t player, float ray_angle,
    sfRenderWindow *window);
void render_wall_column(sfRenderWindow *window, int column, float wall_height,
    sfColor color);
void key_pressed(sfEvent *event, player_t *player);
void print_pos(int player_x, int player_y, player_t *player);

extern const int map[MAP_HEIGHT][MAP_WIDTH];

#endif
