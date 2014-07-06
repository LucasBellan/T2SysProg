#include "R2D2.h"
#include "GL.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

R2D2::R2D2(const Point& iniPos, Maze*l, int maxSteps)
    : Robot(iniPos, l, maxSteps)
{
    srand(time(NULL));
    roboTex = LoadTexture("r2d2.jpg", false);
}

void R2D2::generateSteps()
{
    Point initial = this->maze->getIniPos();
    Point actualPosition = Point(initial.getX(),initial.getY());
    steps.push_back(actualPosition);  //Get the first position in the vector
    int cont = 0;
    bool exit = false;

    // initialize to correct positions
    if(!maze->CanIGoThere(Point(actualPosition.getX(),actualPosition.getY()-1)))direction = Up;
    else if(!maze->CanIGoThere(Point(actualPosition.getX(),actualPosition.getY()+1)))direction = Down;
    else if(!maze->CanIGoThere(Point(actualPosition.getX()+1,actualPosition.getY())))direction = Left;
    else if (!maze->CanIGoThere(Point(actualPosition.getX()-1,actualPosition.getY())))direction = Right;

    while(!exit && maxSteps != 0) // while robot doesn't exit and it doesn't end the steps
    {
        if(moveAhead(&actualPosition)) //move ahead till reach a wall
        {
            turnLeft(actualPosition);// turn left keeping left hand on wall
        }
        else
        {
            do{  // turn right until be able to move ahead
                turnRight(actualPosition);   //turn right keeping left hand on wall

            }while(!moveAhead(&actualPosition));
        }

        if(actualPosition.getX() >= maze->getWidth() ||actualPosition.getX() < 0 || actualPosition.getY() >= maze->getHeight() ||
           actualPosition.getY() < 0){
               exit = true;
        }
    cont ++;
    }
}
void R2D2::draw()
{
    float rx,ry;
    float deltax = GL::getDeltaX();
    float deltay = GL::getDeltaY();
    rx = pos.getX() * deltax;
    ry = pos.getY() * deltay;
    GL::enableTexture(roboTex->texid);
    GL::setColor(255,255,255);
    GL::drawRect(rx, ry, rx+deltax, ry+deltay);
    GL::disableTexture();
}


//move ahead till reach a wall
bool R2D2::moveAhead (Point* ponto)
{
    switch(direction)
    {
        case Up:
            if(maze->CanIGoThere(Point(ponto->getX(),ponto->getY()-1)))
            {
                ponto->setY(ponto->getY()-1);
                steps.push_back(Point(ponto->getX(),ponto->getY()));
               return true;
            }
             return false;
        case Down:
            if(maze->CanIGoThere(Point(ponto->getX(),ponto->getY()+1)))
            {
                ponto->setY(ponto->getY()+1);
                steps.push_back(Point(ponto->getX(),ponto->getY()));
                return true;
            }
             return false;

        case Left:
            if(maze->CanIGoThere(Point(ponto->getX()-1,ponto->getY())))
            {
                ponto->setX(ponto->getX()-1);
                steps.push_back(Point(ponto->getX(),ponto->getY()));
                return true;
           }
            return false;

        case Right:
            if(maze->CanIGoThere(Point(ponto->getX()+1,ponto->getY())))
            {
             ponto->setX(ponto->getX()+1);
                steps.push_back(Point(ponto->getX(),ponto->getY()));
               return true;
            }
             return false;
    }
 return false;
}

void R2D2::turnLeft(const Point& ponto)
{
    switch(direction)
    {
        case Up:
            if(maze->CanIGoThere(Point(ponto.getX()-1,ponto.getY())))
                direction = Left;
            break;

        case Down:
            if(maze->CanIGoThere(Point(ponto.getX()+1,ponto.getY())))
                direction = Right;
            break;

        case Left:
            if(maze->CanIGoThere(Point(ponto.getX(),ponto.getY()+1)))
                direction = Down;
            break;

        case Right:
            if(maze->CanIGoThere(Point(ponto.getX(),ponto.getY()-1)))
                direction = Up;
    }
}

//turn right keeping left hand on wall
void R2D2::turnRight(const Point& ponto)
{
    switch(direction)
    {
        case Up:
            if(!maze->CanIGoThere(Point(ponto.getX(),ponto.getY()-1)))
                direction = Right;
            break;

        case Down:
            if(!maze->CanIGoThere(Point(ponto.getX(),ponto.getY()+1)))
                direction = Left;

            break;

        case Left:
            if(!maze->CanIGoThere(Point(ponto.getX()-1,ponto.getY())))
                direction = Up;
            break;

        case Right:
            if(!maze->CanIGoThere(Point(ponto.getX()+1,ponto.getY())))
                direction = Down;

    }
}

/*
void R2D2::generateSteps()
{
    int cont = 1;
    bool exit = false;
    int x = iniPos.getX();
    int y = iniPos.getY();

    //Get the first position in the vector
    steps.push_back(Point(x,y));

    // initialize to correct positions
    if(!maze->isEmpty(Point(x,y-1)))direction = Up;
    else if(!maze->isEmpty(Point(x,y+1)))direction = Down;
    else if(!maze->isEmpty(Point(x+1,y)))direction = Left;
    else if (!maze->isEmpty(Point(x-1,y)))direction = Right;

    while(!exit && cont < maxSteps) // while robot doesn't exit and it doesn't end the steps
    {
        if(moveAhead(&x,&y)) //move ahead till reach a wall
        {
            turnLeft(&x,&y);// turn left keeping left hand on wall
        }
        else
        {
            do{  // turn right until be able to move ahead
                turnRight(&x,&y);   //turn right keeping left hand on wall

            }while(!moveAhead(&x,&y));
        }

        if(x >= maze->getWidth() || x < 0
                || y >= maze->getHeight() || y < 0)
            exit = true;
    }
  cont ++;
}

void R2D2::draw()
{
    float rx,ry;
    float deltax = GL::getDeltaX();
    float deltay = GL::getDeltaY();
    rx = pos.getX() * deltax;
    ry = pos.getY() * deltay;
    GL::enableTexture(roboTex->texid);
    GL::setColor(255,255,255);
    GL::drawRect(rx, ry, rx+deltax, ry+deltay);
    GL::disableTexture();
}


//move ahead till reach a wall
bool R2D2::moveAhead(int* x,int* y)
{
    switch(direction)
    {
        case Up:
            if(maze->isEmpty(Point(*x,*y-1)))
            {
                *y = *y-1;
                steps.push_back(Point(*x,*y));
                return true;
            }

            return false;

        case Down:
            if(maze->isEmpty(Point(*x,*y+1)))
            {
                *y = *y+1;
                steps.push_back(Point(*x,*y));
                return true;
            }
            return false;

        case Left:
            if(maze->isEmpty(Point(*x-1,*y)))
            {
                *x = *x-1;
                steps.push_back(Point(*x,*y));
                return true;
            }
            return false;

        case Right:
            if(maze->isEmpty(Point(*x+1,*y)))
            {
                *x = *x+1;
                steps.push_back(Point(*x,*y));
               return true;
            }
            return false;
    }
}

void R2D2::turnLeft(int* x,int* y)
{
    switch(direction)
    {
        case Up:
            if(maze->isEmpty(Point(*x-1,*y)))
                direction = Left;
            break;

        case Down:
            if(maze->isEmpty(Point(*x+1,*y)))
                direction = Right;
            break;

        case Left:
            if(maze->isEmpty(Point(*x,*y+1)))
                direction = Down;
            break;

        case Right:
            if(maze->isEmpty(Point(*x,*y-1)))
                direction = Up;
    }
}

//turn right keeping left hand on wall
void R2D2::turnRight(int* x,int* y)
{
    switch(direction)
    {
        case Up:
            if(!maze->isEmpty(Point(*x,*y-1)))
                direction = Right;
            break;

        case Down:
            if(!maze->isEmpty(Point(*x,*y+1)))
                direction = Left;

            break;

        case Left:
            if(!maze->isEmpty(Point(*x-1,*y)))
                direction = Up;
            break;

        case Right:
            if(!maze->isEmpty(Point(*x+1,*y)))
                direction = Down;

    }
}
*/
