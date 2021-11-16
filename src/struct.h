#ifndef __STRUCT__
#define __STRUCT__

typedef struct Joueur{
    int vie;
    int frame;
    int UP;
    SDL_Rect rect;
    SDL_Texture* texture;
    int nbbombe;
    int position;
    int blinking;
}Joueur;

typedef struct Bomb{
    int shown;
    SDL_Rect rect;
    SDL_Texture* texture;
    int frame;
}Bomb;

typedef struct Coeur{
    int shown;
    SDL_Rect rect;
    SDL_Texture* texture;
    int frame; // pour faire bouger les coeurs, un peu comme l'abeille
}Coeur;
typedef struct Textures{
    SDL_Texture* menu;
    SDL_Texture* background;
    SDL_Texture* brick;
}Textures;

#endif
