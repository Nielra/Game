#include "TXLib.h"
//#include "..\proba_lib\Pugovkina_Lib.h"

void MoveBall();
void DrawBall (int x, int y, int rBall, int vx, int vy, COLORREF color, COLORREF fillcolor);
void PhysicsBall (int* x, int* y, int* rBall, int* vx, int* vy, int ax, int ay, int dt);
void ControlBall1 (int* vx, int* vy);
void ControlBall2 (int* vx, int* vy);
void Scatter_Balls (int* x, int* y, int* vx, int* vy);

double DistanceBalls (int xA, int yA, int xB, int yB);

//const int rBall = 20;

int main()
    {
    txCreateWindow (800, 600);

    MoveBall();

    return 0;
    }

void MoveBall()
    {
    int x1  = 30, y1  = 30,
        vx1 =  5, vy1 =  3,
        ax1 =  0, ay1 =  0;

    int x2  = 100, y2  = 100,
        vx2 =   3, vy2 =   5,
        ax2 =   0, ay2 =   0;

    int dt = 1;

    int rBall1 = 100, rBall2 = 20;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        //txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear();

        DrawBall (x1, y1, rBall1, vx1, vy1, TX_LIGHTRED, TX_RED);
        PhysicsBall (&x1, &y1, &rBall1, &vx1, &vy1, ax1, ay1, dt);
        ControlBall1 (&vx1, &vy1);

        DrawBall (x2, y2, rBall2, vx2, vy2, TX_LIGHTGREEN, TX_GREEN);
        PhysicsBall (&x2, &y2, &rBall2, &vx2, &vy2, ax2, ay2, dt);
        ControlBall2 (&vx2, &vy2);

        if (DistanceBalls (x1, y1, x2, y2) <= rBall1 + rBall2)
            {
            // oldX1 = x1 - vx1 * dt;
            // oldY1 = y1 - vy1 * dt;
            // oldX2 = x2 - vx2 * dt;
            // oldY2 = y2 - vy2 * dt;
            //while ((DistanceBalls (x1, y1, x2, y2) != rBall1 + rBall2) or (dt > 0.01))
                    {
                    int oldX =
                    }
            Scatter_Balls (&x1, &y1, &vx1, &vy1);
            Scatter_Balls (&x2, &y2, &vx2, &vy2);
            }

        txSleep (10);
        }
    }

//-----------------------------------------------------------------------------

void DrawBall (int x, int y, int rBall, int vx, int vy, COLORREF color, COLORREF fillcolor)
    {
    txSetColor (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, rBall);
    //txLine (x, y, x + vx * 5, y + vy * 5);
    //txCircle (x + vx * 5, y + vy * 5, 3);
    //Flowers (x, y, TX_YELLOW, TX_RED);
    }

//-----------------------------------------------------------------------------

void PhysicsBall (int* x, int* y, int* rBall, int* vx, int* vy, int ax, int ay, int dt)
    {
    *vx = *vx + ax * dt;
    *vy = *vy + ay * dt;

    *x = *x + *vx * dt;
    *y = *y + *vy * dt;

    if ((*x + (*rBall)) > 800)
        {
        *vx = - (*vx);
        *x = 1600 - 2 * (*rBall) - *x;
        }

    if ((*y + (*rBall)) > 600)
        {
        *vy = - (*vy);
        *y = 1200 - 2 * (*rBall) - *y;
        }

    if ((*x - (*rBall)) < 0)
        {
        *vx = - (*vx);
        *x = 2 * (*rBall) - *x;
        }

    if ((*y - (*rBall)) < 0)
        {
        *vy = - (*vy);
        *y = 2 * (*rBall) - *y;
        }
    }

//-----------------------------------------------------------------------------

void ControlBall1 (int* vx, int* vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (*vx) =  abs (*vx);
    if (txGetAsyncKeyState (VK_LEFT))  (*vx) = -abs (*vx);
    if (txGetAsyncKeyState (VK_UP))    (*vy) = -abs (*vy);
    if (txGetAsyncKeyState (VK_DOWN))  (*vy) =  abs (*vy);

    if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
    }

//-----------------------------------------------------------------------------

void ControlBall2 (int* vx, int* vy)
    {
    if (txGetAsyncKeyState ('D')) (*vx) ++;
    if (txGetAsyncKeyState ('A')) (*vx) --;
    if (txGetAsyncKeyState ('W')) (*vy) --;
    if (txGetAsyncKeyState ('S')) (*vy) ++;

    if (txGetAsyncKeyState ('Z')) *vx = *vy = 0;
    }

//-----------------------------------------------------------------------------

double DistanceBalls (int xA, int yA, int xB, int yB)
    {
    double dist = sqrt ((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
    return dist;
    }

//-----------------------------------------------------------------------------

void Scatter_Balls (int* x, int* y, int* vx, int* vy)
    {
    *vx = - (*vx);
    }
