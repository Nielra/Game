#include "TXLib.h"

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
void Text();

void ControlBall1  (Ball*);
void ControlBall2  (int* vx, int* vy);
void Scatter_Balls (int* x, int* y, int* vx, int* vy);
void Goal          (int* x, int* y, int* kolGoal);
void GameOver      (int* kolUdarov);

double DistanceBalls (int xA, int yA, int xB, int yB);

int main()
    {
    txCreateWindow (800, 650);

    MoveBall();

    return 0;
    }

//-----------------------------------------------------------------------------

void MoveBall()
    {
    HDC vorota  = txLoadImage ("Images\\Goal.bmp");
    HDC numbers = txLoadImage ("Images\\Numbers.bmp");

    Ball ball1 = { .x =  30, .y =  30, .vx = 5, .vy = 3, .rBall = 50,
                   .color = TX_LIGHTRED, .fillcolor = TX_RED};

    Ball ball2 = { .x = 400, .y = 101, .vx = 3, .vy = 5, .rBall = 50,
                   .color = TX_LIGHTBLUE, .fillcolor = TX_BLUE};

    int ax1 = 0, ay1 = 0,
        ax2 = 0, ay2 = 0;

    double dt = 1;

    int kolUdarov = 0;

    int kolGoal = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_GREEN);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor(TX_WHITE);
        txRectangle (0, 600, 800, 650);

        Text();

        txTransparentBlt (txDC(), 252, 0,    0,  0, vorota,  0,                     0, TX_WHITE);
        txTransparentBlt (txDC(), 200, 605, 20, 40, numbers, 40 * (10 - kolUdarov), 0, TX_WHITE);
        txTransparentBlt (txDC(), 730, 605, 20, 40, numbers, 40 * kolGoal,          0, TX_WHITE);

        ball1.Draw();
        ball2.Draw();

        ball1.Physics (ax1, ay1, dt);
        ball2.Physics (ax2, ay2, dt);

        ControlBall1 (&ball1);
        //ControlBall2 (&vx2, &vy2);

        if (DistanceBalls (ball1.x, ball1.y, ball2.x, ball2.y) <= ball1.rBall + ball2.rBall)
            {
            GameOver (&kolUdarov);

            Scatter_Balls (&ball1.x, &ball1.y, &ball1.vx, &ball1.vy);
            Scatter_Balls (&ball2.x, &ball2.y, &ball2.vx, &ball2.vy);

            //printf ("Kol-vo udarov = %d \n", kolUdarov);

            ball2.Change();
            //printf ("radius = %d \n", ball2.rBall);
            }

        if ((292 <= (ball2.x)) and ((ball2.x) <= 508) and ((ball2.y) < 100))
            {
            Goal (&ball2.x, &ball2.y, &kolGoal);
            }

        txSleep (10);
        }

    txDeleteDC (vorota);
    txDeleteDC (numbers);
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

//-----------------------------------------------------------------------------

void Goal (int* x, int* y, int* kolGoal)
    {
    HDC goooal = txLoadImage ("Images\\Goooal.bmp");
    HDC numbers = txLoadImage ("Images\\Numbers.bmp");

    *kolGoal = (*kolGoal) + 1;
    *x = 400;
    *y = 300;

    txPlaySound ("Krik-Goal.wav");

    txTransparentBlt (txDC(), 730, 605, 20, 40, numbers, (*kolGoal) * 40, 0, TX_WHITE);
    txTransparentBlt (txDC(),  30, 110,  0,  0, goooal,  0,               0);

    txSleep (3000);

    txPlaySound (NULL);

    if (*kolGoal == 3)
        {
        HDC kubok  = txLoadImage ("Images\\Kubok.bmp");

        txSetFillColor (TX_GREEN);
        txClear();

        txTransparentBlt (txDC(), 200, 50, 0, 0, kubok, 0, 0);

        txDeleteDC (goooal);
        txDeleteDC (kubok);
        txDeleteDC (numbers);

        exit (1);
        }

    txDeleteDC (goooal);
    txDeleteDC (numbers);
    }

//-----------------------------------------------------------------------------

void GameOver (int* kolUdarov)
    {
    (*kolUdarov) += 1;
    if ((*kolUdarov) == 10)
        {
        HDC gameOver = txLoadImage ("Images\\Game_over.bmp");
        HDC numbers  = txLoadImage ("Images\\Numbers.bmp");

        txPlaySound ("Game_over.wav");

        txTransparentBlt (txDC(),   0,  75,  0,  0, gameOver,                     0, 0);
        txTransparentBlt (txDC(), 200, 605, 20, 40, numbers, 40 * (10 - *kolUdarov), 0, TX_WHITE);

        txSetColor (TX_RED);
        txSetFillColor (TX_RED);
        txSelectFont ("Arial", 50, 0, FW_BOLD);
        txTextOut (300, 550, "Game over");

        txSleep (3000);

        txPlaySound (NULL);

        txDeleteDC (gameOver);
        txDeleteDC (numbers);

        exit (1);
        }
    }

//-----------------------------------------------------------------------------

void Text()
    {
    txSetColor (TX_GREEN);
    txSetFillColor (TX_GREEN);
    txSelectFont ("Arial", 50, 0, FW_BOLD);
    txTextOut (  0, 600, "Attempts");txTextOut (  0, 600, "Attempts");
    txTextOut (600, 600, "Goals");
    txSelectFont ("Arial", 20, 0, FW_BOLD);
    txTextOut (260, 620, "Цель: загнать синий шарик в ворота");
    }
