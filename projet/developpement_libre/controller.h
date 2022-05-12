/**
 * \file graphics.h
 * \brief Header d'un module pour la gestion graphique et des données du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 10 mai 2022
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include "constante.h"
#include "structure.h"
#include "spaceship_data.h"
#include "graphics.h"

void print_ending(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world);
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *textures, world_t * world);
void refresh_menu_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void refresh_pause_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);
void refresh_replay_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);

#endif