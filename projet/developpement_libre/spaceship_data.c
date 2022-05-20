/**
 * \file spaceship_data.c
 * \brief Module pour la gestion des données du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */
 
#include "sdl2-light.h"
#include "spaceship_data.h"
#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "audio.h"

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
    world->nb_vie = 3; //Initialise le nombre de vie
    world->ending = 0; //Permet d'afficher game over en cas d'appui sur ESCAPE sans terminer la partie
    world->nombre_explosions = 0; //Initialise le nombre d'explosions à zéro, le compte et décompte est fait par la fonction apply_explosions
    world->lootbox_active = 0;
    world->invincible = 0;
    world->speed_bonus = 0;
    world->bonus_countdown = 0;
    world->music_playing = 0; //Indique qu'aucune musique ne joue
    world->bfg.missile_launch = 0;
    world->bfg_ammo = 0; //Initialisation du nombre de missile bonus
    init_sprite(&(world->main_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2), SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    init_sprite(&(world->missile), SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-1.8*SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    init_sprite(&(world->bfg), world->main_ship.x, world->main_ship.y , SHIP_SIZE, SHIP_SIZE, BFG_SPEED);
    set_invisible(&(world->missile)); // Le missile est le seul sprite invisible en début de jeu
    set_invisible(&(world->bfg));
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
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1, world_t *world){
    //Utiliser la fonction on_the_screen permet de s'assurer que les sprites qui entrent en collisions sont bien dans le champ de l'écran
    if ((sprites_collide(sp2, sp1)==1) & (on_the_screen(sp1)==1) & (on_the_screen(sp2)==1)){
        sp2->v = 0;
        sp1->v = 0;
        sp2->collided = 1;
        sp1->collided = 1;
        sp1->is_visible = 1;
        sp2->is_visible = 1;
        init_explosion(sp1->x, sp1->y, world);
        play_channel_n_sound("ressources/explosion.wav", 1); //joue le son d'une explosion sur le canal 2 en cas de collision
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
        handle_sprites_collision(&world->main_ship, &world->enemies[i], world); //Gère la collision entre l'ennemi et le vaisseau du joueur
        if(world->missile.is_visible==0){
            handle_sprites_collision(&world->missile, &world->enemies[i], world); //Gère la collision entre l'ennemi et le missile
        }
        if(world->bfg.is_visible==0){
            handle_BFG_collision(&world->bfg, &world->enemies[i], world); //Gère la collision entre l'ennemi et le missile bonus
        }
    }
}

/**
 * @brief Cas où le vaisseau du joueur est touché par un vaisseau ennemi
 * 
 * @param world structure contenant les données du monde
 */
void mayday(world_t * world){
    if(world->main_ship.collided == 1){ //on prends aussi en compte le cas où le vaisseau du joueur a le bonus d'invincibilité
        if(world->invincible == 0){
            world->nb_vie--; //si le vaisseau du joueur est touché, le nombre de vies baisse de 1
        }
        world->main_ship.collided = 0; //on réinitialise la collision du vaisseau joueur
        if(world->nb_vie > 0){
            world->main_ship.is_visible = 0;
        }

        if(world->nb_vie == 2){
            world->main_ship.main_ship_state == 2; //affichage du vaisseau du joueur au stade de dégat 2
            world->main_ship.is_visible = 0;
        }

        if(world->nb_vie == 1){
            world->main_ship.main_ship_state == 1; //affichage du vaisseau du joueur au stade de dégat 1
            world->main_ship.is_visible = 0;
        }

        if(world->nb_vie == 0){
            world->gameover = 1; // signal de fin du jeu
        }
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
    if(world->enemies[NB_ENEMIES-1].y == world->main_ship.y || world->enemies[NB_ENEMIES-1].collided == 1 ){ //Si le nombre d'ennemies touchés + nombre d'ennemies sorties de l'écran sont égales au nombres d'ennemies totales, alors c'est la fin du jeu
        world->gameover = 1; // signal de fin du jeu
        world->ending = 1; //scénario de fin où le joueur termine la partie sans toucher tout les ennemies
    }
}

/**
 * @brief Permet d'augmenter la vitesse des vaisseaux ennemies non collisionés
 * 
 * @param world structure contenant les données du monde
 * @param speed nouvelle vitesse des vaisseau
 */
void speed_enemies_up(world_t * world, int speed){
    for(int i = 0; i < NB_ENEMIES; i++){
            if(world->enemies[i].collided == 0){ //on augmente seulement la vitesse des ennemies qui ne sont pas entrés en collision
                world->enemies[i].v = speed; //on affecte la vitesse speed aux ennemies non collided
            }
        }
}
/**
 * @brief Permet d'augmenter la difficulté du jeu en fonction du score
 * 
 * @param world structure contenant les données du monde
 */
void difficulty_up(world_t * world){
    if(world->score == LEVEL_UP_1){
        speed_enemies_up(world, LEVEL_UP_SPEED_1); //niveau de vitesse 1
    }
    if(world->score == LEVEL_UP_2){
        speed_enemies_up(world, LEVEL_UP_SPEED_2); //niveau de vitesse 2
    }
}

/**
 * @brief Gère les différentes instances d'événements du jeu
 * 
 * @param world structure contenant les données du monde
 */
void compute_game(world_t * world){
    mayday(world); // Cas où le vaisseau du joueur est touché
    perfect_score(world); // Cas où le joueur a touché tout les vaisseaux ennemies
    end_game(world); // Cas où le joueur n'a pas eu tout les ennemies mais il n'en reste plus
    difficulty_up(world); //permet d'augmenter la difficulté en fonction du score
    lootbox_loop(world); //permet d'ajouter des bonus dans le jeu à travers des lootbox
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world structure contenant les données du monde
 */
void update_data(world_t *world){
    if(world->missile.missile_launch == 1){ // cas où le missile est lancé
        missile_launch(world); //fonction qui active le lancement du missile
        enemy_hit(world); //ajoute 1 point au score par ennemi touché
        replace_missile(world); //fonction qui remplace le missile
    }
    if(world->bfg.missile_launch == 1){ // cas où le missile est lancé
        bfg_launch(world); //fonction qui active le lancement du missile
        enemy_hit(world); //ajoute 1 point au score par ennemi touché
        stop_bfg(world); //fonction qui remplace le missile
    }
    limite_horizontale(world);
    limite_verticale(world);
    handle_enemy_collisions(world);
    update_enemies(world);
    compute_game(world);
    bonus_coutdown_and_reset(world); //décompte de la durée des bonus si nécessaire
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
                if(world->speed_bonus == 1){ //Cas où le joueur a ramassé le bonus de vitesse
                    world->main_ship.x += MAIN_SHIP_SPEED_BONUS;
                }
                else{
                    world->main_ship.x += MAIN_SHIP_SPEED;
                }
                align_missile(&(world->main_ship), &(world->missile)); //aligne le missile sur le sprite du joueur
             }

             if(event->key.keysym.sym == SDLK_LEFT){
                 if(world->speed_bonus == 1){ //Cas où le joueur a ramassé le bonus de vitesse
                    world->main_ship.x -= MAIN_SHIP_SPEED_BONUS;
                }
                else{
                    world->main_ship.x -= MAIN_SHIP_SPEED;
                }
                 align_missile(&(world->main_ship), &(world->missile)); //aligne le missile sur le sprite du joueur
             }

             if((event->key.keysym.sym == SDLK_SPACE) & (world->nb_vie != 0 )){
                if(world->bfg_ammo == 0){
                    play_channel_n_sound("ressources/laser_shot.wav",0); //joue un son de laser sur le canal 1 en cas de lancer du missile
                    world->missile.missile_launch = 1; // on active le lancement du missile
                }
                else{
                    align_missile(&(world->main_ship), &(world->bfg)); //aligne le missile bonus sur le vaisseau du joueur
                    play_channel_n_sound("ressources/bfg.wav",0);
                    world->bfg.missile_launch = 1; // on active le lancement du missile bonus
                    world->bfg_ammo--;
                }
                
             }

             if(event->key.keysym.sym == SDLK_ESCAPE){
                  pause_game(world);
              }
         }
    }
}


/**
 * @brief Permet d'initialiser les données du menu de début de jeu
 * 
 * @param world structure contenant les données du monde
 */
void init_menu (world_t *world){
    world->menu = 0;
    world->select = 0;
    world->pause = 0;
}

/**
 * @brief Indique si le joueur a cliqué sur un choix du menu
 * 
 * @param world structure contenant les données du monde
 * @return \a 0 si pas de sélection du joueur \a 1 si le joueur a sélectionné
 */
int is_selected(world_t *world){
    return world->select;
}

/**
 * @brief Permet de controller les choix dans le menu du début du jeu
 * 
 * @param event paramètre qui contient les événements
 * @param world structure contenant les données du monde
 */
void menu_control(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->menu = 2;
            world->select = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             if(event->key.keysym.sym == SDLK_DOWN){
                if(world->menu < 2){
                    world->menu++;
                }

             }

             if(event->key.keysym.sym == SDLK_UP){
                if(world->menu > 0 ){
                    world->menu--;
                }
             }

             if((event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_RETURN)){
                world->select = 1;
             }
         }
    }
}

/**
 * @brief Permet de mettre le jeu en pause
 * 
 * @param world structure contenant les données du monde
 */
void pause_game(world_t * world){
    world->pause = !world->pause;
}

/**
 * @brief Gère le menu de pause
 * 
 * @param event paramètre qui contient les événements
 * @param world structure contenant les données du monde
 */
void handle_pause_menu_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             if(event->key.keysym.sym == SDLK_ESCAPE){
                  pause_game(world);
              }
         }
    }
}

/**
 * @brief Initialise l'explosion
 * 
 * @param x coordonnés x
 * @param y coordonnés y
 * @param world structure contenant les données du monde
 */
void init_explosion(int x, int y, world_t * world){
    if (world->nombre_explosions < NB_EXPLOSIONS_MAX){ // On s'assure que le nombre d'explosions max n'est pas dépassé
            
        //Réinitialisation de la frame et du timer
        world->explosions[world->nombre_explosions].frameNumber = 0;
        world->explosions[world->nombre_explosions].frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
 
        // Initialisation des coordonnées de l'explosion
        world->explosions[world->nombre_explosions].x = x;
        world->explosions[world->nombre_explosions].y = y;
 
        // Hauteur et largeur de l'explosion
        world->explosions[world->nombre_explosions].w = 64;
        world->explosions[world->nombre_explosions].h = 64;

        // Ajout du comptage d'une explosion dans les données du monde
        world->nombre_explosions++;
    }
}

/**
 * @brief COnvertit un int en chaine de caractère afin de permettre son affichage
 * 
 * @return \a char_printing contient le score en chaine de caractères 
 */
char* int_to_char(int a){
    char * char_printing = malloc(sizeof(int)*NB_ENEMIES);
    sprintf(char_printing, "%d", a);
    return char_printing;
}


/**
 * @brief Fait apparaitre des bonus de manière semi aléatoire
 * 
 * @param chance taux de chance d'apparition d'un bonus, plus le nombre est grand et plus les chances sont basses
 * @param world structure contenant les données du monde
 * @return \a 1 si un bonus doit apparaitre \a 0 sinon 
 */
int lootbox_random_spawn(int chance, world_t * world){
    int n = generate_number(0, chance);
    if (n == 5){ //si on tombe sur 5, alors on indique qu'une lootbox va être créée
        return 1;
    }

    return 0;
}

/**
 * @brief Permet de gérer les collisions entre le vaisseau du joueur et les lootbox
 * 
 * @param main_ship vaisseau du joueur
 * @param lootbox lootbox qui donnent les bonus
 * @param world structure contenant les données du monde
 */
void handle_lootbox_collision(sprite_t * main_ship, sprite_t * lootbox, world_t *world){
    //Utiliser la fonction on_the_screen permet de s'assurer que les sprites qui entrent en collisions sont bien dans le champ de l'écran
    if ((sprites_collide(main_ship, lootbox)==1) & (on_the_screen(lootbox)==1) & (on_the_screen(main_ship)==1)){
        lootbox->v = 0;
        lootbox->collided = 1;
        play_channel_n_sound("ressources/coin.wav", 2);
        lootbox->is_visible = 1;
    }
}

/**
 * @brief Permet d'indiquer si une lootbox a été ramassée
 * 
 * @param world structure contenant les données du monde
 */
void handle_lootbox_pick_up(world_t * world){
    handle_lootbox_collision(&world->main_ship, &world->lootbox, world);
    if(world->lootbox.collided == 1){
        world->lootbox_active = 0;
    }

    if(world->lootbox.y > SCREEN_HEIGHT){
        world->lootbox_active = 0;
    }
}

/**
 * @brief bonus qui donne au joueur une vie supplémentaire
 * 
 * @param world structure contenant les données du monde
 */
void bonus_life_up(world_t * world){
    world->lootbox_active = 0;
    world->lootbox.collided = 0;
    world->nb_vie++;
}

/**
 * @brief bonus qui rends le joueur invincible
 * 
 * @param world structure contenant les données du monde
 */
void bonus_invincible(world_t * world){
    world->lootbox_active = 0;
    world->lootbox.collided = 0;
    world->speed_bonus = 0; //annule le bonus de vitesse dans le cas où il avait été attrapé par le joueur
    world->invincible = 1;
    world->bonus_countdown = DUREE_BONUS;
}

/**
 * @brief donne au joueur un bonus de vitesse
 * 
 * @param world structure contenant les données du monde
 */
void bonus_speed_up(world_t * world){
    world->lootbox_active = 0;
    world->lootbox.collided = 0;
    world->invincible = 0; //annule le bonus d'invincibilité dans le cas où il avait été attrapé par le joueur
    world->speed_bonus = 1;
    world->bonus_countdown = DUREE_BONUS;
}

/**
 * @brief permet de donner un bonus de manière aléatoire au joueur
 * 
 * @param world structure contenant les données du monde
 */
void random_bonus(world_t * world){
    srand ( time (NULL) ) ;
    if(world->lootbox.collided == 1){
        int bonus = generate_number(0,4);
        if(bonus == 0){
            if(world->nb_vie < NB_VIES_MAX){ //On ne donne des vies au joueur que s'il n'en a pas le maximum
                bonus_life_up(world);
            }
            else{
                bonus_invincible(world);
            }
        }
        if(bonus == 1){
            bonus_invincible(world);
        }
        if(bonus == 2){
            bonus_bfg(world);
        }
        if(bonus == 3){
            bonus_speed_up(world);
        }
    }
}

/**
 * @brief permet de faire avancer les lootboxs dans le jeu
 * 
 * @param world structure contenant les données du monde
 */
void update_lootbox(world_t * world){
    world->lootbox.y += world->lootbox.v;
}

/**
 * @brief permet de gérer le décompte de durée des bonus invincibilité ou de vitesse
 * 
 * @param world structure contenant les données du monde
 */
void bonus_coutdown_and_reset(world_t * world){
    if(world->bonus_countdown > 0){
        world->bonus_countdown--;
    }
    else{
        world->invincible = 0;
        world->speed_bonus = 0;
    }
}

/**
 * @brief donne au joueur un missile plus puissant (missile bfg)
 * 
 * @param world structure contenant les données du monde
 */
void bonus_bfg(world_t * world){
    if(world->bfg_ammo < NB_BFG_AMMO_MAX){
        world->lootbox_active = 0;
        world->lootbox.collided = 0;
        world->bfg_ammo++;
        init_sprite(&(world->bfg), world->main_ship.x, world->main_ship.y, SHIP_SIZE, SHIP_SIZE, BFG_SPEED);
        world->bfg.missile_launch = 0;
        world->bfg.is_visible = 1;
    }
    else{
        bonus_life_up(world);
    }
}


/**
 * @brief indique que le bfg (missile plus puissant) est lancé
 * 
 * @param world structure contenant les données du monde
 */
void bfg_launch(world_t * world){
    world->bfg.is_visible = 0; //rends le missile bonus visible
    world->bfg.y -= world->bfg.v;
}

/**
 * @brief stop le missile bonus après sa sortie de l'écran et réinitialise son état de lancement
 * 
 * @param world structure contenant les données du monde
 */
void stop_bfg(world_t * world){
    if(world->bfg_ammo > 0){
        if(world->bfg.y < -32){ //si sortie de la limite verticale haute, le missile bonus est arrêté
            world->bfg.v = 0;
            world->bfg.missile_launch = 0;
        }
    }
}

/**
 * @brief gère les collisions entre le missile bonus et les ennemies
 * 
 * @param bfg missile bonus
 * @param enemy ennemies dont on vérifie la collision avec le missile bonus
 * @param world structure contenant les données du monde
 */
void handle_BFG_collision(sprite_t * bfg, sprite_t * enemy, world_t *world){
    //Utiliser la fonction on_the_screen permet de s'assurer que les sprites qui entrent en collisions sont bien dans le champ de l'écran
    if ((sprites_collide(bfg, enemy)==1) & (on_the_screen(bfg)==1) & (on_the_screen(enemy)==1)){
        enemy->v = 0;
        enemy->collided = 1;
        enemy->is_visible = 1;
        world->score++;
        init_explosion(bfg->x, enemy->y, world);
        play_channel_n_sound("ressources/explosion.wav", 1); //joue le son d'une explosion sur le canal 2 en cas de collision
    }
}


/**
 * @brief boucle qui permet de gérer l'apparition et la récupération des lootbox
 * 
 * @param world structure contenant les données du monde
 */
void lootbox_loop(world_t * world){
    if(world->lootbox_active == 0){ //On ne fait pas apparaitre de lootbox s'il y en a déjà une
        int n = lootbox_random_spawn(RANDOM_SPAWN_CHANCE, world);
        if (n == 1 ){ //Si la fonction renvoie 1, alors on créé une lootbox
            world->lootbox_active = 1;
            init_sprite(&(world->lootbox), generate_number(0, SCREEN_WIDTH - SHIP_SIZE / 2 ), -SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED); //place la lootbox de manière semi-aléatoire sur l'axe x
        }
    }
    if (world->lootbox_active == 1){ //Cas où une lootbox est active
        update_lootbox(world); //mouvement de la lootbox
        handle_lootbox_pick_up(world); //vérifie si le joueur a ramassé la lootbox
    }
    if(world->lootbox.collided == 1){
        random_bonus(world); //donne au joueur un bonus aléatoire
    }    
}

/**
 * @brief Permet de gérer les évenements du didacticiel
 * 
 * @param event paramètre qui contient les événements
 * @param world structure contenant les données du monde
 */
void didacticiel_command(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->menu = 1;
            world->select = 1;
        }
       
         //si une touche est appuyée, menu prends la valeur 0 et le jeu va se lancer
         if(event->type == SDL_KEYDOWN){
             if((event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_RETURN)){
                world->menu = 0;
             }
         }
    }
}
