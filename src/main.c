#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

int main(int argc, char* argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *menu = NULL;
    SDL_Event event;
    STATUT statut = STATUT.MENU;

    int statut = EXIT_FAILURE;

    if(0 != init(&window, &renderer, 600, 600))
        goto Quit;
    SDL_SetWindowIcon(window, SDL_LoadBMP("icon.bmp"));
    SDL_SetWindowTitle(window, NAME);
    menu = loadImage("menu.bmp", renderer);
    if(menu == NULL)
        goto Quit;
    showTexture(renderer, menu);
    int LOOP = TRUE;
    while(LOOP){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                LOOP = FALSE;
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); //QUIT
    statut = EXIT_SUCCESS;

Quit://TO QUIT
    if(menu != NULL)
        SDL_DestroyTexture(menu);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
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

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        printf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
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

void showTexture(SDL_Renderer *renderer, SDL_Texture *texture){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL); // Affiche ma texture sur touts l'�cran
    SDL_RenderPresent(renderer);
}

enum POSITION{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};

enum STATUT{
    MENU,
    INGAME,
    ENDGAME
};

struct Joueur{
    int vie;
    int x;
    int y; // ou double si deplacement libre
    int nbbombe;
    Position position;
    //Ajouter l'orientation du joueur

};



