#pragma once
#include <Windows.h>
#include <d3dx9math.h>

//Resource-------------------------------------

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Metroid.rc
//
#define IDI_ICON1                       101

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
//---------------------------------------

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }

#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

// Window
const char CLASS_NAME[] = "Castlevania";
const char GAME_TITLE[] = "Castlevania";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 512;     //32x2x8          // width of game in pixels
const UINT GAME_HEIGHT = 448;    //32x2x7           // height of game in pixels

// Game Manger
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 60.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY = VK_MENU;         // Alt key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key

#define X_KEY 0x58

										 // Source
const char SOURCE_IMAGE[] = "Resouces\\simon.png";//character of game
const char SOURCE_JSON[] = "Resouces\\Simon.json"; //json file of metroid sprite

												 // Ramus
namespace SIMON_BEHAVIOUR
{
	const int front = 7;					//front
	const int jump = 0;						//jump
	const int walking[] = { 2, 3 };		//walking
	const int fighting[] = { 9,10,11 };		//fighting
	const int dieing = 8;					//dieing
}

// Element ID
enum eID {
	SIMON = 0,
};

// Element's status
enum eStatus {
	NORMAL = 0,
	JUMPING = 1,
	WALKING = 2,
	FIGHTING = 3,
	DIEING = 4,
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f