/**
 * \file audio.c
 * \brief Module pour la gestion audio du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 10 mai 2022
 */

#include "sdl2-light.h"
#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2-ttf-light.h"
#include "SDL/SDL_mixer.h"

SDL_Init(SDL_INIT_AUDIO);
