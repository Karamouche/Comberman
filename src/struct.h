#ifndef __STRUCT__
#define __STRUC__

typedef struct Joueur{
    int vie;
    int frame;
    int UP;
    SDL_Rect rect;
    int nbbombe;
    int position;
}Joueur;

typedef struct Bomb{
    int shown;
    SDL_Rect rect;
    SDL_Texture* texture;
    int frame;
}Bomb;

typedef struct Textures{
    SDL_Texture* menu;
    SDL_Texture* background;
    SDL_Texture* brick;
}Textures;

#endif
