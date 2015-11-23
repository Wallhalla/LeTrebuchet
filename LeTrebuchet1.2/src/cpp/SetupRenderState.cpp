#include "SetupRenderState.h"
#include "main.h"

// Just a REMINDER
//THE PROJECTION MATRIX
//Is a 4*4 Matrix which stores information about how the 3D Space is shown in 2D Plane(also called Color Buffer or ViewPort)
//What we see is still 2D with a lookalike of Depth
//The Projection Matrix is set up whith our Viewport Information, 2 Planes the Near and Far Plane which are connected and so
//bringing up a Box in which we can see something.
//
//
//THE MODEL VIEW MATRIX
//also known as Transformation Matrix.
//Everytime we want to do a translation on any of our models, the Model View Matrix is required.
//This Matrix is also a 4*4 Matrix which stores the location and rotation in projection to our PROJECTION MATRIX

// =============== GLOBALS ============================================================================================
GLfloat GlobalAmbientColorLowWhite[] = { 0.2f, 0.2f, 0.2f, 1.0f };

// GLLIGHT0
GLfloat L0_DiffuseColorWhite[] = { 0.2f, 0.2f, 0.2f, 1.0f};
GLfloat L0_SpecularColorWhite[] = { 0.6f, 0.6f, 0.6f, 1.0f };

// GLLIGHT1
GLfloat L1_BlackColor[] = { 0, 0, 0, 1 };
GLfloat L1_WhiteColor[] = { 0.8, 0.8, 0.8, 1 };

// Materials
GLfloat M_AmbDiff[] = { 0.2, 0.2, 0.2, 1 };

// LIGHTPOSITIONS
GLfloat LightPosSun[] = { 0.0f, 200.0f, -200.0f, 1.0f };	// Directional Light shines to negativ Y and positiv Z (towards us)
GLfloat LightPosFromView[] = { 0.0f, 0.0f, 1.0f, 0.0f };	// Light´s Pos default vaule if not specified (apart from us to negativ Z)


// GLLIGHT1
//GLfloat DiffuseColorPosition[] = { 0.0f, 50.f, 0.0f, 1.0f};
//GLfloat DiffuseColorWhite[] = { 0.6f, 0.6f, 0.6f };
//GLfloat DiffuseColorSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLuint textureWood;
GLuint textureGrass;
GLuint textureSkyBox;

extern Toggle toggle;


GLfloat windowWidth, windowHeight;
GLfloat angle, aspect, dnear, dfar, nRange;

bool bselectViewMode = false;

// =============== END OF GLOBALS ============================================================================================

// Main func
void SetupRenderState()
{
	// Background color
	glClearColor(0.2, 0.2, 0.2, 0.0);

	SetupLighting();
	
	// save textures (wood,grass,sky)
	textureWood = SetupTextures(0);
	textureGrass = SetupTextures(1);
	textureSkyBox = SetupTextures(2);	
}


// Lighting func
void SetupLighting()
{
	
	// ======== CULLING to hide surfaces which cant be seen ==========
	glEnable(GL_CULL_FACE);

	// ========== Depth-Testing ===========
	
	if (toggle.bdepthtest)
	{
		glEnable(GL_DEPTH_TEST);
		cout << "Depth Test ON" << endl;
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		cout << "Depth Test OFF" << endl;
	}	

	// ========= FOG ================ (grayscaling to fake distances)
	if (toggle.bfog)
	{
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogi(GL_FOG_START, 1);
		glFogi(GL_FOG_END, 1000);
		cout << "Fog ON" << endl;
	}
	else
	{
		glDisable(GL_FOG);
		cout << "Fog OFF" << endl;
	}

	// ========== LIGHTING ======================================= (Lighting calculations from surface normals)
	if (toggle.blighting)
	{
		glEnable(GL_LIGHTING);
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
		cout << "Lighting ON" << endl;
	}
	else
	{
		glDisable(GL_LIGHTING);
		cout << "Lighting OFF" << endl;
	}
	
	// global ambient light for the scene
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientColorLowWhite);

	if (toggle.blight0)
	{
		//	 LIGHT 0
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosSun);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_DiffuseColorWhite);
		glLightfv(GL_LIGHT0, GL_SPECULAR, L0_SpecularColorWhite);	
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	// Setup material, where the color of material is within lighting calculations
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	
}


// windowWidth and windowHeight stores the Window Width and Height at the Time we resize the Window during runtime
// will be also called at program start, remember first window is a resize-like as well
	void ResizeWindow(GLsizei w, GLsizei h)
	{
		
		angle = 60.0f;
		dnear = 1.0f;
		dfar = 3000.0f;
		nRange = 50;

		windowWidth = (GLfloat)w;
		windowHeight = (GLfloat)h;

		
		// Prevent a divide by zero
		if (windowHeight == 0)
			windowHeight = 1;

		// Set Viewport to window dimensions
		glViewport(0, 0, windowWidth, windowHeight);

		// Reset coordinate system
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		SetViewMode(bselectViewMode);
		
		
	}


	// Perspective or Orthonormal view depends on contextmenu or key 'o'
	void SetViewMode(bool bViewMode)
	{
		// Set Viewport to window dimensions
		glViewport(0, 0, windowWidth, windowHeight);

		// Reset coordinate system
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if (bViewMode)
		{
			// Orthographical View			
			//// Establish clipping volume (left, right, bottom, top, near, far)
			if (windowWidth <= windowHeight)
				glOrtho(-nRange, nRange, -nRange*windowHeight / windowWidth, nRange*windowHeight / windowWidth, dnear, dfar);
			else
				glOrtho(-nRange*windowWidth / windowHeight, nRange*windowWidth / windowHeight, -nRange, nRange, dnear, dfar);

			cout << "Orthonormal View active! <Switch with 'o'>" << endl;
		}
		else
		{
			// Perspective View
			aspect = (GLfloat)windowWidth / (GLfloat)windowHeight;
			gluPerspective(angle, aspect, dnear, dfar);

			cout << "\nPerspective View active! <Switch with 'o'> \n" << endl;
		}
		
		// to make sure GL_PROJECTION is not active when objects will be rendered
		glMatrixMode(GL_MODELVIEW);
	}


	// Load Textures with SOIL.lib
	// very simple way and not the best one, but it does its task
	GLuint SetupTextures(int id)
	{
		GLuint getTexture = 0;	

		// =========================================================
		// =========== Path to TEXTURES ============================
		// =========================================================
		/* load image file directly as a new OpenGL texture */		
		
			if (id == 0)
			{
				getTexture = SOIL_load_OGL_texture
					(
					"Textures\\woodplateRAW.raw",					
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT					
					);
			}

			if (id == 1)
			{
				getTexture = SOIL_load_OGL_texture
					(
					"Textures\\grassRAW.raw",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
			}

			if (id == 2)
			{
				getTexture = SOIL_load_OGL_texture
					(
					"Textures\\skyBoxSphereRAW.raw",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
			}

			/* check for an error during the load process */
			if (getTexture == 0)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
			}
			
		return getTexture;
	}
