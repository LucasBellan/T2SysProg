#include "WALL-E.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

WALL_E::WALL_E(const Point& iniPos, Maze* l, int maxSteps): Robot(iniPos, l, maxSteps)
{
    srand(time(NULL));
    roboTex = LoadTexture("c3po.jpg", false);
}

void WALL_E::draw()
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


bool WALL_E::generateSteps2(const Point& ponto)
{
    if (maze->CanIGoThere(Point(ponto.getX()+1,ponto.getY())) && mazePath[ponto.getX()+1][ponto.getY()] != 'x'){
        mazePath[ponto.getX()+1][ponto.getY()] = 'x';
        if(ponto.getX() >= maze->getWidth() || ponto.getX() < 0 || ponto.getY() >= maze->getHeight() || ponto.getY() < 0){
            mazePath[ponto.getX()+1][ponto.getY()] = '+';
            return true;
        }
        if(generateSteps2(Point(ponto.getX()+1,ponto.getY()))){
            mazePath[ponto.getX()+1][ponto.getY()] = '+';
            return true;
        }
        mazePath[ponto.getX()+1][ponto.getY()] = 'x';
        //return false;
    }
    if (maze->CanIGoThere(Point(ponto.getX(),ponto.getY()-1)) && mazePath[ponto.getX()][ponto.getY()-1] != 'x'){
        mazePath[ponto.getX()][ponto.getY()-1] = 'x';
        if(ponto.getX() >= maze->getWidth() || ponto.getX() < 0 || ponto.getY() >= maze->getHeight() || ponto.getY() < 0){
            mazePath[ponto.getX()+1][ponto.getY()] = '+';
            return true;
        }
        if(generateSteps2(Point(ponto.getX(),ponto.getY()-1))){
            mazePath[ponto.getX()][ponto.getY()-1] = '+';
            return true;
        }
        mazePath[ponto.getX()][ponto.getY()-1] = 'x';
        //return false;
    }
    if (maze->CanIGoThere(Point(ponto.getX(),ponto.getY()+1)) && mazePath[ponto.getX()][ponto.getY()+1] != 'x'){
        mazePath[ponto.getX()][ponto.getY()+1] = 'x';
        if(ponto.getX() >= maze->getWidth() || ponto.getX() < 0 || ponto.getY() >= maze->getHeight() || ponto.getY() < 0){
            mazePath[ponto.getX()+1][ponto.getY()] = '+';
            return true;
        }
        if(generateSteps2(Point(ponto.getX(),ponto.getY()+1))){
            mazePath[ponto.getX()][ponto.getY()+1] = '+';
            return true;
        }
        mazePath[ponto.getX()][ponto.getY()+1] = 'x';
        //return false;
    }
    if (maze->CanIGoThere(Point(ponto.getX()-1,ponto.getY())) && mazePath[ponto.getX()-1][ponto.getY()] != 'x'){
        mazePath[ponto.getX()-1][ponto.getY()] = 'x';
        if(ponto.getX() >= maze->getWidth() || ponto.getX() < 0 || ponto.getY() >= maze->getHeight() || ponto.getY() < 0){
            mazePath[ponto.getX()+1][ponto.getY()] = '+';
            return true;
        }
        if(generateSteps2(Point(ponto.getX()-1,ponto.getY()))){
            mazePath[ponto.getX()-1][ponto.getY()] = '+';
            return true;
        }
        mazePath[ponto.getX()-1][ponto.getY()] = 'x';
        //return false;
    }

    mazePath[ponto.getX()][ponto.getY()] = 'x';
    return false;
}

void WALL_E::generateSteps()
{
    generateSteps2(iniPos);
    bool saiu = false;
    steps.push_back(iniPos);
    Point actualPosition = Point(iniPos.getX(),iniPos.getY());
    while(!saiu){
        if(mazePath[actualPosition.getX()+1][actualPosition.getY()] == '+'){
            actualPosition.setX(actualPosition.getX()+1);
            steps.push_back(actualPosition);
            mazePath[actualPosition.getX()][actualPosition.getY()] = 'x';
            maxSteps--;
            continue;
        }
        if(mazePath[actualPosition.getX()-1][actualPosition.getY()] == '+'){
            actualPosition.setX(actualPosition.getX()-1);
            steps.push_back(actualPosition);
            mazePath[actualPosition.getX()][actualPosition.getY()] = 'x';
            maxSteps--;
            continue;
        }
        if(mazePath[actualPosition.getX()][actualPosition.getY()+1] == '+'){
            actualPosition.setY(actualPosition.getY()+1);
            steps.push_back(actualPosition);
            mazePath[actualPosition.getX()][actualPosition.getY()] = 'x';
            maxSteps--;
            continue;
        }
        if(mazePath[actualPosition.getX()][actualPosition.getY()-1] == '+'){
            actualPosition.setY(actualPosition.getY()-1);
            steps.push_back(actualPosition);
            mazePath[actualPosition.getX()][actualPosition.getY()] = 'x';
            maxSteps--;
            continue;
        }
        if(actualPosition.getX() >= maze->getWidth() || actualPosition.getX() < 0 || actualPosition.getY() >= maze->getHeight() || actualPosition.getY() < 0){
            saiu = true;
        }
    }
}
