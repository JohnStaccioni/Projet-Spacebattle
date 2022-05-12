/**
 * \file controller.c
 * \brief Module pour la gestion graphique et des données du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 10 mai 2022
 */

#include "sdl2-light.h"
#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2-ttf-light.h"

/**
 * @brief Affiche une fin en fonction du scénario de fin stocké dans la structure world
 * 
 * @param renderer moteur de rendu
 * @param world structure contenant les données du monde
 * @param textures image du sprite
 */
void print_ending(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    if(world->ending == 0){ // Cas où le joueur perds
        apply_text(renderer, 50, 200, 200, 100,"GAME OVER!",textures->police);
    }
    if(world->ending == 1){ //Cas où le joueur termine sans toucher tout les ennemies
        apply_text(renderer, 50, 200, 200, 100,"YOU SURVIVED!",textures->police);
    }
    if(world->ending == 2){ //Cas où le joueur touche tout les ennemies
        apply_text(renderer, 50, 200, 200, 100,"CONGRATULATIONS!",textures->police);
    }
}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer moteur de rendu
 * \param world structure contenant les données du monde
 * \param textures image du sprite
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures->main_ship, &(world->main_ship));
    apply_enemies(renderer, textures->enemy_ship, world);
    apply_sprite(renderer, textures->missile, &(world->missile));

    //Affichage du score
    if(!is_game_over(world)){
        apply_text(renderer, 5, 0, 32, 32,score_to_char(world->score),textures->police);
    }
    else{
        print_ending(renderer,world,textures);
    }

    // on met à jour l'écran
    update_screen(renderer);
}

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window fenêtre du jeu
* \param renderer moteur de rendu
* \param textures image du sprite
* \param world structure contenant les données du monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer moteur de rendu
 * \param textures image du sprite
 * \param world structure contenant les données du monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_textures(*renderer,textures);
}

/**
 * @brief permet de mettre en avance la sélection du joueur dans le menu
 * 
 */
void apply_selection_background(ressources_t *texture,SDL_Renderer *renderer, world_t * world){
    if(world->menu == 0){
        apply_texture(texture->selection_background, renderer, 40, 160);
    }
    if(world->menu == 1){
        apply_texture(texture->selection_background, renderer, 40, 260);
    }
}


/**
 * \brief La fonction rafraichit l'écran de menu fonction de l'état des données du monde
 * \param renderer moteur de rendu
 * \param world structure contenant les données du monde
 * \param textures image du sprite
 */

void refresh_menu_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);

    //Affichage des choix du menu
    apply_selection_background(textures,renderer, world);
    apply_text(renderer, 50, 150, 200, 100,"PLAY",textures->police);
    apply_text(renderer, 50, 250, 200, 100,"EXIT",textures->police);

    // on met à jour l'écran
    update_screen(renderer);
}

/**
 * @brief La fonction rafraichit l'écran du menu de pause en fonction de l'état des données du monde
 * 
 * @param renderer moteur de rendu
 * \param world structure contenant les données du monde
 * \param textures image du sprite 
 */
void refresh_pause_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);

    //Affichage des choix du menu
    apply_selection_background(textures,renderer, world);
    apply_text(renderer, 50, 150, 200, 100,"PAUSE",textures->police);

    // on met à jour l'écran
    update_screen(renderer);
}