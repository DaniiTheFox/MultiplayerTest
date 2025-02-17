#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
/*
=====================================================================
=        THIS HEADER IS THE ONE USED FOR ALL GLOBAL VARIABLES       =
=====================================================================
*/
#include "Data/Headers/Game_Main_Global_variables.h"
/*
====================================================
=         ALL GAME ENGINE FUNCTIOS GO HERE         =
====================================================
*/
#include "Data/Headers/Bon_OptCube_Model.h"
#include "Data/Headers/Bon_Aux_Functions.h"
#include "Data/Classes/chunks.h"
#include "Data/Headers/Bon_keyboard_Module.h"
#include "Data/Headers/Bon_Display_Module.h"
/*
============================================================================================
=    PRINCIPAL FUNCTION FOR THE GAME THIS IS THE MAIN BLOCK THAT EXECUTES ALL STATEMENTS   =
============================================================================================
*/
int main(int argc, char **argv){                             // MAIN FUNCTION FOR PROGRAM FUNCTIONALITY
 glutInit(&argc, argv);                                      // START THE OPENGL LIBRARY FOR THE GAME
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // INITIALIZE THE GRAPHICS MODE ON DISPLAY
  glutInitWindowSize(BON_SCREEN_W,BON_SCREEN_H);             // SET THE WINDOW SIZE
  glutInitWindowPosition(300,64);                            // SET THE WINDOW POSITION
  glutCreateWindow("= CLIENT: Block Universe =");            // CREATE A GLUT WINDOW FOR THE GAME
 glDepthFunc(GL_LEQUAL);                                     // START THE DEPTH FUNCTION
 glClearDepth(1.0f);                                         // CLEAR THE DEPTH BUFFER
 glIni();                                                    // THE SETUP FUNCTION
  glutDisplayFunc(BON_GRAPH_FUNCTION);                       // THE FUNCTION TO INITIALIZE AND DRAW THE OBJECTS
  glutKeyboardFunc(BON_KEYBOARD_FUNCTION);                   // THE FUNCTION FOR KEYBOARD INTERACTIONS
  glutPassiveMotionFunc(BON_MOUSE_FUNCTION);                 // THE FUNCTION FOR THE MOUSE INTERACTIONS
  glutIdleFunc(BON_IDLE_FUNCTION);                           // THE FUNCTION WHEN PLAYER IS NOT DOING ANYTHING
 glutMainLoop();                                             // MAIN LOOP FOR THE GAME
 return EXIT_SUCCESS;                                        // RETURN STATEMENT SAME AS RETURN 0;
}
