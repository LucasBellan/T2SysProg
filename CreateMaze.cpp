#include <iostream>
#include "CREATEMAZE.H"

CreateMaze::CreateMaze()
{

}

bool CreateMaze::isEmpty(const Point& pos) const
{
    if(pos.getX()<0 || pos.getX()>=height || pos.getY()<0 || pos.getY()>=width) return true;
    return (lab[pos.getY()][pos.getX()]==' ');
}

int CreateMaze::getWidth()
{
    return this->width;
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
    reader >> a >> x >> y;
	posIni = Point(x,y);
	reader >> a >> robot;

    char cr = ' ';
    reader >> noskipws >> cr;
	for (int i =0; i < height; i++){
        for (int j=0; j <= width; j++){
            char b = NULL;
            reader >> noskipws >> b;
            if (b == '\n'){ continue;}
            if (b == '*'){ lab[i][j] = '*';}
            else { lab[i][j] = ' ';}
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
