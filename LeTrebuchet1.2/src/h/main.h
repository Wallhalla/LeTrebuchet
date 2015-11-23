
#pragma once
#define GL_PI 3.14159

#include "Resources.h"
#include "SetupRenderState.h"
#include "RenderScene.h"
#include "SetupCamera.h"
#include "KeyHandler.h"


int main(int argc, char **argv);

void TimerFunc(int);

int createMenu(void);
void PopUpOptions(int);


// enumeration for context menu (named indecies)
enum
{
	MENU_CAMERAVIEW,
	MENU_DEPTH,
	MENU_FOG,
	MENU_LIGHTING, MENU_LIGHT0, MENU_LIGHT1, 
	MENU_BLEND,
	MENU_TEXTURING,
	MENU_EXIT
};


// structure of boolean to toggle between render specifics
typedef struct
{
	bool bcameraview;
	bool bdepthtest;
	bool bfog;
	bool blighting;
	bool blight0;
	bool blight1;
	bool bblend;
	bool btexture;

}Toggle;


