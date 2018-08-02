#pragma once
#include "GameManager.h"
#include "Simon.h"
#include "Camera.h"
#include "Map.h"
#include "WhiteSkeleton.h"

class Castlevania : public GameManager
{
private:
	static Castlevania* instance;

	TextureManager *textureManager;
	SpriteManager *spriteManager;

	TextureManager *tileset;
	MapInfo * mapInfo;
	Map * mapLevel5;

	Simon * simon;
	
	Camera* camera;

	//Enemy
	WhiteSkeleton *whiteSkeleton;

public:
	Castlevania();
	~Castlevania();

	static Castlevania* getInstance();

	void initialize(HWND hwnd);
	void update(float dt);      // must override pure virtual from Game
	void handleInput(float dt);
	void collisions(float dt);
	void render(); 
	void releaseAll();
	void resetAll();

	HWND getCurrentHWND();
};

