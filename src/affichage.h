#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void render(Joueur *joueur1, Joueur* joueur2, Textures textures, Bomb* bomb1, Bomb* bomb2, SDL_Renderer* renderer, int** map, SDL_Rect* bricks, int statut,Coeurs* coeurs1, Coeurs* coeurs2);
void animateBee(SDL_Renderer* renderer, Joueur* joueur, int beeN);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
int isMapped(int x, int y);
void endBomb(Bomb* bomb, Flams* flams);

#endif
