/**
 * \file audio.h
 * \brief Header pour le module de la gestion audio du jeu
 * \author John STACCIONI / Théo Barrier
 * \version 1.0
 * \date 10 mai 2022
 */

#ifndef AUDIO_H
#define AUDIO_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "structure.h"

void init_audio();
void play_channel_n_sound(const char * path, int n);
void play_music(const char * path);


#endif