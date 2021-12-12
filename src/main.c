#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"
#include "affichage.h"
#include "deplacement.h"
#include "explosion.h"
#include "initialisation.h"


int main(int argc, char* argv[]){
    //ON INITIALISE LE RAND
    srand(time(NULL));
    int statut = MENU;
    int** map;
    map = (int**)malloc(sizeof(int*)*SIZE);
    for(int i = 0 ; i<SIZE ; i++)
        map[i] = (int*)malloc(sizeof(int)*SIZE);
    if(map == NULL)
        goto Quit;

    SDL_Rect* bricks;
    bricks = (SDL_Rect*)malloc(sizeof(SDL_Rect)*NBRICKS);
    if(bricks == NULL)
        goto Quit;
    for(int i = 0 ; i<NBRICKS ; i++){
        bricks[i].h = CASESIZE;
        bricks[i].w = CASESIZE;
    }

    init_map(map, bricks);

        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *background = NULL;
    SDL_Texture *beeTexture1 = NULL;
    SDL_Texture *beeTexture2 = NULL;
    SDL_Texture *bombTexture = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Texture *brickTexture = NULL;
    SDL_Texture *coeurTexture = NULL;
    SDL_Texture *expVertical = NULL;
    SDL_Texture *expHorizontal = NULL;
    SDL_Texture *p1win = NULL;
    SDL_Texture *p2win = NULL;
    SDL_Texture *nwin = NULL;

    Mix_Music *musique;
    musique = Mix_LoadMUS("bee.wav");
    Mix_Chunk *explo;
    explo = Mix_LoadWAV("sounds/CreeperExplosion.wav");
    Mix_Chunk *dead;
    dead = Mix_LoadWAV("sounds/dead.wav");
    Mix_Chunk *dmg;
    dmg = Mix_LoadWAV("sounds/dmg.wav");

    SDL_Event event;

    Joueur* bee1 = malloc(sizeof(Joueur));
    bee1->rect.h = CASESIZE;
    bee1->rect.w = CASESIZE;
    bee1->rect.x = 0 + START1;
    bee1->rect.y = 0 + START1;
    bee1->frame = 0;
    bee1->UP = FALSE;
    bee1->blinking = FALSE;
    bee1->vie = 3;

    Joueur* bee2 = malloc(sizeof(Joueur));
    bee2->rect.h = CASESIZE;
    bee2->rect.w = CASESIZE;
    bee2->rect.x = 0 + START2;
    bee2->rect.y = 0 + START2;
    bee2->frame = 0;
    bee2->UP = FALSE;
    bee2->blinking = FALSE;
    bee2->vie = 3;

    Coeur* vie11 = malloc(sizeof(Coeur));
    vie11->rect.h = CASESIZE;
    vie11->rect.w = CASESIZE;
    vie11->rect.x = 0;
    vie11->rect.y = 0;

    Coeur* vie12 = malloc(sizeof(Coeur));
    vie12->rect.h = CASESIZE;
    vie12->rect.w = CASESIZE;
    vie12->rect.x = 40;
    vie12->rect.y = 0;

    Coeur* vie13 = malloc(sizeof(Coeur));
    vie13->rect.h = CASESIZE;
    vie13->rect.w = CASESIZE;
    vie13->rect.x = 80;
    vie13->rect.y = 0;

    Coeurs* coeurs1 = malloc(sizeof(Coeurs));
    coeurs1->coeur1 = vie11;
    coeurs1->coeur2 = vie12;
    coeurs1->coeur3 = vie13;

    Coeur* vie21 = malloc(sizeof(Coeur));
    vie21->rect.h = CASESIZE;
    vie21->rect.w = CASESIZE;
    vie21->rect.x = 560;
    vie21->rect.y = 560;

    Coeur* vie22 = malloc(sizeof(Coeur));
    vie22->rect.h = CASESIZE;
    vie22->rect.w = CASESIZE;
    vie22->rect.x = 520;
    vie22->rect.y = 560;

    Coeur* vie23 = malloc(sizeof(Coeur));
    vie23->rect.h = CASESIZE;
    vie23->rect.w = CASESIZE;
    vie23->rect.x = 480;
    vie23->rect.y = 560;

    Coeurs* coeurs2 = malloc(sizeof(Coeurs));
    coeurs2->coeur1 = vie21;
    coeurs2->coeur2 = vie22;
    coeurs2->coeur3 = vie23;

    Flams* flams1 = createFlams(renderer);
    Flams* flams2 = createFlams(renderer);


    int exit = EXIT_FAILURE;

    if(0 != init(&window, &renderer, 600, 600))
        goto Quit;
    SDL_SetWindowIcon(window, SDL_LoadBMP("icon.bmp"));
    SDL_SetWindowTitle(window, NAME);

    background = loadImage("background.bmp", renderer);
    if(background == NULL)
        goto Quit;
    beeTexture1 = loadImage("beeTexture1/bas0.bmp", renderer);
    if(beeTexture1 == NULL)
        goto Quit;
    beeTexture2 = loadImage("beeTexture2/bas0.bmp", renderer);
    if(beeTexture2 == NULL)
        goto Quit;
    bombTexture = loadImage("bombTexture/0.bmp", renderer);
    if(bombTexture == NULL)
        goto Quit;
    menuTexture = loadImage("menu.bmp", renderer);
    if(menuTexture == NULL)
        goto Quit;
    brickTexture = loadImage("brick.bmp", renderer);
    if(brickTexture == NULL)
        goto Quit;
    coeurTexture = loadImage("coeur.bmp", renderer);
    if(coeurTexture == NULL)
        goto Quit;
    p1win = loadImage("p1win.bmp", renderer);
    if(p1win == NULL)
        goto Quit;
    p2win = loadImage("p2win.bmp", renderer);
    if(p2win == NULL)
        goto Quit;
    nwin = loadImage("nwin.bmp", renderer);
    if(nwin == NULL)
        goto Quit;

    expHorizontal = loadImage("flams/hori.bmp", renderer);
    expVertical = loadImage("flams/vert.bmp", renderer);
    Textures textures;
    textures.background = background;
    textures.menu = menuTexture;
    textures.brick = brickTexture;
    textures.expHorizontal = expHorizontal;
    textures.expVertical = expVertical;
    textures.p1win = p1win;
    textures.p2win = p2win;

    bee1->position = BAS;
    bee1->vie = 3;
    bee1->nbbombe = 5;
    bee1->texture = beeTexture1;

    bee2->position = BAS;
    bee2->vie = 3;
    bee2->nbbombe = 5;
    bee2->texture = beeTexture2;

    Bomb *bomb1 = malloc(sizeof(Bomb));
    bomb1->frame = 0;
    bomb1->shown = FALSE;
    bomb1->texture = bombTexture;
    bomb1->rect.h = 40;
    bomb1->rect.w = 40;
    bomb1->flams = flams1;

    Bomb *bomb2 = malloc(sizeof(Bomb));
    bomb2->frame = 0;
    bomb2->shown = FALSE;
    bomb2->texture = bombTexture;
    bomb2->rect.h = 40;
    bomb2->rect.w = 40;
    bomb2->flams = flams2;

    vie11->texture = coeurTexture;
    vie12->texture = coeurTexture;
    vie13->texture = coeurTexture;
    vie21->texture = coeurTexture;
    vie22->texture = coeurTexture;
    vie23->texture = coeurTexture;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); // Affiche ma texture sur touts l'écran
    SDL_RenderCopy(renderer, bee1->texture, NULL, &bee1->rect);
    SDL_RenderCopy(renderer, bee2->texture, NULL, &bee2->rect);
    SDL_RenderCopy(renderer, vie11->texture, NULL, &vie11->rect);
    SDL_RenderCopy(renderer, vie12->texture, NULL, &vie12->rect);
    SDL_RenderCopy(renderer, vie13->texture, NULL, &vie13->rect);
    SDL_RenderCopy(renderer, vie21->texture, NULL, &vie21->rect);
    SDL_RenderCopy(renderer, vie22->texture, NULL, &vie22->rect);
    SDL_RenderCopy(renderer, vie23->texture, NULL, &vie23->rect);
    SDL_RenderPresent(renderer);
    //ON JOUE LA MUSIQUE
    Mix_PlayMusic(musique, -1);

    int LOOP = TRUE;
    while(LOOP){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.repeat == 0){
                    switch(event.key.keysym.sym){
                    case SDLK_SPACE:
                        if(statut == MENU){
                            statut = INGAME;
                            if(menuTexture != NULL)
                                SDL_DestroyTexture(menuTexture);
                        }
                        else if(statut == INGAME){
                            if(bomb1->shown == FALSE){
                                bomb1->rect.x = bee1->rect.x;
                                bomb1->rect.y = bee1->rect.y;
                                bomb1->shown = TRUE;
                                setCoordFlams(flams1, bomb1->rect.x, bomb1->rect.y);
                            }
                        }else{
                            LOOP = FALSE;
                        }
                        break;
                    case SDLK_ESCAPE:
                        LOOP = FALSE;
                        break;
                    case SDLK_DOWN:
                        if(statut == INGAME)
                            beemove(bee1, BAS, map, bomb1, bomb2, JOUEUR1);
                        break;
                    case SDLK_UP:
                        if(statut == INGAME)
                            beemove(bee1, HAUT, map, bomb1, bomb2, JOUEUR1);
                        break;
                    case SDLK_LEFT:
                        if(statut == INGAME)
                            beemove(bee1, GAUCHE, map, bomb1, bomb2, JOUEUR1);
                        break;
                    case SDLK_RIGHT:
                        if(statut == INGAME)
                            beemove(bee1, DROITE, map, bomb1, bomb2, JOUEUR1);
                        break;
                    case SDLK_e:
                        if(statut == INGAME){
                            if(bomb2->shown == FALSE){
                                bomb2->rect.x = bee2->rect.x;
                                bomb2->rect.y = bee2->rect.y;
                                bomb2->shown = TRUE;
                                setCoordFlams(flams2, bomb2->rect.x, bomb2->rect.y);
                            }
                        }
                        break;
                    case SDLK_s:
                        if(statut == INGAME)
                            beemove(bee2, BAS, map, bomb1, bomb2, JOUEUR2);
                        break;
                    case SDLK_z:
                        if(statut == INGAME)
                            beemove(bee2, HAUT, map, bomb1, bomb2, JOUEUR2);
                        break;
                    case SDLK_q:
                        if(statut == INGAME)
                            beemove(bee2, GAUCHE, map, bomb1, bomb2, JOUEUR2);
                        break;
                    case SDLK_d:
                        if(statut == INGAME)
                            beemove(bee2, DROITE, map, bomb1, bomb2, JOUEUR2);
                        break;
                }
                }break;

            case SDL_QUIT:
                LOOP = FALSE;
                break;
            }
        }
        if(statut == INGAME){
            bee1->frame++;
            bee2->frame++;
        }

        if(statut == INGAME && (bee1->vie == 0 || bee2->vie == 0)){
            statut = ENDGAME;
            Mix_PlayChannel(-1, dead, 0);
        }

        //BOMB1 ANIMATION
        if(statut == INGAME && bomb1->shown){
            bomb1->frame++;
            if(bomb1->frame == TPSEXPLOSION/6){
                bomb1->texture = loadImage("bombTexture/1.bmp", renderer);
                setCoordFlams(flams1, bomb1->rect.x, bomb1->rect.y);
                Mix_PlayChannel(-1, explo, 0);
            }
            if(bomb1->frame == 2*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/2.bmp", renderer);
            if(bomb1->frame == 3*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/3.bmp", renderer);
            if(bomb1->frame == 4*TPSEXPLOSION/6){
                bomb1->texture = loadImage("bombTexture/4.bmp", renderer);
                flams1->shown = TRUE;
                explosionDamage(bee1, bee2, bomb1, dmg, map);
            }
            if(bomb1->frame == 5*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/5.bmp", renderer);
            if(bomb1->frame == TPSEXPLOSION){
                explosion(bee1,bee2, bomb1, map, bricks);
                endBomb(bomb1, flams1);
                bomb1->texture = loadImage("bombTexture/1.bmp", renderer);
            }
        }
        //BOMB2 ANIMATION
        if(statut == INGAME && bomb2->shown){
            bomb2->frame++;
            if(bomb2->frame == TPSEXPLOSION/6){
                bomb2->texture = loadImage("bombTexture/1.bmp", renderer);
                setCoordFlams(flams2, bomb2->rect.x, bomb2->rect.y);
                Mix_PlayChannel(-1,explo, 0);
            }
            if(bomb2->frame == 2*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/2.bmp", renderer);

            if(bomb2->frame == 3*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/3.bmp", renderer);
            if(bomb2->frame == 4*TPSEXPLOSION/6){
                bomb2->texture = loadImage("bombTexture/4.bmp", renderer);
                flams2->shown = TRUE;
                explosionDamage(bee1, bee2, bomb2, dmg, map);
            }
            if(bomb2->frame == 5*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/5.bmp", renderer);
            if(bomb2->frame == TPSEXPLOSION){
                explosion(bee1,bee2, bomb2, map, bricks);
                endBomb(bomb2, flams2);
                bomb2->texture = loadImage("bombTexture/1.bmp", renderer);
            }
        }
        if(statut == INGAME && bee1->vie == 1){
            coeurs1->coeur1->shown = TRUE;
            coeurs1->coeur2->shown = FALSE;
            coeurs1->coeur3->shown = FALSE;
        }
        if(statut == INGAME && bee1->vie == 2){
            coeurs1->coeur1->shown = TRUE;
            coeurs1->coeur2->shown = TRUE;
            coeurs1->coeur3->shown = FALSE;
        }

        if(statut == INGAME && bee1->vie == 3){
            coeurs1->coeur1->shown = TRUE;
            coeurs1->coeur2->shown = TRUE;
            coeurs1->coeur3->shown = TRUE;
        }
        if(statut == INGAME && bee2->vie == 1){
            coeurs2->coeur1->shown = TRUE;
            coeurs2->coeur2->shown = FALSE;
            coeurs2->coeur3->shown = FALSE;
        }
        if(statut == INGAME && bee2->vie == 2){
            coeurs2->coeur1->shown = TRUE;
            coeurs2->coeur2->shown = TRUE;
            coeurs2->coeur3->shown = FALSE;
        }

        if(statut == INGAME && bee2->vie == 3){
            coeurs2->coeur1->shown = TRUE;
            coeurs2->coeur2->shown = TRUE;
            coeurs2->coeur3->shown = TRUE;
        }
        render(bee1, bee2, textures, bomb1, bomb2, renderer, map, bricks, statut, coeurs1, coeurs2);
        SDL_Delay(16);
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); //QUIT
    exit = EXIT_SUCCESS;

Quit://TO QUIT
    if(background != NULL)
        SDL_DestroyTexture(background);
    if(beeTexture1 != NULL)
        SDL_DestroyTexture(beeTexture1);
    if(beeTexture2 != NULL)
        SDL_DestroyTexture(beeTexture2);
    if(bombTexture != NULL)
        SDL_DestroyTexture(bombTexture);
    if(menuTexture != NULL)
        SDL_DestroyTexture(menuTexture);
    if(brickTexture != NULL)
        SDL_DestroyTexture(brickTexture);
    if(coeurTexture != NULL)
        SDL_DestroyTexture(coeurTexture);
    if(p1win != NULL)
        SDL_DestroyTexture(p1win);
    if(p2win != NULL)
        SDL_DestroyTexture(p2win);
    if(nwin != NULL)
        SDL_DestroyTexture(nwin);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i<SIZE ; i++)
        free(map[i]);
    free(map);
    free(bee1);
    free(bee2);
    free(bricks);
    free(bomb1);
    free(bomb2);
    free(vie11);
    free(vie12);
    free(vie13);
    free(vie21);
    free(vie22);
    free(vie23);
    free(coeurs1->coeur1);
    free(coeurs1->coeur2);
    free(coeurs1->coeur3);
    free(coeurs1);
    free(coeurs2->coeur1);
    free(coeurs2->coeur2);
    free(coeurs2->coeur3);
    free(coeurs2);
    free(flams1);
    free(flams2);
    SDL_Quit();
    Mix_FreeMusic(musique);
    Mix_FreeChunk(dead);
    Mix_FreeChunk(explo);
    Mix_FreeChunk(dmg);
    Mix_CloseAudio();
    free(musique);
    free(dead);
    free(explo);
    free(dmg);
    return exit;
}

