#include "Animations.h"

#include "SetupCamera.h"
#include "SetupRenderState.h"
#include "RenderScene.h"
#include "main.h"



extern GLfloat fireRotation;
extern GLfloat sphereRotation;
extern GLfloat weightPosDelta;

extern GLfloat SphereDistanceX;
extern GLfloat SphereDistanceY;

GLfloat FlyTime = 0;
GLfloat acceleration = 0;

bool bEndOfThrow = false;
bool bEndOfWeightAnim = false;
bool ShootAnim = false;
bool ShootAnimReverse = false;

bool winkAnim = false;


bool IsShooting()
{
	return ShootAnim;
}

bool IsShootingReverting()
{
	return ShootAnimReverse;
}

bool ShouldCannonballFly()
{
	return bEndOfThrow;
}

void DoThrowAnim(void)
{
	if (!ShootAnim || !bEndOfThrow)
	{	

		// alter beam큦, sphere큦 and weight큦 rotation with increasing steps

		if (fireRotation <= 5)
		{
			fireRotation += 0.6f;
		}

		if (fireRotation > 5 && fireRotation <= 10)
		{
			fireRotation += 0.75f;
		}

		if (fireRotation > 10 && fireRotation <= 15)
		{
			fireRotation += 0.9f;
		}

		if (fireRotation > 15 && fireRotation <= 20)
		{
			fireRotation += 1.05f;
		}

		if (fireRotation > 20)
		{
			fireRotation += 1.2f;
		}

		// ============== I REALLY DONT REMEMBER WHY I DID THIS ==================
		weightPosDelta = fireRotation * 0.02;
		sphereRotation = fireRotation;

		if (fireRotation >= 100)
		{
			ShootAnim = false;
			ShootAnimReverse = true;
			bEndOfThrow = true;
		}


		// for the weight큦 shaking			
		/*int n = 3;
		DoWeightAnim(n);

		ShootAnim = false;
		bEndOfWeightAnim = true;
		winkAnim = false;

		RevertThrowAnim();*/
	}
}


// recursive func for the shaking weight inside the scene
void DoWeightAnim(int nlaps)
{
	if (nlaps <= 0) return;

	// to the right
	if (nlaps % 2 == 0)
	{
		while (weightPosDelta <= nlaps)
		{
			weightPosDelta += 0.1;
			RenderScene();
		}
	}


	// back to the left
	if (nlaps % 2 > 0)
	{
		while (weightPosDelta * 2 > 0)
		{
			weightPosDelta -= 0.2;
			RenderScene();
		}
	}

	DoWeightAnim(--nlaps);
}

void RevertThrowAnim(void)
{
	if (fireRotation > 20)
	{
		fireRotation -= 1.2f;
	}

	if (fireRotation > 15 && fireRotation <= 20)
	{
		fireRotation -= 1.05f;
	}

	if (fireRotation > 10 && fireRotation <= 15)
	{
		fireRotation -= 0.9f;
	}

	if (fireRotation > 5 && fireRotation <= 10)
	{
		fireRotation -= 0.75f;
	}

	if (fireRotation <= 5)
	{
		fireRotation -= 0.6f;
	}	

	if (fireRotation < 1)
	{
		fireRotation = 0;
		ShootAnimReverse = false;		
		bEndOfWeightAnim = false;		
	}
}


void CannonballFly(int milisecs)
{
	FlyTime += milisecs;
	const GLfloat gravityConstant = 1.81 * (FlyTime/100)*(FlyTime/100);	

	const GLfloat sphereDirX = -sin(3 * GL_PI / 4);	// 9 degrees
	const GLfloat sphereDirY = -cos(3 * GL_PI / 4);
	
	acceleration = 4;

	SphereDistanceX = acceleration * FlyTime/10 * sphereDirX;
	SphereDistanceY = acceleration * sphereDirY - gravityConstant;
		
	if (FlyTime > 2000)
	{
		FlyTime = 0;
		bEndOfThrow = false;
		SphereDistanceX = 0;
		SphereDistanceY = 0;
		sphereRotation = fireRotation;
	}		
}