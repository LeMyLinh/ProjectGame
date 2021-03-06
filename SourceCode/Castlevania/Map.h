#pragma once
#include "Define.h"
#include "MapInfo.h"
#include "textureManager.h"
#include "graphics.h"


class Map
{
private:
	MapInfo * info;
	TextureManager* texture;
	Graphics* graphics;
	
	bool isContain(RECT rect1, RECT rect2);

public:
	Map();
	~Map();

	bool initialize(Graphics* graphics, TextureManager* texture, MapInfo* info);

	void draw();
	void update(float dt);
	void collision();
};