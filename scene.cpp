#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <bitset>
#include <algorithm>
#include <stdlib.h>     //for using the function sleep

#include "Eigen/Geometry"

#include "Joint.h"
#include "JointSystem.h"

inline float sqr(float x) { return x*x; }

using namespace std;

//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};



//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;
bool debug;
int displayMode;
JointSystem jointSystem;



//****************************************************
// Initialize list of joints pointing in same direction (y-axis)
//***************************************************
void initializeJoints() {
	Joint joint1 = Joint(Eigen::Vector3f(0.0, -0.5, 0.0), 0.2);
	Joint joint2 = Joint(joint1.endingPosition, 0.4);
	Joint joint3 = Joint(joint2.endingPosition, 0.3);
	Joint joint4 = Joint(joint3.endingPosition, 0.1);
	jointSystem.addJoint(joint1);
	jointSystem.addJoint(joint2);
	jointSystem.addJoint(joint3);
	jointSystem.addJoint(joint4);
}

//****************************************************
// Simple init function
//****************************************************
void initScene(){
	initializeJoints();
}


//****************************************************
// reshape viewport if the window is resized
//***************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-w / 1000.0, w / 1000.0, -h / 1000.0, h / 1000.0, 5, -5);

}



//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glRotated(.4, 0, 1, 0);

	glShadeModel(GL_FLAT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLoadIdentity();				        // make sure transformation is "zero'd"

	double colors[] = { 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 1.0, 0.0 };

  // Iterate through joints and render them
  for (std::vector<Joint>::size_type i = 0; i < jointSystem.joints.size(); i++) {
	  glColor3d(colors[i * 3], colors[i * 3 + 1], colors[i * 3 + 2]);
	  jointSystem.joints[i].renderJoint(displayMode);
  }

  glFlush();
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}



//****************************************************
// function that assists with exit of program on space bar press
//***************************************************
void exitOnSpaceBarPress( unsigned char key, int x, int y )
{
    switch ( key ) 
    {
    case 'd':
    	displayMode += 1;
    	break;

    // Space bar
    case ' ':
        exit(1);
    }

    glutPostRedisplay();
}


//****************************************************
// function that prints all of our command line option variables
//***************************************************
void printCommandLineOptionVariables( )
{
  if (debug)
  {
    
  }
}


//****************************************************
// function that parses command line options,
// given number of command line arguments (argc)
// and the argument array (argv)
//***************************************************
void parseCommandLineOptions(int argc, char *argv[])
{
  string flag;

  int i = 1;
  while (i <= argc - 1) {

    flag = argv[i];

    // Advance to next flag, if one exists
    i++;
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

  displayMode = 0;

  // Turns debug mode ON or OFF
  debug = true;

  // This initializes glut
  glutInit(&argc, argv);

  // Parse command line options
  parseCommandLineOptions(argc, argv);
  printCommandLineOptionVariables();

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Initalize theviewport size
  viewport.w = 1000;
  viewport.h = 1000;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  // Program exits if space bar is pressed
  glutKeyboardFunc( exitOnSpaceBarPress );

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}








