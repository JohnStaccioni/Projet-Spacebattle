/**
 * \file audio.c
 * \brief Module pour la gestion audio du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 10 mai 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "audio.h"

/**
 * @brief Initialise et paramètre les canaux audios
 * 
 */
void init_audio(){
    Mix_OpenAudio(41000,MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(3);
    Mix_Volume(1,128);
    Mix_Volume(2,128);
    Mix_Volume(3,128);
}

/**
 * @brief Permet de jouer un son sur un canal n
 * 
 * @param path le chemin du son à jouer
 * @param n le canal sur lequel jouer le son
 */
void play_channel_n_sound(const char * path, int n){
    Mix_Chunk* music = Mix_LoadWAV(path);
    Mix_PlayChannel(n,music, 0);
}

/**
 * @brief Permet de jouer une musique sur le canal 3
 * 
 * @param path le chemin de la musique à jouer
 */
void play_music(const char * path){
    Mix_Chunk* music = Mix_LoadWAV(path);
    Mix_PlayChannel(3,music, -1);
}