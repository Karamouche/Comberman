#define TRUE 1
#define FALSE 0
#define NAME "Comberman"

//RAJOUTER UNE PROTECTION
typedef enum Position Position; // position
typedef struct Joueur Joueur; //joueur
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
