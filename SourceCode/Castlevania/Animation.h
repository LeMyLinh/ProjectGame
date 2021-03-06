#pragma once
#include "Sprite.h"

class Animation
{
private:
	const int* listFrames;
	int totalFrames;
	int currentFrame;
	int startFrame;
	//int endFrame;
	bool canAnimate;
	float timerAnim;
	float frameDelay;
	bool isloop;
	bool isCompleted;
	Sprite *sprite;
	VECTOR2 origin;

public:
	Animation(Sprite *sprite, const int* list, int totalFrames, float timeFrameDelay, bool loop);
	Animation(Sprite *sprite, const int* list, int totalFrames, float timeFrameDelay);
	Animation(Sprite *sprite, VECTOR2 origin, const int* list, int totalFrames, float timeFrameDelay, bool loop);
	Animation(Sprite *sprite, VECTOR2 origin, const int* list, int totalFrames, float timeFrameDelay);

	~Animation();

	void nextFrame();

	void setValueOfCurrentFrame(int index);
	int getCurrentFrame();
	void update(float dt);

	void start();
	void stop();
	bool isFinished();

	void setTimeFrameDelay(float time);
	float getTimeFrameDelay();
};
