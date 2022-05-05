/**
 * \file graphics.c
 * \brief Module pour la gestion graphique du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#include "sdl2-light.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2-ttf-light.h"



/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(ressources_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->main_ship);
    clean_texture(textures->enemy_ship);
    clean_texture(textures->missile);
    clean_font(textures->police);
}


/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, ressources_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->main_ship = load_image("ressources/spaceship.bmp", renderer);
    textures->enemy_ship = load_image("ressources/enemy.bmp", renderer);
    textures->missile = load_image("ressources/missile.bmp", renderer);
    textures->police = load_font("ressources/arial.ttf",14);
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, ressources_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}


/**
 * \brief La fonction qui applique la texture associée au sprite
 * \param renderer moteur de rendu
 * \param texture image du sprite
 * \param sprite structure contenant les informations liés au sprite
*/
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t*sprite){
    if(sprite->collided == 1 && sprite->is_visible == 0){
        clean_texture(texture);
    }
    if(sprite->is_visible == 0){
        SDL_Rect dst = {0, 0, 0, 0};
    
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
        dst.x = sprite->x; dst.y = sprite->y;
    
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
}

/**
 * @brief Permet d'afficher NB_ENEMIES ennemies
 * 
 * @param renderer moteur de rendu
 * @param texture image du sprite
 * @param world structure contenant les données du monde
 */
void apply_enemies(SDL_Renderer *renderer, SDL_Texture *texture, world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        apply_sprite(renderer,texture, &(world->enemies[i]));
    }
}

/**
 * @brief COnvertit le score en chaine de caractère afin de permettre son affichage
 * 
 * @return \a score_printing contient le score en chaine de caractères 
 */
char* score_to_char(int a){
    char * score_printing = malloc(sizeof(int)*NB_ENEMIES);
    sprintf(score_printing, "%d", a);
    return score_printing;
}

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