/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"


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




void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->v = v;
    sprite->is_visible = 0;
}
void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    init_sprite(&(world->main_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    //print_sprite(&(world->main_ship));
    init_sprite(&(world->enemy_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), -SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED);
    //print_sprite(&(world->enemy_ship));
    init_sprite(&(world->missile), SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-1.8*SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
}



/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->enemy_ship.y += ENEMY_SPEED ;
    if(world->missile.is_visible==0){
        world->missile.y -= MISSILE_SPEED;
    }
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             if(event->key.keysym.sym == SDLK_RIGHT){
                 world->main_ship.x += 8;
                 if(world->missile.is_visible==1){
                     world->missile.x += 8;
                 }
             }
             if(event->key.keysym.sym == SDLK_LEFT){
                 world->main_ship.x -= 8;
                 if(world->missile.is_visible==1){
                    world->missile.x -= 8;
                 }
             }
             //si la touche appuyée est 'D'
             if(event->key.keysym.sym == SDLK_d){
                 printf("La touche D est appuyée\n");
              }
             if(event->key.keysym.sym == SDLK_SPACE){
                 set_visible(&(world->missile));
             }
             if(event->key.keysym.sym == SDLK_ESCAPE){
                  printf("La touche ESC est appuyée\n");
                  world->gameover = 1;
              }
         }
    }
    //print_sprite(&(world->main_ship));
}
