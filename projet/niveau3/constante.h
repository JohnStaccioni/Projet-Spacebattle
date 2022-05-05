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
#define NB_ENEMIES 5


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

#endif