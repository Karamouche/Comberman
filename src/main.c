#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

int main(int argc, char* argv[])
{
    int statut = MENU;
    int** map;
    map = (int**)malloc(sizeof(int*)*SIZE);
    for(int i = 0 ; i<SIZE ; i++)
        map[i] = (int*)malloc(sizeof(int)*SIZE);
    if(map == NULL)
        goto Quit;
    init_map(map);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture *beeTexture = NULL;
    SDL_Event event;
    Joueur* bee = malloc(sizeof(Joueur));
    bee->rect.h = CASESIZE;
    bee->rect.w = CASESIZE;
    bee->rect.x = 0 + START;
    bee->rect.y = 0 + START;

    int exit = EXIT_FAILURE;

    if(0 != init(&window, &renderer, 600, 600))
        goto Quit;
    SDL_SetWindowIcon(window, SDL_LoadBMP("icon.bmp"));
    SDL_SetWindowTitle(window, NAME);

    background = loadImage("background.bmp", renderer);
    if(background == NULL)
        goto Quit;
    beeTexture = loadImage("bas.bmp", renderer);
    if(beeTexture == NULL)
        goto Quit;

    bee->position = BAS;
    bee->vie = 3;
    bee->nbbombe = 5;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); // Affiche ma texture sur touts l'écran
    SDL_RenderCopy(renderer, beeTexture, NULL, &bee->rect);
    SDL_RenderPresent(renderer);

    int LOOP = TRUE;
    while(LOOP){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_SPACE:
                    //POSER UNE BOMBE
                    break;
                case SDLK_ESCAPE:
                    LOOP = FALSE;
                    break;
                case SDLK_DOWN:
                    beemove(bee, renderer, BAS, map);
                    break;
                case SDLK_UP:
                    beemove(bee, renderer, HAUT, map);
                    break;
                case SDLK_LEFT:
                    beemove(bee, renderer, GAUCHE, map);
                    break;
                case SDLK_RIGHT:
                    beemove(bee, renderer, DROITE, map);
                    break;
                }break;
            case SDL_QUIT:
                LOOP = FALSE;
                break;
            }
        render(bee, background, beeTexture, renderer, map);
        SDL_Delay(32);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); //QUIT
    exit = EXIT_SUCCESS;

Quit://TO QUIT
    if(background != NULL)
        SDL_DestroyTexture(background);
    if(beeTexture != NULL)
        SDL_DestroyTexture(beeTexture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i<SIZE ; i++)
        free(map[i]);
    free(map);
    free(bee);
    //free(map);
    SDL_Quit();
    return exit;
}


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
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

void init_map(int** map){
    int i = 0;
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

    map[1][1] = JOUEUR;
}

void render(Joueur *joueur, SDL_Texture* background, SDL_Texture* beeTexture, SDL_Renderer* renderer, int** map){
    switch(joueur->position){
    case HAUT:
        beeTexture = loadImage("haut.bmp", renderer);
        break;
    case BAS:
        beeTexture = loadImage("bas.bmp", renderer);
        break;
    case DROITE:
        beeTexture = loadImage("droite.bmp", renderer);
        break;
    case GAUCHE:
        beeTexture = loadImage("gauche.bmp", renderer);
        break;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, beeTexture, NULL, &joueur->rect);
    SDL_RenderPresent(renderer);
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

void beemove(Joueur *joueur,SDL_Renderer* renderer, int DIR, int** map){
    switch(DIR){
    case HAUT:
        joueur->position = HAUT;
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BLOC){
            joueur->rect.y -= CASESIZE;
        }
        break;
    case BAS:
        joueur->position = BAS;
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BLOC){
            joueur->rect.y += CASESIZE;
        }
        break;
    case DROITE:
        joueur->position = DROITE;
        if(map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BLOC){
            joueur->rect.x += CASESIZE;
        }
        break;
    case GAUCHE:
        joueur->position = GAUCHE;
        if(map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BLOC){
            joueur->rect.x -= CASESIZE;
        }
        break;
    }
}




