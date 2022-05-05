/**
 * \file graphics.h
 * \brief Header d'un module pour la gestion graphique du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "constante.h"
#include "structure.h"
#include "spaceship_data.h"


void clean_textures(ressources_t *textures);
void  init_textures(SDL_Renderer *renderer, ressources_t *textures);
void apply_background(SDL_Renderer *renderer, ressources_t *textures);
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t*sprite);
void print_ending(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world);
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *textures, world_t * world);

#endif