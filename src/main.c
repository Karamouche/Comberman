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
    SDL_Texture *bombTexture = NULL;
    SDL_Event event;

    Joueur* bee1 = malloc(sizeof(Joueur));
    bee1->rect.h = CASESIZE;
    bee1->rect.w = CASESIZE;
    bee1->rect.x = 0 + START;
    bee1->rect.y = 0 + START;
    bee1->frame = 0;
    bee1->UP = FALSE;

    int exit = EXIT_FAILURE;

    if(0 != init(&window, &renderer, 600, 600))
        goto Quit;
    SDL_SetWindowIcon(window, SDL_LoadBMP("icon.bmp"));
    SDL_SetWindowTitle(window, NAME);

    background = loadImage("background.bmp", renderer);
    if(background == NULL)
        goto Quit;
    beeTexture = loadImage("beeTexture/bas0.bmp", renderer);
    if(beeTexture == NULL)
        goto Quit;
    bombTexture = loadImage("bomb.bmp", renderer);
    if(bombTexture == NULL)
        goto Quit;

    bee1->position = BAS;
    bee1->vie = 3;
    bee1->nbbombe = 5;

    Bomb *bomb1 = malloc(sizeof(Bomb));
    bomb1->shown = FALSE;
    bomb1->texture = bombTexture;
    bomb1->rect.h = 40;
    bomb1->rect.w = 40;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); // Affiche ma texture sur touts l'écran
    SDL_RenderCopy(renderer, beeTexture, NULL, &bee1->rect);
    SDL_RenderPresent(renderer);

    int LOOP = TRUE;
    while(LOOP){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_SPACE:
                    map[bee1->rect.x/CASESIZE][bee1->rect.y/CASESIZE] = BOMBE;
                    break;
                case SDLK_ESCAPE:
                    LOOP = FALSE;
                    break;
                case SDLK_DOWN:
                    beemove(bee1, renderer, BAS, map);
                    break;
                case SDLK_UP:
                    beemove(bee1, renderer, HAUT, map);
                    break;
                case SDLK_LEFT:
                    beemove(bee1, renderer, GAUCHE, map);
                    break;
                case SDLK_RIGHT:
                    beemove(bee1, renderer, DROITE, map);
                    break;
                }break;
            case SDL_QUIT:
                LOOP = FALSE;
                break;
            }
        }
        bee1->frame++;
        render(bee1, background, beeTexture, bomb1, renderer, map);
        SDL_Delay(16);
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); //QUIT
    exit = EXIT_SUCCESS;

Quit://TO QUIT
    if(background != NULL)
        SDL_DestroyTexture(background);
    if(beeTexture != NULL)
        SDL_DestroyTexture(beeTexture);
    if(bombTexture != NULL)
        SDL_DestroyTexture(bombTexture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i<SIZE ; i++)
        free(map[i]);
    free(map);
    free(bee1);
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
    //BLOCS DU MILIEU
    for(int i = 2 ; i<SIZE-2 ; i+=2){
        for(int j = 2 ; j<SIZE-2 ; j+=2)
            map[i][j] = BLOC;
    }
    map[1][1] = JOUEUR1;
}

void render(Joueur *joueur, SDL_Texture* background, SDL_Texture* beeTexture, Bomb* bomb1, SDL_Renderer* renderer, int** map){
    if(joueur->frame == 20){
        if(joueur->UP)
            joueur->UP = FALSE;
        else
            joueur->UP = TRUE;
        joueur->frame = 0;
        }
    switch(joueur->position){
    case HAUT:
        if(joueur->UP)
            beeTexture = loadImage("beeTexture/haut1.bmp", renderer);
        else
            beeTexture = loadImage("beeTexture/haut0.bmp", renderer);
        break;
    case BAS:
        if(joueur->UP)
            beeTexture = loadImage("beeTexture/bas1.bmp", renderer);
        else
            beeTexture = loadImage("beeTexture/bas0.bmp", renderer);
        break;
    case DROITE:
        if(joueur->UP)
            beeTexture = loadImage("beeTexture/droite1.bmp", renderer);
        else
            beeTexture = loadImage("beeTexture/droite0.bmp", renderer);
        break;
    case GAUCHE:
        if(joueur->UP)
            beeTexture = loadImage("beeTexture/gauche1.bmp", renderer);
        else
            beeTexture = loadImage("beeTexture/gauche0.bmp", renderer);
        break;
    }

    for(int i=0 ; i<SIZE ; i++ ){
        for(int j = 0 ; j<SIZE ; j++){
            if(map[i][j] == BOMBE){
                bomb1->rect.x = i*CASESIZE;
                bomb1->rect.y = j*CASESIZE;
                bomb1->shown = TRUE;
            }
        }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    if(bomb1->shown)
        SDL_RenderCopy(renderer, bomb1->texture, NULL, &bomb1->rect);
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
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BLOC){
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] = JOUEUR1;
            joueur->rect.y -= CASESIZE;
        }
        joueur->position = HAUT;
        break;
    case BAS:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BLOC){
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] = JOUEUR1;
            joueur->rect.y += CASESIZE;
        }
        joueur->position = BAS;
        break;
    case DROITE:
        if(map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BLOC){
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
            map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] = JOUEUR1;
            joueur->rect.x += CASESIZE;
        }
        joueur->position = DROITE;
        break;
    case GAUCHE:
        if(map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BLOC){
            map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
            map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] = JOUEUR1;
            joueur->rect.x -= CASESIZE;
        }
        joueur->position = GAUCHE;
        break;
    }
}




