#pragma once

//Define frame's number of a object status
#define FRAME_NUM_SIMON_STAND 1
#define FRAME_NUM_SIMON_DIE 1
#define FRAME_NUM_SIMON_SIT 1
#define FRAME_NUM_SIMON_JUMP 1
#define FRAME_NUM_SIMON_WALKING 4
#define FRAME_NUM_SIMON_FIGHTING 3
#define FRAME_NUM_SIMON_SIT_FIGHT 3
#define FRAME_NUM_SIMON_UP_FIGHT 3
#define FRAME_NUM_SIMON_DOWN_FIGHT 3
#define FRAME_NUM_SIMON_UPSTAIR 2
#define FRAME_NUM_SIMON_DOWNSTAIR 2

class IndexOfSpriteSheet
{
private:
	static IndexOfSpriteSheet* instance;

public:
	IndexOfSpriteSheet();
	~IndexOfSpriteSheet();

	static IndexOfSpriteSheet* getInstance();
	
	//Simon
	const int stand = 1;
	const int jump = 0;
	const int walking[4] = { 1, 2, 3, 2 };
	const int back = 7;
	const int sit = 0;
	const int fighting[3] = { 9,10,11 };
	const int fight_sit[3] = { 15,16,17 };
	const int fight_down_stair[3] = { 12,13,14 };
	const int fight_up_stair[3] = { 18,19,20 };
	const int down_stair[2] = { 4,2 };
	const int up_stair[2] = { 5,2 };
	const int dieing = 8;
	const int beHit[4] = { 21,31,32,33 };
	//Enemy
	//White Skeleton
	const int whiteSkeleton[2] = { 22, 23 };
	const int whiteBone[2] = { 34, 35 };
	const int axeMan[2] = { 24, 25 };
	const int dragonSkullCannon = 26;
	const int hunchback[2] = { 27, 28 };
	const int medusa[2] = { 29, 30 };


};

