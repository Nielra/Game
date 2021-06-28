#include "TXLib.h"
#include <string.h>

struct Ball
    {
    double x,  y,
           vx, vy;

    int rBall;

    COLORREF color, fillcolor;

    void Draw();

    void Physics (double ax, double ay, int dt);

    void Change ();
    };

void MoveCar();
void GameOver();

void ControlBall (Ball* ball);
void SecretZona  (Ball* ball);

int main()
    {
    txCreateWindow (700, 700);

    MoveCar();

    return 0;
    }

//-----------------------------------------------------------------------------

void MoveCar()
    {
    HDC fon = txLoadImage ("Images\\Fon.bmp");
    HDC map = txLoadImage ("Images\\Map.bmp");

    txPlaySound ("Sounds\\fonGame.wav");

    Ball car = { .x = 450, .y = 660, .vx = 0, .vy = 0, .rBall = 30,
                 .color = TX_LIGHTRED, .fillcolor = TX_RED};

    int ax1 = 0, ay1 = 0;

    double dt = 1;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txClear();

        txBitBlt (txDC(), 0, 0, 0, 0, fon, 0, 0);

        car.Draw();

        Ball oldPoz = car;

        car.Physics (ax1, ay1, dt);

        ControlBall (&car);

        COLORREF color = txGetPixel (car.x, car.y, map);

        if (color == RGB (255, 255, 0))
            {
            SecretZona (&car);
            }

        else if (color != RGB (0, 0, 255)) car = oldPoz;

        if (color == RGB (255, 0, 0))
            {
            GameOver();

            break;
            }

        if (txGetAsyncKeyState (VK_F5)) txBitBlt (txDC(), 0, 0, 0, 0, map, 0, 0);

        txSleep (10);
        }

    txDeleteDC (fon);
    txDeleteDC (map);
    }

//-----------------------------------------------------------------------------

void Ball::Draw()
    {
    txSetColor (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, rBall);
    }

//-----------------------------------------------------------------------------

void Ball::Physics (double ax, double ay, int dt)
    {
    vx = vx + ax * dt;
    vy = vy + ay * dt;

    x = x + vx * dt;
    y = y + vy * dt;

    /*if ((x + rBall) > 800)
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
        } */
    }

//-----------------------------------------------------------------------------

void ControlBall (Ball* ball)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (ball -> x) += 2;
    if (txGetAsyncKeyState (VK_LEFT))  (ball -> x) -= 2;
    if (txGetAsyncKeyState (VK_UP))    (ball -> y) -= 2;
    if (txGetAsyncKeyState (VK_DOWN))  (ball -> y) += 2;
    }

//-----------------------------------------------------------------------------

/*void Ball::Change ()
    {
    if (x < 117) x = 175;
    else if (x < 320) y = 362;
         else if ((x > 420) && (y < 80)) x = 345;
              else if (x > 570) {x = 485; y = 210;}
    } */

//-----------------------------------------------------------------------------

void SecretZona (Ball* ball)
    {
    txPlaySound ("Sounds\\SecretZone.wav");

    txSleep (21000);

    int chislo1 = rand() % 41 + 10,
        chislo2 = rand() % 41 + 10;

    char str1 [25],
         str2 [25];

    itoa (chislo1, str1, 10);
    itoa (chislo2, str2, 10);

    strcat (str1, " + ");
    strcat (str1, str2);

    const char* question = txInputBox ( str1, "Сосчитай");

    if (atoi (question) == chislo1 + chislo2)
        {
        //car.Gange();

        if ((ball -> x) < 117) (ball -> x) = 175;
        else if ((ball -> x) < 320) (ball -> y) = 362;
             else if (((ball -> x) > 420) && ((ball -> y) < 80)) (ball -> x) = 345;
                  else if ((ball -> x) > 570)
                           {
                           (ball -> x) = 485;
                           (ball -> y) = 210;
                           }
        }
    else
        {
        txMessageBox ("Увы, неправильно... Придется двигаться обратно", "Печалька", MB_OK);
        (ball -> x) = 75;
        }
    }

//-----------------------------------------------------------------------------

void GameOver()
    {
    txPlaySound  ("Sounds\\Pobeda.wav");
    txMessageBox ("Ты молодец!!!", "Победа", MB_OK);
    }
