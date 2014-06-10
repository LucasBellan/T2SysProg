#include "C3PO.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

C3PO::C3PO(const Point& iniPos, Maze* l, int maxSteps): Robot(iniPos, l, maxSteps)
{
    srand(time(NULL));
    roboTex = LoadTexture("c3po.jpg", false);
}

void C3PO::draw()
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


void C3PO::generateSteps()
{
    Point initial = this->maze->getIniPos();
    int x = initial.getX();
    int y = initial.getY();
    for (int cont = 0; cont < this->maxSteps; cont++){
        if(x >= maze->getWidth() || x < 0 || y >= maze->getHeight() || y < 0){ return; }
        if (this->maze->isEmpty(this->pos.getX()+1)){
            steps.push_back(Point(x,y));
            x++;
        }
    }
}

void C3PO::generateSteps2()
{
   int cont = 1;
    bool saiu = false;
    int x = iniPos.getX();
    int y = iniPos.getY();
    steps.push_back(Point(x,y));
    while(!saiu && cont < maxSteps)
    {
        int dx, dy;
        do {
            int dir = rand()%4;
            dx = 0;
            dy = 0;
            switch(dir) {
                case 0:	dx = 1;
                    break;
                case 1:	dx = -1;
                    break;
                case 2:	dy = 1;
                    break;
                case 3: dy = -1;
                    break;
            }
        }
        while(!maze->isEmpty(Point(x+dx, y+dy)));
        x += dx;
        y += dy;
        steps.push_back(Point(x, y));
        cont++;
        if(x >= maze->getWidth() || x < 0
                || y >= maze->getHeight() || y < 0)
            saiu = true;
    }
}
