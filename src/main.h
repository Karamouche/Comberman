#define TRUE 1
#define FALSE 0
#define NAME "Comberman"
//RAJOUTER UNE PROTECTION

typedef struct Joueur Joueur; //joueur
enum {HAUT, BAS, GAUCHE, DROITE};
enum {MENU, INGAME, ENDGAME};


int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void showTexture(SDL_Renderer *renderer, SDL_Texture *texture);
