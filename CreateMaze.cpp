#include <iostream>
#include "CreateMaze.h"

CreateMaze::CreateMaze()
{

}

bool CreateMaze::isEmpty(const Point& pos) const
{
    if(pos.getX()<0 || pos.getX()>=dimx || pos.getY()<0 || pos.getY()>=dimy) return true;
    return (lab[pos.getY()][pos.getX()]==' ');
}

int CreateMaze::getWidth()
{
    return this->width;
}

bool CreateMaze::canIgoThere(const Point& p)
{
    if(lab[p.getX()][p.getY()] == '*')
        return false;
    return true;
}

int CreateMaze::getHeight()
{
    return this->height;
}

void CreateMaze::loadMaze(string arquivo)
{
    ifstream reader;
	reader.open( arquivo.c_str(), ios::in );

    if (!reader.is_open()){
        cout<<"Can't open the file :("<<endl;
		reader.close();
		return;
	}
    string a;
    int x,y;
	reader >> a >> height >> width;
	dimx = height; dimy = width;
    reader >> a >> x >> y;
	posIni = Point(x,y);
	reader >> a >> robot;

    char cr = ' ';
    string aux;
    reader >> noskipws >> cr;
	for (int i =0; i < height; i++){
            getline(reader, aux);
        for (int j=0; j < width; j++){
                lab[i][j] = aux[j];
        }
	}

    reader.close();
}

int CreateMaze::getRobot()
{
    return this->robot;
}

char CreateMaze::getCharAt(int i, int j){ return lab[i][j];}

Point CreateMaze::getIniPos()
{
    return this->posIni;
}
