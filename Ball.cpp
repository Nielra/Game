#include "TXLib.h"
//#include "..\proba_lib\Pugovkina_Lib.h"

struct Ball
    {
    int x,  y,
        vx, vy;

    int rBall;

    COLORREF color, fillcolor;
    };

void MoveBall();
void DrawBall (Ball);
void PhysicsBall (Ball*, int ax, int ay, int dt);
void ControlBall1 (Ball*);
void ControlBall2 (int* vx, int* vy);
void Scatter_Balls (int* x, int* y, int* vx, int* vy);

double DistanceBalls (int xA, int yA, int xB, int yB);

int main()
    {
    txCreateWindow (800, 600);

    MoveBall();

    return 0;
    }

//-----------------------------------------------------------------------------

void MoveBall()
    {
    Ball ball1 = { .x =  30, .y =  30, .vx = 5, .vy = 3, .rBall = 100,
                   .color = TX_LIGHTRED, .fillcolor = TX_RED};

    Ball ball2 = { .x = 100, .y = 100, .vx = 3, .vy = 5, .rBall =  20,
                   .color = TX_LIGHTGREEN, .fillcolor = TX_GREEN};

    int ax1 = 0, ay1 = 0,
        ax2 = 0, ay2 = 0;

    int dt = 1;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        //txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear();

        DrawBall (ball1);
        DrawBall (ball2);

        PhysicsBall (&ball1, ax1, ay1, dt);
        PhysicsBall (&ball2, ax2, ay2, dt);

        ControlBall1 (&ball1);
        //ControlBall2 (&vx2, &vy2);

        if (DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) <= ball1.rBall + ball2.rBall)
            {
            // oldX1 = x1 - vx1 * dt;
            // oldY1 = y1 - vy1 * dt;
            // oldX2 = x2 - vx2 * dt;
            // oldY2 = y2 - vy2 * dt;
            //while ((DistanceBalls (x1, y1, x2, y2) != rBall1 + rBall2) or (dt > 0.01))
            //        {
            //        int oldX =
            //        }
            Scatter_Balls (&ball1.x, &ball1.y, &ball1.vx, &ball1.vy);
            Scatter_Balls (&ball2.x, &ball2.y, &ball2.vx, &ball2.vy);
            }

        txSleep (10);
        }
    }

//-----------------------------------------------------------------------------

void DrawBall (Ball ball)
    {
    txSetColor (ball.color, 2);
    txSetFillColor (ball.fillcolor);

    txCircle (ball.x, ball.y, ball.rBall);
    //txLine (x, y, x + vx * 5, y + vy * 5);
    //txCircle (x + vx * 5, y + vy * 5, 3);
    //Flowers (x, y, TX_YELLOW, TX_RED);
    }

//-----------------------------------------------------------------------------

void PhysicsBall (Ball* ball, int ax, int ay, int dt)
    {
    ball -> vx = ball -> vx + ax * dt;
    ball -> vy = ball -> vy + ay * dt;

    ball -> x = ball -> x + ball -> vx * dt;
    ball -> y = ball -> y + ball -> vy * dt;

    if ((ball -> x + ball -> rBall) > 800)
        {
        ball -> vx = - (ball -> vx);
        ball -> x = 1600 - 2 * ball -> rBall - ball -> x;
        }

    if ((ball -> y + ball -> rBall) > 600)
        {
        ball -> vy = - (ball -> vy);
        ball -> y = 1200 - 2 * (ball -> rBall) - ball -> y;
        }

    if ((ball -> x - ball -> rBall) < 0)
        {
        ball -> vx = - (ball -> vx);
        ball -> x = 2 * ball -> rBall - ball -> x;
        }

    if (((ball -> y) - (ball -> rBall)) < 0)
        {
        ball -> vy = - (ball -> vy);
        ball -> y = 2 * ball -> rBall - (ball -> y);
        }
    }

//-----------------------------------------------------------------------------

void ControlBall1 (Ball* ball)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (ball -> vx) =  abs (ball -> vx);
    if (txGetAsyncKeyState (VK_LEFT))  (ball -> vx) = -abs (ball -> vx);
    if (txGetAsyncKeyState (VK_UP))    (ball -> vy) = -abs (ball -> vy);
    if (txGetAsyncKeyState (VK_DOWN))  (ball -> vy) =  abs (ball -> vy);

    if (txGetAsyncKeyState (VK_SPACE)) ball -> vx = ball -> vy = 0;
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
