/**
 * \file spaceship_data.h
 * \brief Header d'un module pour la gestion des données du jeu
 * \author John STACCIONI/ Théo Barrier
 * \version 1.0
 * \date 07 avril 2022
 */

#ifndef SPACESHIP_DATA_H_
#define SPACESHIP_DATA_H_

#include <SDL2/SDL.h>
#include "constante.h"
#include "structure.h"

int generate_number (int a, int b);
void set_visible(sprite_t * sprite);
void set_invisible(sprite_t * sprite);
void set_no_missile_launch(sprite_t * sprite);
void set_not_collided(sprite_t * sprite);
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);
void init_enemies (world_t * world);
void init_data(world_t * world);
void clean_data(world_t *world);
int is_game_over(world_t *world);
void limite_horizontale(world_t *world);
void limite_verticale(world_t * world);
int sprites_collide(sprite_t *sp2, sprite_t *sp1);
int on_the_screen (sprite_t * sp);
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1, world_t * world);
int collided(sprite_t *sp);
void align_missile(sprite_t * ship, sprite_t * missile);
void missile_launch(world_t * world);
void replace_missile(world_t * world);
void enemy_hit(world_t * world);
void update_enemies(world_t * world);
void handle_enemy_collisions(world_t * world);
void update_data(world_t *world);
void mayday(world_t * world);
void perfect_score(world_t * world);
void end_game(world_t * world);
void compute_game(world_t * world);
char* int_to_char(int a);
void handle_events(SDL_Event *event,world_t *world);

//Fonctions rajoutés en développement libre:
void init_menu (world_t *world);
int is_selected(world_t *world);
void menu_control(SDL_Event *event,world_t *world);
void pause_game(world_t * world);
void handle_pause_menu_events(SDL_Event *event,world_t *world);
void speed_enemies_up(world_t * world, int speed);
void difficulty_up(world_t * world);
void init_explosion(int x, int y, world_t * world);

//Fonctions permettant l'ajout des bonus
int lootbox_random_spawn(int chance, world_t * world);
void handle_lootbox_pick_up(world_t * world);
void bonus_life_up(world_t * world);
void bonus_invicible(world_t * world);
void bonus_speed_up(world_t * world);
void random_bonus(world_t * world);
void update_lootbox(world_t * world);
void bonus_coutdown_and_reset(world_t * world);
void bonus_bfg(world_t * world);
void bfg_launch(world_t * world);
void stop_bfg(world_t * world);
void handle_BFG_collision(sprite_t * bfg, sprite_t * enemy, world_t *world);
void lootbox_loop(world_t * world);

//Fonction pour l'affichage du didacticiel
void didacticiel_command(SDL_Event *event,world_t *world);

#endif