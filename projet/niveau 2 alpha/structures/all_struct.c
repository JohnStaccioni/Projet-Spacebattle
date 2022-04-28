/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* main_ship; /*!< Texture liée au vaisseau du joueur. */
    SDL_Texture* enemy_ship; /*!< Texture liée au vaisseau ennemi. */
    SDL_Texture* missile; /*! missile du joueur */
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
    int is_visible; /*!< Permet l'affichage du missile */
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
    sprite_t enemy_ship; /*!< Vaisseau ennemi */
    sprite_t missile; /*!< Missile */
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
    printf("Abscisse du centre du sprite %d \nOrdonné du centre du sprite %d\nLargeur du sprite %d\nHauteur du sprite %d\nVitesse verticale du sprite %d\nVisibilité du sprite %d\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v, sprite->is_visible);
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