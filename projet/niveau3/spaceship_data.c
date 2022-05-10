/**
 * \file spaceship_data.c
 * \brief Module pour la gestion des données du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */
 
#include "sdl2-light.h"
#include "spaceship_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * @brief Génère un nombre aléatoire entre la borne a et b
 * 
 * @param a nombre minimum
 * @param b nombre maximum
 * @return int nmbre aléatoire entre a et b
 */
int generate_number (int a, int b){
    return rand()%(b-a)+a;
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
 * @brief Permet d'initialiser le missile comme non lancé
 * 
 * @param sprite savoir si le missile est lancé
 */
void set_no_missile_launch(sprite_t * sprite){
    sprite->missile_launch = 0;
}

/**
 * @brief Initialise un sprite non collisionné
 * 
 * @param sprite Le sprite à initialiser 
 */
void set_not_collided(sprite_t * sprite){
    sprite->collided = 0;
}

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
    set_visible(sprite);
    set_not_collided(sprite);
    set_no_missile_launch(sprite);
}

/**
 * @brief Initialise NB_ENEMIES de manière semi-aléatoire
 * 
 * @param world structure contenant les données du monde
 */
void init_enemies (world_t * world){
    world->enemies = malloc(sizeof(sprite_t) * NB_ENEMIES);
    int dist = -SHIP_SIZE;
    for(int i = 0; i < NB_ENEMIES; i++){
        init_sprite(&(world->enemies[i]), generate_number(0, SCREEN_WIDTH - SHIP_SIZE / 2 ),dist, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED);
        dist -= VERTICAL_DIST;
    }
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world structure contenant les données du monde
 */
void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->compteur = 0;
    world->score = 0;
    world->ending = 0; //Permet d'afficher game over en cas d'appui sur ESCAPE sans terminer la partie
    init_sprite(&(world->main_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    init_sprite(&(world->missile), SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-1.8*SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile)); // Le missile est le seul sprite invisible en début de jeu
    init_enemies(world);
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world structure contenant les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world structure contenant les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}

/**
 * @brief Gère l'arrivée en bordure du vaisseau joueur
 * 
 * @param world structure contenant les données du monde
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
 * @brief Met à jour le compteur en fonction du nombre d'ennemis arrivés en limite vertical
 * 
 * @param world structure contenant les données du monde
 */
void limite_verticale(world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        if(world->enemies[i].y == SCREEN_HEIGHT + SHIP_SIZE){
            world->compteur++;
        }
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
    if (distance < SHIP_SIZE & ((sp2->is_visible == 0) & (sp1->is_visible == 0))){ //On s'assure que les deux sprites soient bien visibles pour que la collision ait lieu
        return 1;
    }
    return 0;
}

/**
 * @brief Permet de vérifier si un sprite est bien visible dans le champ de l'écran
 * 
 * @param sp le sprite dont on vérifie la visibilité
 * @return \a 1 si le sprite est visible \a 0 sinon
 */
int on_the_screen (sprite_t * sp){
    if(sp->y < SCREEN_HEIGHT & sp->y > 0){
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
    //Utiliser la fonction on_the_screen permet de s'assurer que les sprites qui entrent en collisions sont bien dans le champ de l'écran
    if ((sprites_collide(sp2, sp1)==1) & (on_the_screen(sp1)==1) & (on_the_screen(sp2)==1)){
        sp2->v = 0;
        sp1->v = 0;
        sp2->collided = 1;
        sp1->collided = 1;
        sp1->is_visible = 1;
        sp2->is_visible = 1;
    }
}

/**
 * @brief Assure que le missile est bien aligné avec le vaisseau avant l'envoi
 * 
 * @param ship Le vaisseau
 * @param missile Le missile
 */
void align_missile(sprite_t * ship, sprite_t * missile){
    if(missile->is_visible = 1){
        missile->x = ship->x + SHIP_SIZE/2.5;
    }
}

/**
 * @brief Gère le lancement du missile
 * 
 * @param world structure contenant les données du monde
 */
void missile_launch(world_t * world){
    set_visible(&(world->missile)); //rends le missile visible
    world->missile.y -= world->missile.v; //le missile avance à sa vitesse prédéfini dans init_sprite
}

/**
 * @brief replace le missile après collision ou après sa sortie de l'écran
 * 
 * @param world structure contenant les données du monde
 */
void replace_missile(world_t * world){
    if(world->missile.collided == 1 || world->missile.y < 0){ //si collision ou sortie de la limite verticale haute, le missile est replacé comme au début du jeu
        init_sprite(&(world->missile), world->main_ship.x + SHIP_SIZE/2.5, SCREEN_HEIGHT-1.8*SHIP_SIZE , SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
        set_invisible(&(world->missile));
    }
}

/**
 * @brief Augmente le score à chaque fois que le missile touche un ennemi
 * 
 * @param world structure contenant les données du monde
 */
void enemy_hit(world_t * world){
    if(world->missile.collided == 1){ //si missile collided, alors il a touché un ennemi, le score augmente de 1
        world->score++;
    }
}


/**
 * @brief Fais avancer l'ennemi
 * 
 * @param world structure contenant les données du monde
 */
void update_enemies(world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        world->enemies[i].y += world->enemies[i].v;
    }
}

/**
 * @brief Gère la collision entre l'un des ennemies et un autre sprite
 * 
 * @param world structure contenant les données du monde
 */
void handle_enemy_collisions(world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        handle_sprites_collision(&world->main_ship, &world->enemies[i]); //Gère la collision entre l'ennemi et le vaisseau du joueur
        if(world->missile.is_visible==0){
            handle_sprites_collision(&world->missile, &world->enemies[i]); //Gère la collision entre l'ennemi et le missile
        }
    }
}

/**
 * @brief Cas où le vaisseau du joueur est touché par un vaisseau ennemi
 * 
 * @param world structure contenant les données du monde
 */
void mayday(world_t * world){
    if(world->main_ship.collided == 1){
        world->score = 0; //on passe le score à 0
        world->gameover = 1; // signal de fin du jeu
    }
    
}

/**
 * @brief Cas où le joueur touche tout les ennemis
 * 
 * @param world structure contenant les données du monde
 */
void perfect_score(world_t * world){
    if(NB_ENEMIES - world->score == 0){
        world->score = world->score*2; //score doublé si tout les ennemies sont touchés
        world->gameover = 1; // signal de fin du jeu
        world->ending = 2; // scénario de fin avec score parfait
    }
    
}

/**
 * @brief Cas où le jeu est terminé sans que le vaisseau du joueur soit touché et sans qu'il touche tout les vaisseaux ennemies
 * 
 * @param world structure contenant les données du monde
 */
void end_game(world_t * world){
    if(world->score + world->compteur == NB_ENEMIES){ //Si le nombre d'ennemies touchés + nombre d'ennemies sorties de l'écran sont égales au nombres d'ennemies totales, alors c'est la fin du jeu
        world->gameover = 1; // signal de fin du jeu
        world->ending = 1; //scénario de fin où le joueur termine la partie sans toucher tout les ennemies
    }
}

/**
 * @brief Gère les différentes instances de fin de jeu
 * 
 * @param world structure contenant les données du monde
 */
void compute_game(world_t * world){
    mayday(world); // Cas où le vaisseau du joueur est touché
    perfect_score(world); // Cas où le joueur a touché tout les vaisseaux ennemies
    end_game(world); // Cas où le joueur n'a pas eu tout les ennemies mais il n'en reste plus
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world){
    if(world->missile.missile_launch == 1){ // cas où le missile est lancé
        missile_launch(world); //fonction qui active le lancement du missile
        enemy_hit(world); //ajoute 1 point au score par ennemi touché
        replace_missile(world); //fonction qui remplace le missile
    }
    limite_horizontale(world);
    limite_verticale(world);
    handle_enemy_collisions(world);
    update_enemies(world);
    compute_game(world);
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world structure contenant les données du monde
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
                 world->main_ship.x += MAIN_SHIP_SPEED;
                align_missile(&(world->main_ship), &(world->missile)); //aligne le missile sur le sprite du joueur
             }

             if(event->key.keysym.sym == SDLK_LEFT){
                 world->main_ship.x -= MAIN_SHIP_SPEED;
                 align_missile(&(world->main_ship), &(world->missile)); //aligne le missile sur le sprite du joueur
             }

             if((event->key.keysym.sym == SDLK_SPACE)){
                 world->missile.missile_launch = 1; // on active le lancement du missile
             }

             if(event->key.keysym.sym == SDLK_ESCAPE){
                  printf("La touche ESC est appuyée\n");
                  world->gameover = 1;
              }
         }
    }
}