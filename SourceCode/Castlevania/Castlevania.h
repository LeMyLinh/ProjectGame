#pragma once
#include "GameManager.h"
#include "Simon.h"

class Castlevania : public GameManager
{
private:
	Simon * simon;
	TextureManager *textureManager;
	SpriteManager *spriteManager;
public:
	Castlevania();
	~Castlevania();

	void initialize(HWND hwnd);
	void update(float dt);      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

