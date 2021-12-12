#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

void explosion(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, int** map, SDL_Rect* bricks);
Flams* createFlams(SDL_Renderer* renderer);
void setCoordFlams(Flams* flams, int x, int y);
void explosionDamage(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, Mix_Chunk* dmg, int** map);

#endif // EXPLOSION_H_INCLUDED
