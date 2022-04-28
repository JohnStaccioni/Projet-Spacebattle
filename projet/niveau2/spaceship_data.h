/**
 * \file spaceship_data.h
 * \brief Header d'un module pour la gestion graphique du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#ifndef SPACESHIP_DATA_H_
#define SPACESHIP_DATA_H_

#include <SDL2/SDL.h>
#include "constante.h"
#include "structure.h"


void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);
void set_visible(sprite_t * sprite);
void set_invisible(sprite_t * sprite);
void print_sprite(sprite_t * sprite);
void init_data(world_t * world);
void clean_data(world_t *world);
int is_game_over(world_t *world);
void limite_horizontale(world_t *world);
void limite_verticale(world_t *world);
int sprites_collide(sprite_t *sp2, sprite_t *sp1);
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1);
int collided(sprite_t *sp);
void update_data(world_t *world);
void handle_events(SDL_Event *event,world_t *world);

#endif