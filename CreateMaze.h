#ifndef CREATEMAZE
#define CREATEMAZE
#include <fstream>
#include "Maze.h"

using namespace std;

class CreateMaze : public Maze {
	public:
		CreateMaze();	// Constructor
        bool isEmpty(const Point& ponto) const;
	    int  getWidth();
	    int  getHeight();
	    void loadMaze(string arquivo);
        int  getRobot();
        char getCharAt(int i, int j);
        Point getIniPos();
	private:
		int width, height;	// Maze size
        char lab[100][100];	// The maze
        int robot;
        int dimx, dimy;
        Point posIni;
};


#endif // CREATEMAZE_H_INCLUDED
