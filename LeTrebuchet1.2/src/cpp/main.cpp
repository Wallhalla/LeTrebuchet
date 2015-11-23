#include "main.h"

#include "Animations.h"

// SETUP GL_WINDOW WIDTH AND HEIGHT
GLint windowWidth = 1024;
GLint windowHeight = 768;

// GET CURRENT RESOLUTION FROM WIN API
GLint currentDisplayWidth = GetSystemMetrics(0);	// get current DisplayWidth
GLint currentDisplayHeight = GetSystemMetrics(1);	// get current DisplayHeight

// Declare cameraobject and set up params
Camera mainCam;

// Structure for toggeling inside contextmenu
Toggle toggle;


int oldTimeSinceStart = 0;

// main can by started with extern data 
int main(int argc, char **argv)
{
	// Startvalues for menu
	toggle.bdepthtest = true;
	toggle.bfog = true;
	toggle.blighting = true;
	toggle.blight0 = true;
	toggle.blight1 = true;
	toggle.bblend = true;
	toggle.btexture = true;	

	// Camera Coordinates
	mainCam.eye.x = 0.0f, mainCam.eye.y = 0.0f, mainCam.eye.z = 100.0f;					// Eye Coordinates
	mainCam.center.x = 0.0f, mainCam.center.y = 0.0f, mainCam.center.z = 0.0f;			// CenterPoint Coordinates
	mainCam.up.x = 0.0f, mainCam.up.y = 1.0f, mainCam.up.z = 0.0f;						// Up Vector

	// Initialize GLUT LIB
	glutInit(&argc, argv);
	// Set OpenGL Version 2.0
	glutInitContextVersion(2, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);		// exit the program when window-cross is clicked

	// Initialize Display Mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);		// Double Display Buffer, Init ColorBase, Depth-Testing and Stencil

	// setting up the Window and Position on Monitor
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(currentDisplayWidth / 2 - windowWidth / 2, currentDisplayHeight / 2 - windowHeight / 2); // Get the Window to the middle of current Resolution

	// Create the Window with Title
	glutCreateWindow("Le trebuchét");

	// Show controls in console
	cout << "Controls:\n" << "Press WASD-keys to move Up/Left/Down/Right" << endl;
	cout << "\nPress EQ-keys to move Forward/Backward" << endl;
	cout << "\nPress M-key to shoot the trebuchet" << endl;
	cout << "\nRightclick into screen to open contextmenue\n" << endl;

	// Setup the View
	InitCam(&mainCam);

	//____________CALBACK REGISTER________________________

	// The Callback to store and do all the drawings
	glutDisplayFunc(RenderScene);
	// Idle Callback, RenderScene will be the method when nothing else needs to be done
	glutIdleFunc(RenderScene);
	// The Callback when we resize our window during runtime
	glutReshapeFunc(ResizeWindow);
	// Callback for KeyboardInput
	glutKeyboardFunc(KeyPressed);			// For Pressed Keys
	glutKeyboardUpFunc(KeyReleased);		// For Released Keys
	glutSpecialFunc(SpecialKeyPressed);		// For Pressed Special Keys (like Arrows, Shift a.s.o)
	glutSpecialUpFunc(SpecialKeyReleased);	// For Released Special Keys

	glutEntryFunc(NULL);
	TimerFunc(0);	

	// Delay Redraw Callback
	glutTimerFunc(30, TimerFunc, 1);		
	//________END CALLBACK REGISTER_______________________

	// Init Contextmenu
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	
	createMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Setup before Rendering (Background,Lighting, Blend a.s.o)
	SetupRenderState();

	// Call the GLUT Framework to start and let the system run
	glutMainLoop();
	
	return 0;
}

void TimerFunc(int value)
{
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	if (IsShooting())
	{
		DoThrowAnim();
	}
	if (ShouldCannonballFly())
	{
		CannonballFly(deltaTime);
	}
	if (IsShootingReverting())
	{
		RevertThrowAnim();
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunc, 0);
}


// Options for contextmenu
int createMenu()
{	
	GLvoid *menuFont = GLUT_BITMAP_TIMES_ROMAN_24;	// Setup Textformat
	
	int contextMenu;
	contextMenu = glutCreateMenu(PopUpOptions);

	glutAddMenuEntry("Toggle Camera", MENU_CAMERAVIEW);
	glutAddMenuEntry("Toggle Depth Testing", MENU_DEPTH);
	glutAddMenuEntry("Toggle Fogging", MENU_FOG);

	glutAddMenuEntry("Switch Lighting", MENU_LIGHTING);
	glutAddMenuEntry("   Switch Light 0", MENU_LIGHT0);
	glutAddMenuEntry("   Switch Light 1", MENU_LIGHT1);
	glutAddMenuEntry("   Switch Blending", MENU_BLEND);	

	glutAddMenuEntry("Enable Texturing", MENU_TEXTURING);
	glutAddMenuEntry("Exit", MENU_EXIT);
	return contextMenu;
}



void PopUpOptions(int selection)
{
	// selection is the index of the selected item in menu, and the index is represented by the enumeration name f.e. MENU_CAMERAVIEW = INDEX 0
	switch (selection)
	{
	case MENU_CAMERAVIEW:		toggle.bcameraview = !toggle.bcameraview;	SetViewMode(toggle.bcameraview);	break;
	case MENU_DEPTH:			toggle.bdepthtest = !toggle.bdepthtest;		SetupLighting();					break;
	case MENU_FOG:				toggle.bfog = !toggle.bfog;					SetupLighting();					break;

	case MENU_LIGHTING:  		toggle.blighting = !toggle.blighting;		SetupLighting();					break;
	case MENU_LIGHT0: 			toggle.blight0 = !toggle.blight0;			SetupLighting();					break;
	case MENU_LIGHT1:			toggle.blight1 = !toggle.blight1;												break;
	
	case MENU_BLEND:			toggle.bblend = !toggle.bblend;													break;

	case MENU_TEXTURING: 		toggle.btexture = !toggle.btexture;			break;
	case MENU_EXIT:				exit(0);
	}

	// Redisplay
	glutPostRedisplay();
}