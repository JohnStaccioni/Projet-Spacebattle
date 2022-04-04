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
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* main_ship; /*!< Texture liée au vaisseau du joueur. */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;

/**
 * \brief Structure pour gérer le placement du vaisseau
 */

struct sprite_s{
    SDL_Texture * player_ship; /*!< Texture liée au vaisseau */
    int x; /*!< abscisse du centre du vaisseau */
    int y; /*!< ordonné du centre du vaisseau */
    int w; /*!<largeur du sprite */
    int h; /*!<hauteur du sprite */
    int v; /*!< vitesse verticale du sprite */
};

/**
 * \brief Type qui correspond à sprite_s
 */
typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    sprite_t main_ship; /*!< Vaisseau du joueur */
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

/**
 * \brief programme de test de l'affichage du Vaisseau du joueur
 * \param sprite pointeur vers la structure sprite_t du vaisseau du joueur
 */
 void print_sprite(sprite_t * sprite){
    printf("Abscisse du centre du sprite %d \nOrdonné du centre du sprite %d\nLargeur du sprite %d\nHauteur du sprite %d\nVitesse verticale du sprite %d\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v);
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
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    init_sprite(&(world->main_ship), (SCREEN_WIDTH/2-SHIP_SIZE/2),SCREEN_HEIGHT-3*SHIP_SIZE/2,SHIP_SIZE,SHIP_SIZE,10);
    print_sprite(&(world->main_ship));
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
    /* A COMPLETER */
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
             }
             if(event->key.keysym.sym == SDLK_LEFT){
                 world->main_ship.x -= 8;
             }
             //si la touche appuyée est 'D'
             if(event->key.keysym.sym == SDLK_d){
                 printf("La touche D est appuyée\n");
              }
         }
        print_sprite(&(world->main_ship));
    }
}


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->main_ship);
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->main_ship = load_image("ressources/spaceship.bmp", renderer);
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures){
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
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = sprite->x; dst.y = sprite->y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures->main_ship, &(world->main_ship));
    
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
