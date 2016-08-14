#include "SetupCamera.h"


// ============= GLOBALS ===========================================
GLfloat eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ;
vec3 eyeVector, centerVector, upVector, viewVector;
vec3 u, v, n; // Camera coordcross
GLfloat cameraMatrix[16];
// ============= END OF GLOBALS ====================================

void InitCam(Camera *pCam)
{
	// save params from main.c
	eyeX = pCam->eye.x;
	eyeY = pCam->eye.y;
	eyeZ = pCam->eye.z;
	centerX = pCam->center.x;
	centerY = pCam->center.y;
	centerZ = pCam->center.z;
	upX = pCam->up.x;
	upY = pCam->up.y;
	upZ = pCam->up.z;

	// representive Vectors
	eyeVector = { eyeX, eyeY, eyeZ };
	centerVector = { centerX, centerY, centerZ };
	upVector = { upX, upY, upZ };
	viewVector = eyeVector - centerVector;	// the Vector from eye to center

	// make the Camera CoordSystem
	n = normalize(viewVector);			// get ViewVector with unit Length	(imagine an own Z-Axis)
	u = vec3(cross(upVector, n));		// get a new Vector which is Perpendicular to the Up Coord (here 0,1,0) and n (imagine an own Y-axis)
	u = normalize(u);					// get UpVector with unit Length
	v = vec3(cross(n, u));				// get a new Vector which is Perpendicular to View and Up (imagine a X-Axis)
	

	// refresh CameraMatrix
	SetModelViewMatrix();
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); thats the same without doing the matrix shabadoouu
}

// On cameramove-key is pressed
void UpdateCamTranslation(unsigned char key, GLfloat moveValue)
{
	GLfloat deltaTrans = 1.0f;

	GLfloat deltaX = 0;
	GLfloat	deltaY = 0;
	GLfloat	deltaZ = 0;
	if (key == 'W' || key == 'w')
	{
		deltaY = moveValue * deltaTrans;
	}

	if (key == 'S' || key == 's')
	{
		deltaY = -moveValue * deltaTrans;
	}

	if (key == 'A' || key == 'a')
	{
		deltaX = -moveValue * deltaTrans;
	}

	if (key == 'D' || key == 'd')
	{
		deltaX = moveValue * deltaTrans;
	}

	if (key == 'Q' || key == 'q')
	{
		deltaZ = moveValue * deltaTrans;
	}

	if (key == 'E' || key == 'e')
	{
		deltaZ = -moveValue * deltaTrans;
	}

	eyeVector.x += deltaX * u.x + deltaX * v.x + deltaX * n.x;
	eyeVector.y += deltaY * u.y + deltaY * v.y + deltaY * n.y;
	eyeVector.z += deltaZ * u.z + deltaZ * v.z + deltaZ * n.z;

	// refresh CameraMatrix with new vectors
	SetModelViewMatrix();
}

void SetModelViewMatrix()
{
	// Create CameraMatrix
	/*cameraMatrix = (
	u.x,				v.x,				n.x,				0,
	u.y,				v.y,				n.y,				0,
	u.z,				v.z,				n.z,				0,
	-dot(eyeVector,u), -dot(eyeVector,v), -dot(eyeVector,n),	1.0f);*/
	cameraMatrix[0] = u.x; cameraMatrix[4] = u.y; cameraMatrix[8] = u.z; cameraMatrix[12] = -dot(eyeVector, u);
	cameraMatrix[1] = v.x; cameraMatrix[5] = v.y; cameraMatrix[9] = v.z; cameraMatrix[13] = -dot(eyeVector, v);
	cameraMatrix[2] = n.x; cameraMatrix[6] = n.y; cameraMatrix[10] = n.z; cameraMatrix[14] = -dot(eyeVector, n);
	cameraMatrix[3] = 0.0f; cameraMatrix[7] = 0.0f; cameraMatrix[11] = 0.0f; cameraMatrix[15] = 1.0f;


	glMatrixMode(GL_MODELVIEW);		// Select Modelviewmatrix as current operable
	glLoadMatrixf(cameraMatrix);	// Substitute the cameraMatrix with the actual ModelViewMatrix (First on Stack)
}


// ROTATION



// ZOOM