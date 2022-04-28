/**
 * \file structure.h
 * \brief Header d'un module pour la gestion et modification des structures du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "sdl2-light.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* main_ship; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* enemy_ship; /*!< Texture liée au vaisseau ennemi. */
    SDL_Texture* missile; /*! missile du joueur */
};

/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


/**
 * \brief Structure pour gérer le placement du vaisseau
 */

struct sprite_s{
    SDL_Texture * player_ship; /*!< Texture liée au vaisseau */
    int x; /*!< abscisse du centre du vaisseau */
    int y; /*!< ordonné du centre du vaisseau */
    int w; /*!<largeur du sprite */
    int h; /*!<hauteur du sprite */
    int v; /*!< vitesse verticale du sprite */
    int is_visible; /*!< Visibilité ou invisibilité du sprite */
    int collided; /*!< Indique si deux sprites sont entrés en collision */
};

/**
 * \brief Type qui correspond à sprite_s
 */
typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    sprite_t main_ship; /*!< Vaisseau du joueur */
    sprite_t enemy_ship; /*!< Vaisseau ennemi */
    sprite_t missile; /*!< Missile */
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

#endif