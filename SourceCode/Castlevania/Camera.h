#pragma once
#include <d3dx9.h>
#include <d3d9.h>

#define CAM_POS_X 896
#define CAM_POS_Y 778

class Camera
{
private:
	static Camera *instance;

	int             width;
	int             height;

	D3DXVECTOR3     position;

	D3DXVECTOR2 velocity;

	bool canFollowHorizontal;

public:
	static Camera *getInstance();
	
	Camera();
	Camera(int width, int height);
	~Camera();

	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR3 pos);
	void setPosition(D3DXVECTOR2 pos);

	int getWidth();
	int getHeight();

	D3DXVECTOR3 getPosition();
	RECT getBound();

	D3DXVECTOR2 getVelocity();
	void setVelocity(D3DXVECTOR2 vec);

	RECT getActiveArea();

	void update(float dt);

	void setCanFoLLowHorizontal(bool flag);
	bool canFollowHorizon();
};