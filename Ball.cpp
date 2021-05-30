#include "TXLib.h"
//#include "..\proba_lib\Pugovkina_Lib.h"

void MoveBall();

int main()
    {
    txCreateWindow (800, 600);

    MoveBall();

    return 0;
    }

void MoveBall()
    {
    int x = 0, y = 0,
        vx =5, vy = 3;

    int x1 = 100, y1 = 100,
        vx1 = 3,  vy1 = 5;

    int dt = 1;

    txSetColor (RGB (x, y, x + y), 2);
    txSetFillColor (RGB (x/2, y/2, x/2 + y/2));

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor (RGB (x, y, 128), 2);
        txSetFillColor (RGB (x/2, y/2, 128));

        txCircle (x, y, 20);
        //Flowers (x, y, TX_YELLOW, TX_RED);

        x += vx * dt;
        y += vy * dt;

        if (x > 800)
            {
            vx = -vx;
            x = 800;
            }

        if (y > 600)
            {
            vy = -vy;
            y = 600;
            }

        if (x < 0)
            {
            vx = -vx;
            x = 0;
            }

        if (y < 0)
            {
            vy = -vy;
            y = 0;
            }

        txSetColor (RGB (x1, y1, 128), 2);
        txSetFillColor (RGB (x1/2, y1/2, 128));

        txCircle (x1, y1, 20);
        //Flowers (x, y, TX_YELLOW, TX_RED);

        x1 += vx1 * dt;
        y1 += vy1 * dt;

        if (x1 > 800)
            {
            vx1 = -vx1;
            x1 = 800;
            }

        if (y1 > 600)
            {
            vy1 = -vy1;
            y1 = 600;
            }

        if (x1 < 0)
            {
            vx1 = -vx1;
            x1 = 0;
            }

        if (y1 < 0)
            {
            vy1 = -vy1;
            y1 = 0;
            }

        if (txGetAsyncKeyState (VK_RIGHT)) vx1 ++;
        if (txGetAsyncKeyState (VK_LEFT))  vx1 --;
        if (txGetAsyncKeyState (VK_UP))    vy1 --;
        if (txGetAsyncKeyState (VK_DOWN))  vy1 ++;

        if (txGetAsyncKeyState (VK_SPACE)) vx1 = vy1 = 0;

        txSleep (10);
        }
    }
