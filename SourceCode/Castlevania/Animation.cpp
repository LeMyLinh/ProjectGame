#include "Animation.h"


Animation::Animation(Sprite *sprite, const int* list, int totalFrames, float timeFrameDelay, bool loop)
{
	this->sprite = sprite;
	this->listFrames = list;
	this->totalFrames = totalFrames;
	this->currentFrame = -1;
	this->startFrame = 0;
	this->isloop = loop;
	this->isCompleted = false;
	this->frameDelay = timeFrameDelay;
	this->timerAnim = 0;
	this->canAnimate = false;

	////width, height
	//this->sprite->setSpriteWidth(SpriteManager::getInstance()->getSpritesData()[this->listFrames[0]].width);
	//this->sprite->setSpriteHeigth(SpriteManager::getInstance()->getSpritesData()[this->listFrames[0]].height);
}

Animation::Animation(Sprite *sprite, const int * list, int totalFrames, float timeFrameDelay)
{
	this->sprite = sprite;
	this->listFrames = list;
	this->totalFrames = totalFrames;
	this->currentFrame = -1;
	this->startFrame = 0;
	this->frameDelay = timeFrameDelay;
	this->timerAnim = 0;
	this->canAnimate = false;
	this->isCompleted = false;
	this->isloop = true;

	////width, height
	//this->sprite->setSpriteWidth(SpriteManager::getInstance()->getSpritesData()[this->listFrames[0]].width);
	//this->sprite->setSpriteHeigth(SpriteManager::getInstance()->getSpritesData()[this->listFrames[0]].height);
}

Animation::Animation(Sprite *sprite, VECTOR2 origin, const int* list, int totalFrames, float timeFrameDelay, bool loop)
{
	this->sprite = sprite;
	this->listFrames = list;
	this->totalFrames = totalFrames;
	this->currentFrame = -1;
	this->startFrame = 0;
	this->isloop = loop;
	this->isCompleted = false;
	this->frameDelay = timeFrameDelay;
	this->timerAnim = 0;
	this->canAnimate = false;
	this->origin = origin;
}

Animation::Animation(Sprite *sprite, VECTOR2 origin, const int * list, int totalFrames, float timeFrameDelay)
{
	this->sprite = sprite;
	this->listFrames = list;
	this->totalFrames = totalFrames;
	this->currentFrame = -1;
	this->startFrame = 0;
	this->frameDelay = timeFrameDelay;
	this->timerAnim = 0;
	this->canAnimate = false;
	this->isCompleted = false;
	this->isloop = true;
	this->origin = origin;
}

Animation::~Animation()
{
	delete this->sprite;
}

void Animation::nextFrame()
{
	this->setValueOfCurrentFrame(currentFrame + 1);
}

void Animation::setValueOfCurrentFrame(int index)
{
	if (index == currentFrame || totalFrames == 0)
		return;

	currentFrame = index;

	if (currentFrame > totalFrames - 1)
		currentFrame = startFrame;

	// setRect
	//this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[this->listFrames[currentFrame]].rect);
	const SpriteData *data = &(SpriteManager::getInstance()->getSpritesData()[this->listFrames[currentFrame]]);
	this->sprite->setSpriteDataRect(data->rect);
	this->sprite->setSpriteWidth(data->width);
	this->sprite->setSpriteHeigth(data->height);
	this->sprite->setOrigin(this->origin);



	if (!isloop && currentFrame == totalFrames -1)
	{
		this->stop();
	}
}

int Animation::getCurrentFrame()
{
	return currentFrame;
}

void Animation::update(float dt)
{
	if (!canAnimate)
		return;

	timerAnim += dt;
	if (timerAnim > frameDelay)
	{
		if (canAnimate)
			this->nextFrame();

		timerAnim -= frameDelay;
	}
}

void Animation::start()
{
	if (canAnimate == false)
	{
		canAnimate = true;
		isCompleted = false;
	}
}

void Animation::stop()
{
	if (canAnimate == true)
	{
		canAnimate = false;
	}
}

bool Animation::isFinished()
{
	return isCompleted;
}

void Animation::setTimeFrameDelay(float time)
{
	if (this->frameDelay != time)
		this->frameDelay = time;
}

float Animation::getTimeFrameDelay()
{
	return this->frameDelay;
}