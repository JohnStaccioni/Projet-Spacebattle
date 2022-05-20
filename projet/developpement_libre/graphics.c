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

    clean_texture(textures->logo_jeu);
    clean_texture(textures->background);
    clean_texture(textures->selection_background);
    clean_texture(textures->didacticiel);

    //On nettoie les différentes textures liés au différents états de dégat du vaisseau du joueur
    clean_texture(textures->main_ship_state3);
    clean_texture(textures->main_ship_state2);
    clean_texture(textures->main_ship_state1);
    
    //On nettoie la texture des lootbox et bonus
    clean_texture(textures->lootbox);
    clean_texture(textures->bfg);
    clean_texture(textures->bfg_logo);
    clean_texture(textures->speed_up_logo);
    clean_texture(textures->invincible);


    //Nettoyage des textures qui compte la vie
    clean_texture(textures->troies_vies);
    clean_texture(textures->deux_vies);
    clean_texture(textures->une_vie);


    clean_texture(textures->enemy_ship);
    clean_texture(textures->missile);
    clean_texture(textures->explosions);

    clean_font(textures->police);
    clean_font(textures->title_police);
}


/*void apply_background(SDL_Renderer *renderer, ressources_t *textures){

}*/
/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void  init_textures(SDL_Renderer *renderer, ressources_t *textures){
    textures->logo_jeu = load_image( "ressources/jeu_logo.bmp",renderer);
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->selection_background = load_image("ressources/Fond_texte.bmp",renderer);
    textures->didacticiel = load_image("ressources/didactitiel.bmp",renderer);

    //Textures du vaisseau du joueur
    textures->main_ship_state3 = load_image("ressources/spaceship.bmp", renderer);
    textures->main_ship_state2 = load_image("ressources/spaceship_2.bmp", renderer);
    textures->main_ship_state1 = load_image("ressources/spaceship_1.bmp", renderer);

    //Textures liées aux bonus
    textures->lootbox = load_image("ressources/lootbox.bmp", renderer);
    textures->bfg = load_image("ressources/bfg.bmp",renderer);
    textures->invincible = load_image("ressources/spaceship_invincible.bmp", renderer);
    textures->speed_up = load_image("ressources/spaceship_speed_up.bmp", renderer);
    textures->bfg_logo = load_image("ressources/bfg_logo.bmp", renderer);
    textures->speed_up_logo = load_image("ressources/speed_up_logo.bmp", renderer);

    //TExtures liées au niveau de vie
    textures->troies_vies = load_image("ressources/3_Vies.bmp", renderer);
    textures->deux_vies = load_image("ressources/2_Vies.bmp", renderer);
    textures->une_vie = load_image("ressources/1_Vie.bmp", renderer);

    textures->enemy_ship = load_image("ressources/enemy.bmp", renderer);

    
    textures->missile = load_image("ressources/missile.bmp", renderer);
    textures->title_police = load_font("ressources/Blackout-2am.ttf",20);
    textures->police = load_font("ressources/arial.ttf",14);
    textures->explosions = load_image("ressources/explosion.bmp", renderer);
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
 * @brief Permet d'afficher un écran de didacticiel
 * 
 * @param renderer  moteur de rendu
 * @param textures image à afficher
 */
void affichage_didactitiel(SDL_Renderer *renderer,ressources_t *textures){
     //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_texture(textures->didacticiel, renderer, 0, 0);

    // on met à jour l'écran
    update_screen(renderer);
}
