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
#include "audio.h"

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
    if(world->nb_vie > 2){ //affichage du vaisseau du joueur en état intact
        apply_sprite(renderer, textures->main_ship_state3, &(world->main_ship));
    }
    if(world->nb_vie==2){ //affichage du vaisseau du joueur en état de dégradation 
        apply_sprite(renderer, textures->main_ship_state2, &(world->main_ship));
    }
    if(world->nb_vie==1){ //affichage du vaisseau du joueur en état de dégradation final
        apply_sprite(renderer, textures->main_ship_state1, &(world->main_ship));
    }
    apply_enemies(renderer, textures->enemy_ship, world);
    apply_sprite(renderer, textures->missile, &(world->missile));

    //Affichage du score et du nombre de vie
    if(!is_game_over(world)){
        apply_text(renderer, SCREEN_WIDTH - 30, 0, 32, 32,int_to_char(world->score),textures->police); //affichage du score
        apply_text(renderer, 5 , 0, 32, 32,int_to_char(world->nb_vie),textures->police);
    }
    
    else{
        print_ending(renderer,world,textures);
    }

    //Gestion des explosions
    apply_explosions(renderer, world, textures);

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

/**
 * @brief Permet d'appliquer les explosions quand il y a des collisions
 * 
 * @param renderer moteur de rendu
 * @param world structure contenant les données du monde
 * @param textures image du sprite 
 */
void apply_explosions(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    for (int i = 0; i < world->nombre_explosions; i++)
    {
 
        //Gestion du timer
        // Cas où le timer arrive à zéro
        if (world->explosions[i].frameTimer <= 0)
        {
            //Réinitialisation du timer
            world->explosions[i].frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
 
            //Passage à la frame suivante
            world->explosions[i].frameNumber++;
 
            //Efface l'explosion si on dépasse la dernière frame (animation terminée)
            int w;
            SDL_QueryTexture(textures->explosions, NULL, NULL, &w, NULL);
            if (world->explosions[i].frameNumber >= w / world->explosions[i].w)
            {
                // Libère le sprite 
                world->explosions[i] = world->explosions[world->nombre_explosions - 1];
                world->nombre_explosions--;
                return;
            }
        }
        //Cas où le timer n'est pas encore à zéro, on le décrément
        else
            world->explosions[i].frameTimer--;

        //Affichage de l'explosion
        // Rectangle de destination qui contient la texture
        SDL_Rect dest;
 
        // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
        //au scrolling :
        dest.x = world->explosions[i].x;
        dest.y = world->explosions[i].y;
        dest.w = world->explosions[i].w;
        dest.h = world->explosions[i].h;
 
        // Rectangle source
        SDL_Rect src;
 
        //Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
        //la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 64; 2 = 128...
        src.x = world->explosions[i].frameNumber * world->explosions[i].w;
        src.y = 0;
        src.w = world->explosions[i].w;
        src.h = world->explosions[i].h;
 
        // Dessine l'explosion
        SDL_RenderCopy(renderer, textures->explosions, &src, &dest);
    }
}