#include "../Interp/Point/point.h"

#define MILLISECONDDELAY 100
#define MAXNUMLOOP 8

int main(void)
{
    int i = 1;
    SDL_Simplewin sw;
    point* pt;
    Neill_SDL_Init(&sw);
    pt = point_init();

    /* Set draw color to white */
    Neill_SDL_SetDrawColour(&sw, 255, 255, 255);

    /* Draw an unfilled Octagon */
    do{
        SDL_Delay(MILLISECONDDELAY);
        drawFD(sw.renderer, pt, 30);
        turnLT(pt, 45);
        i++;
        Neill_SDL_UpdateScreen(&sw);
        /* when pressed ESC or killed the SDL window - escape */
        Neill_SDL_Events(&sw);
    } while(!sw.finished && (i <= MAXNUMLOOP));

    if (i > MAXNUMLOOP) {
        while (!sw.finished) {
            Neill_SDL_Events(&sw);
        }
    }

    /* Clear up graphics subsystems */
    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}


