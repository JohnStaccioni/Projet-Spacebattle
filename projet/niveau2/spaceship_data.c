/**
 * \file spaceship_data.c
 * \brief Module pour la gestion graphique du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */
 
#include "sdl2-light.h"
#include "spaceship_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * \brief fonction qui initalise le sprite
 * \param sprite texture du vaisseau du joueur
 * \param x abscisse du centre du sprite
 * \param y ordonné du centre du sprite
 * \param w largeur du sprite
 * \param h hauteur du sprite
 * \param v vitesse verticale du sprite
*/

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->v = v;
    sprite->is_visible = 0;
}

/**
 * \brief Rend un sprite visible
 * \param sprite sprite rendu visible par la fonction
 **/
 void set_visible(sprite_t * sprite){
     sprite->is_visible = 0;
 }

 /**
 * \brief Rend un sprite invisible
 * \param sprite sprite rendu invisible par la fonction
 **/
 void set_invisible(sprite_t * sprite){
     sprite->is_visible = 1;
}

/**
 * \brief programme de test de l'affichage du Vaisseau du joueur
 * \param sprite pointeur vers la structure sprite_t du vaisseau du joueur
 */
 void print_sprite(sprite_t * sprite){
    printf("Abscisse du centre du sprite %d \nOrdonné du centre du sprite %d\nLargeur du sprite %d\nHauteur du sprite %d\nVitesse verticale du sprite %d\nVisibilité du sprite %d\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v, sprite->is_visible);
 }


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    init_sprite(&(world->main_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    world->main_ship.collided = 0;
    //print_sprite(&(world->main_ship));
    init_sprite(&(world->enemy_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), -SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED);
    world->enemy_ship.collided = 0;
    //print_sprite(&(world->enemy_ship));
    init_sprite(&(world->missile), SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-1.8*SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
    world->missile.collided = 0;
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
 * @brief Gère l'arrivée en bordure du vaisseau joueur
 * 
 * @param world les données du monde
 */
void limite_horizontale(world_t *world){
    if(world->main_ship.x <= 0){
        world->main_ship.x = 0;
    }
    if(world->main_ship.x >= SCREEN_WIDTH-SHIP_SIZE){
        world->main_ship.x = SCREEN_WIDTH-SHIP_SIZE;
    }
}

/**
 * @brief Gère l'arrivée en bordure verticale du vaisseau ennemi 
 * 
 * @param world 
 */
void limite_verticale(world_t *world){
    if(world->enemy_ship.y >= SCREEN_HEIGHT + SHIP_SIZE){
        world->enemy_ship.y = -SHIP_SIZE;
    }
}

/**
 * @brief Indique si deux sprites sont entrés en collision
 * 
 * @param sp2 Le sprite pour lequel on teste la collision avec le sprite sp1
 * @param sp1 Le sprite pour lequel on teste la collision avec le sprite sp2
 * @return \a int 1 si collision, 0 sinon
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    int collision_x = sp2->x - sp1->x;
    int collision_y = sp2->y - sp1->y;
    int distance = sqrt(collision_x * collision_x + collision_y * collision_y);

    // cas où il y a une collision entre deux sprites
    if (distance < SHIP_SIZE){
        return 1;
    }
    return 0;
}

/**
 * @brief Gère la collision de deux sprites, met leur vitesse à 0 et indique qu'ils sont entrés en collision dans la structure des sprites
 * 
 * @param sp2 Le sprite 2 pour lequel on change les paramètres si une collision a lieu
 * @param sp1 Le sprite 1 pour lequel on change les paramètres si une collision a lieu
 */
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1){
    if (sprites_collide(sp2, sp1)==1){
        sp2->v = 0;
        sp1->v = 0;
        sp2->collided = 1;
        sp1->collided = 1;
        sp1->is_visible = 1;
        sp2->is_visible = 1;
    }
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world){
    world->enemy_ship.y += world->enemy_ship.v ;
    if (world->missile.is_visible==0) {
        world->missile.y -= world->missile.v;
        handle_sprites_collision(&world->enemy_ship, &world->missile);
    }
    limite_horizontale(world);
    limite_verticale(world);
    handle_sprites_collision(&world->main_ship, &world->enemy_ship);
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
             if((event->key.keysym.sym == SDLK_SPACE) /*&& (world->main_ship.collided !=1)*/){
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