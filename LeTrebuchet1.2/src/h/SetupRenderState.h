#pragma once
#include "Resources.h"
//#include "..\soil\Simple OpenGL Image Library\src\SOIL.h"
#include "../ThirdParty/soil/Simple OpenGL Image Library/src/SOIL.h"

void SetupRenderState();

void SetupLighting();

GLuint SetupTextures(int);

void ResizeWindow(GLsizei, GLsizei);

void SetViewMode(bool);
