#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"
#include "affichage.h"


void render(Joueur *joueur1, Joueur* joueur2, Textures textures, Bomb* bomb1, Bomb* bomb2, SDL_Renderer* renderer, int** map, SDL_Rect* bricks, int statut, Coeurs* coeurs1, Coeurs* coeurs2){
    if(statut == MENU){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures.menu, NULL, NULL);
        SDL_RenderPresent(renderer);
    }else if(statut == INGAME){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures.background, NULL, NULL);

        animateBee(renderer, joueur1, 1);
        animateBee(renderer, joueur2, 2);
        int b = 0;
        for(int i=0 ; i<SIZE ; i++ ){
            for(int j = 0 ; j<SIZE ; j++){
                if(map[i][j] == BRICK){
                    bricks[b].x = i * CASESIZE;
                    bricks[b].y = j * CASESIZE;
                    SDL_RenderCopy(renderer, textures.brick, NULL, &bricks[b]);
                    b++;
                }
            }
        }
        if(bomb1->shown)
            SDL_RenderCopy(renderer, bomb1->texture, NULL, &bomb1->rect);
        if(bomb2->shown)
            SDL_RenderCopy(renderer, bomb2->texture, NULL, &bomb2->rect);

        if(coeurs1->coeur1->shown)
            SDL_RenderCopy(renderer, coeurs1->coeur1->texture, NULL, &coeurs1->coeur1->rect);
        if(coeurs1->coeur2->shown)
            SDL_RenderCopy(renderer, coeurs1->coeur2->texture, NULL, &coeurs1->coeur2->rect);
        if(coeurs1->coeur3->shown)
            SDL_RenderCopy(renderer, coeurs1->coeur3->texture, NULL, &coeurs1->coeur3->rect);
        if(coeurs2->coeur1->shown)
            SDL_RenderCopy(renderer, coeurs2->coeur1->texture, NULL, &coeurs2->coeur1->rect);
        if(coeurs2->coeur2->shown)
            SDL_RenderCopy(renderer, coeurs2->coeur2->texture, NULL, &coeurs2->coeur2->rect);
        if(coeurs2->coeur3->shown)
            SDL_RenderCopy(renderer, coeurs2->coeur3->texture, NULL, &coeurs2->coeur3->rect);
        if(bomb1->flams->shown){
            if(isMapped(bomb1->flams->b1.x/CASESIZE, bomb1->flams->b1.y/CASESIZE)){
                if(map[bomb1->flams->b1.x/CASESIZE][bomb1->flams->b1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->b1);
                    if(isMapped(bomb1->flams->b2.x/CASESIZE, bomb1->flams->b2.y/CASESIZE))
                        if(map[bomb1->flams->b2.x/CASESIZE][bomb1->flams->b2.y/CASESIZE] == BRICK || map[bomb1->flams->b2.x/CASESIZE][bomb1->flams->b2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->b2);
                }else if(map[bomb1->flams->b1.x/CASESIZE][bomb1->flams->b1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->b1);
            }

            if(isMapped(bomb1->flams->h1.x/CASESIZE, bomb1->flams->h1.y/CASESIZE)){
                if(map[bomb1->flams->h1.x/CASESIZE][bomb1->flams->h1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->h1);
                    if(isMapped(bomb1->flams->h2.x/CASESIZE, bomb1->flams->h2.y/CASESIZE))
                        if(map[bomb1->flams->h2.x/CASESIZE][bomb1->flams->h2.y/CASESIZE] == BRICK || map[bomb1->flams->h2.x/CASESIZE][bomb1->flams->h2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->h2);
                }else if(map[bomb1->flams->h1.x/CASESIZE][bomb1->flams->h1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb1->flams->h1);
            }

            if(isMapped(bomb1->flams->g1.x/CASESIZE, bomb1->flams->g1.y/CASESIZE)){
                if(map[bomb1->flams->g1.x/CASESIZE][bomb1->flams->g1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->g1);
                    if(isMapped(bomb1->flams->g2.x/CASESIZE, bomb1->flams->g2.y/CASESIZE))
                        if(map[bomb1->flams->g2.x/CASESIZE][bomb1->flams->g2.y/CASESIZE] == BRICK || map[bomb1->flams->g2.x/CASESIZE][bomb1->flams->g2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->g2);
                }else if(map[bomb1->flams->g1.x/CASESIZE][bomb1->flams->g1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->g1);
            }

            if(isMapped(bomb1->flams->d1.x/CASESIZE, bomb1->flams->d1.y/CASESIZE)){
                if(map[bomb1->flams->d1.x/CASESIZE][bomb1->flams->d1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->d1);
                    if(isMapped(bomb1->flams->d2.x/CASESIZE, bomb1->flams->d2.y/CASESIZE))
                        if(map[bomb1->flams->d2.x/CASESIZE][bomb1->flams->d2.y/CASESIZE] == BRICK || map[bomb1->flams->d2.x/CASESIZE][bomb1->flams->d2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->d2);
                }else if(map[bomb1->flams->d1.x/CASESIZE][bomb1->flams->d1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb1->flams->d1);
            }
        }
        if(bomb2->flams->shown){
            if(isMapped(bomb2->flams->b1.x/CASESIZE, bomb2->flams->b1.y/CASESIZE)){
                if(map[bomb2->flams->b1.x/CASESIZE][bomb2->flams->b1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->b1);
                    if(isMapped(bomb2->flams->b2.x/CASESIZE, bomb2->flams->b2.y/CASESIZE))
                        if(map[bomb2->flams->b2.x/CASESIZE][bomb2->flams->b2.y/CASESIZE] == BRICK || map[bomb2->flams->b2.x/CASESIZE][bomb2->flams->b2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->b2);
                }else if(map[bomb2->flams->b1.x/CASESIZE][bomb2->flams->b1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->b1);
            }

            if(isMapped(bomb2->flams->h1.x/CASESIZE, bomb2->flams->h1.y/CASESIZE)){
                if(map[bomb2->flams->h1.x/CASESIZE][bomb2->flams->h1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->h1);
                    if(isMapped(bomb2->flams->h2.x/CASESIZE, bomb2->flams->h2.y/CASESIZE))
                        if(map[bomb2->flams->h2.x/CASESIZE][bomb2->flams->h2.y/CASESIZE] == BRICK || map[bomb2->flams->h2.x/CASESIZE][bomb2->flams->h2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->h2);
                }else if(map[bomb2->flams->h1.x/CASESIZE][bomb2->flams->h1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expVertical, NULL, &bomb2->flams->h1);
            }

            if(isMapped(bomb2->flams->g1.x/CASESIZE, bomb2->flams->g1.y/CASESIZE)){
                if(map[bomb2->flams->g1.x/CASESIZE][bomb2->flams->g1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->g1);
                    if(isMapped(bomb2->flams->g2.x/CASESIZE, bomb2->flams->g2.y/CASESIZE))
                        if(map[bomb2->flams->g2.x/CASESIZE][bomb2->flams->g2.y/CASESIZE] == BRICK || map[bomb2->flams->g2.x/CASESIZE][bomb2->flams->g2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->g2);
                }else if(map[bomb2->flams->g1.x/CASESIZE][bomb2->flams->g1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->g1);
            }

            if(isMapped(bomb2->flams->d1.x/CASESIZE, bomb2->flams->d1.y/CASESIZE)){
                if(map[bomb2->flams->d1.x/CASESIZE][bomb2->flams->d1.y/CASESIZE] == VIDE){
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->d1);
                    if(isMapped(bomb2->flams->d2.x/CASESIZE, bomb2->flams->d2.y/CASESIZE))
                        if(map[bomb2->flams->d2.x/CASESIZE][bomb2->flams->d2.y/CASESIZE] == BRICK || map[bomb2->flams->d2.x/CASESIZE][bomb2->flams->d2.y/CASESIZE] == VIDE)
                            SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->d2);
                }else if(map[bomb2->flams->d1.x/CASESIZE][bomb2->flams->d1.y/CASESIZE] == BRICK)
                    SDL_RenderCopy(renderer, textures.expHorizontal, NULL, &bomb2->flams->d1);
            }
        }

        SDL_RenderCopy(renderer, joueur1->texture, NULL, &joueur1->rect);
        SDL_RenderCopy(renderer, joueur2->texture, NULL, &joueur2->rect);
        SDL_RenderPresent(renderer);

    }else{
        SDL_RenderClear(renderer);
        if(joueur1->vie == 0){
            SDL_RenderCopy(renderer, textures.p2win, NULL, NULL);
        }else if(joueur2->vie == 0){
            SDL_RenderCopy(renderer, textures.p1win, NULL, NULL);
        }else{
            SDL_RenderCopy(renderer, textures.nwin, NULL, NULL);
        }
        SDL_RenderPresent(renderer);
    }
}

void animateBee(SDL_Renderer* renderer, Joueur* joueur, int beeN){
    if(joueur->frame == 20){
            if(joueur->UP)
                joueur->UP = FALSE;
            else
                joueur->UP = TRUE;
            joueur->frame = 0;
            }
        SDL_DestroyTexture(joueur->texture);
        switch(joueur->position){
        case HAUT:
            if(joueur->UP)
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/haut1.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/haut1.bmp", renderer);
            else
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/haut0.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/haut0.bmp", renderer);
            break;
        case BAS:
            if(joueur->UP)
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/bas1.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/bas1.bmp", renderer);
            else
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/bas0.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/bas0.bmp", renderer);
            break;
        case DROITE:
            if(joueur->UP)
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/droite1.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/droite1.bmp", renderer);
            else
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/droite0.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/droite0.bmp", renderer);
            break;
        case GAUCHE:
            if(joueur->UP)
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/gauche1.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/gauche1.bmp", renderer);
            else
                if(beeN == 1)
                    joueur->texture = loadImage("beeTexture1/gauche0.bmp", renderer);
                else
                    joueur->texture = loadImage("beeTexture2/gauche0.bmp", renderer);
            break;
        }
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

void endBomb(Bomb* bomb, Flams* flams){
    flams->shown = FALSE;
    bomb->frame = 0;
    bomb->shown = FALSE;
}
int isMapped(int x, int y){
    if(x>=0 && x<15 && y>=0 && y<15)
        return TRUE;
    return FALSE;
}

