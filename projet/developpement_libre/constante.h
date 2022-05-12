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
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8

/**
 * \brief Vitesse des vaisseaux ennemis
 */
#define ENEMY_SPEED 2

/**
 * \brief Vitesse du missile
 */
#define MISSILE_SPEED 10

/**
 * @brief Nombre d'ennemies
 * 
 */
#define NB_ENEMIES 999


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
#define LEVEL_1 15

/**
 * @brief Score où le niveau de difficulté passe au niveau 2
 * 
 */
#define LEVEL_2 30

/**
 * @brief Vitesses des ennemies au niveau de difficulté 1
 * 
 */
#define LEVEL_1_SPEED 3

/**
 * @brief Vitesses des ennemies au niveau de difficulté 2
 * 
 */
#define LEVEL_2_SPEED 4

#endif