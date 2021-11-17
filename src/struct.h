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

typedef struct Flams{
    int shown;
    SDL_Rect g1;
    SDL_Rect g2;
    SDL_Rect d1;
    SDL_Rect d2;
    SDL_Rect h1;
    SDL_Rect h2;
    SDL_Rect b1;
    SDL_Rect b2;
}Flams;

typedef struct Bomb{
    int shown;
    SDL_Rect rect;
    SDL_Texture* texture;
    Flams* flams;
    int frame;
}Bomb;

typedef struct Coeur{
    int shown;
    SDL_Rect rect;
    SDL_Texture* texture;
}Coeur;

typedef struct Coeurs{
    Coeur* coeur1;
    Coeur* coeur2;
    Coeur* coeur3;
}Coeurs;

typedef struct Textures{
    SDL_Texture* menu;
    SDL_Texture* background;
    SDL_Texture* brick;
    SDL_Texture* expHorizontal;
    SDL_Texture* expVertical;
}Textures;

#endif
