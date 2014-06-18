#include "TestMaze.h"
#include "RobotB9.h"
#include "CreateMaze.h"
#include "GL.h"
#include "C3PO.h"

using namespace std;

int main()
{
    GL::init();
    // Load the test maze
    //Maze* lab = new CreateMaze();
    TestMaze* lab = new TestMaze();
    //CreateMaze* lab = new CreateMaze();
    //lab->loadMaze("maze1.txt");
    lab->loadMaze(" ");

    cout<< "Height: " << lab->getHeight()<<" " <<" Width: "<<lab->getWidth()<<" Robot: "<<lab->getRobot()<<endl;
    for (int i =0; i < lab->getHeight(); i++){
        for (int j=0; j < lab->getWidth(); j++){
            cout<<lab->getCharAt(i,j);
        }
        cout<<endl;
	}

    Point posIni = lab->getIniPos();
    cout << "Starting pos: " << posIni.getX() << " , " << posIni.getY() << endl;
    cout << "Width:" << lab->getWidth() << " Height:"<< lab->getHeight()<<endl;
    //RobotB9* robo = new RobotB9(posIni, lab, 200); // 200 passos no maximo
    C3PO* robo = new C3PO(posIni, lab, 200); // 200 passos no maximo

    GL::setMazeRobot(lab, robo);

	GL::loop();

}
