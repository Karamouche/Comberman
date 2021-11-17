#ifndef __MAIN__
#define __MAIN__
#define TRUE 1
#define FALSE 0
#define NAME "Comberman"
#define CASESIZE 40
#define START1 40
#define START2 520
#define SIZE 15
#define NBRICKS 40
#define TPSEXPLOSION 45
#define LENEXPLOSION 2

enum{HAUT, BAS, GAUCHE, DROITE};
enum{MENU, INGAME, ENDGAME};
enum{VIDE, BLOC, BRICK, JOUEUR1, JOUEUR2};


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void beemove(Joueur* joueur, int DIR, int** map, Bomb* bomb1, Bomb* bomb2, int num);
void render(Joueur *joueur1, Joueur* joueur2, Textures textures, Bomb* bomb1, Bomb* bomb2, SDL_Renderer* renderer, int** map, SDL_Rect* bricks, int statut,Coeurs* coeurs1, Coeurs* coeurs2);
void init_map(int** map, SDL_Rect* bricks);
void explosion(Joueur* joueur1, Joueur* joueur2, Bomb* bomb, Flams* flams, int** map, SDL_Rect* bricks);
void animateBee(SDL_Renderer* renderer, Joueur* joueur, int beeN);
Flams* createFlams(SDL_Renderer* renderer);
void setCoordFlams(Flams* flams, int x, int y);
int isMapped(int x, int y);

#endif
