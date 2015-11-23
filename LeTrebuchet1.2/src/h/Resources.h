#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windows.system.h>
#include <math.h>

// Includes für OpenGL
#include <GL/gl.h>  // OpenGL Base Library
#include <GL/glu.h> // OpenGL Utility Library
#include <GL/freeglut.h>



#include <cmath> // Substitute some GLT Classes (provide f.e. vector and matrices classes)
#include <iostream>
#include <string>
#include "ComputerGraphics.h"


using namespace std;


// Camerastructs
typedef struct{
	GLfloat x, y, z;
} Points3f;

typedef struct{
	Points3f eye, center, up;
} Camera;