#include <stdio.h>
#include "main.h"
#include <SDL2/SDL.h>

#define TRUE 1
#define FALSE 0


enum Position{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};


struct Joueur{
    int vie;
    int x;
    int y; // ou double si deplacement libre
    int nbbombe;
    Position position;
    //Ajouter l'orientation du joueur

};

int main(int argc, char* argv[])
{
    SDL_Window *window = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) != FALSE) // INIT
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    window = SDL_CreateWindow("Comberman",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
    if(window == NULL){
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        //PROGRAMME PRINCIPAL
        SDL_Delay(3000);
        SDL_DestroyWindow(window);
    }
    SDL_Quit(); //QUIT
    return EXIT_SUCCESS;
}
