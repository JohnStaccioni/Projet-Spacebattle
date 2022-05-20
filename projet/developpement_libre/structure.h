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
#include "constante.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct ressources_s{
    SDL_Texture* logo_jeu; /*!< Texture liée au logo du jeu */

    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* selection_background; /*! Texture liée à l'image en arrière plan de la sélection du joueur dans le menu */
    SDL_Texture* didacticiel; /*!< Texture liée à l'image du didacticiel. */

    //Textures liées au vaisseau du joueur
    SDL_Texture* main_ship_state3; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* main_ship_state2; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* main_ship_state1; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* invincible; /*!< Texture liée au vaisseau du joueur lorsqu'il est invincible. */
    SDL_Texture* speed_up; /*!< Texture liée au vaisseau du joueur lorsqu'il a le bonus de vitesse. */

    SDL_Texture* enemy_ship; /*!< Texture liée au vaisseau ennemi. */

    SDL_Texture* missile; /*!< missile du joueur */

    //Textures liées au bonus
    SDL_Texture* bfg; /*!< missile bonus */
    SDL_Texture* bfg_logo; /*!< logo qui indique que le joueur détient un missile bonus */
    SDL_Texture* speed_up_logo; /*!< logo qui indique que le joueur détient le bonus d'accéleration*/
    SDL_Texture* troies_vies; /*!< logo pour troies vies*/
    SDL_Texture* deux_vies; /*!< logo pour deux vies */
    SDL_Texture* une_vie; /*!< logo pour une vie */


    TTF_Font* title_police; /*!< police utilisée pour les titres dans le jeu */
    TTF_Font* police; /*!< police utilisée pour les affichages dans le jeu */
    SDL_Texture* explosions; /*!< Texture liée aux explosions */
    SDL_Texture* lootbox; /*!< Texture liée aux lootbox */
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
    int main_ship_state; /*!< Indique l'état du vaisseau, permet de simuler des dégats sur le vaisseau du joueur */
};

/**
 * \brief Type qui correspond à sprite_s
 */
typedef struct sprite_s sprite_t;


/**
 * @brief Structure permettant de gérer les animations
 * 
 */
struct animation_s{
    int frameNumber; /*!< Champ indiquant le nombre de frame par bmp pour l'animation*/
    int frameTimer; /*!< Temps entre deux frame */
    int x; /*!< abscisse du centre du vaisseau */
    int y; /*!< ordonné du centre du vaisseau */
    int w; /*!<largeur du sprite */
    int h; /*!<hauteur du sprite */
};

typedef struct animation_s animation_t;

/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int select; /*!< Champ  permettant de gérer le choix sélectionné dans le menu du jeu */
    int menu; /*!< Champ  permettant de gérer les choix dans le menu du jeu */
    int pause; /*!< Champ  permettant de gérer l'état en pause ou non du jeu*/
    int music_playing; /*!< Champ  permettant de gérer l'état en pause ou non du jeu*/
    int nb_vie; /*!< Nombre de vie du joueur*/
    sprite_t main_ship; /*!< Vaisseau du joueur */
    sprite_t missile; /*!< Missile */
    sprite_t bfg; /*!< Missile bonus avec un plus gros champ d'actions*/
    sprite_t * enemies; /*!< Vaisseaux ennemis */
    sprite_t lootbox; /*!< Permet l'ajout de lootbox qui donnent des bonus si le joueur les ramasse */
    int compteur; /*!< Compteur du nombre de vaisseaux sortis de l'écran */
    int score; /*!< Score du joueur */
    int ending; /*!< Permet d'indiquer le type de fin de jeu */
    animation_t explosions[NB_EXPLOSIONS_MAX]; /*!< Permet d'inclure des effets d'explosions */
    int nombre_explosions; /*!< Nombre d'effets d'explosions en cours */
    int lootbox_active; /*!< Permet de définir si une lootbox est active */
    int invincible; /*!< Permet de gérer l'état d'invincibilité du vaisseau du joueur*/
    int speed_bonus; /*!< Permet de gérer le bonus d'augmentation de vitesse du vaisseau du joueur*/
    int bfg_ammo;
    
    int bonus_countdown; /*!< Permet de compter le temps d'un bonus*/
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

#endif