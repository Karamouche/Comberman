#define TRUE 1
#define FALSE 0
#define NAME "Comberman"
#define CASESIZE 40
#define START 40
#define SIZE 15

//RAJOUTER UNE PROTECTION

typedef struct Joueur{
    int vie;
    SDL_Rect rect;
    int nbbombe;
    int position;
}Joueur;
enum {HAUT, BAS, GAUCHE, DROITE};
enum {MENU, INGAME, ENDGAME};
enum{VIDE, JOUEUR, BLOC, BRIQUE, BOMBE};


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void beemove(Joueur* joueur,SDL_Renderer* renderer, int DIR, int** map);
void render(Joueur *joueur, SDL_Texture* background, SDL_Texture* beeTexture, SDL_Renderer* renderer, int** map);
void init_map(int** map);
