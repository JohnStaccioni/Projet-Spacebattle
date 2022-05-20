/**
 * \file constante.h
 * \brief Header d'un module pour la gestion et modification des constantes du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#ifndef CONSTANTE_H
#define CONSTANTE_H

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32

/**
 * @brief Vitesse horizontale du joueur
 * 
 */
#define MAIN_SHIP_SPEED 8

/**
 * @brief Vitesse horizontale du joueur
 * 
 */
#define MAIN_SHIP_SPEED_BONUS 14

/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8

/**
 * \brief Vitesse des vaisseaux ennemis
 */
#define ENEMY_SPEED 1

/**
 * \brief Vitesse du missile
 */
#define MISSILE_SPEED 10

/**
 * @brief Nombre d'ennemies
 * 
 */
#define NB_ENEMIES 500


/**
 * @brief Distance verticale entre deux ennemis
 * 
 */
#define VERTICAL_DIST 2 * SHIP_SIZE

/**
 * @brief Nombre de boucles avant de fermer l'application
 * 
 */
#define TURNING_OFF 100

/**
 * @brief Score où le niveau de difficulté passe au niveau 1
 * 
 */
#define LEVEL_UP_1 10


/**
 * @brief Vitesses des ennemies au niveau de difficulté 1
 * 
 */
#define LEVEL_UP_SPEED_1 2

/**
 * @brief Score où le niveau de difficulté passe au niveau 2
 * 
 */
#define LEVEL_UP_2 20


/**
 * @brief Vitesses des ennemies au niveau de difficulté 2
 * 
 */
#define LEVEL_UP_SPEED_2 3


/**
 * @brief Nombre d'explosions possibles en simultané
 * 
 */
#define NB_EXPLOSIONS_MAX 10

/**
 * @brief Temps entre deux frames pour une animation
 * 
 */
#define TIME_BETWEEN_2_FRAMES_PLAYER 5

/**
 * @brief Correspond à 1 sur la chance d'apparition d'un bonus par séquence de rafraichissement
 * 
 */
#define RANDOM_SPAWN_CHANCE 100


/**
 * @brief Temps du bonus invicibilité
 * 
 */
#define DUREE_BONUS 500

/**
 * @brief Permet de définir un nombre de vie maximum que le joueur peut acquérir
 * 
 */
#define NB_VIES_MAX 3

/**
 * @brief Permet de définir le nombre de munitions du missile bonus (plus gros missile)
 * 
 */
#define NB_BFG_AMMO_MAX 1


/**
 * @brief Vitesse du missile bonus
 * 
 */
#define BFG_SPEED 2

#endif