#ifndef WALL-E_H_INCLUDED
#define WALL-E_H_INCLUDED

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"

using namespace std;

class WALL_E: public Robot {
	public:
        WALL_E(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        bool generateSteps2(const Point& ponto);
        vector<Point> getSteps();
    private:
        char mazePath[100][100];
        TEX* roboTex; // robot texture id
};

#endif // WALL-E_H_INCLUDED
