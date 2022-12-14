/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author John STACCIONI / Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#include "sdl2-light.h"
#include "constante.h"
#include "structure.h"
#include "graphics.h"
#include "controller.h"
#include "spaceship_data.h"
#include "audio.h"
#include "SDL_mixer.h"

int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    ressources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init_menu(&world);
    init(&window,&renderer,&textures,&world);
    init_audio();
    
    //Menu du jeu
    while(is_selected(&world) == 0){
        if(world.music_playing == 0){ //Si aucune musique ne joue, alors on joue le thème du menu, permet d'éviter que la musique boucle
            play_music("ressources/menu_theme.wav");
            world.music_playing = 1;
        }
         //gestion des évènements du menu
        menu_control(&event,&world);

        //rafraichissement de l'écran
        refresh_menu_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //affichage du didactitiel
    while(world.menu == 1){
          //gestion des évènements du didactitiel
        didacticiel_command(&event,&world);

        //rafraichissement de l'écran
        affichage_didactitiel(renderer, &textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    //Jeu en cours
    if(world.menu == 0){
        world.music_playing = 0; //remise à zéro de la musique
        while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        if(world.music_playing == 0){//Si aucune musique ne joue, alors on joue le thème du jeu, permet d'éviter que la musique boucle
            play_music("ressources/gameplay_theme.mp3");
            world.music_playing = 1;
        }
            //gestion des évènements
            handle_events(&event,&world);
        
            //mise à jour des données liée à la physique du monde
            update_data(&world);
        
            //rafraichissement de l'écran
            refresh_graphics(renderer,&world,&textures);
        
            // pause de 10 ms pour controler la vitesse de rafraichissement
            pause(10);


            //Jeu mis en pause
            while(world.pause == 1){
                //gestion des évènements dans le menu pause 
                handle_pause_menu_events(&event, &world);


                //affichage d'un texte indiquant la pause du jeu
                refresh_pause_graphics(renderer,&world,&textures);
            }
                
        }

        //Boucle de fin de jeu pour laisser le temps d'afficher le score
        for(int i = 0; i < 200; i++){ //boucle qui permet l'affichage à la fin du jeu et ferme l'application au bout de quelques secondes
            //gestion des évènements
            handle_events(&event,&world);
        
            //mise à jour des données liée à la physique du monde
            update_data(&world);
        
            //rafraichissement de l'écran
            refresh_graphics(renderer,&world,&textures);
        
            // pause de 10 ms pour controler la vitesse de rafraichissement
            pause(10);
        }
    }
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
