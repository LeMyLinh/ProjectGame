#include "IndexOfSpriteSheet.h"


IndexOfSpriteSheet* IndexOfSpriteSheet::instance = nullptr;

IndexOfSpriteSheet::IndexOfSpriteSheet()
{
}


IndexOfSpriteSheet::~IndexOfSpriteSheet()
{
	delete instance;
}

IndexOfSpriteSheet* IndexOfSpriteSheet::getInstance() 
{
	if (instance == nullptr)
		instance = new IndexOfSpriteSheet();

	return instance;
}