#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    SDL_Window *window = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("Ma premiere fenetre",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
    if(NULL == window){
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        //PROGRAMME PRINCIPAL
        SDL_Delay(3000);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
