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