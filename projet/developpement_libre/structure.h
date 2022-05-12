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
#include "sdl2-ttf-light.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* selection_background; /*! Texture liée à l'image en arrière plan de la sélection du joueur dans le menu */
    SDL_Texture* main_ship; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* enemy_ship; /*!< Texture liée au vaisseau ennemi. */
    SDL_Texture* missile; /*! missile du joueur */
    TTF_Font* police; /*! police utilisée pour les affichages dans le jeu */
};

/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct ressources_s ressources_t;


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
    int missile_launch; /*!< Indique si le missile est lancé */
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
    int select; /*!< Champ  permettant de gérer le choix sélectionné dans le menu du jeu */
    int menu; /*!< Champ  permettant de gérer les choix dans le menu du jeu */
    int pause; /*!< Champ  permettant de gérer l'état en pause ou non du jeu*/
    sprite_t main_ship; /*!< Vaisseau du joueur */
    sprite_t missile; /*!< Missile */
    sprite_t * enemies; /*!< Vaisseaux ennemis */
    int compteur; /*!< Compteur du nombre de vaisseaux sortis de l'écran */
    int score; /*!< Score du joueur */
    int ending; /*!< Permet d'indiquer le type de fin de jeu */
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

#endif