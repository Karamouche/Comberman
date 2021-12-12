#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"
#include "initialisation.h"


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s",
        SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED, window, renderer))
    {
        fprintf(stderr,
        "Erreur SDL_CreateWindowAndRenderer : %s",
        SDL_GetError());
        return -1;
    }
    return 0;
}

void init_map(int** map, SDL_Rect* bricks){
    //TOUTE LA MAP EN VIDE
    for(int i = 0 ; i < SIZE ; i++){
        for(int j = 0 ; j < SIZE ; j++)
            map[i][j] = VIDE;
    }
    //ON POSE LES MURS
    for(int i = 0 ; i<SIZE ; i++)
        map[0][i] = BLOC;
    for(int i = 0 ; i<SIZE ; i++)
        map[14][i] = BLOC;
    for(int i = 0 ; i<SIZE ; i++)
        map[i][0] = BLOC;
    for(int i = 0 ; i<SIZE ; i++)
        map[i][14] = BLOC;
    //BLOCS DU MILIEU
    for(int i = 2 ; i<SIZE-2 ; i+=2){
        for(int j = 2 ; j<SIZE-2 ; j+=2)
            map[i][j] = BLOC;
    }
    int i = 0;
    int j = 0;
    for(int n = 0 ; n<NBRICKS ; n++){
        i = rand() % SIZE;
        j = rand() % SIZE;
        while(map[i][j] != VIDE){
            i = rand() % SIZE;
            j = rand() % SIZE;
        }
        map[i][j] = BRICK;
        //A CHANGER
        map[1][2] = VIDE;
        map[2][1] = VIDE;
        map[13][12] = VIDE;
        map[12][13] = VIDE;
    }
    map[1][1] = JOUEUR1;
    map[13][13] = JOUEUR2;
}
