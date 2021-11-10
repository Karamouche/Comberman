#define TRUE 1
#define FALSE 0
#define NAME "Comberman"
#define CASESIZE 40
#define START 40
#define SIZE 15

//RAJOUTER UNE PROTECTION

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
    int time;
}Bomb;

typedef struct Textures{
    SDL_Texture* menu;
    SDL_Texture* background;
    SDL_Texture* brick;
}Textures;
enum {HAUT, BAS, GAUCHE, DROITE};
enum {MENU, INGAME, ENDGAME};
enum{VIDE, BLOC, BRIQUE, BOMBE, JOUEUR1, JOUEUR2};


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void beemove(Joueur* joueur,SDL_Renderer* renderer, int DIR, int** map);
void render(Joueur *joueur, Textures textures, SDL_Texture* beeTexture, Bomb* bomb1, SDL_Renderer* renderer, int** map, int statut);
void init_map(int** map);
