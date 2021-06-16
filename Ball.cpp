#include "TXLib.h"
//#include "..\proba_lib\Pugovkina_Lib.h"

struct Ball
    {
    int x,  y,
        vx, vy;

    int rBall;

    COLORREF color, fillcolor;

    void Draw();

    void Physics (int ax, int ay, int dt);

    void Change ();
    };

void MoveBall();
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
    Ball ball1 = { .x =  30, .y =  30, .vx = 5, .vy = 3, .rBall = 50,
                   .color = TX_LIGHTRED, .fillcolor = TX_RED};

    Ball ball2 = { .x = 400, .y = 400, .vx = 3, .vy = 5, .rBall = 50,
                   .color = TX_LIGHTGREEN, .fillcolor = TX_GREEN};

    int ax1 = 0, ay1 = 0,
        ax2 = 0, ay2 = 0;

    double dt = 1;

    int kolUdarov = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        //txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear();

        ball1.Draw();
        ball2.Draw();

        ball1.Physics (ax1, ay1, dt);
        ball2.Physics (ax2, ay2, dt);

        ControlBall1 (&ball1);
        //ControlBall2 (&vx2, &vy2);

        if (DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) <= ball1.rBall + ball2.rBall)
            {
            kolUdarov += 1;

            /*ball1.x = ball1.x - ball1.vx * dt;  //возврат к старым значениям
            ball1.y = ball1.y - ball1.vy * dt;
            ball2.x = ball2.x - ball2.vx * dt;
            ball2.y = ball2.y - ball2.vy * dt;

            //while ((DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) != ball1.rBall + ball2.rBall) or (dt > 0.01))
            do
                {
                dt = dt * 0.5;

                ball1.x = ball1.x + ball1.vx * dt;  printf ("x1 = %d \n",ball1.x);
                ball1.y = ball1.y + ball1.vy * dt;  printf ("y1 = %d \n",ball1.y);
                ball2.x = ball2.x + ball2.vx * dt;  printf ("x2 = %d \n",ball2.x);
                ball2.y = ball2.y + ball2.vy * dt;  printf ("y2 = %d \n",ball2.y);

                if (DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) > ball1.rBall + ball2.rBall)
                    {
                    ball1.x = ball1.x + ball1.vx * dt;  printf ("x1 in if = %d \n", ball1.x);
                    ball1.y = ball1.y + ball1.vy * dt;  printf ("y1 in if = %d \n", ball1.y);
                    ball2.x = ball2.x + ball2.vx * dt;  printf ("x2 in if = %d \n", ball2.x);
                    ball2.y = ball2.y + ball2.vy * dt;  printf ("y2 in if = %d \n", ball2.y);
                    }
                }
                while ((DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) == ball1.rBall + ball2.rBall) or (dt < 0.01));


            dt = 1; */

            Scatter_Balls (&ball1.x, &ball1.y, &ball1.vx, &ball1.vy);
            Scatter_Balls (&ball2.x, &ball2.y, &ball2.vx, &ball2.vy);

            printf ("Kol-vo udarov = %d \n", kolUdarov);

            //ball1.Physics (ax1, ay1, dt);
            //ball2.Physics (ax2, ay2, dt);

            //ball1.Draw();
            //ball2.Draw();

            ball2.Change();
            printf ("radius = %d \n", ball2.rBall);
            }

        txSleep (10);
        }
    }

//-----------------------------------------------------------------------------

void Ball::Draw()
    {
    txSetColor (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, rBall);
    //txLine (x, y, x + vx * 5, y + vy * 5);
    //txCircle (x + vx * 5, y + vy * 5, 3);
    //Flowers (x, y, TX_YELLOW, TX_RED);
    }

//-----------------------------------------------------------------------------

void Ball::Physics (int ax, int ay, int dt)
    {
    vx = vx + ax * dt;
    vy = vy + ay * dt;

    x = x + vx * dt;
    y = y + vy * dt;

    if ((x + rBall) > 800)
        {
        vx = -vx;
        x = 1600 - 2 * rBall - x;
        }

    if ((y + rBall) > 600)
        {
        vy = -vy;
        y = 1200 - 2 * rBall - y;
        }

    if ((x - rBall) < 0)
        {
        vx = -vx;
        x = 2 * rBall - x;
        }

    if ((y - rBall) < 0)
        {
        vy = -vy;
        y = 2 * rBall - y;
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
    *vy = - (*vy);
    }

//-----------------------------------------------------------------------------

void Ball::Change ()
    {
    rBall = rBall - 5;
    }
