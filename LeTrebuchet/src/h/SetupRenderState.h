#pragma once
#include "Resources.h"

#include "Simple OpenGL Image Library/src/SOIL.h"

void SetupRenderState();

void SetupLighting();

GLuint SetupTextures(int);

void ResizeWindow(GLsizei, GLsizei);

void SetViewMode(bool);
