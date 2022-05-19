/**
 * \file tests.c
 * \brief Programme de tests du jeu
 * \author John STACCIONI / Théo Barrier
 * \version 1.0
 * \date 20 avril 2022
 */

#include "constante.h"
#include "structure.h"
#include "spaceship_data.h"
#include "time.h"

/**
 * @brief Affichage des tests pour la fonction limite_horizontale
 * 
 * @param world structure contenant les données du monde
 */
void test_limite_horizontale_param(world_t * world){
    printf("Le vaisseau est situé à %d sur l'axe x.", world->main_ship.x);
    limite_horizontale(world);
    printf(" Il est replacé à %d.\n", world->main_ship.x);
}

/**
 * @brief Fonction de test pour la fonction limite_horizontale avec des paramètres
 * 
 */
void test_limite_horizontale(){
    world_t world;
    world.main_ship.x= 356;
    test_limite_horizontale_param(&world);
    world.main_ship.x= 15;
    test_limite_horizontale_param(&world);
    world.main_ship.x= -48;
    test_limite_horizontale_param(&world);
}


/**
 * @brief Affichage des tests pour la fonction limite_verticale
 * 
 * @param world structure contenant les données du monde
 */

/*
void test_limite_verticale_param(world_t * world){
    printf("Le vaisseau est situé à %d sur l'axe y.", world->enemy_ship.y);
    limite_verticale(world);
    printf(" Il est replacé à %d.\n", world->enemy_ship.y);
}
*/


/**
 * @brief Fonction de test pour la fonction limite_verticale avec des paramètres
 * 
 */

/*
void test_limite_verticale(){
    world_t world;
    world.enemy_ship.y= 800;
    test_limite_verticale_param(&world);
    world.enemy_ship.y= 250;
    test_limite_verticale_param(&world);
}
*/

/**
 * @brief Affichage des tests pour la fonction sprites_collide
 * 
 * @param sp2 Le sprite pour lequel on teste la collision avec le sprite sp1
 * @param sp1 Le sprite pour lequel on teste la collision avec le sprite sp2
 */
void test_sprites_collide_param(sprite_t *sp2, sprite_t *sp1){
    if(sprites_collide(sp2,sp1) == 1){
        printf("Le sprite 1 est situé aux points x = %d et y = %d.\nLe sprite 2 est situé aux points x = %d et y = %d.\nLes deux sprites sont donc rentrés en collision.\n",sp1->x,sp1->y,sp2->x,sp2->y);
    }
    else{
        printf("Le sprite 1 est situé aux points x = %d et y = %d.\nLe sprite 2 est situé aux points x = %d et y = %d.\nLes deux sprites ne sont pas entrés en collision.\n",sp1->x,sp1->y,sp2->x,sp2->y);
    }
}

/**
 * @brief Fonction de test pour la fonction sprites_collide avec des paramètres
 * 
 */
void test_sprites_collide(){
    sprite_t * vaisseau_1 = malloc(sizeof(sprite_t));
    sprite_t * vaisseau_2 = malloc(sizeof(sprite_t));
    vaisseau_1->x=100;
    vaisseau_1->y=200;
    vaisseau_2->x=100;
    vaisseau_2->y=200;
    test_sprites_collide_param(vaisseau_1, vaisseau_2);
    printf("\n");
    vaisseau_1->x=100;
    vaisseau_1->y=200;
    vaisseau_2->x=500;
    vaisseau_2->y=300;
    test_sprites_collide_param(vaisseau_1, vaisseau_2);
    printf("\n");
    vaisseau_1->x=100;
    vaisseau_1->y=200;
    vaisseau_2->x= vaisseau_1->x + SHIP_SIZE ;
    vaisseau_2->y= vaisseau_1->y + SHIP_SIZE;
    test_sprites_collide_param(vaisseau_1, vaisseau_2);
    printf("\n");
}

/**
 * @brief Affichage des tests pour la fonction handle_sprites_collision
 * 
 * @param sp2 Le sprite pour lequel on teste la collision avec le sprite sp1
 * @param sp1 Le sprite pour lequel on teste la collision avec le sprite sp2
 */
void test_handle_sprites_collision_param(sprite_t *sp2, sprite_t *sp1, world_t * world){
    handle_sprites_collision(sp2,sp1, world);
    if(sprites_collide(sp2,sp1)==1){
        printf("Les deux sprites sont entrés en collision et leur vitesse est passé à %d pour sp1 et %d pour sp2.\n", sp1->v, sp2->v);
    }
    else{
        printf("Les deux sprites ne sont pas entrés en collision, leur vitesse est à %d pour sp1 et %d pour sp2.\n", sp1->v, sp2->v);
    }
}

/**
 * @brief Fonction de test pour la fonction handle_sprites_collide avec des paramètres
 * 
 */
void test_handle_sprites_collision(){
    sprite_t * vaisseau_1 = malloc(sizeof(sprite_t));
    sprite_t * vaisseau_2 = malloc(sizeof(sprite_t));
    world_t * world;
    vaisseau_1->x = 100;
    vaisseau_1->y = 200;
    vaisseau_1->v = 5;
    vaisseau_2->x = 100;
    vaisseau_2->y = 200;
    vaisseau_2->v = 2;
    test_handle_sprites_collision_param(vaisseau_1, vaisseau_2, world);
    printf("\n");
    vaisseau_1->x = 100;
    vaisseau_1->y = 200;
    vaisseau_1->v = 5;
    vaisseau_2->x = 500;
    vaisseau_2->y = 300;
    vaisseau_2->v = 2;
    test_handle_sprites_collision_param(vaisseau_1, vaisseau_2, world);
    printf("\n");
    vaisseau_1->x = 100;
    vaisseau_1->y = 200;
    vaisseau_1->v = 5;
    vaisseau_2->x = vaisseau_1->x + SHIP_SIZE ;
    vaisseau_2->y = vaisseau_1->y + SHIP_SIZE;
    vaisseau_2->v = 2;
    test_handle_sprites_collision_param(vaisseau_1, vaisseau_2, world);
    printf("\n");
}

/**
 * @brief Affichage pour le test de la fonction init_ennemies
 * 
 * @param world structure contenant les données du monde
 */
void test_init_ennemies_param(world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        printf("Ennemi %d :\nX: %d / Y: %d\n\n", i, world->enemies[i].x, world->enemies[i].y);
    }
}

/**
 * @brief Tests de la fonction init_ennemies avec des paramètres
 * 
 */
void test_init_ennemies(){
    world_t world;
    init_enemies(&world);
    test_init_ennemies_param(&world);
}

/**
 * @brief Affichage du test pour la fonction update_data
 * 
 * @param world structure contenant les données du monde
 */
void test_update_data_param(world_t * world){
    for(int i = 0; i < NB_ENEMIES; i++){
        printf("Ennemi %d :\n Après une séquence, Y = %d\n\n", i, world->enemies[i].y);
    }
}

/**
 * @brief Test de la fonction update_data avec des paramètres
 * 
 */
void test_update_data(){
    world_t world;
    init_enemies(&world);
    update_enemies(&world);
    test_update_data_param(&world);
}

int main( int argc, char* args[]){
    srand(time(NULL));
    test_limite_horizontale();
    //test_limite_verticale();
    test_sprites_collide();
    test_handle_sprites_collision();
    test_init_ennemies();
    test_update_data();
    return EXIT_SUCCESS;
}