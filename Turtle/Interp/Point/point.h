#include "../../General/general.h"
#include "../SDL/neillsdl2.h"
/* Record current position and direction of drawing */

/* Centralize starting point */
#define INITIAL_X WWIDTH/2
#define INITIAL_Y WHEIGHT/2
/* Initialize drawing direction as Up forward,
 * and its angle between positive X-axis is 90 */
#define INITIAL_ANGLE 90

typedef struct point{
    /* current point (cx, cy) */
    double cx;
    double cy;
    /* current angle */
    double ca;
} point;

point* point_init(void);
double deg2rad (double degrees);
/* Point -> SDL */
void drawFD(SDL_Renderer *rend, point* P, double fdLength);
void turnRT(point* P, double deltaAngle);
void turnLT(point* P, double deltaAngle);

