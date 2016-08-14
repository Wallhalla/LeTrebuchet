#pragma once

#include <cmath>
#include <iostream>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif


// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Include our class libraries and constants ---
//

namespace ComputerGraphics 
{

//  Helper function to load vertex and fragment shader files
GLuint InitShader( const char* vertexShaderFile,
		   const char* fragmentShaderFile );

//  Defined constant for when numbers are too small to be used in the
//    denominator of a division operation.  This is only used if the
//    DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = M_PI / 180.0f;

}  // namespace Angel

#include "vec.h"
#include "mat.h"
//#include "CheckError.h"

// #define Print(x)  do { std::cerr << #x " = " << (x) << std::endl; } while(0)

//  Globally use our namespace in our example programs.
using namespace ComputerGraphics;

