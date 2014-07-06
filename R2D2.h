#ifndef R2D2_H
#define R2D2_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"


class R2D2 : public Robot
{
    public:
        R2D2(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
        enum enum_direction {Up, Down, Left, Right};
        bool moveAhead (Point* ponto);
        void turnLeft(const Point& ponto);
        void turnRight(const Point& ponto);
    private:
        TEX* roboTex; // robot texture id
        enum_direction direction;

};

#endif // R2D2_H
