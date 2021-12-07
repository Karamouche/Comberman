#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "struct.h"
#include "main.h"

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

    expHorizontal = loadImage("flams/hori.bmp", renderer);
    expVertical = loadImage("flams/vert.bmp", renderer);
    Textures textures;
    textures.background = background;
    textures.menu = menuTexture;
    textures.brick = brickTexture;
    textures.expHorizontal = expHorizontal;
    textures.expVertical = expVertical;

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
                        if(statut == MENU)
                            statut = INGAME;
                        else if(statut == INGAME){
                            if(bomb1->shown == FALSE){
                                bomb1->rect.x = bee1->rect.x;
                                bomb1->rect.y = bee1->rect.y;
                                bomb1->shown = TRUE;
                                setCoordFlams(flams1, bomb1->rect.x, bomb1->rect.y);
                            }
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
            Mix_PlayChannel(-1, dead, 1);
            LOOP=FALSE;
        }
        //BOMB1 ANIMATION
        if(statut == INGAME && bomb1->shown){
            bomb1->frame++;
            if(bomb1->frame == TPSEXPLOSION/6){
                bomb1->texture = loadImage("bombTexture/1.bmp", renderer);
                setCoordFlams(flams1, bomb1->rect.x, bomb1->rect.y);
                Mix_PlayChannel(-1, explo, 1);
            }
            if(bomb1->frame == 2*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/2.bmp", renderer);
            if(bomb1->frame == 3*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/3.bmp", renderer);
            if(bomb1->frame == 4*TPSEXPLOSION/6){
                bomb1->texture = loadImage("bombTexture/4.bmp", renderer);
                flams1->shown = TRUE;
            }
            if(bomb1->frame == 5*TPSEXPLOSION/6)
                bomb1->texture = loadImage("bombTexture/5.bmp", renderer);
            if(bomb1->frame == TPSEXPLOSION){
                explosion(bee1,bee2, bomb1, flams1, map, bricks,dmg);
                bomb1->texture = loadImage("bombTexture/1.bmp", renderer);
            }
        }
        //BOMB2 ANIMATION
        if(statut == INGAME && bomb2->shown){
            bomb2->frame++;
            if(bomb2->frame == TPSEXPLOSION/6){
                bomb2->texture = loadImage("bombTexture/1.bmp", renderer);
                setCoordFlams(flams2, bomb2->rect.x, bomb2->rect.y);
                Mix_PlayChannel(-1,explo, 1);
            }
            if(bomb2->frame == 2*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/2.bmp", renderer);

            if(bomb2->frame == 3*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/3.bmp", renderer);
            if(bomb2->frame == 4*TPSEXPLOSION/6){
                bomb2->texture = loadImage("bombTexture/4.bmp", renderer);
                flams2->shown = TRUE;
            }
            if(bomb2->frame == 5*TPSEXPLOSION/6)
                bomb2->texture = loadImage("bombTexture/5.bmp", renderer);
            if(bomb2->frame == TPSEXPLOSION){

                explosion(bee1,bee2, bomb2, flams2, map, bricks,dmg);

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
    free(coeurs1);
    free(coeurs2);
    free(flams1);
    free(flams2);
    SDL_Quit();
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    Mix_FreeChunk(dead);
    Mix_FreeChunk(explo);
    Mix_FreeChunk(dmg);
    return exit;
}


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

void beemove(Joueur *joueur, int DIR, int** map, Bomb* bomb1, Bomb* bomb2, int num){
    switch(DIR){
    case HAUT:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BRICK &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y - CASESIZE) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x || bomb2->rect.y != joueur->rect.y - CASESIZE)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] = num;
                joueur->rect.y -= CASESIZE;
               }
        }
        joueur->position = HAUT;
        break;
    case BAS:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BRICK &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y + CASESIZE) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x || bomb2->rect.y != joueur->rect.y + CASESIZE)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] = num;
                joueur->rect.y += CASESIZE;
            }
        }
        joueur->position = BAS;
        break;
    case DROITE:
        if(map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BRICK &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x + CASESIZE || bomb1->rect.y != joueur->rect.y) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x + CASESIZE || bomb2->rect.y != joueur->rect.y)){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] = num;
                joueur->rect.x += CASESIZE;
            }
        }
        joueur->position = DROITE;
        break;
    case GAUCHE:
        if(map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BRICK &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != JOUEUR1 &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != JOUEUR2){
            if((!bomb1->shown || bomb1->rect.x != joueur->rect.x - CASESIZE || bomb1->rect.y != joueur->rect.y) && (!bomb2->shown || bomb2->rect.x != joueur->rect.x - CASESIZE || bomb2->rect.y != joueur->rect.y)) {
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] = num;
                joueur->rect.x -= CASESIZE;
            }
        }
        joueur->position = GAUCHE;
        break;
    }
}

void explosion(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, Flams* flams, int** map, SDL_Rect* bricks,Mix_Chunk* dmg){
    int x = bomb->rect.x;
    int y = bomb->rect.y;
    bomb->frame = 0;
    bomb->shown = FALSE;
    int bTop = FALSE;
    int bBot = FALSE;
    int bLeft = FALSE;
    int bRight = FALSE;
    flams->shown = FALSE;
    for(int i = 1; i <= LENEXPLOSION ; i++){
        //MODIFIER LA CONDITION CAR BUG
        if(isMapped(x/CASESIZE, y/CASESIZE + i)){
            if(map[x/CASESIZE][y/CASESIZE + i] == BRICK && !bBot){
                map[x/CASESIZE][y/CASESIZE + i] = VIDE;
                bBot = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE + i] == BLOC)
                bBot = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
             else if(map[x/CASESIZE][y/CASESIZE + i] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
        }
        if(isMapped(x/CASESIZE, y/CASESIZE - i)){
            if(map[x/CASESIZE][y/CASESIZE - i] == BRICK && !bTop){
                map[x/CASESIZE][y/CASESIZE - i] = VIDE;
                bTop = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE - i] == BLOC)
                bTop = TRUE;
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
             else if(map[x/CASESIZE][y/CASESIZE - i] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
        }
        if(isMapped(x/CASESIZE + i, y/CASESIZE)){
            if(map[x/CASESIZE + i][y/CASESIZE] == BRICK && !bRight){
                map[x/CASESIZE + i][y/CASESIZE] = VIDE;
                bRight = TRUE;
            }else if(map[x/CASESIZE + i][y/CASESIZE] == BLOC)
                bRight = TRUE;
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
             else if(map[x/CASESIZE + i][y/CASESIZE] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
        }
        if(isMapped(x/CASESIZE - i, y/CASESIZE)){
            if(map[x/CASESIZE - i][y/CASESIZE] == BRICK && !bLeft){
                map[x/CASESIZE - i][y/CASESIZE] = VIDE;
                bLeft = TRUE;
            }else if(map[x/CASESIZE - i][y/CASESIZE] == BLOC)
                bLeft = TRUE;
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR1){
                joueur1->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
             else if(map[x/CASESIZE - i][y/CASESIZE] == JOUEUR2){
                joueur2->vie--;
                Mix_PlayChannel(-1, dmg, 1);}
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

int isMapped(int x, int y){
    if(x>=0 && x<15 && y>=0 && y<15)
        return TRUE;
    return FALSE;
}



