#include "RenderScene.h"
#include "Animations.h"
#include "main.h"




// ============================ GLOBALS ===============================================
extern GLuint textureWood;
extern GLuint textureGrass;
extern GLuint textureSkyBox;

// Solid Objects
GLUquadric *sphere = gluNewQuadric();		// WorldSphere
GLUquadric *cylinder = gluNewQuadric();		// Trebuchet-Axle
GLUquadric *cylinderTops = gluNewQuadric();	// Axle Top and Bottom
GLUquadric *throwArm = gluNewQuadric();		// The throwing Beam

GLfloat earthRot = 0.0f;
const GLfloat throwArmBaseRotation = -16.0f;

// FireRotation
GLfloat fireRotation = 0.0f;
GLfloat sphereRotation = 0.0f;

// The Weigth
GLfloat x, y, z;
GLfloat weightX = -70;
GLfloat weightY = 0.0;
GLfloat weightPosDelta = 0.0f;

// The Sphere
GLfloat SphereDistanceX = 0;
GLfloat SphereDistanceY = 0;

// connection to contextmenu
extern Toggle toggle;

// connection to Light1 settings
extern GLfloat L1_BlackColor[];
extern GLfloat L1_WhiteColor[];
extern GLfloat LightPosFromView[];

extern GLfloat M_AmbDiff[];


// Ugly manakin values

GLfloat startPosManX = 50.0f;
GLfloat startPosManZ = 10.0f;

extern bool winkAnim;
bool breverse = false;

int armangle = 0;
int counter = 0;

// ============================ END OF GLOBALS ==========================================


void RenderScene()
{	
	

	// Enable background color and depth test
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// initialize random generator for explosion particles
	srand(time(NULL));

	DrawLandAndSky();

	glCullFace(GL_BACK);

	// Translate in the middle	
	x = -17.5f;
	y = -20.0f;
	
	// Translate TrebuchetStatic Z and draw the construction twice
	z = 20.0f;
	DrawTrebuchetStatics(x, y,z);
	z = -10.0f;
	DrawTrebuchetStatics(x,y,z);
	
	DrawTrebuchetDynamic();	

	DrawGravitySphere();	

	UglyManakin();

	glutSwapBuffers();	
}

void DrawTrebuchetStatics(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	
	// TEXTUREFILTERING - REMINDER

	/* // ======== WithOut TextureFiltering ==========================
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	*/

	// // ======== LINEAR TextureFiltering ==========================
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	
	glTranslatef(x, y, z);

	glFrontFace(GL_CCW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glColor3f(0.6f, 0.6f, 0.6f);	// Groundcolor to mix with Texture

	if (toggle.btexture)
	{
		glBindTexture(GL_TEXTURE_2D, textureWood);
		glEnable(GL_TEXTURE_2D);
		// ======== MIPMAP AND LINEAR TextureFiltering ==========================
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// ===============================================================
	/* =================== LEFT BEAMSIDES (Testcolor RED)=============*/
	// ===============================================================

	// Left BEAM FRONT	
	glBegin(GL_TRIANGLE_STRIP);	

		glTexCoord2d(0.0, 0.0);  glVertex3f(0, 0, 0);	// Bottom Left
		glTexCoord2d(1.0, 0.0);  glVertex3f(5, 0, 0);	// Bottom Right
		glTexCoord2d(0.0, 1.0);  glVertex3f(7, 39, 0);	// Top Left
		glTexCoord2d(1.0, 1.0);  glVertex3f(12, 39, 0);	// Top Right
				
	glEnd();		

	// Left BEAM BACK
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -5);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(5, 0, -5);	// Bottom Right
		glTexCoord2d(0.0, 1.0); glVertex3f(7, 39, -5);	// Top Left
		glTexCoord2d(1.0, 1.0); glVertex3f(12, 39, -5);	// Top Right
	
	glEnd();

	// Left BEAM LEFT
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -5);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(0, 0, 0);	// Bottom Right
		glTexCoord2d(0.0, 1.0); glVertex3f(7, 39, -5);	// Top Left
		glTexCoord2d(1.0, 1.0); glVertex3f(7, 39, 0);	// Top Right

	glEnd();
	
	// Left BEAM RIGHT
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.0, 0.0); glVertex3f(5, 0, 0);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(5, 0, -5);	// Bottom Right
		glTexCoord2d(0.0, 1.0); glVertex3f(12, 39, 0);	// Top Left
		glTexCoord2d(1.0, 1.0); glVertex3f(12, 39, -5);	// Top Right
	
	glEnd();		

	//Left BEAM BOTTOM
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -5);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(5, 0, -5);	// Bottom Right
		glTexCoord2d(0.0, 1.0); glVertex3f(0, 0, 0);	// Top Left
		glTexCoord2d(1.0, 1.0); glVertex3f(5, 0, 0);	// Top Right

	glEnd();	

	// Left BEAM TOP
	glBegin(GL_TRIANGLE_STRIP);	

		glTexCoord2d(0.0, 1.0); glVertex3f(7, 39, -5);	// Top Left
		glTexCoord2d(0.0, 0.0); glVertex3f(7, 39, 0);	// Bottom Left
		glTexCoord2d(1.0, 1.0); glVertex3f(12, 39, -5);	// Top Right
		glTexCoord2d(1.0, 0.0); glVertex3f(12, 39, 0);	// Bottom Right

	glEnd();


	// ==============================================================
	/* =================== RIGHT BEAMSIDES (Testcolor BLUE)==========*/
	// ==============================================================
	
	// right BEAM FRONT	
	glBegin(GL_TRIANGLE_STRIP);
	
		glTexCoord2d(1.0, 1.0); glVertex3f(30, 39, 0);	// Top Right
		glTexCoord2d(0.0, 1.0); glVertex3f(25, 39, 0);	// Top Left
		glTexCoord2d(1.0, 0.0); glVertex3f(35, 0, 0);	// Bottom Right
		glTexCoord2d(0.0, 0.0); glVertex3f(30, 0, 0);	// Bottom Left

	glEnd();

	
	// right BEAM BACK
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(1.0, 1.0); glVertex3f(25, 39, -5);	// Top Left
		glTexCoord2d(0.0, 1.0); glVertex3f(30, 39, -5);	// Top Right
		glTexCoord2d(1.0, 0.0); glVertex3f(30, 0, -5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(35, 0, -5);	// Bottom Right
	
	glEnd();		
		
	// right BEAM LEFT
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(1.0, 1.0); glVertex3f(25, 39, 0);	// Top Right
		glTexCoord2d(0.0, 1.0); glVertex3f(25, 39, -5);	// Top Left
		glTexCoord2d(1.0, 0.0); glVertex3f(30, 0, 0);	// Bottom Right
		glTexCoord2d(0.0, 0.0); glVertex3f(30, 0, -5);	// Bottom Left

	glEnd();

	// right BEAM RIGHT
	glBegin(GL_TRIANGLE_STRIP);
	
		glTexCoord2d(0.0, 1.0); glVertex3f(30, 39, 0);	// Top Left
		glTexCoord2d(0.0, 0.0); glVertex3f(35, 0, 0);	// Bottom Left
		glTexCoord2d(1.0, 1.0); glVertex3f(30, 39, -5);	// Top Right
		glTexCoord2d(1.0, 0.0); glVertex3f(35, 0, -5);	// Bottom Right

	glEnd();

	// right BEAM BOTTOM
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(1.0, 0.0); glVertex3f(35, 0, -5);	// Bottom Right
		glTexCoord2d(1.0, 1.0); glVertex3f(35, 0, 0);	// Top Right
		glTexCoord2d(0.0, 0.0); glVertex3f(30, 0, -5);	// Bottom Left
		glTexCoord2d(0.0, 1.0); glVertex3f(30, 0, 0);	// Top Left

	glEnd();		

	// right BEAM TOP
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.0, 1.0); glVertex3f(25, 39, -5);	// Top Left
		glTexCoord2d(0.0, 0.0); glVertex3f(25, 39, 0);	// Bottom Left
		glTexCoord2d(1.0, 1.0); glVertex3f(30, 39, -5);	// Top Right
		glTexCoord2d(1.0, 0.0); glVertex3f(30, 39, 0);	// Bottom Right

	glEnd();
			
	// =======================================================
	/* =================== LINK BEAMSIDES (TOP-LINK)==========*/
	// =======================================================
	
	// Link BEAM FRONT
	glBegin(GL_TRIANGLES);

	
	glColor3f(0.3f, 0.3f, 0.3f);

		glTexCoord2d(1.0, 1.0); glVertex3f(11, 38, -0.5);	// Top Left
		glTexCoord2d(0.0, 1.0); glVertex3f(10, 30, -0.5);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(26, 38, -0.5);	// Top Right

		glTexCoord2d(0.0, 1.0); glVertex3f(10, 30, -0.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(27, 30, -0.5);	// Bottom Right
		glTexCoord2d(1.0, 0.0); glVertex3f(26, 38, -0.5);	// Top Right
	
	glEnd();
	
	// Link BEAM BACK
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(1.0, 1.0); glVertex3f(11, 38, -4.5);	// Top Left
		glTexCoord2d(1.0, 0.0); glVertex3f(26, 38, -4.5);	// Top Right
		glTexCoord2d(0.0, 1.0); glVertex3f(10, 30, -4.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(27, 30, -4.5);	// Bottom Right

	glEnd();

	// Link BEAM BOTTOM
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(1.0, 0.0); glVertex3f(10, 30, -0.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(10, 30, -4.5);	// Top Left
		glTexCoord2d(1.0, 1.0); glVertex3f(27, 30, -0.5);	// Bottom Right
		glTexCoord2d(0.0, 1.0); glVertex3f(27, 30, -4.5);	// Top Right

	glEnd();

	// Link BEAM TOP
	glBegin(GL_TRIANGLE_STRIP);
	
		glTexCoord2d(1.0, 1.0); glVertex3f(11, 38, -4.5);	// Top Left
		glTexCoord2d(0.0, 1.0); glVertex3f(11, 38, -0.5);	// Bottom Left
		glTexCoord2d(1.0, 0.0); glVertex3f(26, 38, -4.5);	// Top Right
		glTexCoord2d(0.0, 0.0); glVertex3f(26, 38, -0.5);	// Bottom Right

	glEnd();


	// =======================================================
	/* =================== LINK BEAMSIDES (MIDDLE-LINK)=======*/
	// =======================================================
	
	// Link BEAM FRONT
	glBegin(GL_TRIANGLES);


	glColor3f(0.3f, 0.3f, 0.3f);

		glTexCoord2d(0.5, 0.5); glVertex3f(6, 15, -0.5);	// Top Left
		glTexCoord2d(0.0, 0.5); glVertex3f(6, 12, -0.5);	// Bottom Left
		glTexCoord2d(0.5, 0.0); glVertex3f(29, 15, -0.5);	// Top Right

		glTexCoord2d(0.0, 0.5); glVertex3f(6, 12, -0.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(29, 12, -0.5);	// Bottom Right
		glTexCoord2d(0.5, 0.0); glVertex3f(29, 15, -0.5);	// Top Right
		
	glEnd();

	// Link BEAM BACK
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.5, 0.5); glVertex3f(6, 15, -4.5);	// Top Left
		glTexCoord2d(0.5, 0.0); glVertex3f(29, 15, -4.5);	// Top Right
		glTexCoord2d(0.0, 0.5); glVertex3f(6, 12, -4.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(29, 12, -4.5);	// Bottom Right

	glEnd();

	// Link BEAM BOTTOM
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.5, 0.0); glVertex3f(6, 12, -0.5);	// Bottom Left
		glTexCoord2d(0.0, 0.0); glVertex3f(6, 12, -4.5);	// Top Left
		glTexCoord2d(0.5, 0.5); glVertex3f(29, 12, -0.5);	// Bottom Right
		glTexCoord2d(0.0, 0.5); glVertex3f(29, 12, -4.5);	// Top Right

	glEnd();

	// Link BEAM TOP
	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(0.5, 0.5); glVertex3f(6, 15, -4.5);	// Top Left
		glTexCoord2d(0.0, 0.5); glVertex3f(6, 15, -0.5);	// Bottom Left
		glTexCoord2d(0.5, 0.0); glVertex3f(29, 15, -4.5);	// Top Right
		glTexCoord2d(0.0, 0.0); glVertex3f(29, 15, -0.5);	// Bottom Right

	glEnd();

	/*
	==================== END OF WOODEN TEXTURE =======================
	*/
	glDisable(GL_TEXTURE_2D);
	
	

	// Background mixcolor
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

	glPopMatrix();
}

void DrawTrebuchetDynamic()
{
	glPushMatrix();

		// Translate Axle to middle of Link-Beam
		glTranslatef(0.5f, 0.0f, 0.0f);
		glTranslatef(0.0f, 14.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -10.0f);
	
		// ========================================================================
		// ========================== THE AXLE ====================================
		// ========================================================================

		if (toggle.btexture)
		{
			glBindTexture(GL_TEXTURE_2D, textureWood);
			glEnable(GL_TEXTURE_2D);
		}

		// Disable culling to see whole cylinder, independent the way you look at it
		glDisable(GL_CULL_FACE);

		gluQuadricNormals(cylinder, GLU_SMOOTH);
		gluQuadricTexture(cylinder, GL_TRUE);
				
					
		// The Axle Cylinder
		glPushMatrix();
			GLfloat cylinderHeight = 33.0f;
			glRotatef(throwArmBaseRotation + fireRotation, 0.0f, 0.0f, 1.0f);
			gluCylinder(cylinder, 0.5f, 0.5f, cylinderHeight, 8.0f, 8.0f);
		glPopMatrix();
		
		// Disk Front
		glPushMatrix();
			gluQuadricNormals(cylinderTops, GLU_SMOOTH);
			gluQuadricTexture(cylinderTops, GL_TRUE);
			glTranslatef(0.0f, 0.0f, cylinderHeight);
			glRotatef(throwArmBaseRotation + fireRotation, 0.0f, 0.0f, 1.0f);
			gluDisk(cylinderTops, 0.0f, 0.5f, 8.0f, 8.0f);
		glPopMatrix();


		// Disk Back
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 0.0f);
			glRotatef(-(throwArmBaseRotation + fireRotation), 0.0f, 0.0f, 1.0f);
			gluDisk(cylinderTops, 0.0f, 0.5f, 8.0f, 8.0f);
		glPopMatrix();

	glPopMatrix();

	// ========================================================================
	// ========================== THE THROWING BEAM AND WEIGHT ================
	// ========================================================================

	glPushMatrix();
	
		// Translate to middle of Axle
		glTranslatef(0.5f, 0.0f, 0.0f);
		glTranslatef(0.0f, 14.0f, 0.0f);

		glRotatef(throwArmBaseRotation + fireRotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(55.0f, 0.0f, 0.0f);
				
		// ========================================================================
		// ========================== THE WEIGHT ==================================
		// ========================================================================
		glPushMatrix();			
						
			glTranslatef(weightX, weightY - weightPosDelta, 0);
			
			glRotatef(-(throwArmBaseRotation + fireRotation), 0, 0, 1.0f);
			glScalef(15, 18, 15);
			glutSolidCube(1.0f);							

		glPopMatrix();
			
		glScalef(140.0f, 2.0f, 4.0f);
		glutSolidCube(1.0f);

	glPopMatrix();

	/*
	==================== END OF WOODEN TEXTURE =======================
	*/
	glDisable(GL_TEXTURE_2D);
	

	// RE-Enable culling
	glEnable(GL_CULL_FACE);	
}

void DrawGravitySphere()
{
	glPushMatrix();		

	// Translate to middle of Axle
	glTranslatef(0.5f, 0.0f, 0.0f);
	glTranslatef(0.0f, 14.0f, 0.0f);

	// Rotate Sphere with Beam put it at the end of plank and rotate back to origin
	glRotatef(throwArmBaseRotation + sphereRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(125, 0, 0);
	glTranslatef(0, 7.0, 0);
	glTranslatef(-3.0f, 0, 0);	
	glRotatef(-(throwArmBaseRotation + sphereRotation), 0.0f, 0.0f, 1.0f);
			
	// Translate Shooting distance
		
	glTranslatef(	SphereDistanceX, //x
					SphereDistanceY, //y
					0);//z		
		
		
		// =================== X/Y AXIS ON SPHERE ================================
		// ========== For Testingpurposes, outcomment if wanted ==================
		// Draw X/Y- Axis at Sphere Location

		glBegin(GL_LINES); // Red for X-Axis
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(-20, 0, 0);
		glEnd();

		glBegin(GL_LINES); // Green for Y-Axis
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 20, 0);
		glEnd();
		glColor3f(0, 0, 0);
		
		// LIGHT1 for Sphere
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosFromView);
		glLightfv(GL_LIGHT1, GL_AMBIENT, L1_BlackColor);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_WhiteColor);
		glLightfv(GL_LIGHT1, GL_SPECULAR, L1_WhiteColor);

		glDisable(GL_LIGHT0);

		if (toggle.blight1)
		{
			glEnable(GL_LIGHT1);
		}
		
		if (toggle.bblend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
		}

		glColorMaterial(GL_FRONT, GL_SHININESS);
		glutSolidSphere(6, 37, 17);
		
		if (toggle.bblend) glDisable(GL_BLEND);

		
		glDisable(GL_LIGHT1);
		if(toggle.blight0) glEnable(GL_LIGHT0);
		
		glColor4f(1, 1, 1, 0);
		
	glPopMatrix();
	
}

void DrawLandAndSky()
{

	if (toggle.blighting)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
	}	
	
	if (toggle.bfog)
	{
		glDisable(GL_FOG);
	}

	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
		

	// Skybox texture
	if (toggle.btexture)
	{
		glBindTexture(GL_TEXTURE_2D, textureSkyBox);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}


	//=========================================
	// ========== DRAW EARTH-SPHERE =================
	//=========================================

	// Frontsphere will be culled away (you can look from out of the sphere into the scene if wanted
	glCullFace(GL_FRONT);

	const GLdouble radius = 600;

	glPushMatrix();

		glRotatef(90, 1, 0, 0);
		glRotatef(earthRot, 0, 0, 1);
		gluSphere(sphere, radius, 37, 17);
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	//=======================================================
	// ========== DRAW Circle(GrassTerrain) =================
	//=======================================================

	glCullFace(GL_BACK);

	if (toggle.blighting)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	if (toggle.btexture)
	{
		glBindTexture(GL_TEXTURE_2D, textureGrass);
		glEnable(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glBegin(GL_TRIANGLE_FAN);

		const GLfloat TexCenterPoint = 0.5f;
		const GLfloat TexVectorLength = 1;			// can be used if we want to avoid the texture repeat below, in this case comment repeat out and set Length to 0.5f!


		// first vertex of triangle-fan in the center
		glTexCoord2d(TexCenterPoint, TexCenterPoint); glVertex3f(0, -20.f, 0);

		const GLfloat triangleAmount = 20.0f;
		GLfloat x = 0.0f, z = 0.0f;

		for (int i = 0; i <= triangleAmount; i++)
		{
			x = 0 + (radius * sin(i * 2.0f * GL_PI / triangleAmount));		// Value '0' not necessary, this value is the WorldCoordinate for X (would be for Y and Z as well)
			z = 0 + (radius * cos(i * 2.0f * GL_PI / triangleAmount));

			// Get the same CircleCoords in UV-Map 
			// from TexCenterPoint (UV-Map) the same circleratio like the triangleVertex 
			// multiplied with TexVectorLength which is the CircleRadiant inside the UV-Map

			glTexCoord2d(	/*U-Coord*/ TexCenterPoint + sin(i * 2.0f * GL_PI / triangleAmount) * TexVectorLength,
							/*V-Coord*/	TexCenterPoint + cos(i * 2.0f * GL_PI / triangleAmount) * TexVectorLength);

			glVertex3f(x, -20.0f, z);// set next Vertex 
		}

	glEnd();

	glDisable(GL_TEXTURE_2D);
		
	// simulate earth rotation
	earthRot += 0.005;
	if (earthRot >= 360)
	{
		earthRot = 0;
	}

	if (toggle.bfog) glEnable(GL_FOG);
}

void DrawExplosion(int something)
{
	// recursive function to draw cubes every call,
	// each cube gets a reddish color which is randomized
	if (something <= 0) return;
		
		glPushMatrix();

			// draw the cannonball again, just grey
			glColor3f(0.2, 0.2, 0.2);
			glutSolidSphere(6, 37, 17);

			// get a random red value and a random green value
			GLfloat randomExplodeColorRed = (GLfloat)(rand() % 10) / 10 + 0.1;
			GLfloat randomExplodeColorGreen = (GLfloat)(rand() % 10) / 10 + 0.1;

			// green needs to be below the red value so if its greater green is set to zero
			if (randomExplodeColorGreen > randomExplodeColorRed) randomExplodeColorGreen = 0;
			
			glTranslatef(50 , -30 + something, 0);
			
			// random location of explosion particle
			GLfloat randomPositionX = (GLfloat) (rand() % 100);
			GLfloat randomPositionY = (GLfloat) (rand() % 40);			
			
			if (toggle.blighting)	glDisable(GL_LIGHTING);
			
			// translate to the random location
			glTranslatef(-randomPositionX, randomPositionY, 0);
			// set the new random color
			glColor3f(randomExplodeColorRed, randomExplodeColorGreen, 0);			
			// draw the cube (expl. particle)
			glutSolidCube(1.5);						

			if (toggle.blighting)	glEnable(GL_LIGHTING);

		glPopMatrix();	

		// redraw scene
		glutPostRedisplay();	

	DrawExplosion(--something);
	
}

void UglyManakin()
{
	// really sorry for showing this... even though im no artist ;)
	glDisable(GL_LIGHTING);
	glColor3f(0.3f, 0.3f, 0.3f);

	glPushMatrix();
		glTranslatef(startPosManX, -5, startPosManX);
		
		glPushMatrix();
			glRotatef(90, 1, 0, 0);			
			glutSolidSphere(2.0f, 37, 17);	// Head	
		glPopMatrix();
		
		// LEFT ARM
		glPushMatrix();

			glTranslatef(-1, -2, 0);

			glPushMatrix();
			glColor3f(1, 0, 0);
				glutSolidSphere(0.4f, 8, 8); // LeftArmLink
				glRotatef(-90, 0, 1, 0);	
				glRotatef(0.4f*-armangle, 1, 0, 0);
				glutSolidCylinder(0.5f, 4, 8, 8);
				glTranslatef(0, 0, 4);
				glutSolidSphere(0.4f, 8, 8);										
				glRotatef(-armangle*0.8, 1, 0, 0);
				glutSolidCylinder(0.5f, 3.5f, 8, 8);			
		
			glPopMatrix();

		glPopMatrix();

		//// RIGHT ARM		
		glPushMatrix();

			glTranslatef(1, -2, 0);

			glPushMatrix();

				glutSolidSphere(0.4f, 8, 8); // RightArmLink
				glRotatef(90, 0, 1, 0);
				glRotatef(0.4f*-armangle, 1, 0, 0);
				glutSolidCylinder(0.5f, 4, 8, 8);
				glTranslatef(0, 0, 4);
				glutSolidSphere(0.4f, 8, 8);		
				glRotatef(-armangle*0.8, 1, 0, 0);
				glutSolidCylinder(0.5f, 3.5f, 8, 8);

			glPopMatrix();

		glPopMatrix();

		// correct torso
		glPushMatrix();
		glColor3f(0, 0, 0);
			glTranslatef(0, -6, 0);
			glScalef(1.5f, 5.0f, 1.5f);
			glutSolidSphere(1, 8, 8);

		glPopMatrix();

		// LEFT LEG
		glPushMatrix();

			glColor3f(1, 1, 0);
			glTranslatef(-1.0f, -10, 0);
			glRotatef(-15, 0, 0, 1);
			glScalef(1.0f, 5.0f, 0.8f);
			glutSolidSphere(1, 37, 20);

		glPopMatrix();

		// Right LEG
		glPushMatrix();

			glColor3f(1, 1, 0);
			glTranslatef(1.0f, -10, 0);
			glRotatef(15, 0, 0, 1);
			glScalef(1.0f, 5.0f, 0.8f);
			glutSolidSphere(1, 37, 20);

		glPopMatrix();

	glPopMatrix();

	// WINK-ANIMATION CONTROL
	if (winkAnim) armangle++;
	if (breverse) armangle--;
	
	if (armangle >= 110)
	{
		winkAnim = false;
		breverse = true;
	}

	if (breverse && armangle <= 0)
	{
		breverse = false;
		winkAnim = true;
	}
	
	if (toggle.blighting)
	{
		glEnable(GL_LIGHTING);
	}

	glColor3f(1, 1, 1);
}
