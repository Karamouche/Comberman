#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

void game(SDL_Window* window){

int exit = EXIT_FAILURE;
SDL_Event event2;
int LOOP = TRUE;
SDL_Renderer *renderer = NULL;
SDL_Texture *fond = NULL;
    if(0 != init(&window, &renderer, 600, 600))
        goto Quit;

SDL_SetWindowIcon(window, SDL_LoadBMP("icon.bmp"));
SDL_SetWindowTitle(window, NAME);
fond = loadImage("fond.bmp", renderer);
if(fond == NULL)
    goto Quit;
showTexture(renderer, fond);

while(LOOP){

    while(SDL_PollEvent(&event2)){
            switch(event2.type){
            case SDL_KEYDOWN:
                switch(event2.key.keysym.sym){

                    case SDLK_ESCAPE:
                        LOOP = FALSE;
                        break;
                }
            case SDL_QUIT:
                LOOP= FALSE;
                break;
            }
    }



}

SDL_DestroyWindow(window);
SDL_Quit(); //QUIT
exit = EXIT_SUCCESS;

Quit://TO QUIT
    if(fond != NULL)
        SDL_DestroyTexture(fond);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return exit;


}

