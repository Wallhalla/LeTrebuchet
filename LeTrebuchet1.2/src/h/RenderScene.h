#pragma once
#include "Resources.h"
#include "SetupRenderState.h"
#include <time.h>

void RenderScene();

void DrawTrebuchetStatics(GLfloat, GLfloat, GLfloat);
void DrawTrebuchetDynamic();
void DrawExplosion(int);
void DrawLandAndSky();
void DrawGravitySphere();
void UglyManakin();