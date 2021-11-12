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
#define TPSEXPLOSION 60
#define LENEXPLOSION 2

//RAJOUTER UNE PROTECTION

enum {HAUT, BAS, GAUCHE, DROITE};
enum {MENU, INGAME, ENDGAME};
enum{VIDE, BLOC, BRICK, JOUEUR1, JOUEUR2};


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void beemove(Joueur* joueur, int DIR, int** map, Bomb* bomb1);
void render(Joueur *joueur1, Joueur* joueur2, Textures textures, Bomb* bomb, SDL_Renderer* renderer, int** map, SDL_Rect* bricks, int statut);
void init_map(int** map, SDL_Rect* bricks);
void explosion(Joueur* joueur, Bomb* bomb, int** map, SDL_Rect* bricks);
void animateBee(SDL_Renderer* renderer, Joueur* joueur, int beeN);

#endif
