#include "point.h"

point* point_init(void)
{
    point* P = (point*) ncalloc(1, sizeof(point));
    P->cx = INITIAL_X;
    P->cy = INITIAL_Y;
    P->ca = INITIAL_ANGLE;
    return P;
}

double deg2rad (double degrees)
{
    return degrees * M_PI / 180.0;
}

void drawFD(SDL_Renderer *rend, point* P, double fdLength)
{
    double dx,dy;
    dx = cos(deg2rad(P->ca)) * fdLength;
    dy = sin(deg2rad(P->ca)) * fdLength;
    SDL_RenderDrawLine(rend, P->cx, P->cy, P->cx + dx, P->cy - dy);
    /* move to the latest point */
    P->cx = P->cx + dx;
    P->cy = P->cy - dy;
}

/* Assume the angle change of Right Turn is < 0, and vice versa */
void turnRT(point* P, double deltaAngle)
{
    P->ca = P->ca - deltaAngle;
}

void turnLT(point* P, double deltaAngle)
{
    P->ca = P->ca + deltaAngle;
}





