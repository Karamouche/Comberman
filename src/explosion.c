#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"



void explosion(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, int** map, SDL_Rect* bricks){
    int x = bomb->rect.x;
    int y = bomb->rect.y;
    int bTop = FALSE;
    int bBot = FALSE;
    int bLeft = FALSE;
    int bRight = FALSE;
    for(int i = 1; i <= LENEXPLOSION ; i++){
        //MODIFIER LA CONDITION CAR BUG
        if(isMapped(x/CASESIZE, y/CASESIZE + i) && !bBot){
            if(map[x/CASESIZE][y/CASESIZE + i] == BRICK){
                map[x/CASESIZE][y/CASESIZE + i] = VIDE;
                bBot = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE + i] == BLOC)
                bBot = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR1){
                bBot = TRUE;
            }
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR2){
                bBot = TRUE;
            }
        }
        if(isMapped(x/CASESIZE, y/CASESIZE - i) && !bTop){
            if(map[x/CASESIZE][y/CASESIZE - i] == BRICK){
                map[x/CASESIZE][y/CASESIZE - i] = VIDE;
                bTop = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE - i] == BLOC)
                bTop = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR1){
                bTop = TRUE;
            }
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR2){
                bTop = TRUE;
            }
        }
        if(isMapped(x/CASESIZE + i, y/CASESIZE) && !bRight){
            if(map[x/CASESIZE + i][y/CASESIZE] == BRICK){
                map[x/CASESIZE + i][y/CASESIZE] = VIDE;
                bRight = TRUE;
            }else if(map[x/CASESIZE + i][y/CASESIZE] == BLOC)
                bRight = TRUE;
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR1){
                bRight = TRUE;
            }
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR2){
                bRight = TRUE;
            }
        }
        if(isMapped(x/CASESIZE - i, y/CASESIZE) && !bLeft){
            if(map[x/CASESIZE - i][y/CASESIZE] == BRICK){
                map[x/CASESIZE - i][y/CASESIZE] = VIDE;
                bLeft = TRUE;
            }else if(map[x/CASESIZE - i][y/CASESIZE] == BLOC)
                bLeft = TRUE;
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR1){
                bLeft = TRUE;
            }
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR2){
                bLeft = TRUE;
            }
        }
    }
}

void explosionDamage(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, Mix_Chunk* dmg, int** map){
    int x = bomb->rect.x;
    int y = bomb->rect.y;
    int bTop = FALSE;
    int bBot = FALSE;
    int bLeft = FALSE;
    int bRight = FALSE;
    for(int i = 1; i <= LENEXPLOSION ; i++){
        if(isMapped(x/CASESIZE, y/CASESIZE + i) && !bBot){
            if(map[x/CASESIZE][y/CASESIZE + i] == BRICK){
                bBot = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE + i] == BLOC)
                bBot = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
        }
        if(isMapped(x/CASESIZE, y/CASESIZE - i) && !bTop){
            if(map[x/CASESIZE][y/CASESIZE - i] == BRICK){
                bTop = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE - i] == BLOC)
                bTop = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
        }
        if(isMapped(x/CASESIZE + i, y/CASESIZE) && !bRight){
            if(map[x/CASESIZE + i][y/CASESIZE] == BRICK){
                bRight = TRUE;
            }else if(map[x/CASESIZE + i][y/CASESIZE] == BLOC)
                bRight = TRUE;
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
        }
        if(isMapped(x/CASESIZE - i, y/CASESIZE) && !bLeft){
            if(map[x/CASESIZE - i][y/CASESIZE] == BRICK){
                bLeft = TRUE;
            }else if(map[x/CASESIZE - i][y/CASESIZE] == BLOC)
                bLeft = TRUE;
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 0);
            }
        }
    }
}

Flams* createFlams(SDL_Renderer* renderer){
    Flams* flams = malloc(sizeof(Flams));
    //HAUTEUR
    flams->b1.h = CASESIZE;
    flams->b2.h = CASESIZE;
    flams->h1.h = CASESIZE;
    flams->h2.h = CASESIZE;
    flams->g1.h = CASESIZE;
    flams->g2.h = CASESIZE;
    flams->d1.h = CASESIZE;
    flams->d2.h = CASESIZE;
    //LARGEUR
    flams->b1.w = CASESIZE;
    flams->b2.w = CASESIZE;
    flams->h1.w = CASESIZE;
    flams->h2.w = CASESIZE;
    flams->g1.w = CASESIZE;
    flams->g2.w = CASESIZE;
    flams->d1.w = CASESIZE;
    flams->d2.w = CASESIZE;

    flams->shown = FALSE;

    return flams;
}

void setCoordFlams(Flams* flams, int x, int y){
    //X
    flams->b1.x = x;
    flams->b2.x = x;
    flams->h1.x = x;
    flams->h2.x = x;
    flams->g1.x = x - CASESIZE;
    flams->g2.x = x - 2*CASESIZE;
    flams->d1.x = x + CASESIZE;
    flams->d2.x = x + 2*CASESIZE;
    //Y
    flams->b1.y = y + CASESIZE;
    flams->b2.y = y + 2*CASESIZE;
    flams->h1.y = y - CASESIZE;
    flams->h2.y = y - 2*CASESIZE;
    flams->g1.y = y;
    flams->g2.y = y;
    flams->d1.y = y;
    flams->d2.y = y;
}
