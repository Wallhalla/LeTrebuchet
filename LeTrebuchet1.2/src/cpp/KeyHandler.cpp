#include "KeyHandler.h"
#include "SetupCamera.h"
#include "SetupRenderState.h"

#include "Animations.h"

#include <ctype.h>


unsigned char getKey;
bool ViewParam = false;

extern bool ShootAnim;
extern bool winkAnim;

// what needs to be done when a key boolean is true...
void KeyOperations(void)
{
	if (getKey != 0)
	{
		bool IsMovementInput = false;
		switch (getKey)
		{
		case 'W': IsMovementInput = true; break;
		case 'w': IsMovementInput = true; break;
		case 'S': IsMovementInput = true; break;
		case 's': IsMovementInput = true; break;
		case 'A': IsMovementInput = true; break;
		case 'a': IsMovementInput = true; break;
		case 'D': IsMovementInput = true; break;
		case 'd': IsMovementInput = true; break;
		case 'Q': IsMovementInput = true; break;
		case 'q': IsMovementInput = true; break;
		case 'E': IsMovementInput = true; break;
		case 'e': IsMovementInput = true; break;
		}//switch

		if (IsMovementInput)
		{
			UpdateCamTranslation(getKey, 2.0f);
		}
		else
		{
			// toggle camera viewmode
			if (getKey == 'o')
			{
				ViewParam = !ViewParam;
				SetViewMode(ViewParam);
			}

			// let the ugly man start/stop wink
			if (getKey == 'z')
			{
				winkAnim = !winkAnim;
			}

			// Play throw animation -> rotate Beam/Sphere and Weight
			if (getKey == 'm')
			{
				ShootAnim = true;
				winkAnim = true;
			}
		}// else
	}// getkey
}//KeyOperations

// no specials defined
void SpecialKeyOperations(void)
{}


// On Key Enter set its represented boolean true
void KeyPressed(unsigned char key, int mouseX, int mouseY)
{
	getKey = key;	
	KeyOperations();
}


// set represented boolean false
void KeyReleased(unsigned char key, int mouseX, int mouseY)
{
	getKey = 0;	
}


// special key pressed = true
void SpecialKeyPressed(int sKey, int mouseX, int mouseY)
{
	SpecialKeyOperations();
}


// special key pressed = false
void SpecialKeyReleased(int sKey, int mouseX, int mouseY)
{
	
}

