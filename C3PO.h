#ifndef C3PO_H
#define C3PO_H

#include "Maze.h"
#include "Robot.h"
#include "Texture.h"

using namespace std;

class C3PO: public Robot {
	public:
        C3PO(const Point& iniPos, Maze*l, int maxSteps);	// Constructor
        void draw();
        void generateSteps();
        void generateSteps2();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // robot texture id
};


#endif // C3PO
