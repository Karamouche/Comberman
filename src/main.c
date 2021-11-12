#include <stdio.h>
#include <stdlib.h>
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

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *background = NULL;
    SDL_Texture *beeTexture = NULL;
    SDL_Texture *bombTexture = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Texture *brickTexture = NULL;
    SDL_Event event;

    Joueur* bee1 = malloc(sizeof(Joueur));
    bee1->rect.h = CASESIZE;
    bee1->rect.w = CASESIZE;
    bee1->rect.x = 0 + START;
    bee1->rect.y = 0 + START;
    bee1->frame = 0;
    bee1->UP = FALSE;
    bee1->blinking = FALSE;

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
    menuTexture = loadImage("menu.bmp", renderer);
    if(menuTexture == NULL)
        goto Quit;
    brickTexture = loadImage("brick.bmp", renderer);
    if(brickTexture == NULL)
        goto Quit;

    Textures textures;
    textures.background = background;
    textures.menu = menuTexture;
    textures.brick = brickTexture;


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
                    if(statut == MENU)
                        statut = INGAME;
                    else if(statut == INGAME){
                        if(bomb1->shown == FALSE){
                            bomb1->rect.x = bee1->rect.x;
                            bomb1->rect.y = bee1->rect.y;
                            bomb1->shown = TRUE;
                        }
                    }
                    break;
                case SDLK_ESCAPE:
                    LOOP = FALSE;
                    break;
                case SDLK_DOWN:
                    if(statut == INGAME)
                        beemove(bee1, BAS, map, bomb1);
                    break;
                case SDLK_UP:
                    if(statut == INGAME)
                        beemove(bee1, HAUT, map, bomb1);
                    break;
                case SDLK_LEFT:
                    if(statut == INGAME)
                        beemove(bee1, GAUCHE, map, bomb1);
                    break;
                case SDLK_RIGHT:
                    if(statut == INGAME)
                        beemove(bee1, DROITE, map, bomb1);
                    break;
                }break;
            case SDL_QUIT:
                LOOP = FALSE;
                break;
            }
        }
        if(statut == INGAME)
            bee1->frame++;
        if(statut == INGAME && bomb1->shown){
            bomb1->frame++;
            if(bomb1->frame == TPSEXPLOSION){
                explosion(bee1, bomb1, map, bricks);
            }
        }
        render(bee1, textures, beeTexture, bomb1, renderer, map, bricks, statut);
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
    if(menuTexture != NULL)
        SDL_DestroyTexture(menuTexture);
    if(brickTexture != NULL)
        SDL_DestroyTexture(brickTexture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i<SIZE ; i++)
        free(map[i]);
    free(map);
    free(bee1);
    free(bricks);
    free(bomb1);
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
    }
    map[1][1] = JOUEUR1;
}

void render(Joueur *joueur, Textures textures, SDL_Texture* beeTexture, Bomb* bomb1, SDL_Renderer* renderer, int** map, SDL_Rect* bricks, int statut){
    if(statut == MENU){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures.menu, NULL, NULL);
        SDL_RenderPresent(renderer);
    }else if(statut == INGAME){
        if(joueur->frame == 20){
            if(joueur->UP)
                joueur->UP = FALSE;
            else
                joueur->UP = TRUE;
            joueur->frame = 0;
            }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures.background, NULL, NULL);
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
        SDL_RenderCopy(renderer, beeTexture, NULL, &joueur->rect);
        SDL_RenderPresent(renderer);
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

void beemove(Joueur *joueur, int DIR, int** map, Bomb* bomb1){
    switch(DIR){
    case HAUT:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] != BRICK){
            if(!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y - CASESIZE){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE - 1] = JOUEUR1;
                joueur->rect.y -= CASESIZE;
               }

        }
        joueur->position = HAUT;
        break;
    case BAS:
        if(map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BLOC &&
           map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] != BRICK){
            if(!bomb1->shown || bomb1->rect.x != joueur->rect.x || bomb1->rect.y != joueur->rect.y + CASESIZE){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE + 1] = JOUEUR1;
                joueur->rect.y += CASESIZE;
            }
        }
        joueur->position = BAS;
        break;
    case DROITE:
        if(map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] != BRICK){
            if(!bomb1->shown || bomb1->rect.x != joueur->rect.x + CASESIZE || bomb1->rect.y != joueur->rect.y){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE + 1][joueur->rect.y/CASESIZE] = JOUEUR1;
                joueur->rect.x += CASESIZE;
            }
        }
        joueur->position = DROITE;
        break;
    case GAUCHE:
        if(map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BLOC &&
           map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] != BRICK){
            if(!bomb1->shown || bomb1->rect.x != joueur->rect.x - CASESIZE || bomb1->rect.y != joueur->rect.y){
                map[joueur->rect.x/CASESIZE][joueur->rect.y/CASESIZE] = VIDE;
                map[joueur->rect.x/CASESIZE - 1][joueur->rect.y/CASESIZE] = JOUEUR1;
                joueur->rect.x -= CASESIZE;
            }
        }
        joueur->position = GAUCHE;
        break;
    }
}

void explosion(Joueur* joueur, Bomb* bomb, int** map, SDL_Rect* bricks){
    int x = bomb->rect.x;
    int y = bomb->rect.y;
    bomb->frame = 0;
    bomb->shown = FALSE;
    int bTop = FALSE;
    int bBot = FALSE;
    int bLeft = FALSE;
    int bRight = FALSE;
    for(int i = 1; i <= LENEXPLOSION ; i++){
            //RAJOUTER LES DEGATS SUR LES JOUEURS
        if(x/CASESIZE + i<15 && x/CASESIZE - i>=0 && y/CASESIZE + i<15 && y/CASESIZE - i >= 0){
            if(map[x/CASESIZE][y/CASESIZE + i] == BRICK && !bBot){
                map[x/CASESIZE][y/CASESIZE + i] = VIDE;
                bBot = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE + i] == BLOC)
                bBot = TRUE;
            if(map[x/CASESIZE][y/CASESIZE - i] == BRICK && !bTop){
                map[x/CASESIZE][y/CASESIZE - i] = VIDE;
                bTop = TRUE;
            }else if(map[x/CASESIZE][y/CASESIZE - i] == BLOC)
                bTop = TRUE;
            if(map[x/CASESIZE + i][y/CASESIZE] == BRICK && !bRight){
                map[x/CASESIZE + i][y/CASESIZE] = VIDE;
                bRight = TRUE;
            }else if(map[x/CASESIZE + i][y/CASESIZE] == BLOC)
                bRight = TRUE;
            if(map[x/CASESIZE - i][y/CASESIZE] == BRICK && !bLeft){
                map[x/CASESIZE - i][y/CASESIZE] = VIDE;
                bLeft = TRUE;
            }else if(map[x/CASESIZE - i][y/CASESIZE] == BLOC)
                bLeft = TRUE;
        }
    }
}




