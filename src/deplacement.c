#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"



void beemove(Joueur *joueur, int DIR, int** map, Bomb* bomb1, Bomb* bomb2, int num){
    switch(DIR){
    case HAUT:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BRICK &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y - CASESIZE) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x || bomb2->rect.y != joueur->rect.y - CASESIZE)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] = num;
                joueur->rect.y -= CASESIZE;
               }
        }
        joueur->position = HAUT;
        break;
    case BAS:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BRICK &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y + CASESIZE) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x || bomb2->rect.y != joueur->rect.y + CASESIZE)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] = num;
                joueur->rect.y += CASESIZE;
            }
        }
        joueur->position = BAS;
        break;
    case DROITE:
        if(map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BRICK &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x + CASESIZE || bomb1->rect.y != joueur->rect.y) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x + CASESIZE || bomb2->rect.y != joueur->rect.y)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] = num;
                joueur->rect.x += CASESIZE;
            }
        }
        joueur->position = DROITE;
        break;
    case GAUCHE:
        if(map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BRICK &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x - CASESIZE || bomb1->rect.y != joueur->rect.y) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x - CASESIZE || bomb2->rect.y != joueur->rect.y)) {
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] = num;
                joueur->rect.x -= CASESIZE;
            }
        }
        joueur->position = GAUCHE;
        break;
    }
}
